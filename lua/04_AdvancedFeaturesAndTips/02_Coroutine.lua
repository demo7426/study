--[[
    02_协程练习，学习参考链接为 https://blog.csdn.net/wangshuai6707/article/details/132403666
    备注：
        协程是一种轻量级的线程，可以在代码中实现协作式的多任务处理。
        在Lua中，可以使用coroutine.create创建协程，使用coroutine.resume来启动和恢复协程的执行。
        协程可以通过yield来暂停自己的执行，并通过resume从暂停的位置继续执行。
--]]

local coro = coroutine.create(
    function()
        for i = 1, 3 do
            print("coroutine"..i)
            coroutine.yield()
        end
    end
)

coroutine.resume(coro)
coroutine.resume(coro)
coroutine.resume(coro)



