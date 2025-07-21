"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	user.py
作  者:	钱锐      版: V0.1.0     新建日期: 2025.07.21
描  述: 实现查询参数（请求参数）
备  注:
修改记录:

  1.  日期: 2025.07.21
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

from typing import Union, Optional
from fastapi import APIRouter

g_jobs_router = APIRouter()

@g_jobs_router.get('/jobs/{kd}')
async def get_user_article(kd: str, xl: Union[str, None] = None, gj: Optional[str] = None):   # xl、gj为查询参数（请求参数）
    return {
        "kd": kd,
        "xl": xl,
        "gj": gj
    }

