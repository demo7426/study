"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.py
作  者:	钱锐      版: V0.1.0     新建日期: 2025.07.21
描  述: 实现fastapi的路由分发
备  注:
修改记录:

  1.  日期: 2025.07.21
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

import uvicorn
from fastapi import FastAPI

from apps.shop import g_shop_router
from apps.jobs import g_jobs_router
from apps.user import g_uesr_router

app = FastAPI(debug=True)

app.include_router(g_shop_router, prefix="/shop_router", tags=['shop接口'])
app.include_router(g_jobs_router, prefix="/jobs_router", tags=['jobs接口'])
app.include_router(g_uesr_router, prefix="/user_router", tags=['user接口'])

if __name__ == '__main__':
    uvicorn.run("main:app", host='0.0.0.0', port=8080, reload=True)

