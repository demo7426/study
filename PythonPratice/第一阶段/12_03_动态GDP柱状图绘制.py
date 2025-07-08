"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	12_03_动态GDP柱状图绘制.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.07.04
描  述: 动态GDP柱状图绘制
备  注:
修改记录:

  1.  日期: 2025.07.04
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

from pyecharts.charts import Bar, Timeline
from pyecharts.options import LabelOpts, TitleOpts
from pyecharts.globals import ThemeType

#读取数据
f = open("./可视化案例数据/动态柱状图数据/1960-2019全球GDP数据.csv", "r", encoding="GB2312")

src_data_list = f.readlines()

#关闭文件
f.close()

#删除第一条数据
src_data_list.pop(0)

data_dict = {}
for line in src_data_list:
    year = line.split(',')[0]       #年份
    country = line.split(',')[1]    #国家
    gdp = float(line.split(',')[2])   #gdp数据

    try:
        data_dict[year].append([country, gdp])
    except KeyError:
        data_dict[year] = []
        data_dict[year].append([country, gdp])

#排序年份
sorted_year_list = sorted(data_dict.keys())

#构建时间线对象
timeline = Timeline({"theme": ThemeType.LIGHT})

for year in sorted_year_list:
    data_dict[year].sort(key=lambda x: x[1], reverse=True)

    #取出本年份前8名的国家
    year_data = data_dict[year][0:8][::-1]

    x_data = []
    y_data = []

    for country_gdp in year_data:
        x_data.append(country_gdp[0])
        y_data.append(country_gdp[1] / 100000000)

    #构建柱状图
    bar = Bar()
    bar.add_xaxis(x_data)
    bar.add_yaxis("GDP(亿)", y_data, label_opts=LabelOpts(position="right"))

    #反转x轴和y轴
    bar.reversal_axis()

    bar.set_global_opts(
        title_opts=TitleOpts(title=f"{year}年全球前8GDP数据")
    )

    timeline.add(bar, str(year))

#设置自动播放
timeline.add_schema(
    play_interval=1000,     #自动播放的时间间隔，单位毫秒
    is_timeline_show=True,  #是否在自动播放的时候，显示时间段
    is_auto_play=True,      #是否自动播放
    is_loop_play=True       #是否循环播放
)

#绘图
timeline.render("动态GDP柱状图绘制.html")
