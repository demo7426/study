"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	10_04_pyecharts的入门使用.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.07.01
描  述: pyecharts的入门使用
备  注:
修改记录:

  1.  日期: 2025.07.01
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

#导包
from pyecharts.charts import Line
from pyecharts.options import TitleOpts, LegendOpts, ToolboxOpts, VisualMapOpts

#创建一个折线图对象
line = Line()

#给折线图对象添加x轴的数据
line.add_xaxis(["中国", "美国", "英国"])

#给折线图对象添加y轴的数据
line.add_yaxis("GDP", [30, 20, 10])

line.set_global_opts(
    title_opts=TitleOpts(title="GDP展示", pos_left="center", pos_bottom="%1"),
    legend_opts=LegendOpts(is_show=True),
    toolbox_opts=ToolboxOpts(is_show=True),
    visualmap_opts=VisualMapOpts(is_show=True),
)

#通过rendder方法，将代码生成为图像
line.render()





