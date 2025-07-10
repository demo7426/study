"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	01_11_函数和方法类型注解.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.07.10
描  述: 函数和方法类型注解
备  注:
修改记录:

  1.  日期: 2025.07.10
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

#对形参进行类型注解
def add(x: int, y: int):
    return x + y

#对返回值进行类型注解
def func(data: list) -> list:
    return data

print(func([1, 2, 3]))


