"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	record.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.07.11
描  述:
备  注:
修改记录:

  1.  日期: 2025.07.11
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

class Record:
    def __init__(self, date: str, id: str, price: int, province: str):
        self.date: str = date           #订单日期
        self.id: str = id               #订单ID
        self.price: int = price         #订单价格
        self.province: str = province   #省份

    def __str__(self):
        return f'{self.date}，{self.id}，{self.price}，{self.province}'