section .text
	global ft_list_remove_if
	extern free

bits 64
ft_list_remove_if:			; void	ft_list_remove_if(t_list **begin_list, void *data, int (*cmp)(), void (*f)(void *));


	mov r8, [rdi]			; head = *begin_list
	push rdi
	xor r9, r9				; prev = NULL

	.loop:
		cmp r8, 0			; if (head == NULL)
		je .end				; goto end

		mov rdi, [r8]		; tmp = head->data
		call rdx			; res = cmp(head->data, data)
		cmp rax, 0			; if (res == 0)
		je .remove			; goto remove

		mov r9, r8			; prev = head
		mov r8, [r8 + 8]	; head = head->next
		jmp .loop			; goto loop

	.remove:
		cmp r9, 0			; if (prev == NULL)
		je .remove_head		; goto remove_head
		jne .remove_mid		; else goto remove_mid

	.remove_head:
		; mov rdi, [r8]		; tmp = head->data
		call rcx			; f(tmp)

		mov rdi, r8			; tmp = head
		mov r8, [r8 + 8]	; head = head->next
		call free			; free(tmp)

		pop rdi				; get begin_list ptr
		mov [rdi], r8		; *begin_list = head
		push rdi			; save begin_list ptr

		jmp .loop			; goto loop

	.remove_mid:
		; mov rdi, [r8]		; tmp = head->data
		call rcx			; f(tmp)

		mov rdi, r8			; tmp = head
		mov r8, [r8 + 8]	; head = head->next
		call free			; free(tmp)

		mov [r9 + 8], r8	; prev->next = head

		jmp .loop			; goto loop

	.end:
		pop rdi
		ret