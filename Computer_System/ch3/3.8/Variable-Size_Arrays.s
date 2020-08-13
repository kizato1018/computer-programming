	.file	"Variable-Size_Arrays.c"
	.text
	.globl	var_prod_ele_opt
	.type	var_prod_ele_opt, @function
var_prod_ele_opt:
.LFB0:
	.cfi_startproc
	nop
	leaq	0(,%rdi,4), %r9 		;// 4n in %r9
	imulq	%r9, %rcx				;// 4n*i in %rcx
;//	leaq	0(,%rcx,4), %r10		;// 4n*i in %r10
	addq	%rcx, %rsi
	leaq	(%rdx,%r8,4), %rcx		;// B+4k in %rcx
	movl	$0, %edx				;// j = 0
	movl	$0, %eax				;// result = 0
.L3:
	movl	(%rsi,%rdx,4), %r8d		;// Read Arow[j]
	imull	(%rcx), %r8d				;// Multiply by *Bptr
	addl	%r8d, %eax				;// Add to result
	addq	%r9, %rcx				;// Bptr += n
	addq	$1, %rdx				;// j++
	cmpq	%rdx, %rdi				;// Compare j:n
	jg	.L3							;// If n > j, goto loop
	rep ret
	.cfi_endproc
.LFE0:
	.size	var_prod_ele_opt, .-var_prod_ele_opt
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
