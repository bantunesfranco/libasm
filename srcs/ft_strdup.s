section .text
	global ft_strdup
	extern ft_strcpy
	extern ft_strlen
	extern malloc
	extern __errno_location

bits 64
ft_strdup:

	cmp rdi, 0					; if str == NULL
	jz .error					; goto error

	push rdi					; save string in stack
	call ft_strlen				; len = ft_strlen(string)
	inc rax						; len++ for null terminator

	mov rdi, rax				; set 1st arg to len
	call malloc					; ptr = malloc(len)

	cmp rax, 0					; if ptr == NULL
	jz .error					; goto error

	mov rdi, rax				; set 1st arg to ptr
	pop rsi						; set 2nd arg to string from stack

	call ft_strcpy				; newStr = ft_strcpy(ptr, string)
	ret							; return newStr

	.error:
		xor rax, rax			; ret = NULL
		ret						; return ret
