.586P
.MODEL FLAT, STDCALL
includelib kernel32.lib

ExitProcess PROTO : DWORD
MessageBoxA PROTO : DWORD, : DWORD, : DWORD, : DWORD

stackCheck	PROTO

.STACK 4096

.CONST

.DATA

	MB_OK EQU 0
	STR1  DB "Точило О.В. 2 курс 4 группа", 0
	STR2  DB "0", 0
	HW	  DD ?

	myBytes		DB 10h, 20h, 30h, 40h
	myWords		DW 8Ah, 3Bh, 44h, 5Fh, 99h
	myDoubles	DD 1, 2, 3, 4, 5, 6
	myPointer	DD myDoubles

	n			DD 7
	array		DD 1, 2, 0, 4, 5, 6, 7

	char1 DB "( 2 4", 0
	bool1 DB 1
	char2 DB "qwerty", 0

.CODE

main PROC
	
	PUSH	1
	PUSH	2
	PUSH	3

	INVOKE	stackCheck
	POP		EAX
	POP		EAX
	POP		EAX

	mov EBX, myPointer
	mov EAX, [EBX + 4]
	mov EDX, [EBX + 8]

	mov EAX, 0
	mov ESI, 0
	mov EDX, 0
	mov ECX, n

	cycle:
	mov EDX, [array + ESI]
	add EAX, EDX
	add ESI, 4
	loop cycle

	mov ESI, 0
	mov EDX, 0
	mov EBX, 0
	mov ECX, n
	cycle1:
	cmp EDX, [array + ESI]
	jz inv0ke
	add ESI, 4
	loop cycle1
	mov EBX, 1

	add STR2, BL
	inv0ke:
	INVOKE MessageBoxA, HW, OFFSET STR2, OFFSET STR1, MB_OK


	push -1
	call ExitProcess
main ENDP

stackCheck PROC, 

	POP		EAX
	POP		EAX
	POP		EAX

	MOV		EAX, 10h
	RET

stackCheck ENDP

end main