"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	12_01_基础柱状图构建.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.07.04
描  述: 基础柱状图构建
备  注:
修改记录:

  1.  日期: 2025.07.04
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

from pyecharts.charts import Bar
from pyecharts.options import LabelOpts

#使用bar构建基础柱状图
bar = Bar()

#添加x轴的数据
bar.add_xaxis(["中国", "美国", "英国"])

#添加y轴的数据
bar.add_yaxis("GDP", [30, 20, 10], label_opts=LabelOpts(position="right"))

#反转x、y轴
bar.reversal_axis()

#绘图
bar.render("基础柱状图构建.html")

