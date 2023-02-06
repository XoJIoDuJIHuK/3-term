.586P
.MODEL FLAT, STDCALL
includelib kernel32.lib
ExitProcess PROTO : DWORD
.STACK 4096
.CONST
.DATA
	char1 DB "( 2 4", 0
	bool1 DB 1
	char2 DB "qwerty", 0
	.CODE
main PROC
	push - 1
	call ExitProcess
main ENDP
end main