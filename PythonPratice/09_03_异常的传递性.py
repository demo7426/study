"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	09_03_异常的传递性.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.06.30
描  述: 异常的传递性
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
    异常的传递性
    :return:
    """
    f = open("09_02_异常的捕获.txt", "r", encoding="utf-8")


if __name__ == '__main__':
    try:
        test_00()
    except Exception as e:
        print(e)



