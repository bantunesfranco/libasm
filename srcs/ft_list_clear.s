section .text
	global ft_list_clear
	extern free

bits 64
ft_list_clear:					; int ft_list_clear(t_list **begin_list, void (*free_fct)(void *))

	push rdi
	push r8

	cmp rdi, 0					; if (begin_list == NULL)
	je .end						; return

	mov r8, [rdi]				; head = *begin_list

	.loop:
		cmp r8, 0				; if (*begin_list == NULL)
		je .end					; return

		push rsi

		mov rax, [r8 + 8]		; next = head->next
		push rax
		push r8
	
		mov rdi, [r8]			; tmp = head->data
		call rsi				; f(tmp)

		pop rdi
		call free				; free(head)

		pop r8
		pop rsi
		jmp .loop

	.end:
		pop r8
		pop rdi
		ret						; return len
