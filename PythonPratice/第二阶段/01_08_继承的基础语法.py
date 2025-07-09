"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	01_08_继承的基础语法.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.07.09
描  述: 继承的基础语法
备  注:
修改记录:

  1.  日期: 2025.07.09
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

class Phone:
    producer = "华为"

    def call_by_4g(self):
        print("4g通话")

class NTF_Reader:
    producer = "中兴"

    nfc_type = "第五代"

    def read_card(self):
        print("读取NFC卡")

    def write_card(self):
        print("写入NFC卡")

class RemoteControl:
    rc_type = "红外遥控"

    def control(self):
        print("红外遥控开启")

#单继承
class Phone_2025(Phone):
    face_id = "10001"                               #面部识别ID

    def call_by_5g(self):
        print("2025年新功能：5g通话")

#多继承
class MyPhone(Phone, NTF_Reader, RemoteControl):    #多继承中，如果父类有同名方法或属性，先继承的优先级高于后继承
    pass                                            #pass是占位语句，用来保证函数（方法）或类定义的完整性，表示无内容，空的意思


if __name__ == '__main__':
    phone = Phone_2025()
    phone.call_by_4g()
    phone.call_by_5g()

    my_phone = MyPhone()
    print(my_phone.producer)
    my_phone.call_by_4g()
    my_phone.read_card()
    my_phone.write_card()
    my_phone.control()



