"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	02_12_综合案例.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.07.13
描  述: 综合案例
备  注:
修改记录:

  1.  日期: 2025.07.13
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""


from pymysql import Connection


"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	01_14_数据分析案例.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.07.11
描  述: 数据分析案例
备  注:
修改记录:

  1.  日期: 2025.07.11
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

from pyecharts.charts import Bar
from pyecharts.options import *
from pyecharts.globals import ThemeType

from data_parse import parse_file

if __name__ == '__main__':
    parse_file_txt = parse_file.ParseFile_TXT()
    parse_file_json = parse_file.ParseFile_JSON()

    list_record: list[parse_file.Record] = parse_file_txt.GetData("./案例数据/2011年1月销售数据.txt")
    list_record += parse_file_json.GetData("./案例数据/2011年2月销售数据JSON.txt")

    # 获取到MySQL数据库的连接对象
    mysql_conn = Connection(
        host='localhost',
        port=3306,
        user='root',
        passwd='123456',
        # autocommit=True  # 自动提交
    )

    # 获取游标对象
    cursor = mysql_conn.cursor()
    mysql_conn.select_db('world')

    cursor.execute("create table if not exists orders (Date DATE, ID VARCHAR(64), Price INT, province VARCHAR(8));")

    for record in list_record:
        cursor.execute(f"insert into orders values ('{record.date}', '{record.id}', {record.price}, '{record.province}')")

    mysql_conn.commit()

    # # 使用游标对象，执行sql语句
    # cursor.execute('select * from orders')
    #
    # # 获取查询结果
    # result: tuple = cursor.fetchall()
    # for row in result:
    #     print(row)

    # 关闭到数据库的链接
    mysql_conn.close()

