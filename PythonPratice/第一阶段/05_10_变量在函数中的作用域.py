"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	05_10_变量在函数中的作用域.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.06.14
描  述: 变量在函数中的作用域
备  注:
修改记录:

  1.  日期: 2025.06.14
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

num = 10


def func_a():
    print(f"func_a:{num}")


def func_b():
    global num                  #显示指出num为全局变量num
    num = 20
    print(f"func_b:{num}")


func_a()
func_b()
print(f"{num}")
