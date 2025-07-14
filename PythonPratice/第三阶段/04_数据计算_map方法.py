"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	04_数据计算_map方法.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.07.15
描  述: 数据计算_map方法
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

os.environ['PYSPARK_PYTHON'] = r'C:\Users\Lenovo\AppData\Local\Programs\Python\Python38\python.exe'

conf = SparkConf().setMaster("local[*]").setAppName("test_spark_app")
sc = SparkContext(conf=conf)

# 通过parallelize方法，将python对象加载到spark内，成为rdd对象
rdd_00 = sc.parallelize([1, 2, 3, 4, 5])

def func(x):
    """
    (T) -> U 输入一个类型，返回另外一个类型
    :param x:
    :return:
    """
    return x + 2

rdd_00 = rdd_00.map(func).map(lambda x: x * 10)

# 查看rdd内容
print(rdd_00.collect())

sc.stop()




