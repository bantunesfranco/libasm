section .text
	global ft_list_size

bits 64
ft_list_size:
	xor rax, rax
	push rdi
	mov rdi, [rdi]

	.loop:
		cmp rdi, 0
		je .end
		inc rax
		mov rdi, [rdi + 8]
		jmp .loop

	.end:
		ret