"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	01_12_Union联合类型注解.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.07.10
描  述: Union联合类型注解
备  注:
修改记录:

  1.  日期: 2025.07.10
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

from typing import Union

my_list: list[Union[int, str]] = [1, 2, "itheima", "itcast"]

def func(data: Union[int, str]) -> Union[int, str]:
    print(data)
    return data

func(1)



