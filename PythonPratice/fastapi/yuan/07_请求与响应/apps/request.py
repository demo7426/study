"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	request.py
作  者:	钱锐      版: V0.1.0     新建日期: 2025.07.22
描  述: Request对象
备  注:
修改记录:

  1.  日期: 2025.07.22
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

from typing import Union, Optional
from fastapi import APIRouter, Request

g_request_router = APIRouter()

@g_request_router.get('/items')
async def items(request: Request):
    return {
        "请求url": request.url,
        "请求ip": request.client.host,
        "请求port": request.client.port,
        "请求宿主": request.headers.get("user-agent"),
        "cookie": request.cookies
    }

