"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	06_06_列表的循环遍历.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.06.17
描  述: 列表的循环遍历
备  注:
修改记录:

  1.  日期: 2025.06.17
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

my_list = [21, 25, 21, 23, 22, 20]

num = 0
while num < len(my_list):
    print(my_list[num])
    num += 1

print()

for num in my_list:
    print(num)