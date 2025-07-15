"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	09_数据计算_distinct方法.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.07.15
描  述: 数据计算_distinct方法
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
rdd = sc.parallelize([1, 2, 3, 1, 2])

# distinct 去重
rdd = rdd.distinct()

# 查看rdd内容
print(rdd.collect())

sc.stop()




