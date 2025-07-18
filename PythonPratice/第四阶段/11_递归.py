"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	11_递归.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.07.18
描  述: 递归
备  注:
修改记录:

  1.  日期: 2025.07.18
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

import os

def test_os():
    print(os.listdir("../.."))      #列出路径下的内容
    print(os.path.isdir("../.."))   #判断指定路径是不是文件夹
    print(os.path.exists("../.."))  #判断指定路径是否存在

def get_files_recursive_from_dir(path):
    if not os.path.exists(path):
        return None

    file_list: list = []
    dir_list: list = os.listdir(path)
    for dir_name in dir_list:
        new_dir_path = path + "/" + dir_name

        if os.path.isdir(new_dir_path):     # 文件夹
            file_list += get_files_recursive_from_dir(new_dir_path)
        else:
            file_list.append(dir_name)

    return file_list

if __name__ == '__main__':
    file_list: list = get_files_recursive_from_dir("../..")

    for file in file_list:
        print(file)






