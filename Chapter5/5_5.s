	.file	"5_5.c"
	.text
	.globl	poly
	.type	poly, @function
poly:
.LFB0:
	.cfi_startproc
	movsd	(%rdi), %xmm2
	testq	%rsi, %rsi
	jle	.L1
	leaq	8(%rdi), %rax
	leaq	8(%rdi,%rsi,8), %rdx
	movapd	%xmm0, %xmm1
.L3:
	movapd	%xmm1, %xmm3
	mulsd	(%rax), %xmm3
	addsd	%xmm3, %xmm2
	mulsd	%xmm0, %xmm1
	addq	$8, %rax
	cmpq	%rdx, %rax
	jne	.L3
.L1:
	movapd	%xmm2, %xmm0
	ret
	.cfi_endproc
.LFE0:
	.size	poly, .-poly
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	movl	$0, %eax
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.3.0-27ubuntu1~18.04) 7.3.0"
	.section	.note.GNU-stack,"",@progbits
