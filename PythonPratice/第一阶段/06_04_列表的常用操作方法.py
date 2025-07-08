"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	06_04_列表的常用操作方法.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.06.17
描  述: 列表的常用操作方法
备  注:
修改记录:

  1.  日期: 2025.06.17
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

my_list = ["itcast", "itheima", "python"]

#1、查找列表元素
index = my_list.index("itheima")
print(f"itheima索引为：{index}")

# index = my_list.index("itheima00")
# print(f"itheima00索引为：{index}")

#2、修改特定下表索引的值
my_list[0] = "传智教育"
print(my_list)

#3、在指定的下标位置插入新元素
my_list.insert(1, "best")
print(my_list)

#4、在列表的尾部追加单个元素
my_list.append("追加元素00")
print(my_list)

#5、在列表的尾部追加多个元素
my_list.extend(["追加元素01", "追加元素02", "追加元素03"])
print(my_list)

#6、删除指定下表索引的元素（两种方式）
#6.1、方式1：del 列表[下标]
del my_list[0]
print(my_list)

#6.2、方式2：del 列表.pop(下标)
my_list.pop(1)
print(my_list)

#7、删除某元素在列表中的第一个匹配项
my_list = ["python", "itheima", "python"]
my_list.remove("python")
print(my_list)

#8、清空列表
my_list.clear()
print(my_list)

#9、统计列表内某元素的数量
my_list = ["python", "itheima", "python"]
print(f"python元素的数量为{my_list.count("python")}个")

#10、统计列表中全部元素的数量
print(f"列表的元素总数量为{len(my_list)}个")
