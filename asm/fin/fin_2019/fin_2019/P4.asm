include C:/irvine/IRVINE32.INC

.data
NROW BYTE ?				;�C��
NCOL BYTE ?				;���
ARDAT DWORD 100 DUP (?) ;�}�C���e
ROWNO BYTE ?			;�C��
COLNO BYTE ?			;�渹

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