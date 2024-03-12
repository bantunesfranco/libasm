section .text
	global ft_strlen

bits 64
ft_strlen:
	xor rax, rax

	.loop:
		cmp byte [rdi + rax], byte 0
		je .end
		inc rax
		jmp .loop

	.end:
		ret
