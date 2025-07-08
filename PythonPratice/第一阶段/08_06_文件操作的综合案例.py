"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	08_06_文件操作的综合案例.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.06.29
描  述: 文件操作的综合案例
备  注:
修改记录:

  1.  日期: 2025.06.29
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

def copy_src_file_formal_line_to_new_file(src_file_name, dst_file_name):
    """
    将指定文件中的测试行
    :param file_name:文件名称
    :return:关键字在文件内容中出现次数
    """
    f_src = open(src_file_name, "r", encoding='utf-8')
    f_dst = open(dst_file_name, "w", encoding='utf-8')

    #写入头，头不做判定
    file_head = f_src.readline()
    f_dst.write(file_head)

    file_lines = f_src.readlines()

    for i in range(len(file_lines)):
        #file_lines[i] = file_lines[i].strip()
        if file_lines[i].count("测试") > 0:
            continue

        f_dst.write(file_lines[i])

    print(file_lines)

    f_src.close()
    f_dst.close()


copy_src_file_formal_line_to_new_file("08_06_文件操作的综合案例.txt", "08_06_文件操作的综合案例.txt.bak")

