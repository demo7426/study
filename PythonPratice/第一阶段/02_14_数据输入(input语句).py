"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	02_14_数据输入(input语句).py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.06.09
描  述: 数据输入(input语句)
备  注:
修改记录:

  1.  日期: 2025.06.09
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V1.0.0
"""

name = input("请输入您的名字:")
print("您的名字为:%s" % name)

print("请输入您的电话号码:")
telephone = input()
print("您的电话号码为:%s, telephone类型为:%s" % (telephone, type(telephone)))
