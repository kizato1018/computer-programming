	.file	"test.c"
	.text
	.globl	get
	.type	get, @function
get:
.LFB0:
	.cfi_startproc
	addq	$10, %rdi
	movq	%rdi, (%rsi)
	ret
	.cfi_endproc
.LFE0:
	.size	get, .-get
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
