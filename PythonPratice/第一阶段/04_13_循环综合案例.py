"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	04_13_循环综合案例.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.06.11
描  述: 循环综合案例
备  注:
修改记录:

  1.  日期: 2025.06.11
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

money = 10000

for i in range(1,21):
    import random
    performance = random.randint(1,10)

    if performance < 5:
        print(f"员工{i}绩效不满足要求，不发放工资")
        continue

    if money <= 0:
        print(f"工资发放完毕，当前余额为{money}")
        break

    money -= 1000
    print(f"员工{i}绩效满足要求，发放工资，当前余额为{money}")


