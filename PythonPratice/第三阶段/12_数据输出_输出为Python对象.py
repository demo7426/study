"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	12_数据输出_输出为Python对象.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.07.16
描  述: 数据输出_输出为Python对象
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

conf = SparkConf().setMaster("local[*]").setAppName("test_spark_app")
sc = SparkContext(conf=conf)

# 通过parallelize方法，将python对象加载到spark内，成为rdd对象
rdd = sc.parallelize([1, 2, 3, 4, 5])

# collect算子，输出rdd为list对象
print(rdd.collect())

# reduce算子，对rdd进行两两聚合
print(rdd.reduce(lambda a, b: a + b))

# take算子，取出rdd前n个元素，组成list返回
print(rdd.take(3))

# count，统计rdd内有多少条数据，返回值为数字
print(rdd.count())

sc.stop()

