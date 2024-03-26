section .text
	global ft_strlen

bits 64
ft_strlen:								; size_t ft_strlen(char *str)
	xor rax, rax						; i = 0

	.loop:
		cmp byte [rdi + rax], byte 0	; if (str[i] == '\0')
		je .end							; break
		inc rax							; i++
		jmp .loop						; while (str[i])

	.end:
		ret								; return i
