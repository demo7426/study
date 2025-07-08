"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	07_02_函数的多种参数使用形式.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.06.23
描  述: 函数的多种参数使用形式
备  注:
修改记录:

  1.  日期: 2025.06.23
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

def user_info(name, age, gender):
    print(f"您的名字是：{name}，年龄是：{age}，性别是：{gender}")

#位置参数，默认使用形式
user_info("小明", 20, "男")

#关键字参数
user_info(name="小王", age=11, gender="女")
user_info(age=18, gender="男", name="小明")
user_info("小红", gender="女", age=30)

#缺省参数（默认值）
def user_default_info(name, age, gender="男"):
    print(f"您的名字是：{name}，年龄是：{age}，性别是：{gender}")

user_default_info("小许", age=13)

#不定长-位置不定长，*号
#不定长定义的形式参数会作为元组存在，接收不定长数量的参数传入
def user_info(*args):
    print(f"args参数的类型是：{type(args)}，内容是：{args}")

user_info(1, 2, 3, "小明", "男孩")

#不定长-关键字不定长，**号
def user_info(**kwargs):
    print(f"kwargs参数的类型是：{type(kwargs)}，内容是：{kwargs}")

user_info(name="小王", age=28, gender="男", addr="北京")