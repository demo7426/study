"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	06_18_数据容器的通用操作.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.06.22
描  述: 数据容器的通用操作
备  注:
修改记录:

  1.  日期: 2025.06.22
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

#演示数据容器的通用功能
my_list = [1, 2, 3, 4, 5]
my_tuple = (1, 2, 3, 4, 5)
my_str = "abcdefg"
my_set = {1, 2, 3, 4, 5}
my_dict = {"key1": 1, "key2": 2, "key3": 3}

#len元素个数
print(f"列表  元素个数有：{len(my_list)}")
print(f"元组  元素个数有：{len(my_tuple)}")
print(f"字符串元素个数有：{len(my_str)}")
print(f"集合  元素个数有：{len(my_set)}")
print(f"字典  元素个数有：{len(my_dict)}")

#max最大元素
print(f"列表  最大元素为：{max(my_list)}")
print(f"元组  最大元素为：{max(my_tuple)}")
print(f"字符串最大元素为：{max(my_str)}")
print(f"集合  最大元素为：{max(my_set)}")
print(f"字典  最大元素为：{max(my_dict)}")

#min最小元素
print(f"列表  最小元素为：{min(my_list)}")
print(f"元组  最小元素为：{min(my_tuple)}")
print(f"字符串最小元素为：{min(my_str)}")
print(f"集合  最小元素为：{min(my_set)}")
print(f"字典  最小元素为：{min(my_dict)}")

#类型转换：容器转列表
print(f"列表 转列表的结果是：{list(my_list)}")
print(f"元组 转列表的结果是：{list(my_tuple)}")
print(f"字符串转列表的结果是：{list(my_str)}")
print(f"集合 转列表的结果是：{list(my_set)}")
print(f"字典 转列表的结果是：{list(my_dict)}")

#类型转换：容器转元组
print(f"列表 转元组的结果是：{tuple(my_list)}")
print(f"元组 转元组的结果是：{tuple(my_tuple)}")
print(f"字符串转元组的结果是：{tuple(my_str)}")
print(f"集合 转元组的结果是：{tuple(my_set)}")
print(f"字典 转元组的结果是：{tuple(my_dict)}")

#类型转换：容器转字符串
print(f"列表 转字符串的结果是：{str(my_list)}")
print(f"元组 转字符串的结果是：{str(my_tuple)}")
print(f"字符串转字符串的结果是：{str(my_str)}")
print(f"集合 转字符串的结果是：{str(my_set)}")
print(f"字典 转字符串的结果是：{str(my_dict)}")

#类型转换：容器转集合
print(f"列表 转集合的结果是：{set(my_list)}")
print(f"元组 转集合的结果是：{set(my_tuple)}")
print(f"字符串转集合的结果是：{set(my_str)}")
print(f"集合 转集合的结果是：{set(my_set)}")
print(f"字典 转集合串的结果是：{set(my_dict)}")

#进行容器排序
my_list = [2, 5, 4, 3, 1]
my_tuple = (2, 5, 4, 3, 1)
my_str = "deacbgf"
my_set = {2, 5, 4, 3, 1}
my_dict = {"key2": 1, "key3": 2, "key1": 3}

print(f"列表 对象的排序结果：{sorted(my_list)}")
print(f"元组 对象的排序结果：{sorted(my_tuple)}")
print(f"字符串对象的排序结果：{sorted(my_str)}")
print(f"集合 对象的排序结果：{sorted(my_set)}")
print(f"字典 对象的排序结果：{sorted(my_dict)}")

print(f"列表 对象的倒序结果：{sorted(my_list, reverse=True)}")
print(f"元组 对象的倒序结果：{sorted(my_tuple, reverse=True)}")
print(f"字符串对象的倒序结果：{sorted(my_str, reverse=True)}")
print(f"集合 对象的倒序结果：{sorted(my_set, reverse=True)}")
print(f"字典 对象的倒序结果：{sorted(my_dict, reverse=True)}")



