%include "macrodef.s"

	section	.text
	global	empties
empties:
	push	rbp		;uint64_t empties(uint64_t rdi) {
	mov	rbp,rsp		; uint64_t a = 0x0000000000000000;
	xor	rax,rax		; for (i = 0; i < 0x10; i++) {
%assign f 0x400
%rep 16
	bextr	rsi,rdi,f	;  // determine whether the cell is clear (1)
	setz	cl		;  uint8_t c = (rdi & (0xf << (4*i))) ? 0 : 1;
	mov	dl,al		;
	and	dl,0x0f		;  // cl == 1+al if clear, cl == al if not clear
	add	cl,dl		;  uint8_t d = (rdi & (0xf << (4*i))) ? 0 :0xf0;
	cmp	cl,dl		;
	mov	dl,0		;
	mov	si,0x00f0	;
	cmovne	dx,si		;
	or	dl,cl		;  // shift in either 0 or f, append new count
	shl	rax,4		;  a = (a << 4) | (c ? 0xf0 : 0) | ((a+c)&0xf);
	mov	al,dl		; } // will remain all zero if truly full
%assign f f+4
%endrep
	mov	rsp,rbp		;
	pop	rbp		; return a; // empty nybbles mask:count of empty
	ret			;} // or 0xfffffffffffffff0 if all empty (error)
				;  // or 0xffffffffffffffff if only cell 0 full
				;  // or 0x0000000000000000 if grid is full
	global	efields
efields:
	mov	rdx,0xf0	;uint64_t efields(uint64_t rdi) { // 63:4,3:0
	xor	cl,cl		; uint8_t c = 0;
%rep 15
	mov	rax,rdx		; for (uint64_t rdx = 0xf0; rdx; rdx <<= 4)
	shl	rdx,4		;
	and	rax,rdi		;  // count empty nybbles above count nybble 3:0
	setnz	al		;
	add	cl,al		;  c += (rdi & rdx) ? 1 : 0;
%endrep
	sub	cx,di		; // if 15 empty nybbles masked (all 1) but the
	shrd	rdi,rcx,4	; // count in lower nybble is 0, grid is empty
	mov	rax,rdi		; return (((c<(rdi&0xf))?0xf:0)<<60) | (rdi>>4);
	ret			;}

	global	dropnew
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
	ror	rdi,cl
	and	rdi,6
	and	rcx,0x3c

	mov	rdx,rax
.Lfindemp:
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

