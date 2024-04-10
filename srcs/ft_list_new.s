section .text
	global ft_list_new
	extern malloc

bits 64
ft_list_new:				; t_list *ft_list_new(void *data)
	push rdi				; save data in the stack

	mov rdi, 16				; sizeof(t_list)
	call malloc				; ptr = malloc(16)
	cmp rax, 0				; if (ptr == NULL)
	pop rdi					; get data from the stack
	je .error				; goto error

	mov [rax], rdi			; ret->data = data
	mov qword [rax + 8], 0	; ret->next = NULL
	ret

	.error:
		xor rax, rax		; ret = NULL
		ret					; return ret