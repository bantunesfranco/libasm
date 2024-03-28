section .text
	global ft_list_remove_if

bits 64
ft_list_remove_if:				; void	ft_list_remove_if(t_list **begin_list, void *data, int (*cmp)(), void (*f)(void *));

	push rdi
	push rsi
	mov rdi, [rdi]

	.loop:
		call [rdx]
		cmp rax, 0
		je .remove


	.remove:
		push [rdi+8]
		push rdi
		