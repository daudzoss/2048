%include "macrodef.s"

altern	equ	0x5555555555555555

	section	.text
	global	empties
empties:
	push	rbp		;register uint64_t empties(register uint64_t di)
	mov	rbp,rsp		;{register uint64_t a = 0x0000000000000000;
	xor	rax,rax		; for (int i = 0; i < 0x10; i++) {
%assign f 0x400
%rep 16
	bextr	rsi,rdi,f	;  // determine whether the cell is clear (1)
	setz	cl		;  uint8_t c = (di & (0xf << (4*i))) ? 0 : 1;
	mov	dl,al		;
	and	dl,0x0f		;  // c == 1+a if clear, c == a if not clear
	add	cl,dl		;  uint8_t d = (di & (0xf << (4*i))) ? 0 :0xf0;
	cmp	cl,dl		;
	mov	dl,0		;  // a=0xfffffffffffffff0 if all empty (error)
	mov	si,0x00f0	;  // a=0xffffffffffffffff if only cell 0 full
	cmovne	dx,si		;  // a=0x0000000000000000 if grid is full
	or	dl,cl		;
	shl	rax,4		;  // shift in either 0 or f, append new count
	mov	al,dl		;  a = (a << 4) | (c ? 0xf0 : 0) | ((a+c)&0xf);
%assign f f+4
%endrep
	mov	rsp,rbp		; } // will remain all zero if truly full
	pop	rbp		; return a; // empty nybbles mask:count of empty
	ret			;} // empties()

	global	efields
efields:
	mov	rdx,0xf0	;register uint64_t efields(register uint64_t di)
	xor	cl,cl		;{register uint8_t c = 0;
%rep 15
	mov	rax,rdx		; for (register uint64_t d = 0xf0; d; d <<= 4)
	shl	rdx,4		;
	and	rax,rdi		;  // count empty nybbles above count nybble 3:0
	setnz	al		;
	add	cl,al		;  c += (rdi & d) ? 1 : 0;
%endrep
	sub	cx,di		; // if 15 empty nybbles masked (all 1) but the
	shrd	rdi,rcx,4	; // count in lower nybble is 0, grid is empty
	mov	rax,rdi		; return (((c<(di&0xf)) ? 0xf:0)<<60) | (di>>4);
	ret			;} // efields()

	global	dropnew
dropnew:
	push	rbp		;register uint64_t dropnew(register uint64_t di)
	mov	rbp,rsp		;{
	lea	rsp,[rsp-16]	;
	mov	[rsp+0],rbx	;

	mov	rbx,rdi		; register uint64_t b = di;
	call	empties		;
	mov	rdi,rax		;//FIXME:empties(0x123456789abcdef0) is 1 not f1
	call	efields		; register uint64_t a = efields(empties(di));
	or	rax,0		;
	jz	.Lcantdrop	; if (a) { // grid has empty spaces

	xor	rcx,rcx		;  register uint64_t c = 0;
%rep	16
	xor	rcx,rbx		;  for (int i = 0; i < 16; i++)
	ror	rbx,4		;   c ^= (b = (b >> 4) | (b << 60)); // 16 xor
%endrep
	mov	rdi,altern	;  // c is random, or at least highly obfuscated
	shr	rdi,cl		;  di = 0x5555555555555555 >> c;
	and	rdi,3		;  di &= 3; // guaranteed to be 2=2^1 or 4=2^2
	and	cl,0x3c		;  c &= 0x3c; // guaranteed 0,4,8,12,16,..,56,60
	ror	rdi,cl		;  di = (di >> 4) | (di << 60);

	mov	rdx,rax		;  do { // rotate from random position to empty
.Lfindemp:
	mov	rax,rdx		;
	ror	rdi,4		;   di = (di >> 4) | (di << 60);
	and	rax,rdi		;   a &= di;
	jz	.Lfindemp	;  } while (a == 0);

.Lcantdrop:
	or	rax,rbx		;  return a | b; // add new cell to original
	mov	rbx,[rsp+0]	;
	mov	rsp,rbp		;
	pop	rbp		;
	ret			;} // dropnew()

