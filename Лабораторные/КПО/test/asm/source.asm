.586

.MODEL FLAT, STDCALL

includelib libucrt.lib

fsq PROTO

.CONST

	

.DATA

	

.CODE

main PROC
	
	CALL fsq

main ENDP

fsq PROC

	MOV EAX, 10h
	RET

fsq ENDP

END main