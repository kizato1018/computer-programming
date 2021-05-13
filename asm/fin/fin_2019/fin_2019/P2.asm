include C:/irvine/IRVINE32.INC

.data
TDATA BYTE "This is a book.", 0 
SCHAR BYTE 's'

.code
main proc
	mov edi, OFFSET TDATA
	mov al, SCHAR
	mov ecx, LENGTHOF TDATA-1
L1:
	repnz scasb
	jnz L2
	dec edi
	sub BYTE PTR [edi], 20h
	inc edi
	jmp L1
L2:
	mov edx, OFFSET TDATA
	call writestring



main endp
end main