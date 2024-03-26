section .text
	global ft_list_size

bits 64
ft_list_size:					; int ft_list_size(t_list **begin_list);
	xor rax, rax				; len = 0
	push rdi					; save rdi
	mov rdi, [rdi]				; head = *begin_list

	.loop:
		cmp rdi, 0				; if (head == NULL)
		je .end					; goto end
		inc rax					; len++
		mov rdi, [rdi + 8]		; head = head->next
		jmp .loop				; while (head != NULL)

	.end:
		ret						; return len