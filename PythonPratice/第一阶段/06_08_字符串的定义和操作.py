"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	06_08_字符串的定义和操作.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.06.18
描  述: 字符串的定义和操作
备  注:
修改记录:

  1.  日期: 2025.06.18
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

#index方法
str_name = "itheima is itcast"
print(f"itcast的索引位置为{str_name.index("itcast")}")

#replace方法
str_replace_name = str_name.replace("it", "程序")
print(str_replace_name)

#split方法
name_list = str_name.split(" ")
print(name_list)

#strip方法
str_name = "12itheima is itcast21"
str_name = str_name.strip("12")
print(str_name)

#统计子字符串在字符串中出现的次数
str_name = "python c++ java lua python c#"
print(f"python子字符串的数量为{str_name.count("python")}个")

#统计字符串的长度
print(f"字符串长度为:{len(str_name)}")
