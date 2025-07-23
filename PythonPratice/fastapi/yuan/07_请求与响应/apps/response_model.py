"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	response_model.py
作  者:	钱锐      版: V0.1.0     新建日期: 2025.07.23
描  述: 响应模型相关参数
备  注:
修改记录:

  1.  日期: 2025.07.23
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

from typing import Union, List

from pydantic import BaseModel, EmailStr, validator
from fastapi import APIRouter

class UserIn(BaseModel):
    name: str
    password: str = "123"
    email: EmailStr = "123@163.com"
    full_name: Union[str, None] = None

class UserOut(BaseModel):
    name: str
    email: EmailStr
    full_name: Union[str, None] = None

g_response_model_router = APIRouter()

@g_response_model_router.post("/user", response_model=UserOut)
async def add(user: UserIn):
    return user


"""
    使用路径操作装饰器的 response_model 参数来定义响应模型，特别是确保私有数据被过滤掉。
    使用 response_model_exclude_unset 来仅返回显式设定的值。 
    除了response_model_exclude_unset以外，还有response_model_exclude_defaults和response_model_exclude_none，
    我们可以很直观的了解到他们的意思，不返回是默认值的字段和不返回是None的字段。
"""
# @g_response_model_router.get("/user/{user_id}", response_model=UserIn, response_model_exclude={"name"})           #返回除name的字段
# @g_response_model_router.get("/user/{user_id}", response_model=UserIn, response_model_include={"name"})           #仅返回name的字段
@g_response_model_router.get("/user/{user_id}", response_model=UserIn, response_model_exclude_unset=True)      #仅返回显式设定的值
async def add(user_id: str):

    users = {
        "foo": {"name": "Foo", "email": "123456@163.com"},
        "bar": {"name": "Bar", "full_name": "Bar full name"},
    }

    return users[user_id]



