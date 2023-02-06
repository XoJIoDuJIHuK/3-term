.586P
.MODEL FLAT, STDCALL
includelib kernel32.lib

ExitProcess PROTO : DWORD
MessageBoxA PROTO : DWORD, : DWORD, : DWORD, : DWORD

.STACK 4096

.CONST

.DATA
MB_OK		EQU 0
HW			DD ?
VAL1		EQU 3
VAL2		EQU 5
VAL_RESULT	EQU VAL1 + VAL2 + 48

STR1		DB "SE_Lab02", 0
STR2		DB "Результат сложения =  ", 0
STR3		DB "Результат сложения = ", VAL_RESULT, 0

.CODE

main PROC
START:
	
	mov STR2 + 21, VAL_RESULT
	INVOKE MessageBoxA, HW, OFFSET STR2, OFFSET STR1, MB_OK

	push - 1
	call ExitProcess
main ENDP

end main