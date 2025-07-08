"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	01_05_魔术方法.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.07.08
描  述: 魔术方法
备  注: 如果在构造函数内部有属性赋值操作，在赋值时，属性就直接被定义，不需要单独定义
修改记录:

  1.  日期: 2025.07.08
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

class Student:
    def __init__(self, name, age):          #构造函数
        self.name = name
        self.age = age

    def __str__(self):                      #字符串转换函数
        return f"名称为：{self.name}, 年龄为：{self.age}"

    def __lt__(self, other):                #类似于C++的小于运算重载
        return self.age < other.age

    def __le__(self, other):                #类似于C++的小于等于运算重载
        return self.age <= other.age

    def __eq__(self, other):                #类似于C++的等于运算重载
        return self.age == other.age

if __name__ == '__main__':
    student_00 = Student("林俊杰", 41)
    student_01 = Student("周杰伦", 41)

    print(student_00.name, student_00.age)
    print(student_01.name, student_01.age)

    print(student_00)
    print(student_01)

    print(student_00 < student_01)

    print(student_00 <= student_01)

    print(student_00 == student_01)
