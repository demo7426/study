"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.py
作  者:	钱锐      版: V0.1.0     新建日期: 2025.07.30
描  述: 实现CORS组件操作，响应客户端跨域请求
备  注: 响应跨域请求，响应头添加：response.headers['Access-Control-Allow-Origin'] = '*' 即可
       或者使用 add_middleware，fastapi框架控制客户端跨域请求的响应
修改记录:

  1.  日期: 2025.07.30
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

import inspect
import time
import uvicorn
from fastapi import FastAPI, Request
from fastapi.middleware.cors import CORSMiddleware

app = FastAPI(debug=True)

origins = [
    "http://localhost:63342",
]

app.add_middleware(
    CORSMiddleware,
    allow_origins=['*'],        # *--代表所有客户端
    allow_credentials=True,
    allow_methods=['*'],
    allow_headers=['*'],
)

@app.middleware('http')
async def add_cros_header(request: Request, call_next):
    """
    添加响应头中间件
    :param request:
    :param call_next:
    :return:
    """
    # 请求代码块
    print(inspect.currentframe().f_code.co_name, "，请求代码块")

    response = await call_next(request)

    # 响应代码块
    # response.headers['Access-Control-Allow-Origin'] = '*'
    print(inspect.currentframe().f_code.co_name, "，响应代码块")

    return response

@app.get('/')
async def get_user():

    print(inspect.currentframe().f_code.co_name)

    return {
        "user": "current user"
    }

if __name__ == '__main__':
    uvicorn.run('main:app', host='127.0.0.1', port=8080, reload=True)