.586

.MODEL FLAT, STDCALL

includelib SE_asm01d.lib
includelib libucrt.lib

EXTERN getmin : PROC
EXTERN getmax : PROC
SetConsoleTitleA	PROTO : DWORD
GetStdHandle		PROTO : DWORD
WriteConsoleA		PROTO : DWORD, : DWORD, : DWORD, : DWORD, : DWORD
;system				PROTO C : DWORD
intTOString			PROTO : DWORD, : DWORD

.CONST

	CNSLTTL		DB "Getmin + getmax", 0
	STR_PAUSE	DB "pause", 0

.DATA

	cnslhndl	DD 0
	arrayA		DD 1, 1, 5, 7, 9, 1, 1, 6, 8, -10
	lengthA		DD LENGTHOF arrayA
	strInt		DB 0, 0, 0, 0, 0
	intLength	DB LENGTHOF strInt
	outStr		DB "getmax + getmin = 00000", 10, 0
	intStrStart DD OFFSET outStr + 18
	min			DD 0
	max			DD 0
	testStr		BYTE 6, "qwerty"
	testStr2	BYTE 256 DUP(0)
	testStr_OFFSET DWORD OFFSET testStr


.CODE

main PROC
	
	MOV			ECX, 0
	MOV			ECX, testStr_OFFSET[0]
	MOV			CL, testStr[0]
	MOV			testStr2[0], CL

	PUSH		lengthA
	PUSH		OFFSET arrayA
	CALL		getmin
	MOV			EBX, EAX
	PUSH		lengthA
	PUSH		OFFSET arrayA
	CALL		getmax
	ADD			EBX, EAX
	INVOKE		intToString, intStrStart, EBX
	PUSH		OFFSET CNSLTTL
	CALL		SetConsoleTitleA
	PUSH		-11
	CALL		GetStdHandle
	MOV			cnslhndl, EAX
	PUSH		0
	PUSH		0
	PUSH		SIZEOF outStr
	PUSH		OFFSET outStr
	PUSH		cnslhndl
	CALL		WriteConsoleA
	;INVOKE		system, OFFSET STR_PAUSE
	MOV			EAX, EAX		; ����� ���� ��� ����� �������� �������

main ENDP

intToString PROC uses EAX EBX ECX EDX ESI, destArray : DWORD, number : DWORD	; esi ��� �������,

	MOV			ESI, destArray	; eax ��� �����, edx ��� �������, ebx ��� ���������,
	MOV			EAX, number		; ecx ��� ��������
	MOV			EBX, 10
	MOV			CL, intLength
	MOV			CH, 0

	.IF (number > 7fffffffh)	; ���� �������������
		PUSH	ECX				; ��������� �������� ���������
		MOV		CL, "-"			; ��������� �� ������ ����� � ������� ���� "�����"
		MOV		[ESI], CL
		POP		ECX				; ������� �������� ���������
		MOV		CH, 1			; ������� ���� ����� ������������� �� �������� �� �������
		NEG		EAX				; ���������� �������������� ����� � ��������������
	.ENDIF

	.WHILE (EAX > 0 && CL > CH)
		MOV		EDX, 0			; ��������� ������� (�� ������ ������)
		CDQ						; ���������� ����-�� ��� � ����-�� ���, �������� ����� ������ ����� �����
		IDIV	EBX				; ������� � �������� ��� �� ���
		ADD		EDX, 48			; ��� ������ �����������
		PUSH	ECX				; ��������� �������� ���������
		AND		ECX, 000000FFH	; �� ����� �������� ������ ��������� ����
		ADD		ECX, -1
		MOV		[ESI + ECX], DL
		POP		ECX				; ������������ ���
		ADD		CL, -1; i++
	.ENDW
	RET

intToString ENDP

END main