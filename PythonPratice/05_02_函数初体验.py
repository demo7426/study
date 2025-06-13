"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	05_02_函数初体验.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.06.13
描  述: 函数初体验
备  注:
修改记录:

  1.  日期: 2025.06.13
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""


def my_len(data):
    count = 0
    for i in data:
        count += 1
    print(f"长度为:{count}")


name = "itheima"

my_len(name)
my_len("itcast")
