section .text
	global ft_atoi_base
	extern ft_strlen

bits 64
ft_atoi_base:								; int ft_atoi_base(char *str, char *base)

	push rdi								; save str

	mov rdi, rsi							; tmp = base
	call ft_strlen							; len = ft_strlen(tmp)
	cmp rax, 2								; if (len < 2)
	pop rdi									; restore str
	jl .error

	push rcx								; save rcx
	push r8
	xor rcx, rcx							; i = 0
	xor r8, r8								; j = 0

	.check_base_dup_loop1:
		cmp byte [rsi+rcx], 0				; while (base[i] != NULL)
		je .is_whitespace
		mov r8, rcx						; j = i
		inc r8								; j++

	.is_invalid:
		cmp byte [rsi+rcx], 9				; if (base[j] == '\t')
		je .base_error
		cmp byte [rsi+rcx], 10				; if (base[j] == '\n')
		je .base_error
		cmp byte [rsi+rcx], 11				; if (base[j] == '\v')
		je .base_error
		cmp byte [rsi+rcx], 12				; if (base[j] == '\f')
		je .base_error
		cmp byte [rsi+rcx], 13				; if (base[j] == '\r')
		je .base_error
		cmp byte [rsi+rcx], 32				; if (base[j] == ' ')
		je .base_error
		cmp byte [rsi+rcx], 43				; if (base[j] == '+')
		je .base_error
		cmp byte [rsi+rcx], 45				; if (base[j] == '-')
		je .base_error

	.check_base_dup_loop2:
		cmp byte [rsi+r8], 0				; while (base[j] != NULL)
		jz .check_base_dup_end2

		mov al, byte [rsi+rcx]				; tmp = base[i] (al is lower 8 bits of rax)
		cmp al, byte [rsi+r8]				; if (tmp == base[j])
		je .base_error

		inc r8								; j++
		jmp .check_base_dup_loop2

	.check_base_dup_end2:
		inc rcx								; i++
		jmp .check_base_dup_loop1

	.is_whitespace:
		cmp byte [rdi], 32						; if (str[i] <= ' ') (whitespace or non-printable character)
		jle .skip_whitespace

	xor r8, r8								; multiplier = 1 (bit set to 0)
	; sub rsp, 8								; reserve 4 bytes for multiplier count
	; mov dword [rsp], 0						; multiplier count = 0

	jmp .get_multiplier						; goto get_multiplier

	.skip_whitespace:
		inc rdi								; str++
		jmp .is_whitespace					; goto is_whitespace

	.is_minus:
		xor r8, 1							; multiplier = -multiplier (0 xor 1 = 1) (1 xor 1 = 0) (bit set to 1, mult = -1)

	.is_plus:
		; mov dword [rsp], 1					; multiplier count++
		inc rdi								; str++

	.get_multiplier:
		; cmp dword [rsp], 1					; if (multiplier count != 0)
		; jg .multiplier_error

		cmp byte [rdi], 43					; if (str[i] == '+')
		je .is_plus							; goto is_plus
	
		cmp byte [rdi], 45					; if (str[i] == '-')
		je .is_minus						; goto is_minus
	
	; add rsp, 8								; restore stack

	.atoi_start:
		push r9
		xor rax, rax						; res = 0

	.atoi_loop:
		cmp byte [rdi], 0					; while (str[i] != NULL)
		je .atoi_end

		push rax
		xor r9, r9							; i = 0

	.find_base_value:
		cmp byte [rsi+r9], 0				; while (base[i] != NULL)
		je .input_error
	
		mov al, byte [rdi]
		cmp al, byte [rsi+r9]
		je .calc_value
		inc r9
		jne .find_base_value

	.calc_value:
		pop rax
		imul rax, rcx						; res *= len
		add rax, r9							; res += i
		inc rdi								; str++
		jmp .atoi_loop

	.atoi_end:
		pop r9
		cmp r8, 0							; if (multiplier == 0)
		pop r8
		pop rcx
		jne .sign 							; goto sign
		ret

	.sign:
		imul rax, -1						; res *= multiplier
		ret

	.input_error:
		pop rax
		pop r9
		pop r8
		pop rcx
		jmp .error

	; .multiplier_error:
	; 	add rsp, 8							; restore stack
	; 	pop r8
	; 	pop rcx
	; 	jmp .error

	.base_error:
		pop r8
		pop rcx								; restore len

	.error:
		xor rax, rax						; res = 0
		ret									; return (res)
