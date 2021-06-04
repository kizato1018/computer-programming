.386
.model flat,stdcall
.stack 4096
INCLUDE C:/irvine/IRVINE32.INC
ExitProcess proto,dwExitCode:dword

.data
str1 BYTE "輸入陣列元素個數：", 0
str2 BYTE "陣列1內容：", 0
str3 BYTE "陣列2內容：", 0
str4 BYTE "陣列1的和：", 0
str5 BYTE "陣列2的和：", 0
str6 BYTE "陣列1跟陣列2的和：", 0

arr1 SDWORD 10000 DUP (?)
arr2 SDWORD 10000 DUP (?)
len1 DWORD ?
len2 DWORD ?
sum1 SDWORD ?
sum2 SDWORD ?

.code
main proc
	mov edx, OFFSET str1
	call writestring
	mov esi, OFFSET arr1
	call readdec
	mov len1, eax
	mov ecx, eax
input1:
	call readint
	mov [esi], eax
	add esi, TYPE arr1
	loop input1

	mov edx, OFFSET str1
	call writestring
	mov esi, OFFSET arr2
	call readdec
	mov len2, eax
	mov ecx, eax

input2:
	call readint
	mov [esi], eax
	add esi, TYPE arr2
	loop input2
	
	mov esi, OFFSET arr1
	mov ecx, len1
	
	mov edx, OFFSET str2
	call writestring
	mov ebx, 0
output1:
	mov eax, [esi]
	add ebx, eax
	call writeint
	add esi, TYPE arr1
	loop output1
	call crlf
	mov sum1, ebx

	mov esi, OFFSET arr2
	mov ecx, len2
	
	mov edx, OFFSET str3
	call writestring
	mov ebx, 0
output2:
	mov eax, [esi]
	add ebx, eax
	call writeint
	add esi, TYPE arr2
	loop output2
	call crlf
	mov sum2, ebx

	;a[0]+a[2]+...+a[n]
	;b[0]+b[1]+...+b[n]
	mov edx, OFFSET str4
	call writestring
	mov eax, sum1
	call writeint
	call crlf
	mov edx, OFFSET str5
	call writestring
	mov eax, sum2
	call writeint
	call crlf


	;a[0]+b[0], a[1]+b[1], ... ,a[n]+b[n] (如果長度不一樣就補0)
	mov esi, OFFSET arr1
	mov edi, OFFSET arr2
	mov edx, OFFSET str6
	call writestring
	mov ecx, len1
	cmp	ecx, len2
	jae addition
	mov ecx, len2
addition:
	mov eax, [esi]
	add eax, [edi]
	add esi, TYPE arr1
	add edi, TYPE arr2
	call writeint
	loop addition

	invoke ExitProcess,0
main endp
end main