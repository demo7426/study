"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	09_02_异常的捕获.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.06.30
描  述: 异常的捕获
备  注:
修改记录:

  1.  日期: 2025.06.30
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

def test_00():
    """
    捕获常规异常
    :return:
    """
    try:
        f = open("09_02_异常的捕获.txt", "r", encoding="utf-8")
    except:
        print("捕获常规异常")


def test_01():
    """
    捕获指定异常
    :return:
    """
    try:
        f = open("09_02_异常的捕获.txt", "r", encoding="utf-8")
    except FileNotFoundError as e:
        print(f"捕获指定异常：{e}")

def test_02():
    """
    捕获指定的多个异常
    :return:
    """
    try:
        print(num)
    except (NameError, FileNotFoundError) as e:
        print(f"捕获指定的多个异常：{e}")

def test_03():
    """
    捕获全部异常
    :return:
    """
    try:
        print(num)
    except Exception as e:
        print(f"捕获全部异常：{e}")

def test_04():
    """
    异常的else和finally语法
    :return:
    """
    try:
        print()
    except Exception as e:
        print(f"捕获全部异常：{e}")
    else:
        print("没有出现异常，执行else分支")
    finally:
        print("执行finally分支")

if __name__ == '__main__':
    test_00()
    test_01()
    test_02()
    test_03()
    test_04()


