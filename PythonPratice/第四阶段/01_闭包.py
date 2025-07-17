"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	01_闭包.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.07.17
描  述: 闭包
备  注:
修改记录:

  1.  日期: 2025.07.17
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

def account_create(init_amount: int = 0):

    def atm(num: int, deposit: bool = True):

        nonlocal init_amount

        if deposit:
            init_amount += num
            print(f"存款+{num}，账户余额{init_amount}")
        else:
            init_amount -= num
            print(f"存款-{num}，账户余额{init_amount}")

    return atm

atm = account_create(1000)

atm(200)
atm(100, False)
