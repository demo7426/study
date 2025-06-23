"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	07_03_函数作为参数传递.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.06.23
描  述: 函数作为参数传递
备  注:
修改记录:

  1.  日期: 2025.06.23
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

def test_func(calculate):
    result = calculate(1, 2)
    print(f"calculate参数的类型是：{type(calculate)}")
    print(f"计算结果为：{result}")

def add(a, b):
    return a + b

test_func(add)
