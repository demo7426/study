"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	08_03_文件读取的课后练习讲解.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.06.29
描  述: 文件读取的课后练习讲解
备  注:
修改记录:

  1.  日期: 2025.06.29
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

def get_file_word_number(file_name, key_word):
    """
    读取全部内容，通过字符串count方法统计关键字出现的次数
    :param file_name:文件名称
    :param key_word:关键字
    :return:关键字在文件内容中出现次数
    """
    f = open(file_name, "r", encoding='utf-8')

    file_content = f.read()

    f.close()
    return file_content.count(key_word)

def get_file_word_number_02(file_name, key_word):
    """
    读取一行一行的内容，逐一匹配
    :param file_name:文件名称
    :param key_word:关键字
    :return:关键字在文件内容中出现次数
    """
    word_count = 0
    f = open(file_name, "r", encoding='utf-8')

    for line in f:
        line = line.strip()     #去掉开头和结尾的空格和换行符
        words = line.split(" ")

        for word in words:
            if word == key_word:
                word_count += 1

    f.close()

    return word_count

key_word = "itheima"

word_num = get_file_word_number("./08_03_文件读取的课后练习讲解.txt", key_word)
print(f"关键字{key_word}在文件内部的数量为：{word_num}个")

word_num = get_file_word_number_02("./08_03_文件读取的课后练习讲解.txt", key_word)
print(f"关键字{key_word}在文件内部的数量为：{word_num}个")