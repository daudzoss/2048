	global	logbase2
	segment	.text
logbase2:
	mov	rax,-1
	bsr	rax,rdi
	ret

