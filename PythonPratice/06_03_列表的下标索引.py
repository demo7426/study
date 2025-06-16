"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	06_03_列表的下标索引.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.06.16
描  述: 表的下标索引
备  注:
修改记录:

  1.  日期: 2025.06.16
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

my_list = ["itcast", "itheima", "python"]

print(my_list[0])
print(my_list[1])
print(my_list[2])

print()
print(my_list[-1])
print(my_list[-2])
print(my_list[-3])

my_list = [["itcast", 2, True], [False, "itheima", 6]]
print()
print(my_list[1][1])
