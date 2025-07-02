"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	10_06_生成折线图.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.07.02
描  述: 生成折线图
备  注:
修改记录:

  1.  日期: 2025.07.02
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""
import json
from pyecharts.charts import Line
from pyecharts.options import TitleOpts, LegendOpts, ToolboxOpts, VisualMapOpts, LabelOpts

f_us = open("./可视化案例数据/折线图数据/美国.txt", "r", encoding="utf-8")
f_jp = open("./可视化案例数据/折线图数据/日本.txt", "r", encoding="utf-8")
f_in = open("./可视化案例数据/折线图数据/印度.txt", "r", encoding="utf-8")

us_data = f_us.read()
jp_data = f_jp.read()
in_data = f_in.read()
f_us.close()

us_data = us_data.replace("jsonp_1629344292311_69436(", "")
jp_data = jp_data.replace("jsonp_1629350871167_29498(", "")
in_data = in_data.replace("jsonp_1629350745930_63180(", "")

#获取符合json格式的数据
us_data = us_data[0:-2:1]
jp_data = jp_data[0:-2:1]
in_data = in_data[0:-2:1]

us_dict = json.loads(us_data)
jp_dict = json.loads(jp_data)
in_dict = json.loads(in_data)

us_trend_data = us_dict["data"][0]["trend"]
jp_trend_data = jp_dict["data"][0]["trend"]
in_trend_data = in_dict["data"][0]["trend"]

#获取日期
us_x = us_trend_data["updateDate"][0:314:1]
jp_x = jp_trend_data["updateDate"][0:314:1]
in_x = in_trend_data["updateDate"][0:314:1]

us_y = us_trend_data["list"][0]["data"][0:314:1]
jp_y = jp_trend_data["list"][0]["data"][0:314:1]
in_y = in_trend_data["list"][0]["data"][0:314:1]

#创建一个折线图对象
line = Line()

#给折线图对象添加x轴的数据
line.add_xaxis(us_x)

#给折线图对象添加y轴的数据，并取消每个折线的节点纵坐标的数值显示
line.add_yaxis("美国确诊人数", us_y, label_opts=LabelOpts(is_show=False))
line.add_yaxis("日本确诊人数", jp_y, label_opts=LabelOpts(is_show=False))
line.add_yaxis("印度确诊人数", in_y, label_opts=LabelOpts(is_show=False))

line.set_global_opts(
    title_opts=TitleOpts(title="2020年美日印三国确诊人数对比折线图", pos_left="center", pos_bottom="1%"),
    legend_opts=LegendOpts(is_show=True),
    toolbox_opts=ToolboxOpts(is_show=True),
    #visualmap_opts=VisualMapOpts(is_show=True),
)

#通过rendder方法，将代码生成为图像
line.render()





