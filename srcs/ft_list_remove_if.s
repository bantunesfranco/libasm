section .text
	global ft_list_remove_if
	extern free

bits 64
ft_list_remove_if:			; void	ft_list_remove_if(t_list **begin_list, void *data, int (*cmp)(), void (*f)(void *));

	push r8
	push r9
	mov r8, [rdi]
	xor r9, r9

	.loop:
		cmp r8, 0
		je .end

		push rcx
		push rdx
		push rdi
		push r8
		push rsi
		push r9

		mov rdi, [r8]
		call rdx

		pop r9
		pop rsi
		pop r8
		pop rdi
		pop rdx
		pop rcx

		cmp rax, 0
		je .remove

		mov r9, r8
		mov r8, [r8 + 8]

		jmp .loop

	.remove:
		push r9
		push rdi
		push rsi
		push rcx
		push rdx

		cmp r9, 0
		je .remove_head
		jne .remove_middle

	.remove_head:
		mov rax, [r8 + 8]
		push rax
		push r8

		mov rdi, qword [r8]
		call rcx

		pop rdi
		call free

		pop r8
		pop rdx
		pop rcx
		pop rsi
		pop rdi
		pop r9

		mov [rdi], r8
		jmp .loop

	.remove_middle:
		mov rax, [r8 + 8]
		push rax
		push r8

		mov rdi, qword [r8]
		call rcx

		pop rdi
		call free

		pop r8
		pop rdx
		pop rcx
		pop rsi
		pop rdi
		pop r9

		mov [r9 + 8], r8
		jmp .loop

	.end:
		pop r8
		pop r9
		ret