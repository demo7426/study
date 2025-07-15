"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	10_数据计算_sortBy方法.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.07.15
描  述: 数据计算_sortBy方法
备  注:
修改记录:

  1.  日期: 2025.07.15
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
rdd = sc.textFile("./orders.txt")

rdd = rdd.flatMap(lambda x: x.split("|"))


list_city_money: list = []                  # 用于保存(城市, 销售额)
list_category: list = []                    # 用于保存(商品类别)
list_category_city: list = []               # 用于保存(商品类别, 城市)
for lines in rdd.collect():
    json_data = json.loads(lines)

    list_city_money.append((json_data["areaName"], int(json_data["money"])))
    list_category.append(json_data["category"])
    list_category_city.append((json_data["category"], json_data["areaName"]))

# 各个城市销售额排名，从大到小
rdd_00 = sc.parallelize(list_city_money)
rdd_00 = rdd_00.reduceByKey(lambda x, y: x + y)                             # 聚合
rdd_00 = rdd_00.sortBy(lambda x: x[1], ascending=False, numPartitions=1)    # 排序
result_00 = rdd_00.collect()

# 全部城市，有哪些商品类别在售卖
rdd_01 = sc.parallelize(list_category)
rdd_01 = rdd_01.distinct()
result_01 = rdd_01.collect()

# 北京，有哪些商品类别在售卖
rdd_02 = sc.parallelize(list_category_city)
rdd_02 = rdd_02.filter(lambda x: x[1] == "北京")
rdd_02 = rdd_02.map(lambda x: (x[0])).distinct()
result_02 = rdd_02.collect()

print(result_00)
print(result_01)
print(result_02)

sc.stop()

