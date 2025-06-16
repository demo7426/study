"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	05_11_函数综合案例.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.06.14
描  述: 函数综合案例
备  注:
修改记录:

  1.  日期: 2025.06.14
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

name = None             #姓名
balance = 5000000       #余额

name = input("请输入您的姓名：")

def query_money(show_header):
    """
    查询余额
    :param show_header:
    :return:
    """
    if show_header:
        print("------------余额------------")
    print(f"{name}，您好，您的余额剩余：{balance}元")


def save_money(money):
    """
    存款
    :param money:
    :return:
    """
    global balance
    balance += money
    print(f"{name}，您好，您存款{money}元成功")
    query_money(False)


def withdraw_money(money):
    """
    取款
    :param money:
    :return:
    """
    global balance
    balance -= money
    print(f"{name}，您好，您取款{money}元成功")
    query_money(False)


def main_menu():
    """
    主菜单
    :return:
    """
    print(f"{name}：您好，欢迎来到黑马银行ATM，请选择操作")
    print("查询余额\t [输入1]")
    print("存款\t\t [输入2]")
    print("取款\t\t [输入3]")
    print("退出\t\t [输入4]")
    return int(input("请输入您的选择："))


while True:
    key_input_num = main_menu()

    if key_input_num == 1:
        query_money(True)
        continue
    elif key_input_num == 2:
        money = int(input("您想要存多少钱，请输入："))
        save_money(money)
        continue
    elif key_input_num == 3:
        money = int(input("您想要存取多少钱，请输入："))
        withdraw_money(money)
        continue
    else:
        print("程序退出")
        break





