section .text
	global ft_list_push_front
	extern ft_create_elem

bits 64
ft_list_push_front: 			; void ft_list_push_front(t_list **begin_list, void *data)

	push rdi					; save begin_list (address)

	mov rdi, rsi				; set 1st arg to data
	call ft_create_elem			; node = ft_create_elem(data)

	cmp rax, 0					; if (node == NULL)
	je .error					; goto error

	pop rdi						; restore begin_list
	mov rsi, [rdi]				; tmp = *begin_list
	mov qword [rax + 8], qword rsi	; node->next = tmp
	mov qword [rdi] , rax		; *begin_list = node

	xor rax, rax				; clear rax
	ret							; return

	.error:
		pop rdi					; restore begin_list
		ret						; return


