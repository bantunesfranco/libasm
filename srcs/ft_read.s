section .text
	global ft_read
	extern __errno_location

bits 64
ft_read:
	
	; cmp rdx, 0					; check if 3rd arg is 0
	; jl .is_error				; if 3rd arg < 0, goto is_error

	xor rax, rax				; set rax to 0 (read syscall)
	syscall						; write() syscall
	cmp rax, 0					; if write < 0
	jl .set_errno				; goto set_errno
	ret

	.set_errno:
		mov rdi, rax			; save rax in rdi
		neg rdi					; res = -res

		call __errno_location	; error = &errno (gets address of errno)
		mov [rax], rdi			; *error = errno (sets errno value to address of errno)
		jmp .is_error

	.is_error:
		mov rax, -1				; res = -1
		ret						; return res