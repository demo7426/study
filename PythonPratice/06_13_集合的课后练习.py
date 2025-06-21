"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	06_13_集合的课后练习.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.06.21
描  述: 集合的课后练习
备  注:
修改记录:

  1.  日期: 2025.06.21
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

my_list = ["黑马程序员", "传智播客", "黑马程序员", "传智播客", "itheima", "itcast", "itheima", "itcast", "best"]

my_set = set()
for item in my_list:
    my_set.add(item)

print(my_set)

