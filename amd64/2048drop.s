	global	efields,dropnew
efields:
	mov	rdx,0xf0	;uint64_t efields(uint64_t rdi) {
	xor	cl,cl		; uint8_t cl = 0;
%rep 15
	mov	rax,rdx		; uint64_t rdx;
	shl	rdx,4		; for (rdx = 0xf0; rdx; rdx <<= 4) {
	and	rax,rdi		;  cl += (rdi & rdx) ? 1 : 0;
	csetnz	ax		; }
	add	cl,al		; rdx = 0xf;
%endrep
	sub	cx,di		; if (c < (rdi & 0xf))
	shrd	rdi,8,rcx	;
	mov	rax,rdi		;
	ret			;}

dropnew:
	push	rbp
	mov	rbp,rsp
	lea	rsp,[rsp-16]
	mov	[rsp+0],rbx

	mov	rbx,rdi
	call	empties
	xor	rdi,rdi
	or	rdi,rax
	jz	.Lcantdrop

	call	efields
	xor	rcx,rcx
%rep	16
	xor	rcx,rbx
	ror	rbx,4
%endrep
	mov	rdi,0x5555555555555555
	ror	rdi,rcx
	and	rdi,6
	and	rcx,0x3c

	mov	rdx,rax
.Lfindemp
	mov	rax,rdx
	ror	rdi,4
	and	rax,rdi
	jz	.Lfindemp

.Lcantdrop:
	or	rax,rbx
	mov	rbx,[rsp+0]
	mov	rsp,rbp
	pop	rbp
	ret

