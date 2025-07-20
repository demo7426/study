"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	12_fastapi的路由分发include_router.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.07.20
描  述: fastapi的路由分发include_router
备  注:
修改记录:

  1.  日期: 2025.07.20
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

import uvicorn
from fastapi import FastAPI

from apps.shop.urls import shop
from apps.user.urls import user


app = FastAPI(debug=True)

app.include_router(shop, prefix='/shop', tags=['购物中心接口'])
app.include_router(user, prefix='/user', tags=['用户中心接口'])

if __name__ == '__main__':
    uvicorn.run("12_fastapi的路由分发include_router:app", host='0.0.0.0', port=8080, reload=True)



