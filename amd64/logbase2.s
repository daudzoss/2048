;;; yasm -felf64 -gdwarf2 logbase2.s # slavishly loads rax (duh)
;;; nasm -felf64 -gdwarf logbase2.s # loads 63 into eax (correct)

	global	logbase2
	segment	.text
logbase2:
	push	rbp
	
	lzcnt	rdi,rdi
	mov	rax,63
	sub	rax,rdi
	
	pop	rbp
	ret

