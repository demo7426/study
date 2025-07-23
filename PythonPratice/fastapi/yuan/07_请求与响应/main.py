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
from starlette.staticfiles import StaticFiles

from apps.shop import g_shop_router
from apps.jobs import g_jobs_router
from apps.user import g_uesr_router
from apps.regin import g_regin_router
from apps.file import g_file_router
from apps.request import g_request_router
from apps.response_model import g_response_model_router

app = FastAPI(debug=True)

app.include_router(g_shop_router, prefix="/shop_router", tags=['路径参数'])
app.include_router(g_jobs_router, prefix="/jobs_router", tags=['查询参数（请求参数）'])
app.include_router(g_uesr_router, prefix="/user_router", tags=['请求体数据'])
app.include_router(g_regin_router, prefix="/regin_router", tags=['form表单'])
app.include_router(g_file_router, prefix="/file", tags=['文件上传'])
app.include_router(g_request_router, prefix="/request", tags=['获取客户端相关ip、port、路由等信息'])
app.include_router(g_response_model_router, prefix="/response_model", tags=['响应模型相关参数'])

app.mount("/static", StaticFiles(directory="static"))

# import os
# import asyncio
# from fastapi import FastAPI, Response, HTTPException
# from fastapi.responses import StreamingResponse
# from starlette.concurrency import run_in_threadpool
# import aiofiles
#
# # 大文件下载接口（核心优化）
# @app.get("/download/{file_path:path}")
# async def download_large_file(file_path: str, response: Response):
# """
# 优化的大文件下载接口，支持接近千兆网极限速度
# - 异步流式传输，无内存占用压力
# - 优化的块大小和传输策略
# """
# # 文件路径处理（根据实际存储位置调整）
# base_dir = r"D:\PythonPractice\pythonProject\fastapi\yuan\07_请求与响应"  # 建议使用SSD存储
# full_path = os.path.abspath(os.path.join(base_dir, file_path))
#
# # 验证文件存在性
# if not os.path.exists(full_path) or not os.path.isfile(full_path):
#     raise HTTPException(status_code=404, detail="文件不存在")
#
# # 获取文件元信息
# file_size = os.path.getsize(full_path)
# file_name = os.path.basename(full_path)
#
# # 设置响应头（关键优化）
# response.headers.update({
#     "Content-Length": str(file_size),  # 告知客户端文件总大小
#     "Content-Disposition": f"attachment; filename*=UTF-8''{file_name}",
#     "Cache-Control": "no-cache",  # 大文件通常不缓存
#     "X-Accel-Buffering": "no",  # 禁用代理缓冲（如Nginx）
#     "Connection": "keep-alive"
# })
#
# # 异步分块读取文件（核心优化点：块大小）
# async def file_chunks_generator():
#     chunk_size = 16 * 1024 * 1024  # 16MB块（根据测试调整，4-32MB最佳）
#     async with aiofiles.open(full_path, mode='rb') as f:
#         while chunk := await f.read(chunk_size):
#             yield chunk
#             # 控制协程切换节奏，避免过度切换开销
#             await asyncio.sleep(0)
#
# return StreamingResponse(
#     file_chunks_generator(),
#     media_type="application/octet-stream"
# )

if __name__ == '__main__':
    uvicorn.run("main:app", host='0.0.0.0', port=8080, reload=True)

