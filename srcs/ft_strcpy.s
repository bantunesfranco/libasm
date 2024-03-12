section .text
	global ft_strcpy

bits 64
ft_strcpy:
	.loop:
		mov al, [rsi]
		test al, al
		jz .end

		mov [rdi], al

		inc rsi
		inc rdi
		jmp .loop

	.end:
		mov qword [rdi], 0
		mov rax, rdi
		ret
