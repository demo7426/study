"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	14_综合案例.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.07.16
描  述: 综合案例
备  注:
修改记录:

  1.  日期: 2025.07.16
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

import json
from pyspark import SparkConf, SparkContext

import os

os.environ['PYSPARK_PYTHON'] = r'C:\Users\25758\AppData\Local\Programs\Python\Python38\python.exe'
os.environ['HADOOP_HOME'] = r'C:\hadoop-3.0.0'

conf = SparkConf().setMaster("local[*]").setAppName("test_spark_app")
conf.set("spark.default.parallelism", 1)        # 设置分区数量

sc = SparkContext(conf=conf)

rdd = sc.textFile("./search_log.txt")

# 热门搜索时间段（小时精度）Top3
time_period_list: list = (rdd.map(lambda line: line[:2:1]).                             # 取出小时
       map(lambda line: (line, 1)).                                                     # 转换为元组
       reduceByKey(lambda a, b: a + b).                                                 # 分组聚合
       sortBy(lambda x: x[1], ascending=False, numPartitions=1).                        # 排序
       take(3))                                                                         # 取出前3数据

# 热门搜索词Top3
key_word_list: list = ((rdd.map(lambda line: line.split("\t")).                         # 切分数据
       map(lambda line: line[2]).                                                       # 取出关键字
       map(lambda line: (line, 1)).                                                     # 转换为元组
       reduceByKey(lambda a, b: a + b).                                                 # 分组聚合
       sortBy(lambda x: x[1], ascending=False, numPartitions=1)).                       # 排序
       take(3))                                                                         # 取出前3数据

# 统计黑马程序员关键字在哪个时段被搜索最多
hei_ma_time_period_list: list = ((rdd.map(lambda line: line.split("\t")).               # 切分数据
       map(lambda line: (line[0][:2:1], line[2])).                                      # 取出(时间段, 关键字)
       filter(lambda x: x[1] == "黑马程序员").                                            # 过滤
       map(lambda line: (line, 1)).                                                     # 转换为元组
       reduceByKey(lambda a, b: a + b).                                                 # 分组聚合
       sortBy(lambda x: x[1], ascending=False, numPartitions=1)).                       # 排序
       take(3))                                                                         # 取出前3数据

# 将数据转换为JSON格式，写出为文件
(rdd.map(lambda line: line.split("\t")).
 map(lambda x: {"time": x[0], "user_id": x[1], "key_word": x[2], "rank1": x[3], "rank2": x[4], "url": x[5]}).
 saveAsTextFile("./search_log_json"))

print(time_period_list)
print(key_word_list)
print(hei_ma_time_period_list)

sc.stop()

