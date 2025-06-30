"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	str_util.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.06.30
描  述: 字符串处理相关
备  注:
修改记录:

  1.  日期: 2025.06.30
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

def str_reverse(s):
    """
    反转字符串
    :param s:
    :return:
    """
    return s[::-1]

def substr(s, x, y):
    """
    截取字符串
    :param s:
    :param x:
    :param y:
    :return:
    """
    return s[x:y]
