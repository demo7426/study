"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	07_数据计算_练习案例1.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.07.15
描  述: 数据计算_练习案例1
备  注:
修改记录:

  1.  日期: 2025.07.15
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

from pyspark import SparkConf, SparkContext

import os

os.environ['PYSPARK_PYTHON'] = r'C:\Users\25758\AppData\Local\Programs\Python\Python38\python.exe'

conf = SparkConf().setMaster("local[*]").setAppName("test_spark_app")
sc = SparkContext(conf=conf)

# 通过parallelize方法，将python对象加载到spark内，成为rdd对象
rdd = sc.textFile("./hello.txt")

rdd = rdd.flatMap(lambda line: line.split(" "))
rdd = rdd.map(lambda word: (word, 1))
rdd = rdd.reduceByKey(lambda x, y: x + y)     # reduceByKey中的回调函数，只负责聚合，不理会分组

# 查看rdd内容
print(rdd.collect())

sc.stop()




