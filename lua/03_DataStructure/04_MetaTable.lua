--[[
    04_元表和元方法练习，学习参考链接为 https://blog.csdn.net/wangshuai6707/article/details/132403666
--]]

--创建元表
local myMetaTable = {}

--定义元方法
myMetaTable.__add = function(a, b)
    return a[1] + b[1]
end

--定义表
local obj01 = { 10 }
local obj02 = { 20 }

--设置元表
setmetatable(obj01, myMetaTable)
setmetatable(obj02, myMetaTable)

--调用元方法
local result = obj01 + obj02
print(result)




