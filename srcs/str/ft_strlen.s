section .text
	global ft_strlen

bits 64
ft_strlen:
	push rbp
	mov rbp, rsp
	mov rax, 0
	.loop:
		cmp BYTE [rdi + rax], BYTE 0
		je .end
		inc rax
		jmp .loop
	.end:
		mov rsp, rbp
		pop rbp
		ret
