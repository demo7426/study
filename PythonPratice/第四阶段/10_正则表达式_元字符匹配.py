"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	10_正则表达式_元字符匹配.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.07.18
描  述: 正则表达式_元字符匹配
备  注:
修改记录:

  1.  日期: 2025.07.18
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

import re

# 匹配账号，只能由字母和数字组成，长度限制6到10位
str_reg = '^[a-zA-Z0-9]{6,10}$'

str_findall = re.findall(str_reg, "0123456789")

print(str_findall)

# 匹配QQ号，要求纯数字，长度5~11，第一位不位0
str_reg = '^[1-9]{1}[0-9]{4,10}$'

str_findall = re.findall(str_reg, "2575801234")

print(str_findall)

# 匹配邮箱地址，只允许qq、163、gmail这三种邮箱地址
str_reg = '(^[\w-]+(\.[\w-]+)*@(qq|163|gmail)(\.[\w-]+)$)'

str_findall = re.findall(str_reg, "2575801234@163.com")

print(str_findall)



