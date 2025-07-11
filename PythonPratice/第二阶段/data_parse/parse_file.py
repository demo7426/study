"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	parse_file.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.07.11
描  述: 读取文件并解析
备  注:
修改记录:

  1.  日期: 2025.07.11
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""
import json
from .record import *

class ParseFile:
    def GetData(self):
        pass

class ParseFile_TXT(ParseFile):
    def GetData(self, file_path: str) -> list[Record]:
        """
        解析传入的txt格式文本文件，并返回
        :param file_path:文件路径
        :return:Record链表
        """

        record_list: list[Record] = []

        try:
            f = open(file_path, 'r', encoding='utf-8')

            lines = f.readlines()

            for line in lines:
                line = line.strip()

                line_list: list[str] = line.split(",")

                record = Record(line_list[0], line_list[1], int(line_list[2]), line_list[3])
                record_list.append(record)

        except Exception as e:
            print(e)
        else:
            f.close()

        return record_list


class ParseFile_JSON(ParseFile):
    def GetData(self, file_path: str) -> list[Record]:
        """
        解析传入的json格式文本文件，并返回
        :param file_path:文件路径
        :return:Record链表
        """

        record_list: list[Record] = []

        try:
            f = open(file_path, 'r', encoding='utf-8')

            lines = f.readlines()

            for line in lines:
                line = line.strip()

                line_dict: list[str] = json.loads(line)

                record = Record(line_dict['date'], line_dict['order_id'], int(line_dict['money']), line_dict['province'])
                record_list.append(record)

        except Exception as e:
            print(e)
        else:
            f.close()

        return record_list

if __name__ == '__main__':
    parse_file_txt = ParseFile_TXT()
    parse_file_json = ParseFile_JSON()

    parse_file_txt.GetData("../案例数据/2011年1月销售数据.txt")
    parse_file_json.GetData("../案例数据/2011年2月销售数据JSON.txt")

