"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	11_路径操作装饰器方法参数简介.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.07.20
描  述: 路径操作装饰器方法参数简介
备  注:
修改记录:

  1.  日期: 2025.07.20
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

from fastapi import FastAPI
import uvicorn

app = FastAPI(debug=True)

@app.get("/items",
         tags=["这是items测试接口"],
         summary="this is items测试 summary",
         description="this is items测试 description",
         response_description="this is items测试 response_description"
         )
async def test():
    return {"Hello": "World"}

if __name__ == '__main__':
    uvicorn.run("11_路径操作装饰器方法参数简介:app", host='0.0.0.0', port=8080, reload=True)
