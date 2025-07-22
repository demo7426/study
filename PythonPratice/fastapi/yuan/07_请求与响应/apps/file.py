"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	file.py
作  者:	钱锐      版: V0.1.0     新建日期: 2025.07.22
描  述: 实现文件上传
备  注:
修改记录:

  1.  日期: 2025.07.22
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

from typing import List
from fastapi import APIRouter, File, UploadFile

g_file_router = APIRouter()

@g_file_router.post("/file")
async def create_file(file: bytes = File()):
    print("file：", file)
    return {"file_size": len(file)}

@g_file_router.post("/files")
async def create_files(files: List[bytes] = File()):
    return {"file_size": [len(file) for file in files]}

@g_file_router.post("/upload_file")
async def create_file(upload_file: UploadFile):

    with open(upload_file.filename, "wb") as f:
        for line in upload_file.file:
            f.write(line)

    return {
        "file_name": upload_file.filename,
        "file_size": upload_file.size
    }

@g_file_router.post("/upload_files")
async def create_files(upload_files: List[UploadFile]):

    for upload_file in upload_files:
        with open(upload_file.filename, "wb") as f:
            for line in upload_file.file:
                f.write(line)

    return {
        "file_name": [upload_file.filename for upload_file in upload_files],
        "file_size": [upload_file.size for upload_file in upload_files]
    }

