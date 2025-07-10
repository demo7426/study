"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	01_10_变量的类型注解.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.07.10
描  述: 变量的类型注解
备  注:
修改记录:

  1.  日期: 2025.07.10
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

import json
import random

#基础数据类型注解
age: int = 18
name: str = "itheima"
is_ok: bool = False

#类对象类型注解
class Student:
    pass

student: Student = Student()

#基础容器类型注解
my_list: list = [1, 2, 3]
my_tuple: tuple = (1, 2, 3)
my_set: set = {1, 2, 3}
my_dict: dict = {'a': 1, 'b': 2, 'c': 3}

#容器类型详细注解
my_list_01: list[int] = [1, 2, 3]
my_tuple_01: tuple[str, int, bool] = ('itheima', 2, True)
my_set_01: set[int] = {1, 2, 3}
my_dict_01: dict[str, int] = {'a': 1, 'b': 2, 'c': 3}

#在注释中进行类型注解
random_num = random.randint(1, 100)                     # type: int
dict_data = json.loads('{"name": "zhangsan"}')                # type: dict[str, str]

def func():
    return 10

ret = func()        # type: int

#类型注解的限制
#类型注解只是提示性的，并非决定性的。数据类型和注解类型无法对应也不会导致错误
var_00: int = "itcast"
var_01: bool = 123

