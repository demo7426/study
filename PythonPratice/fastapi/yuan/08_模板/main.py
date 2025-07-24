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
from fastapi import FastAPI, Request
from starlette.templating import Jinja2Templates

app = FastAPI()

templates = Jinja2Templates(directory="templates")

@app.get("/")
async def index(request: Request):
    return templates.TemplateResponse("index.html",
            {
                "request": request,
                "user": "zhang san",
                "age": 24,
                "books": ["金瓶梅", "聊斋", "剪灯新话", "国色天香"],
                "book_dict":{
                    "金瓶梅": {"price": 100, "publish": "苹果出版社"},
                    "聊斋": {"price": 200, "publish": "橘子出版社"}
                }
            }
        )

if __name__ == '__main__':
    uvicorn.run("main:app", host='0.0.0.0', port=8080, reload=True)

