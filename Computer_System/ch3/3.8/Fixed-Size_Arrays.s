	.file	"Fixed-Size_Arrays.c"
	.text
	.globl	fix_prod_ele_opt
	.type	fix_prod_ele_opt, @function
fix_prod_ele_opt:
.LFB0:
	.cfi_startproc
	salq	$6, %rdx
	addq	%rdx, %rdi
	leaq	(%rsi,%rcx, 4), %rcx
	leaq	1024(%rcx), %rsi
	movl	$0, %eax
.L2:
	movl	(%rdi), %edx
	imull	(%rdx), %edx
	addl	%edx, %eax
	addq	$4, %rdi
	addq	$64, %rcx
	cmpq	%rcx, %rsi
	jne	.L2
	rep ret
	.cfi_endproc
.LFE0:
	.size	fix_prod_ele_opt, .-fix_prod_ele_opt
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
