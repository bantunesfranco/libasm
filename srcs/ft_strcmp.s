section .text
	global ft_strcmp

bits 64
ft_strcmp:
	xor rax, rax

	.loop:
		mov al, byte [rdi]
		mov ah, byte [rsi]

		cmp al, ah
		jne .not_equal

		test al, ah
		jz .end

		inc rsi
		inc rdi
		jmp .loop

	.not_equal:
		sub al, ah
		js .negative
		movzx rax, al
		jmp .end

	.negative:
		movsx rax, al
		jmp .end

	.end:
		ret