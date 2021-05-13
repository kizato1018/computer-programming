include C:/irvine/IRVINE32.INC

.data
NROW BYTE ?				;列數
NCOL BYTE ?				;行數
ARDAT DWORD 100 DUP (?) ;陣列內容
ROWNO BYTE ?			;列號
COLNO BYTE ?			;行號

.code
main proc
	call readdec
	mov NROW, al
	call readdec
	mov NCOL, al
	mov bl, NROW
	mul bl
	movzx ecx, ax
	;call dumpregs
	mov edi, OFFSET ARDAT
RARDAT:
	call readdec
	mov DWORD PTR [edi], eax
	add edi, 4
	loop RARDAT

	call readdec
	mov ROWNO, al
	mul NCOL
	movzx ebx, ax
	call readdec
	and eax, 0ffh
	add ebx, eax

	mov edi, OFFSET ARDAT
	SHL ebx, 2
	add edi, ebx
	mov eax, [edi]
	call writedec
	exit

main endp
end main