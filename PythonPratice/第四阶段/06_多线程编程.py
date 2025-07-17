"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	06_多线程编程.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.07.17
描  述: 多线程编程
备  注:
修改记录:

  1.  日期: 2025.07.17
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

import time
import threading

def sing(msg):
    while True:
        print(msg)
        time.sleep(1)

def dance(msg):
    while True:
        print(msg)
        time.sleep(1)


if __name__ == '__main__':

    """
    thread_obj =threading.Thread([group[,target[,name [,args [,kwargs]]]]])-group:暂时无用，未来功能的预留参数
    target:执行的目标任务名
    args:以元组的方式给执行任务传参
    kwargs:以字典方式给执行任务传参
    name:线程名，一般不用设置 
    """
    sing_thread = threading.Thread(target=sing, args=("正在唱歌...", ))
    dance_thread = threading.Thread(target=dance, kwargs={"msg": "正在跳舞..."})

    sing_thread.start()
    dance_thread.start()



