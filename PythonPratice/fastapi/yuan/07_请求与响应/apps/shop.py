"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	shop.py
作  者:	钱锐      版: V0.1.0     新建日期: 2025.07.21
描  述: 实现路径参数
备  注:
修改记录:

  1.  日期: 2025.07.21
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

from fastapi import APIRouter

g_shop_router = APIRouter()

@g_shop_router.get('/article/1')              # 当请求行路径参数为/article/1 时，会执行user_root，因为它写在user_article前面
async def get_user_root():
    return {"shop_id": 1}

@g_shop_router.get('/article/{id}')
async def get_user_article(id: int):              # 增加对参数的类型注解后，可以强制要求http参数输入类型
    return {'article_id': id}

