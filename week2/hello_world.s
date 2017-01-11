	.file	"hello_world.c"
	.globl	OS_EVERYTHING_OKAY
	.bss
	.align 4
	.type	OS_EVERYTHING_OKAY, @object
	.size	OS_EVERYTHING_OKAY, 4
OS_EVERYTHING_OKAY:
	.zero	4
	.globl	OS_NOT_EVERYTHING_OKAY
	.data
	.align 4
	.type	OS_NOT_EVERYTHING_OKAY, @object
	.size	OS_NOT_EVERYTHING_OKAY, 4
OS_NOT_EVERYTHING_OKAY:
	.long	1
	.section	.rodata
.LC0:
	.string	"Hello world!"
	.text
	.globl	hello_world
	.type	hello_world, @function
hello_world:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$.LC0, %edi
	call	puts
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	hello_world, .-hello_world
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$0, %eax
	call	hello_world
	movl	OS_EVERYTHING_OKAY(%rip), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3"
	.section	.note.GNU-stack,"",@progbits
