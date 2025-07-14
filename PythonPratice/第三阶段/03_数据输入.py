"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	03_数据输入.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.07.14
描  述: pyspark数据输入
备  注:
修改记录:

  1.  日期: 2025.07.14
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

from pyspark import SparkConf, SparkContext

import os

os.environ['PYSPARK_PYTHON'] = r'C:\Users\Lenovo\AppData\Local\Programs\Python\Python38\python.exe'

conf = SparkConf().setMaster("local[*]").setAppName("test_spark_app")
sc = SparkContext(conf=conf)

# 通过parallelize方法，将python对象加载到spark内，成为rdd对象
rdd_00 = sc.parallelize([1, 2, 3, 4, 5])
rdd_01 = sc.parallelize((1, 2, 3, 4, 5))
rdd_02 = sc.parallelize('abcdefg')
rdd_03 = sc.parallelize({1, 2, 3, 4, 5})
rdd_04 = sc.parallelize({'key1': 'value1', 'key2': 'value2'})

# 查看rdd内容
print(rdd_00.collect())
print(rdd_01.collect())
print(rdd_02.collect())
print(rdd_03.collect())
print(rdd_04.collect())

# 通过textFile方法
rdd_05 = sc.textFile('./hello.txt')

print(rdd_05.collect())

sc.stop()




