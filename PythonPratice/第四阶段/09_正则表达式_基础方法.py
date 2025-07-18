"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	09_正则表达式_基础方法.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.07.18
描  述: 正则表达式_基础方法
备  注:
修改记录:

  1.  日期: 2025.07.18
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

import re

str_data = "python heima python itcast"

# 从头开始匹配，匹配第一个命中项
str_match = re.match("python", str_data)

# 全局匹配，匹配第一个命中项
str_search = re.search("python", "heima python itcast python")

str_findall = re.findall("python", "heima python itcast python")

print(str_match)
print(str_match.span())
print(str_match.group())

print(str_search)
print(str_search.span())
print(str_search.group())

print(str_findall)



