"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	models.py
作  者:	钱锐      版: V0.1.0     新建日期: 2025.07.27
描  述: 实现数据库模型
备  注:
修改记录:

  1.  日期: 2025.07.27
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

from tortoise.models import Model
from tortoise import fields

class Clas(Model):
    """
    班级类
    """
    name = fields.CharField(max_length=255, description="班级名称")

class Teacher(Model):
    """
    老师类
    """
    id = fields.IntField(pk=True)
    name = fields.CharField(max_length=255, description="姓名")
    tno = fields.IntField(description="账号")
    pwd = fields.CharField(max_length=255, description="密码")

class Student(Model):
    id = fields.IntField(pk=True)
    sno = fields.IntField(description="学号")
    pwd = fields.CharField(max_length=255, description="密码")
    name = fields.CharField(max_length=255, description="姓名")

    # 一对多
    clas = fields.ForeignKeyField("models.Clas", related_name="students")

    # 多对多
    course = fields.ForeignKeyField("models.Course", related_name="students", description="学生选课表")

class Course(Model):
    id = fields.IntField(pk=True)
    name = fields.CharField(max_length=255, description="课程名")
    teacher = fields.ForeignKeyField("models.Teacher", related_name="courses", description = "客户讲师")




