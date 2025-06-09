"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	02_10_字符串格式化.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.06.09
描  述: 字符串格式化
备  注:
修改记录:

  1.  日期: 2025.06.09
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V1.0.0
"""

name = "黑马程序员"
address = "成都市武侯区"
telephone = 13412341234

print("我是%s,家住:%s,电话:%s" % (name, address, telephone))

name = "传智教育"
setup_year = 2006
stock_price = 19.99

print("%s,成立于:%d,股价:%f" % (name, setup_year, stock_price))

