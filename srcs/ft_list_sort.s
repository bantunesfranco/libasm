section .text
	global ft_list_sort

bits 64
ft_list_sort:					; int ft_list_sort(t_list *begin_list, int (*cmp)());

	xor rax, rax
	push r8
	push rdx
	push rsi
	push rdi

	mov r8, [rdi]				; head = *begin_list
	mov rdx, rsi				; save cmp in rdx

	cmp r8, 0					; if head == NULL
	je .end						; return

	.loop:
		mov rsi, [r8+8]			; next = head->next
		cmp rsi, 0				; while (next != NULL)
		je .reset				; reset loop

		mov rdi, [r8]			; data1 = head->data
		mov rsi , [rsi]			; data2 = next->data
		
		push rax				; save is_swap
		push rdx				; save cmp
		push r8					; save head
		push rsi				; save data2
		push rdi				; save data1
	
		call rdx				; res = cmp(data1, data2)
		movsxd rax, eax			; sign extend res

		pop rdi					; restore data1
		pop rsi					; restore data2
		pop r8					; restore head
		pop rdx					; restore cmp
	
		cmp rax, 0				; if (res <= 0)
		pop rax					; restore is_swap
		jle .next				; next iteration

		mov rax, 1				; is_swap = 1
		push rdi				; tmp1 = head->data
		push rsi				; tmp2 = next->data
		mov rsi, [r8+8]			; next = head->next
		pop qword [r8]			; head->data = tmp2
		pop qword [rsi]			; next->data = tmp1

	.next:
		mov r8, [r8+8]			; head = head->next
		jmp .loop				; next iteration

	.reset:
		cmp rax, 0				; if (is_swap == 0)
		je .end					; return
		xor rax, rax			; else is_swap = 0
		pop rdi					; restore begin_list
		mov r8, [rdi]			; head = *begin_list
		push rdi				; save begin_list
		jmp .loop				; restart loop

	.end:
		pop rdi					; restore begin_list
		pop rsi					; restore cmp
		pop rdx
		pop r8
		ret
