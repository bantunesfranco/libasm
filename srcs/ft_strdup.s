section .text
	global ft_strdup
	extern ft_strcpy
	extern ft_strlen
	extern malloc

bits 64
ft_strdup: ; rdi = str

	mov rsi, rdi

	call ft_strlen
	add rax, 1

	mov rdi, rax
	call malloc

	mov rdi, rax
	call ft_strcpy

	ret	


