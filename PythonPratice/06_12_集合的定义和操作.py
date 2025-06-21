"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	06_12_集合的定义和操作.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.06.21
描  述: 集合的定义和操作
备  注:
修改记录:

  1.  日期: 2025.06.21
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

my_set = {"itheima", 10, False, 10, "itheima"}
print(my_set)

#集合内添加一个元素
my_set.add("itcast")
print(my_set)

#移除集合内指定的元素
my_set.remove("itheima")
print(my_set)

#从集合中随机取出一个元素
element = my_set.pop()
print(f"取出的元素是：{element}, 集合为：{my_set}")

#将集合清空
my_set.clear()

#得到一个元素集合00有，而集合01没有的新集合
my_set00 = {1, 2, 3}
my_set01 = {2, 4, 5}
print(f"{my_set00.difference(my_set01)}")

#更新一个元素集合00有，而集合01没有
my_set00.difference_update(my_set01)
print(f"{my_set00}")

#取并集
my_set00 = {1, 2, 3}
my_set01 = {2, 4, 5}
print(f"{my_set00.union(my_set01)}")

#统计集合内部元素数量
print(f"集合内部元素数量：{len(my_set00)}个")
