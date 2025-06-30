"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	09_05_自定义模块并导入.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.06.30
描  述: 自定义模块并导入
备  注:
修改记录:

  1.  日期: 2025.06.30
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

#创建一个包
#导入自定义的包中的模块，并使用
# import my_packet.my_packet_my_module_00
# import my_packet.my_packet_my_module_01
#
# print(my_packet.my_packet_my_module_00.add(1, 2))
# print(my_packet.my_packet_my_module_01.sub(1, 2))

from my_packet import my_packet_my_module_00
from my_packet import my_packet_my_module_01

print(my_packet_my_module_00.add(1, 2))
print(my_packet_my_module_01.sub(1, 2))

#通过__all__变量，控制import *
# from my_packet import *
#
# print(my_packet_my_module_00.add(1, 2))







