.586
.MODEL FLAT, STDCALL
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
	JLE		cycleEnd				;���� min � EAX ������ ���� ����� �������� �������, ���������� ������������
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
	JGE		cycleEnd				;���� max � EAX ������ ���� ����� �������� �������, ���������� ������������
	MOV		EAX, EBX
	cycleEnd:
	ADD		ESI, 4
	LOOP	cycleStart
	RET
getmax ENDP
END