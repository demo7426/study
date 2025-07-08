"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	01_07_封装的课后练习题讲解.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.07.08
描  述: 封装的课后练习题讲解
备  注:
修改记录:

  1.  日期: 2025.07.08
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

class Phone:
    __is_5g_enable = False   #是否开启5g；True--开启5g；False--关闭5g；

    def __check_5g(self):   #判断5g是否开启
        if self.__is_5g_enable:
            print("5g开启")
        else:
            print("5g关闭，使用4g网络")

    def call_by_5g(self):
        self.__check_5g()
        print("正在通话中")

if __name__ == '__main__':
    phone = Phone()
    phone.call_by_5g()


