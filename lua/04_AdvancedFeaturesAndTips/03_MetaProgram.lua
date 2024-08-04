--[[
    03_元编程练习，学习参考链接为 https://blog.csdn.net/wangshuai6707/article/details/132403666
    备注：
        元编程是指编写能够操作和生成代码的代码。
        在Lua中，可以使用加载和执行字符串、动态创建函数和修改函数等技术实现元编程。
        元编程在动态配置、代码生成和运行时扩展等领域具有广泛的应用。
        元编程技术可以通过在运行时生成和修改代码来实现动态和灵活的行为，为应用程序提供更大的自定义能力。
--]]

--动态创建函数
local funcStr = "return function(a,b) return a + b end"
local dynamicFunc = load(funcStr)()

--调用动态创建的函数
local result = dynamicFunc(3, 4)
print(result)
