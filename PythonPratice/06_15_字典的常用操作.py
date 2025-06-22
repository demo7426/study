"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	06_15_字典的常用操作.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.06.22
描  述: 字典的常用操作
备  注:
修改记录:

  1.  日期: 2025.06.22
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

my_dict = {"周杰伦": 99, "林俊杰": 88, "张学友": 77}

#新增元素
my_dict["张信哲"] = 66
print(f"字典经过新增元素后，结果：{my_dict}")

#更新元素
my_dict["林俊杰"] = 33
print(f"字典经过更新元素后，结果：{my_dict}")

#删除元素
score = my_dict.pop("周杰伦")
print(f"字段被移除了一个元素，结果：{my_dict}，周杰伦的考试分数是：{score}")

#清空元素，clear
my_dict.clear()
print(f"字典经过清空元素后，结果：{my_dict}")

my_dict = {"周杰伦": 99, "林俊杰": 88, "张学友": 77}

#获取全部的key
keys = my_dict.keys()
print(f"字典的全部keyus是：{keys}")

#遍历字典
#方式1：通过获取到全部的key来完成遍历
for key in keys:
    print(f"1：字典的key是：{key}")
    print(f"1：字典的value是：{my_dict[key]}")

#方式2：直接对字典进行for循环，每一次循环都是直接得到key
for key in my_dict:
    print(f"2：字典的key是：{key}")
    print(f"2：字典的value是：{my_dict[key]}")

#统计字典的元素数量，len()函数
print(f"字典的元素数量是：{len(my_dict)}个")

