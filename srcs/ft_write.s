section .text
	global ft_write

bits 64
ft_write:


	mov rax, 1
	syscall


	ret