section .text
	global ft_strdup
	extern ft_strcpy
	extern ft_strlen
	extern malloc
	extern __errno_location

bits 64
ft_strdup:

	push rdi					; save string in stack
	call ft_strlen				; len = ft_strlen(string)
	inc rax						; len++ for null terminator

	mov rdi, rax				; set 1st arg to len
	call malloc					; ptr = malloc(len)

	test rax, rax				; if ptr == NULL
	jnz .error					; goto error

	mov rdi, rax				; set 1st arg to ptr
	pop rsi						; set 2nd arg to string from stack

	call ft_strcpy				; newStr = ft_strcpy(ptr, string)
	ret							; return newStr

	.error:
		mov rdi, rax			; save return value in rdi
		neg rdi					; negate rdi for positive value

		call __errno_location	; error = &errno (gets address of errno)
		mov [rax], rdi			; *error = errno (sets errno value to address of errno)

		mov rax, -1				; ret = 1
		ret						; return ret
