"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	user.py
作  者:	钱锐      版: V0.1.0     新建日期: 2025.07.21
描  述: 实现请求体数据
备  注:
修改记录:

  1.  日期: 2025.07.21
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

from typing import Union, List, Optional
from datetime import date

from dataclasses import Field
from fastapi import APIRouter
from pydantic import BaseModel, Field, field_validator

class Addr(BaseModel):
    province: str                                   # 省份
    city: str                                       # 城市

class User(BaseModel):
    name: str                                       # 姓名
    age: int = Field(default=0, gt=0, lt=200)       # 年龄范围在0~200岁
    birth: Union[date, None] = None                 # 出生日期
    friends: List[int] = []                         # 朋友的id
    description: Optional[str] = None               # 详细描述
    addr: Addr                                      # 地址

    @field_validator("name")
    def name_must_alpha(cls, value):
        assert value.isalpha(), "name must be alpha"
        return value

class Data(BaseModel):
    data: List[User]

g_uesr_router = APIRouter()

@g_uesr_router.post('/user_info')
async def post_user_info(user: User):
    return user

@g_uesr_router.post('/user_list_info')
async def post_user_list_info(user: Data):
    return user


