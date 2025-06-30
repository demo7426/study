"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	file_util.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.06.30
描  述: 文件处理相关
备  注:
修改记录:

  1.  日期: 2025.06.30
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

def print_file_info(file_name):
    """
    打印文件全部内容
    :param file_name:
    :return:
    """
    try:
        f = open(file_name, 'r', encoding='utf-8')
        print(f.read())
    except Exception as e:
        print(e)
    else:
        f.close()

def append_to_file(file_name, data):
    """
    向文件内部追加数据
    :param file_name:
    :param data:
    :return:
    """
    f = open(file_name, 'a', encoding='utf-8')
    f.write(data)
    f.close()