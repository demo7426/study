"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	06_05_列表的常用操作课后练习讲解.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.06.17
描  述: 列表的常用操作课后练习讲解
备  注:
修改记录:

  1.  日期: 2025.06.17
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

my_list = [21, 25, 21, 23, 22, 20]

my_list.append(31)
print(my_list)

my_list.extend([29, 33, 30])
print(my_list)

print(my_list[0])

print(my_list[-1])

print(f"元素31的下标位置为{my_list.index(31)}")