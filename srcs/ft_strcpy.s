section .text
	global ft_strcpy

bits 64
ft_strcpy:						; char *ft_strcpy(char *dst, const char *src)
	xor rcx, rcx				; i = 0 

	.loop:
		mov dl, [rsi + rcx]		; c = src[i]
		mov [rdi + rcx], dl		; dst[i] = c

		test dl, dl				; if (c == 0)
		jz .end					; break

		inc rcx					; i++
		jmp .loop				; while (src[i])

	.end:
		mov rax, rdi			; ptr = dst
		ret						; return ptr
