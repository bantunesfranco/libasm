section .text
	global ft_strcmp

bits 64
ft_strcmp:
	xor rax, rax			; res = 0

	.loop:
		mov al, byte [rdi]	; c1 = *s1
		mov ah, byte [rsi]	; c2 = *s2

		cmp al, ah			; if (c1 != c2)
		jne .not_equal		; break

		test al, ah			; if (c1 == '\0' && c2 == '\0')
		jz .end				; break

		inc rsi				; s1++
		inc rdi				; s2++
		jmp .loop			; while (c1 == c2)

	.not_equal:
		sub al, ah			; diff = c1 - c2
		js .negative		; if (diff < 0)
		movzx rax, al		; res = diff (zero extended)
		ret					; return res

	.negative:
		movsx rax, al		; rax = diff (sign extended)
		ret
	
	.end:
		ret					; return res