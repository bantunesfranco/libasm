section .text
	global ft_list_sort

bits 64
ft_list_sort:					; int ft_list_sort(t_list *begin_list, int (*cmp)());
	push rdx
	push rdi
	xor rax, rax
	mov rdi, [rdi]
	mov rdx, rsi

	.loop:
		cmp rsi, 0
		je .reset

		mov rsi, [rdi+8]
		push rdx
		call rdx
		pop rdx

		cmp rax, 0
		jle .next

		mov rax, 1
		push qword [rdi]
		push qword [rsi]
		pop qword [rdi]
		pop qword [rsi]

	.next:
		mov rsi, rdi
		jmp .loop

	.reset:
		cmp rax, 0
		je .end
		xor rax, rax
		pop rdi
		push rdi
		mov rdi, [rdi]
		jmp .loop

	.end:
		pop rdi
		ret

	




