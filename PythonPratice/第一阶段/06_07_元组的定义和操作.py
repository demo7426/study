"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	06_07_元组的定义和操作.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.06.18
描  述: 元组的定义和操作
备  注:
修改记录:

  1.  日期: 2025.06.18
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

#定义元组
my_tuple = ("itcast", 1, False)
my_tuple2 = ()
my_tuple3 = tuple()

print(f"{my_tuple}的类型为{type(my_tuple)}")
print(f"{my_tuple2}的类型为{type(my_tuple2)}")
print(f"{my_tuple3}的类型为{type(my_tuple3)}")

#定义单个元素
my_tuple4 = ("hello", )
print(f"{my_tuple4}的类型为{type(my_tuple4)}")

#元组的嵌套
my_tuple5 = ((1, 2, 3), (4, 5, 6))
print(f"{my_tuple5}的类型为{type(my_tuple5)}")

#下标索引去取出内容
print(f"{my_tuple5[1][2]}")

#元组的操作：index查找方法
index = my_tuple.index(False)
print(f"index = {index}")

#元组的操作：count统计方法
my_tuple = ("python", "java", "python", "c++")
print(f"python的数量为{my_tuple.count("python")}个")

#元组的操作：len函数统计元组元素数量
len = len(my_tuple)
print(f"my_tuple的元素数量为{len}个")

#元素的遍历：while
i = 0
while i < len:
    print(my_tuple[i])
    i += 1

#元素的遍历：for
for element in my_tuple:
    print(element)