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

    list_record = parse_file_txt.GetData("./案例数据/2011年1月销售数据.txt")
    #list_record: list[parse_file.Record] =  parse_file_json.GetData("./案例数据/2011年2月销售数据JSON.txt")

    dict_record: [str, int] = {}
    for record in list_record:          #合并同一天的数据到字典中
        if record.date in dict_record:
            dict_record[record.date] += record.price
        else:
            dict_record[record.date] = record.price

    bar = Bar(init_opts=InitOpts(
        theme=ThemeType.LIGHT
    ))

    bar.add_xaxis(list(dict_record.keys()))

    bar.add_yaxis("销售额", list(dict_record.values()), label_opts=LabelOpts(is_show=False))

    bar.set_global_opts(
        title_opts=TitleOpts(title="每日销售额")
    )

    bar.render()


