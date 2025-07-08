"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	06_09_字符串的课后练习讲解.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.06.18
描  述: 字符串的课后练习讲解
备  注:
修改记录:

  1.  日期: 2025.06.18
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

str_msg = "itheima itcast boxuegu"

print(f"字符串{str_msg}中有：{str_msg.count("it")}个it字符")

str_msg_replace = str_msg.replace(" ", "|")
print(f"字符串{str_msg}，被替换空格后，结果：{str_msg_replace}")

print(f"字符串{str_msg_replace}，按照|分割后，得到：{str_msg_replace.split("|")}")



