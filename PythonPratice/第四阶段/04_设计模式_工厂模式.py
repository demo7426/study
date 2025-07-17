"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	04_设计模式_工厂模式.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.07.17
描  述: 设计模式_工厂模式
备  注:
修改记录:

  1.  日期: 2025.07.17
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

class Person:
    pass

class Student(Person):
    pass

class Teacher(Person):
    pass

class Worker(Person):
    pass

class PersonFactory:            # 工厂

    def get_person(self, type: str):
        if type == 'student':
            return Student()
        elif type == 'teacher':
            return Teacher()
        else:
            return Worker()

pf = PersonFactory()

pf.get_person('student')
pf.get_person('teacher')
pf.get_person('worker')

