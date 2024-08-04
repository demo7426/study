--[[
    01_基础语法练习，学习参考链接为 https://blog.csdn.net/wangshuai6707/article/details/132403666
--]]

--基本数据类型
local str = "Hello world"       
local num = 42.63
local bool = false
local nilValue = nil

print(str)
print(num)
print(bool)
print(nilValue)

--[[
    变量赋值
--]]
local x = 10
x = x + 5

--条件语句
print()
if x > 10 then
    print("x is greater than 10")
elseif x < 10 then
    print("x is less than 10")
else
    print("x is equal to 10")
end

--循环语句
print()
for i = 1, x do
    print("For count: "..i)
end

local i = 1
print()
while i <= x do
    print("While count:"..i)
    i = i + 1
end

print()
repeat
    i = i - 1
    print("Repeat count: "..i)
until i == 1

