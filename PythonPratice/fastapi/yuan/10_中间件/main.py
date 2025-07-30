"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.py
作  者:	钱锐      版: V0.1.0     新建日期: 2025.07.30
描  述: 实现fastapi的中间件操作
备  注:
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

app = FastAPI(debug=True)

@app.middleware('http')
async def add_headers(request: Request, call_next):
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
    response.headers['author'] = 'qianrui'
    print(inspect.currentframe().f_code.co_name, "，响应代码块")

    return response

@app.middleware('http')
async def filter(request: Request, call_next):
    """
    过滤中间件（最外层中间件，中间件调用顺序，由函数定义顺序决定）
    :param request:
    :param call_next:
    :return:
    """
    # 请求代码块
    start_time = time.time()

    print(inspect.currentframe().f_code.co_name, "，请求代码块")

    response = await call_next(request)

    # 响应代码块
    response.headers['filter'] = 'filter'
    print(inspect.currentframe().f_code.co_name, "，响应代码块, " + str(time.time() - start_time) + '秒')

    return response

@app.get('/user')
async def get_user():

    time.sleep(2)
    print(inspect.currentframe().f_code.co_name)

    return {
        "user": "current user"
    }

@app.get('/item/{item_id}')
async def get_item(item_id: int):

    time.sleep(3)
    print(inspect.currentframe().f_code.co_name)

    return {
        "item_id": item_id
    }

if __name__ == '__main__':
    uvicorn.run('main:app', host='127.0.0.1', port=8080, reload=True)