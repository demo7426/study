"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.py
作  者:	钱锐      版: V0.1.0     新建日期: 2025.07.27
描  述: 实现TORTOISE_ORM数据库操作
备  注:
修改记录:

  1.  日期: 2025.07.27
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

"""
sql 语法，用于初始化fastapi数据库，mysql的fastapi数据库需要先手动创建
-- 插入 3 个班级
INSERT INTO clas (name) VALUES ('一班'), ('二班'), ('三班');

-- 插入 3 个老师
INSERT INTO teacher (id, name, tno, pwd) VALUES
(1, '张老师', 1001, '123456'),
(2, '李老师', 1002, '123456'),
(3, '王老师', 1003, '123456');

-- 插入 5 门课程
INSERT INTO course (id, name, teacher_id) VALUES
(101, '数学', 1),
(102, '英语', 2),
(103, '物理', 3),
(104, '化学', 1),
(105, '语文', 2);

-- 插入 10 个学生
INSERT INTO student (id, sno, pwd, name, clas_id, course_id) VALUES
(1001, 20230001, '123456', '小明', 1, 101),
(1002, 20230002, '123456', '小红', 2, 102),
(1003, 20230003, '123456', '小刚', 3, 103),
(1004, 20230004, '123456', '小芳', 1, 101),
(1005, 20230005, '123456', '小龙', 2, 105),
(1006, 20230006, '123456', '小艾', 3, 104),
(1007, 20230007, '123456', '小杰', 1, 103),
(1008, 20230008, '123456', '小雪', 2, 102),
(1009, 20230009, '123456', '小天', 3, 105),
(1010, 20230010, '123456', '小李', 1, 101);
"""

import uvicorn
from fastapi import FastAPI
from tortoise.contrib.fastapi import register_tortoise
from settings import TORTOISE_ORM

from student import g_student_router

app = FastAPI(debug=True)

app.include_router(g_student_router, prefix="/student", tags=["学生信息"])

# 该方法会在fastapi启动时触发，内部通过传递进去的app对象，监听服务启动和终止事件
# 当检测到启动事件时，会初始化Tortoise对象，如果generate_schemas为True则还会进行数据库迁移
# 当检测到终止事件时，会关闭连接
register_tortoise(
    app,
    config=TORTOISE_ORM,
    # generate_schemas=True,  # 如果数据库为空，则自动生成对应表单，生产环境不要开
    # add_exception_handlers=True,  # 生产环境不要开，会泄露调试信息
)

if __name__ == '__main__':
    uvicorn.run('main:app', host='127.0.0.1', port=8080, reload=True)