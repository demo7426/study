"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	01_09_复写父类成员和调用父类成员.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.07.09
描  述: 复写父类成员和调用父类成员
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

    def call_by_5g(self):
        print("使用5g网络进行通话")


class Phone_2025(Phone):
    producer = "中兴"

    def call_by_5g(self):
        print("开启cpu单核模式，确保通话的时候更省电")

        """
        方式1：                                        方式2：
        调用父类成员                                    使用super()调用父类成员
        使用成员变量：父类名.成员变量                      使用成员变量：super().成员变量
        使用成员方法：父类名.成员方法(self)                使用成员方法：super().成员方法()
        """
        print(f"父类的厂商是：{Phone.producer}")
        Phone.call_by_5g(self)

        print(f"父类的厂商是：{super().producer}")
        super().call_by_5g()

        print("关闭cpu单核模式，确保性能")

if __name__ == '__main__':
    phone = Phone_2025()

    print(phone.producer)
    phone.call_by_5g()




