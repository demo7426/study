"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	regin.py
作  者:	钱锐      版: V0.1.0     新建日期: 2025.07.22
描  述: 实现form表单数据
备  注:
修改记录:

  1.  日期: 2025.07.22
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

from fastapi import APIRouter, Form

g_regin_router = APIRouter()

@g_regin_router.post("/")
async def regin(username: str = Form(), password: str = Form()):
    return {"username": username, "password": password}



