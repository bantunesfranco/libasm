section .text
	global ft_read
	extern error

bits 64
ft_read:
	
	test rdx, rdx
	js .is_error

	xor rax, rax
	syscall
	; cmp rax, 0
	; jl .set_errno
	ret

	; .set_errno:
	; 	mov rdi, rax
	; 	call error
	; 	jmp .is_error

	.is_error:
		mov rax, -1
		ret