"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	09_04_模块的概念和导入.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.06.30
描  述: 模块的概念和导入
备  注:
修改记录:

  1.  日期: 2025.06.30
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

#使用import导入time模块使用sllep功能（函数）
# import time
#
# print("你好")
# time.sleep(2)
# print("我好")

#使用from导入time的sleep功能（函数）
# from time import sleep
#
# print("你好")
# sleep(2)
# print("我好")

#使用*导入time的全部功能
# from time import *
#
# print("你好")
# sleep(2)
# print("我好")

#使用*导入time的全部功能
from time import sleep as sl

print("你好")
sl(2)
print("我好")

