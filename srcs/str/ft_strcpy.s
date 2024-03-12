section .text
	global ft_strcpy


bits 64
ft_strcpy:
	push rbp
	mov rbp, rsp

	lea rdi, [rsi]
	mov rax, rdi

	mov rsp, rbp
	pop rbp
	ret
