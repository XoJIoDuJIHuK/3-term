.586

.MODEL FLAT, STDCALL

includelib Asm01a.lib
includelib ucrt.lib

intTOString			PROTO : DWORD, : DWORD
getmin				PROTO : DWORD, : DWORD
getmax				PROTO : DWORD, : DWORD
SetConsoleTitleA	PROTO : DWORD
GetStdHandle		PROTO : DWORD
WriteConsoleA		PROTO : DWORD, : DWORD, : DWORD, : DWORD, : DWORD
system				PROTO C : DWORD

.STACK 4096

.CONST

	CNSLTTL		DB "Getmin + getmax", 0
	STR_PAUSE	DB "pause", 0

.DATA

	cnslhndl	DD 0
	arrayA		DD 10, 13, 5, 7, 9, -30, 4, 6, 8, 10
	lengthA		DD LENGTHOF arrayA
	strInt		DB 0, 0, 0, 0, 0
	intLength	DB LENGTHOF strInt
	outStr		DB "getmax + getmin = 00000", 10, 0
	intStrStart DD OFFSET outStr + 18
	min			DD 0
	max			DD 0

.CODE

main PROC

	INVOKE		getmin, OFFSET arrayA, lengthA
	MOV			EBX, EAX
	INVOKE		getmax, OFFSET arrayA, lengthA
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
	INVOKE		system, OFFSET STR_PAUSE
	;INVOKE		printconsole, OFFSET outStr, OFFSET CNSLTTL
	MOV			EAX, EAX; чтобы было где точку останова ставить

main ENDP

intToString PROC uses EAX EBX ECX EDX ESI, destArray : DWORD, number : DWORD	; esi для массива,

	MOV			ESI, destArray	; eax для числа, edx для остатка, ebx для основания,
	MOV			EAX, number			; ecx для счётчика
	MOV			EBX, 10
	MOV			CL, intLength
	MOV			CH, 0

	.IF (number > 7fffffffh); если отрицательное
		PUSH	ECX; сохранить значение счётчиков
		MOV		CL, "-"; поместить на первое место в массиве знак "минус"
		MOV		[ESI], CL
		POP		ECX; вернуть значения счётчиков
		MOV		CH, 1; вставка цифр будет производиться до нулевого не включая
		NEG		EAX; приведение отрицательного числа к положительному
	.ENDIF

	.WHILE (EAX > 0 && CL > CH)
		MOV		EDX, 0; обнуление остатка (на всякий случай)
		CDQ; приведение чего-то там к чему-то там, прочитай перед сдачей ВАЖНО БЛЯТЬ
		IDIV	EBX; деление с остатком ЕАХ на ЕБХ
		ADD		EDX, 48; шоб символ распознался
		PUSH	ECX; сохранить значения счётчиков
		AND		ECX, 000000FFH; по маске оставить только последний байт
		ADD		ECX, -1
		MOV		[ESI + ECX], DL
		POP		ECX; восстановить ЕСХ
		ADD		CL, -1; i++
	.ENDW
	RET

intToString ENDP

END main