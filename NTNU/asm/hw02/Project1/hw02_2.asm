.386
.model flat,stdcall
.stack 4096
INCLUDE C:/irvine/IRVINE32.INC
ExitProcess proto,dwExitCode:dword

.data
t1 BYTE "�{��2", 0
str1 BYTE "��J�Q���ơG", 0
str2 BYTE "��J���ơG", 0
str3 BYTE "���סG", 0

buffer BYTE 10 DUP (?)
s1 BYTE 10 DUP (?)
s2 BYTE 10 DUP (?)
num1 SDWORD 0
num2 SDWORD 0
s1_len BYTE ?
s2_len BYTE ?

ans SDWORD 0

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
	loop ToDec2

	mov eax, num1  
	mov ebx, num2
	mul ebx
	mov ans, eax
	mov edx, OFFSET str3
	call WriteString
	call WriteDec



	invoke ExitProcess,0
main endp
end main