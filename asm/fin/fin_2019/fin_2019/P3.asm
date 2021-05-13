include C:/irvine/IRVINE32.INC

.data
AUGEND BYTE 4 DUP(?)
ADDEND BYTE 4 DUP (?)
SUM BYTE 5 DUP (0)

.code
main proc
	call readhex
	mov DWORD PTR AUGEND, eax
	call readhex
	mov DWORD PTR ADDEND, eax

	mov ax, WORD PTR AUGEND
	add ax, WORD PTR ADDEND
	mov WORD PTR SUM, ax
	mov ax, WORD PTR AUGEND+2
	adc ax, WORD PTR ADDEND+2	;add with carry flag
	mov WORD PTR SUM+2, ax
	mov eax, 0
	adc al, 0
	mov SUM+4, al

	call writehex
	mov eax, DWORD PTR SUM
	call writehex
	call CRLF



main endp
end main