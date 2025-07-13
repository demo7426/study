"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	02_10_Python操作MySQL基础使用.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.07.13
描  述: Python操作MySQL基础使用
备  注:
修改记录:

  1.  日期: 2025.07.13
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""


from pymysql import Connection

# 获取到MySQL数据库的连接对象
mysql_conn = Connection(
    host='localhost',
    port=3306,
    user='root',
    passwd='123456',
    autocommit=True         # 自动提交
)

# 获取游标对象
cursor = mysql_conn.cursor()
mysql_conn.select_db('world')

cursor.execute("create table if not exists student (ID INT primary key, Name VARCHAR(255), Age SMALLINT, Gender VARCHAR(2));")

try:
    cursor.execute("insert into student values (10001, '周杰伦', 21, '男')")
    cursor.execute("insert into student values (10002, '林俊杰', 31, '男')")

    # 通过commot手动提交（事务）
    # mysql_conn.commit()

except Exception as e:
    print(e)

# 使用游标对象，执行sql语句
cursor.execute('select * from student')

# 获取查询结果
result: tuple = cursor.fetchall()
for row in result:
    print(row)

# 关闭到数据库的链接
mysql_conn.close()

