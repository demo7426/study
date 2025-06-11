"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	03_09_判断语句综合案例.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.06.11
描  述: 判断语句综合案例
备  注:
修改记录:

  1.  日期: 2025.06.11
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

import random

num = random.randint(1, 10)

guess_num = int(input("请输入第一次猜测的数字: "))

if guess_num == num:
    print("恭喜你第一次就猜对了")
else:
    if guess_num > num:
        print("猜测的数字大了")
    elif guess_num < num:
        print("猜测的数字小了")

    guess_num = int(input("请输入第二次猜测的数字: "))

    if guess_num == num:
        print("恭喜你猜对了")
    else:
        if guess_num > num:
            print("猜测的数字大了")
        elif guess_num < num:
            print("猜测的数字小了")

        guess_num = int(input("请输入第三次猜测的数字: "))

        if guess_num == num:
            print("恭喜你最后一次猜对了")
        else:
            print("Sorry, 三次均没有猜对")