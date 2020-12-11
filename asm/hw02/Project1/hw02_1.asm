.386
.model flat,stdcall
.stack 4096
INCLUDE C:/irvine/IRVINE32.INC
ExitProcess proto,dwExitCode:dword

.data
t1 BYTE "程式1", 0
str1 BYTE "輸入被乘數：", 0
str2 BYTE "輸入乘數：", 0
str3 BYTE "答案：", 0

buffer BYTE 10 DUP (?)
s1 BYTE 10 DUP (?)
s2 BYTE 10 DUP (?)
num1 SDWORD 0
num2 SDWORD 0
s1_len BYTE ?
s2_len BYTE ?


ans SDWORD ?
ans_len BYTE 0
ans_s BYTE 10 DUP (?)

.code
main proc
	mov edx, OFFSET t1
	call WriteString
	call CRLF
	mov edx, OFFSET str1
	call WriteString
	mov edx, OFFSET s1
	mov ecx, 6
	call ReadString
	mov s1_len, al
	mov edx, OFFSET str2
	call WriteString
	mov edx, OFFSET s2
	mov ecx, 6
	call ReadString
	mov s2_len, al
	
	movzx ecx, s1_len
	mov esi, OFFSET s1
ToDec1:
	mov eax, num1
	imul eax, 10
	mov num1, eax
	movzx eax, BYTE PTR [esi]
	sub eax, 48
	add num1, eax
	inc esi
	;mov eax, num1
	;call WriteDec
	;call CRLF
	loop ToDec1
	movzx ecx, s2_len
	mov esi, OFFSET s2
ToDec2:
	mov eax, num2
	imul eax, 10
	mov num2, eax
	movzx eax, BYTE PTR [esi]
	sub eax, 30h
	add num2, eax
	inc esi
	;mov eax, num2
	;call WriteDec
	;call CRLF
	loop ToDec2
	mov eax, 0
	mov ebx, num1
	mov edx, num2
BinMul:
	test edx, 1
	jz next
	add eax, ebx
next:
	shl ebx, 1
	shr edx, 1
	jnz BinMul

	mov ans, eax
	;call WriteDec
	;call CRLF

	mov	esi, 0
	mov ebx, 10
ToStr:
	mov edx, 0
	div ebx
	add edx, 30h
	mov ans_s[esi], dl
	inc esi
	test eax, eax
	jnz ToStr

	mov eax, esi
	mov ebx, 2
	mov edx, 0
	div ebx
	mov ecx, eax
	mov edi, 0
	dec esi
RevStr:
	movzx eax, ans_s[esi]
	movzx ebx, ans_s[edi]
	xchg eax, ebx
	mov ans_s[esi], al
	mov ans_s[edi], bl
	dec esi
	inc edi
	loop RevStr

	mov edx, OFFSET str3
	call WriteString
	mov edx, OFFSET ans_s
	call WriteString




	invoke ExitProcess,0
main endp
end main