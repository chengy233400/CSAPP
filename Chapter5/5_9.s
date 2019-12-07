	.file	"5_9.c"
	.text
	.globl	merge
	.type	merge, @function
merge:
.LFB0:
	.cfi_startproc
	testq	%rcx, %rcx
	jle	.L13
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	movl	$0, %eax
	movl	$0, %r9d
	movl	$0, %r8d
	jmp	.L5
.L3:
	addq	$1, %r9
	movq	%r11, %r10
.L4:
	addq	$1, %rax
	movq	%rax, %r11
	movq	%r10, -8(%rdx,%rax,8)
	cmpq	%r9, %r8
	movq	%r9, %r10
	cmovge	%r8, %r10
	cmpq	%rcx, %r10
	jge	.L16
.L5:
	movq	(%rdi,%r8,8), %r10
	movq	(%rsi,%r9,8), %r11
	cmpq	%r11, %r10
	jge	.L3
	addq	$1, %r8
	jmp	.L4
.L16:
	cmpq	%rcx, %r8
	jge	.L6
	movq	%r8, %rbp
	movq	%rcx, %r10
	subq	%r8, %r10
	salq	$3, %r10
	leaq	(%rdi,%r8,8), %rbx
	leaq	(%rdx,%rax,8), %r8
	movl	$0, %eax
.L7:
	movq	(%rbx,%rax), %rdi
	movq	%rdi, (%r8,%rax)
	addq	$8, %rax
	cmpq	%r10, %rax
	jne	.L7
	leaq	(%rcx,%r11), %rax
	subq	%rbp, %rax
.L6:
	cmpq	%rcx, %r9
	jge	.L1
	subq	%r9, %rcx
	salq	$3, %rcx
	leaq	(%rsi,%r9,8), %rdi
	leaq	(%rdx,%rax,8), %rsi
	movl	$0, %eax
.L8:
	movq	(%rdi,%rax), %rdx
	movq	%rdx, (%rsi,%rax)
	addq	$8, %rax
	cmpq	%rcx, %rax
	jne	.L8
.L1:
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
.L13:
	.cfi_restore 3
	.cfi_restore 6
	rep ret
	.cfi_endproc
.LFE0:
	.size	merge, .-merge
	.ident	"GCC: (Ubuntu 7.3.0-27ubuntu1~18.04) 7.3.0"
	.section	.note.GNU-stack,"",@progbits
