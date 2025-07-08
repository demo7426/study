"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	09_08_异常_模块_包_综合案例讲解.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.06.30
描  述: 异常_模块_包_综合案例讲解
备  注:
修改记录:

  1.  日期: 2025.06.30
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

from my_utils import file_util
from my_utils import str_util

if __name__ == '__main__':
    file_util.print_file_info("08_06_文件操作的综合案例.txt")
    file_util.append_to_file("09_08_异常_模块_包_综合案例讲解.txt", "itheima")

    print(str_util.str_reverse("黑马程序员"))
    print(str_util.substr("黑马程序员", 0, 2))



