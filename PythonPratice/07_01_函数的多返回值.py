"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	07_01_函数的多返回值.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.06.23
描  述: 函数的多返回值
备  注:
修改记录:

  1.  日期: 2025.06.23
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

def test_func():
    return 1, "hello", False

x, y, z = test_func()

print(f"{x}, {y}, {z}")

