section .text
	global ft_list_new
	extern malloc
	extern __errno_location

bits 64
ft_list_new:
	push rdi

	mov rdi, 16
	call malloc
	cmp rax, 0
	je .error

	.error:
		xor rax, rax			; ret = NULL
		ret						; return ret