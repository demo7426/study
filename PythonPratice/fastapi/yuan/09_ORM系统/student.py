"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	student.py
作  者:	钱锐      版: V0.1.0     新建日期: 2025.07.27
描  述: 实现student url操作
备  注:
修改记录:

  1.  日期: 2025.07.27
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""
from http.client import HTTPException
from typing import List, Union
from pydantic import BaseModel

from models import *
from fastapi import APIRouter

class StudentModel(BaseModel):
    name: str
    sno: int
    pwd: str
    clas_id: Union[int, None] = None
    course: List[int] = []


g_student_router = APIRouter()

@g_student_router.get("/")
async def get_all_student():
    """
    获取所有的学生信息
    :return:
    """
    students = await Student.all().values("name", "clas__name")

    # 过滤获取
    # students = await Student.filter(name__icontains='天').values("name", "clas__name")

    # 过滤获取
    # students = await Student.get(name='小天').values("name", "clas__name")

    return students

@g_student_router.post("/")
async def add_student(stu: StudentModel):
    """添加学生信息"""
    print(stu)
    student = await Student.create(name=stu.name, sno=stu.sno, pwd=stu.pwd, clas_id=stu.clas_id)

    # 添加多对多关系记录
    courses = await Course.filter(id__in=stu.course)
    await student.course.add(*courses)

    return student

@g_student_router.put("/{student_id}")
async def update_student(student_id: int, student: StudentModel):
    data = student.dict(exclude_none=True)
    courses = data.pop("course")

    await Student.filter(id=student_id).update(**data)

    courses = await Course.filter(id__in=student.course)
    edit_student = await Student.get(id=student_id)
    await  edit_student.course.clear()
    await edit_student.course.add(*courses)

    return student

@g_student_router.delete("/{student_id}")
async def delete_student(student_id: int):
    deleted_count = await Student.filter(id=student_id).delete()        #条件删除
    if not deleted_count:
        raise HTTPException(status_code=404, detail=f"student {student_id} not found")

    return {}

