%include "macrodef.s"

nybmask	equ	0x0f0f0f0f0f0f0f0f
	
tilt_l	equ	0x02
tilt_r	equ	0xfe
tilt_d	equ	0x08
tilt_u	equ	0xf8
	
	section	.data
values:
	db	"       ",0	;char values[] = {"       ",
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
newrow:	
	db	10,0		;char newrow[] = {'\n', '\0'};
cout:
	db	"%c",0
strout:
	db	"%s",0
	
	section	.text
	global	print4x4
	extern	printf
print4x4:
	push	rbp		;void print4x4(uint64_t rdi) {
	mov	rbp,rsp		;
	lea	rsp,[rsp-32]	; auto
	lea	rsi,[rsp+16]	;  uint8_t rsi[16];
	mov	[rsp+8],r12	; rdi =(rdi&(0xff<<56)>>56)|(rdi&(0xff<<48)>>40)
	mov	[rsp+0],rbx	;      |(rdi&(0xff<<40)>>24)|(rdi&(0xff<<32)>>8)
	mov	rcx,nybmask	;      |(rdi&(0xff<<24)<<8)|(rdi&(0xff<<16)<<24)
	bswap	rdi		;      |(rdi&(0xff<<8)<<40)|(rdi&(0xff<<0)<<56);
	mov	rax,rdi		; // put pre-located tiles into rows 2,3
	and	rax,rcx		; for (int i = 0; i < 8; i++)
	mov	[rsi+8],rax	;  rsi[i+8] = (rdi >> (i*8)) & 0x0f;
	shr	rdi,4		; // put interleaved tiles into rows 0,1
	and	rdi,rcx		; for (int i = 0; i < 8; i++)
	mov	[rsi+0],rdi	;  rsi[i+0] = ((rdi>>4) >> (i*8)) & 0x0f;

.L1print4x4:
	mov	ebx,[rsi]	; for (int i = 0; i < 4; i++) {
.L2print4x4:
	xor	rax,rax		;  for (int j = 0; j < 4; j++) {
	mov	al,bl		;
	mov	r12,rsi		;
	lea	rdi,[rel values];
	lea	rdi,[rdi+8*rax]	;
	mov	al,0		;
	call	printf		;   printf("%s", values[rsi[i*4+j]]);
	mov	rsi,r12		;
	mov	cl,0xff		;
	shrd	ebx,ecx,8	;
	mov	eax,ebx		;
	inc	eax		;
	jnz	.L2print4x4	;  }
	mov	r12,rsi		;
	lea	rdi,[rel newrow];
	mov	al,0		;
	call	printf		;  printf("%c", '\n');
	mov	rsi,r12		;
	lea	rsi,[rsi+4]	;
	cmp	rsi,rbp		;
	jne	.L1print4x4	; }
	mov	rbx,[rsp+0]	;
	mov	r12,[rsp+8]	;
	mov	rsp,rbp		;
	pop	rbp		;
	ret			;}

	global	move
move:	
	push	rbp		;uint64_t move(uint8_t rdi, uint64_t rsi) {
	mov	rbp,rsp		;
	lea	rsp,[rsp-16]	; auto rsp[2]; // rcx and rdx backup
	
	mov	rax,nybmask	;
	mov	rcx,rsi		;
	shr	rdx,4		; // upper two rows:
	and	rcx,rax		; uint64_t rcx = (rsi & 0xf0f0f0f0f0f0f0f0)>>4;
	mov	[rsp+0],rcx	; rsp[0] = rcx;
	mov	rdx,rsi		; // lower two rows:
	and	rdx,rax		; uint64_t rdx = (rsi & 0x0f0f0f0f0f0f0f0f);
	mov	[rsp+8],rdx	; rsp[1] = rdx;

	mov	rax,rsi		; uint64_t rax = rsi; // default return value
	cmp	rdi,tilt_l	; switch (rdi) {
	jne	.Lr		;  case tilt_l: // first bias left
	
	mov	rax,0xf<<58	;
;	mov	rdx,
;	and	rax,rcx		;
	
	
;	cmov
;	xor

;	mov	rax,0x0f<<
	shr	rax,32		;
	xor	rax,rdx		;
	and	rax,0x0f000000	;
	
.Lr:
	cmp	rdi,tilt_r	;
	jne	.Ld		;  case tilt_r:

.Ld:
	cmp	rdi,tilt_d	;
	jne	.Lu		;  case tilt_d:
	
.Lu:
	cmp	rdi,tilt_u	;
	jne	.Lbad		;  case tilt_u:

.Lbad:
	mov	rsp,rbp		; }
	pop	rbp		; return rax;
	ret			;}
	

	extern	empties
	global	anymove
anymove:
	push	rbp		;uint64_t anymove(uint8_t rdi) {
	mov	rbp,rsp		;
	lea	rsp,[rsp-16]	; uint64_t rax;

	mov	[rsp+0],rbx	;
;	mov	[rsp+8],r12	;
	mov	rbx,rdi		;
	
	call	empties		;
	or	rax,0		; if ((rax = empties(rdi)) == 0)  
	jnz	.Lfound		;  return rax; // board has no empty cells

	mov	edi,tilt_l ;
	mov	rsi,rbx		;
	call	move		;
	xor	rax,rbx		; if ((rax = move(tilt_l, rdi) ^ rdi) != 0)
	jne	.Lfound		;  return rax; // tilting left results in change
	
	mov	edi,tilt_r	;
	mov	rsi,rbx		;
	call	move		;
	xor	rax,rbx		; if ((rax = move(tilt_r, rdi) ^ rdi) != 0)
	jne	.Lfound		;  return rax;// tilting right results in change
	
	mov	edi,tilt_d	;
	mov	rsi,rbx		;
	call	move		;
	xor	rax,rbx		; if ((rax = move(tilt_d, rdi) ^ rdi) != 0)
	jne	.Lfound		;  return rax; // tilting down results in change
	
	mov	edi,tilt_u	;
	mov	rsi,rbx		;
	call	move		;
	xor	rax,rbx		; if ((rax = move(tilt_u, rdi) ^ rdi) != 0)

.Lfound:
;	mov	r12,[rsp+8]	;
	mov	rbx,[rsp+0]	;  return rax; // tilting up results in change
	mov	rsp,rbp		;
	pop	rbp		; return 0;
	ret			;}

