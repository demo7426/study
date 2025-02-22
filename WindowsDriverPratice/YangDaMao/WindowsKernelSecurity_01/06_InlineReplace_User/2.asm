
extern MessageBoxA:PROC
extern MyTest:PROC

public MyFun

.code
	MyFun proc
		sub		rsp,20h
		mov		rax,MyTest
		call	rax
		add		rsp,20h
		ret
	MyFun endp
end
