    .file   "variable_matrix.c"
    .text
    .globl	F1
	.type	F1, @function
F1:
.LFB0:
    leaq	0(,%rdi,4), %r9         ;// 4n in %r9
    imulq   %rdi, %rcx              ;// n*i in %r10
    leaq	0(,%rcx,4), %r10	    ;// put (4n*i) into %r10
    leaq    (%rdx, %r8, 4), %rcx    ;// *Bptr = &B[0][k] in %rcx
    movl    $0, %edx                ;// j = 0 in %rdx
    movl    $0, %eax                ;// result = 0 in %eax
.L1:
    movl    (%rsi, %rdx, 4), %r8d
    imull   (%rcx), %r8d
    addl    %r8d, %eax
    addq    $1, %rdx
    addq    %r9, %rcx
    cmpq    %rdi, %rdx
    jne     .L1
    ret
