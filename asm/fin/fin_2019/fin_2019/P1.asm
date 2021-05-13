include C:/irvine/IRVINE32.INC

.data
monthstr BYTE 5 dup(0)
wktb BYTE "janfebmaraprmayjunjulaugsepoctnovdec"

.code
main proc
	mov dx, 380h
	shr dx, 5
	and dx, 0fh
	dec dl
	mov eax, 3
	mul dl
	mov esi, OFFSET wktb
	add esi, eax
	mov edi, OFFSET monthstr
	mov ecx, 3
	cld
	rep movsb
	mov BYTE PTR [edi], 0

	mov edx, offset monthstr
	call writestring
	exit

	call dumpregs



main endp
end main