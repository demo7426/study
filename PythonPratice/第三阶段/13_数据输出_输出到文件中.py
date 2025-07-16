"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	13_数据输出_输出到文件中.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.07.16
描  述: 数据输出_输出到文件中
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
# conf.set("spark.default.parallelism", 1)        # 设置分区数量

sc = SparkContext(conf=conf)

# 通过parallelize方法，将python对象加载到spark内，成为rdd对象
rdd_00 = sc.parallelize([1, 2, 3, 4, 5], numSlices=1)                                   # numSlices设置分区数量
rdd_01 = sc.parallelize([("hello", 3), ("Spark", 2), ("caculate", 1)], numSlices=1)     # numSlices设置分区数量
rdd_02 = sc.parallelize([[1, 2, 3], [4, 5, 6], [7, 8, 9]], numSlices=2)                 # numSlices设置分区数量

rdd_00.saveAsTextFile("./output_00")
rdd_01.saveAsTextFile("./output_01")
rdd_02.saveAsTextFile("./output_02")

sc.stop()

