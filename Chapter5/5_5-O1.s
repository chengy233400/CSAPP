/bin/bash: q: command not found
	.text
	.globl	poly
	.type	poly, @function
poly:
.LFB0:
	.cfi_startproc
	testq	%rsi, %rsi
	jle	.L2
	movl	$1, %eax
.L3:
	addq	$1, %rax
	cmpq	%rax, %rsi
	jge	.L3
.L2:
	rep ret
	.cfi_endproc
.LFE0:
	.size	poly, .-poly
	.ident	"GCC: (Ubuntu 7.3.0-27ubuntu1~18.04) 7.3.0"
	.section	.note.GNU-stack,"",@progbits
