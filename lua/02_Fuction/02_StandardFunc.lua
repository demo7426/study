--[[
    02_标准库函数练习，学习参考链接为 https://blog.csdn.net/wangshuai6707/article/details/132403666
--]]

local str = "Hello world"

--字符串处理
local strUpper = string.upper(str)                      --大小写转换
print(strUpper)

strUpper = string.lower(strUpper)                       --大小写转换
print(strUpper)

--表操作
local tableTmp = {1, 2, 3, 4, 5, 6, 7, 8, 9}
table.insert(tableTmp, 10)
print(table.concat(tableTmp, ", "))

--文件操作
local file = io.open("Test.txt", "r")
local content = file:read("*a")
file:close()
print(content)
