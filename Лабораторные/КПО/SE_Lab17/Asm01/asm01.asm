.586
.MODEL FLAT, STDCALL
includelib kernel32.lib

getmin PROTO : DWORD, : DWORD

.STACK 4096

.CONST

.DATA

	arrayA DD 10, 13, 5, 7, 9, 3, 4, 6, 8, 10
	lengthA DD 0
	min DD 0

.CODE

getmin PROC uses EBX ECX EDX ESI, array : DWORD, lengthA : DWORD
	ADD		lengthA, -1
	MOV		EDX, array
	MOV		EAX, [EDX]
	MOV		ECX, lengthA
	MOV		ESI, 4
	cycleStart:
	MOV		EBX, [EDX + ESI]
	CMP		EAX, EBX
	JLE		cycleEnd				;если min в EAX меньше либо равно элементу массива, пропускаем присваивание
	MOV		EAX, EBX
	cycleEnd:
	ADD		ESI, 4
	LOOP	cycleStart
	RET
getmin ENDP
getmax PROC uses EBX ECX EDX ESI, array : DWORD, lengthA : DWORD
	ADD		lengthA, -1
	MOV		EDX, array
	MOV		EAX, [EDX]
	MOV		ECX, lengthA
	MOV		ESI, 4
	cycleStart:
	MOV		EBX, [EDX + ESI]
	CMP		EAX, EBX
	JGE		cycleEnd				;если max в EAX меньше либо равно элементу массива, пропускаем присваивание
	MOV		EAX, EBX
	cycleEnd:
	ADD		ESI, 4
	LOOP	cycleStart
	RET
getmax ENDP

main PROC
	MOV		lengthA, LENGTHOF arrayA
	INVOKE	getmin, OFFSET arrayA, lengthA
	MOV		min, EAX
main ENDP
end main