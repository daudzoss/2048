nybmask	equ	0x0f0f0f0f0f0f0f0f
	section	.data
strings:
	db	"       ",0	;char strings[] = {"       ",
	db	"[   1] ",0	;                  "[   1] ",
	db	"[   2] ",0	;                  "[   2] ",
	db	"[   4] ",0	;                  "[   4] ",
	db	"[   8] ",0	;                  "[   8] ",
	db	"[  16] ",0	;                  "[  16] ",
	db	"[  32] ",0	;                  "[  32] ",
	db	"[  64] ",0	;                  "[  64] ",
	db	"[ 128] ",0	;                  "[ 128] ",
	db	"[ 256] ",0	;                  "[ 256] ",
	db	"[ 512] ",0	;                  "[ 512] ",
	db	"[1024] ",0	;                  "[1024] ",
	db	"[2048] ",0	;                  "[2048] ",
	db	"[2^12] ",0	;                  "[2^12] ",
	db	"[2^13] ",0	;                  "[2^13] ",
	db	"[2^14] ",0	;                  "[2^14] ",
	db	"[2^15] ",0	;                  "[2^15] "};

	section	.text
	global	print4x4
	extern	puts
print4x4:
	push	rbp		;void print4x4(uint64_t rdi) {
	mov	rbp,rsp		;
	lea	rsp,[rsp-32]	; auto
	mov	[rsp+0],rbx	;
	mov	[rsp+8],r12	;
	
	lea	rsi,[rsp+16]	;  uint8_t rsi[16];
	mov	rcx,nybmask	;
	mov	rax,rdi		; // put pre-located tiles into rows 0,1
	and	rax,rcx		; for (int i = 0; i < 8; i++)
	mov	[rsi+0],rax	;  rsi[i] = (rdi >> (i*8)) & 0x0f;
	shr	rdi,4		; // put interleaved tiles into rows 2,3
	and	rdi,rcx		; for (int i = 0; i < 8; i++)
	mov	[rsi+8],rdi	;  rsi[i+8] = ((rdi>>4) >> (i*8)) & 0x0f;

.L1print4x4:
	mov	ebx,[rsi]	; for (int i = 0; i < 4; i++) {
.L2print4x4:
	xor	rax,rax		;  for (int j = 0; j < 4; j++) {
	mov	al,bl		;
	mov	rdi,strings	;
	lea	rdi,[rdi+4*rax]	;
	mov	r12,rsi		;
	call	puts		;   puts(strings[rsi[i*4+j]]);
	mov	rsi,r12		;
	mov	cl,0xff		;
	shrd	ebx,ecx,8	;
	mov	eax,ebx		;
	inc	eax		;
	jnz	.L2print4x4	;  }
	lea	rsi,[rsi+4]	;
	cmp	rsi,rbp		;
	jne	.L1print4x4	; }
	mov	rbx,[rsp+0]	;
	mov	r12,[rsp+8]	;
	mov	rsp,rbp		;
	pop	rbp		;
	ret			;}

%if 1
%macro	bextr	3
	mov	%1,%2
	shr	%1,%3&0x3f
	and	%1,(1<<(%3>>8))-1
%endmacro
%macro	cmovne	2
	jne	%%equal
	mov	%1,%2
%%equal:	
%endmacro
%endif
	
	global	empties
empties:
	push	rbp		;uint64_t empties(uint64_t rdi) {
	mov	rbp,rsp		; uint64_t a = 0x0000000000000000;
	xor	rax,rax		;
	xor	eax,eax		; for (i = 0; i < 0x10; i++) {
%assign f 0x400
%rep 16
	bextr	rsi,rdi,f	;  // determine whether the cell is clear (1)
	setz	cl		;  uint8_t c = (rdi & (0xf << (4*i))) ? 0 : 1;
	add	cl,al		;
	xor	dl,dl		;  // cl == 1+al if clear, cl == al if not clear
	cmp	cl,al		;  uint8_t d = (rdi & (0xf << (4*i))) ? 0 :0xf0;
	cmovne	dx,0x00f0	;
	or	dl,cl		;  // shift in either 0 or f, append new count
	shl	rax,4		;  a = (a << 4) | (c ? 0xf0 : 0) | ((a+c)&0xf);
	mov	al,dl		; } // will remain all zero if truly full
%assign f f+4
%endrep
	pop	rbp		; return a; // empty nybbles mask:count of empty
	ret			;} // or 0xfffffffffffffff0 if all empty (error)
				;  // or 0xffffffffffffffff if only cell 0 empty
