"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	01_13_多态.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.07.10
描  述: 多态
备  注:
修改记录:

  1.  日期: 2025.07.10
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

class Animal:           #拥有抽象方法的类，为抽象类
    def speak(self):    #没有具体的实现，为抽象方法
        pass

class Dog(Animal):
    def speak(self):
        print("汪汪汪")

class Cat(Animal):
    def speak(self):
        print("喵喵喵")

def func(animal: Animal):
    animal.speak()

if __name__ == '__main__':
    dog = Dog()
    cat = Cat()

    func(dog)
    func(cat)

