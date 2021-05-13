include C:/irvine/IRVINE32.INC

.data
STUDENTS BYTE 100 DUP (10 DUP (?), 10 DUP (?), ?)
SNAME BYTE 10 DUP (?)
NOSTUD BYTE ?
SCORE BYTE 0
buffer BYTE 22 DUP (?)

.code
main proc
	call readdec
	mov NOSTUD, al
	movzx ecx, NOSTUD
	mov edx, OFFSET STUDENTS
READ:
	push ecx
	mov ecx, 20
	call readstring
	call readdec
	add edx, 20
	mov [edx], al
	inc edx
	pop ecx
	loop READ
	mov edx, OFFSET SNAME
	mov ecx, 10
	call readstring

	mov edi, OFFSET STUDENTS
	movzx ecx, NOSTUD
CHECK:
	push ecx
	mov ecx, 20
L5:
	mov al, [edi]
	call writechar
	inc edi
	loop L5

	mov al, [edi]
	call writedec
	inc edi
	call CRLF

	pop ecx
	loop CHECK
	mov edx, OFFSET SNAME
	mov ecx, 10
	call writestring
	call CRLF


	mov esi, OFFSET STUDENTS+10
	movzx ecx, NOSTUD
L1:
	call dumpregs
	push ecx
	push esi
	mov ecx, 10
	mov edi, OFFSET SNAME
	cld
	repz cmpsb
	call dumpregs
	jz L2
	pop esi
	add esi, 21
	pop ecx
	loop L1
	clc
	jmp L3
L2:
	stc
	call dumpregs
	movzx eax, BYTE PTR [esi]
	mov SCORE, al
	call writedec

L3:
	call dumpregs
	exit

main endp
end main