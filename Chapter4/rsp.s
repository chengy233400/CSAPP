	.file	"rsp.c"
	.text
	.globl	checkRspValue
	.type	checkRspValue, @function
checkRspValue:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	
	movq %rsp,%rdi
	# pushq %rsp
	# popq %rdx
	# cmpq %rdx,%rax
	pushq %rsp
	# %rsp = %rsp - 8
	addq $8,%rsp
	cmpq %rsp,%rdi
	sete %al
	movzbq %al,%rax

	# popq %rsp
	movq %rdi,%rsp

	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	checkRspValue, .-checkRspValue
	.ident	"GCC: (Ubuntu 7.3.0-27ubuntu1~18.04) 7.3.0"
	.section	.note.GNU-stack,"",@progbits
