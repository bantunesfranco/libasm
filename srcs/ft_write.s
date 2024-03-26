section .text
	global ft_write
	extern __errno_location

bits 64
ft_write:						; ssize_t ft_write(int fd, const void *buf, size_t count)

	mov rax, 1					; set rax to 1 (write syscall) 
	syscall						; write()
	cmp rax, 0					; if write() < 0
	jl .set_errno				; goto .set_errno
	ret							; return

	.set_errno:
		mov rdi, rax			; save rax in rdi
		neg rdi					; res = -res

		call __errno_location	; error = &errno (gets address of errno)
		mov [rax], rdi			; *error = errno (sets errno value to address of errno)
		jmp .is_error

	.is_error:
		mov rax, -1				; res = -1
		ret						; return res