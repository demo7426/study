"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	11_02_全国疫情地图构建.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.07.03
描  述: 全国疫情地图构建
备  注:
修改记录:

  1.  日期: 2025.07.03
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

import json
from pyecharts.charts import Map
from pyecharts.options import TitleOpts, VisualMapOpts

#读取文件数据
f = open("./可视化案例数据/地图数据/疫情.txt", "r", encoding="utf-8")

#获取全部数据
data = f.read()

f.close()

data_dict = json.loads(data)

provience_data_list = data_dict["areaTree"][0]["children"]

data_list = []  #各省确诊数据

for provience_data in provience_data_list:
    provience_name = provience_data["name"] + "省"
    provience_confirm = provience_data["total"]["confirm"]
    data_list.append((provience_name, provience_confirm))

#创建地图对象
map = Map()

map.add("各省份确诊人数", data_list, "china")

map.set_global_opts(
    title_opts=TitleOpts(title="全国疫情地图"),
    visualmap_opts=VisualMapOpts(
        is_show=True,       #是否显示
        is_piecewise=True,  #是否分段
        pieces=[
            {"min": 1, "max": 99, "label": "1~99人", "color": "#CCFFFF"},
            {"min": 100, "max": 999, "label": "100~999人", "color": "#FFFF99"},
            {"min": 1000, "max": 4999, "label": "1000~4999人", "color": "#FF9966"},
            {"min": 5000, "max": 9999, "label": "5000~9999人", "color": "#FF6666"},
            {"min": 10000, "max": 99999, "label": "10000~99999人", "color": "#CC3333"},
            {"min": 100000, "label": "100000+人", "color": "#990033"},
        ]
    )
)

map.render("全国疫情地图.html")

