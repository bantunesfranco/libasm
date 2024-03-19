section .text
	global ft_strcpy

bits 64
ft_strcpy:
	xor rcx, rcx

	.loop:
		mov dl, [rsi + rcx]
		mov [rdi + rcx], dl

		test dl, dl
		jz .end

		inc rcx
		jmp .loop

	.end:
		mov rax, rdi
		ret
