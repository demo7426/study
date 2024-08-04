--[[
    01_闭包练习，学习参考链接为 https://blog.csdn.net/wangshuai6707/article/details/132403666
    备注：
        闭包是指一个函数以及与其相关的引用环境的组合。
        在Lua中，闭包可以捕获并访问其创建时的变量和状态。
        闭包在实际应用中常用于实现回调函数、函数工厂和状态管理等功能。
        闭包可以在函数内部创建并返回，从而保留了函数创建时的上下文信息和状态。
--]]

--创建闭包
function makeCounter()
    local counter = 0

    return function()
        counter = counter + 1
        return counter
    end
end

--使用闭包
local counter = makeCounter()

for i = 10, 14 do
    print(counter())
end

