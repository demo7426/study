"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	12_02_基础时间线柱状图绘制.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.07.04
描  述: 基础时间线柱状图绘制
备  注:
修改记录:

  1.  日期: 2025.07.04
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

from pyecharts.charts import Bar, Timeline
from pyecharts.options import LabelOpts
from pyecharts.globals import ThemeType

#使用bar构建基础柱状图
bar_00 = Bar()
bar_01 = Bar()
bar_02 = Bar()

#添加x轴的数据
bar_00.add_xaxis(["中国", "美国", "英国"])
bar_01.add_xaxis(["中国", "美国", "英国"])
bar_02.add_xaxis(["中国", "美国", "英国"])

#添加y轴的数据
bar_00.add_yaxis("GDP", [30, 20, 10], label_opts=LabelOpts(position="right"))
bar_01.add_yaxis("GDP", [40, 30, 20], label_opts=LabelOpts(position="right"))
bar_02.add_yaxis("GDP", [40, 60, 30], label_opts=LabelOpts(position="right"))

#反转x、y轴
bar_00.reversal_axis()
bar_01.reversal_axis()
bar_02.reversal_axis()

#构建时间线对象
timeline = Timeline({"theme": ThemeType.LIGHT})

#在时间线内添加柱状图对象
timeline.add(bar_00, "点1")
timeline.add(bar_01, "点2")
timeline.add(bar_02, "点3")

#设置自动播放
timeline.add_schema(
    play_interval=1000,     #自动播放的时间间隔，单位毫秒
    is_timeline_show=True,  #是否在自动播放的时候，显示时间段
    is_auto_play=True,      #是否自动播放
    is_loop_play=True       #是否循环播放
)

#绘图
timeline.render("基础时间线柱状图绘制.html")
