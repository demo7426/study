"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	02_装饰器.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.07.17
描  述: 装饰器
备  注:
修改记录:

  1.  日期: 2025.07.17
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

# def outer(func):
#
#     def inner():
#         print("准备睡觉")
#         func()
#         print("起床了")
#
#     return inner
#
# def sleep():
#     import time
#     import random
#
#     print("睡眠中......")
#     time.sleep(random.randint(1, 5))

def outer(func):

    def inner():
        print("准备睡觉")
        func()
        print("起床了")

    return inner

@outer          # 装饰器语法糖，自动将sleep函数注册到outer中，等同于上面注释后的写法
def sleep():
    import time
    import random

    print("睡眠中......")
    time.sleep(random.randint(1, 5))

sleep()


