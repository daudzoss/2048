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
	push	rbp		;void print4x4(register uint64_t di) {
	mov	rbp,rsp		;
	lea	rsp,[rsp-32]	; auto uint8_t tile[16];
	lea	rsi,[rsp+16]	; register uint64_t* si = tile;
	mov	[rsp+8],r12	; di = (di&(0xff<<56)>>56) | (di&(0xff<<48)>>40)
	mov	[rsp+0],rbx	;      |(di&(0xff<<40)>>24) | (di&(0xff<<32)>>8)
	mov	rcx,nybmask	;      |(di&(0xff<<24)<<8) | (di&(0xff<<16)<<24)
	bswap	rdi		;      |(di&(0xff<<8)<<40) | (di&(0xff<<0)<<56);
	mov	rax,rdi		; // put pre-located tiles into rows 2,3
	and	rax,rcx		; for (int i = 0; i < 8; i++)
	mov	[rsi+8],rax	;  si[i+8] = (di >> (i*8)) & 0x0f;
	shr	rdi,4		; // put interleaved tiles into rows 0,1
	and	rdi,rcx		; for (int i = 0; i < 8; i++)
	mov	[rsi+0],rdi	;  si[i+0] = ((di>>4) >> (i*8)) & 0x0f;

.L1print4x4:
	mov	ebx,[rsi]	; for (int i = 0; i < 4; i++) {
.L2print4x4:
	xor	rax,rax		;  for (int j = 0; j < 4; j++) {
	mov	al,bl		;
	mov	r12,rsi		;
	lea	rdi,[rel values];
	lea	rdi,[rdi+8*rax]	;
	mov	al,0		;
	call	printf		;   printf("%s", values[si[i*4+j]]);
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
	ret			;} // print4x4()

	global	move
move:	
	push	rbp		;register uint64_t move(register uint8_t di,
	mov	rbp,rsp		;                       register uint64_t si) {
	lea	rsp,[rsp-32]	;
	mov	[rsp+0],r12	;
	mov	[rsp+8],r13	;
	mov	[rsp+16],r14	;
	mov	[rsp+24],r15	; register r12d, r13d, r14d, r15d; // 4 32b rows
	
	mov	rax,nybmask	; register uint64_t a = 0xf0f0f0f0f0f0f0f0;
	mov	rcx,rsi		; register uint64_t c, d
	shr	rdx,4		; // upper two rows:
	and	rcx,rax		; c = si & a;
	mov	rdx,rsi		; // lower two rows:
	and	rdx,rax		; d = si & (a>>4);
	shld	r12,rcx,32	; r12d = 0x00000000ffffffff & (rcx >> 32); //top
	mov	r13,rcx		; r13d = 0x00000000ffffffff & rcx;
	shld	r14,rdx,32	; r14d = 0x00000000ffffffff & (rdx >> 32);
	mov	r15,rdx		; r15d = 0x00000000ffffffff & rdx;         //bot

	mov	rax,rsi		; register uint64_t a = si; // default rtn value

	cmp	rdi,tilt_l	; switch (di) {
	jne	.Lr		;  case tilt_l: // first bias left
%assign i 12
%rep 4
	mov	eax,0xff000000	;
%assign j 0	
%rep 4
%assign k 0
%rep 4-j
	mov	ecx,r %+ i %+ d	;
	shl	ecx,8		;
	mov	edx,eax		;
	and	edx,r %+ i %+ d	;
	cmovnz	r %+ i %+ d,ecx	;
%assign k k+1
%endrep
	ror	eax,8		;
%assign j j+1
%endrep
%assign i i+1
%endrep

.Lr:
	cmp	rdi,tilt_r	;
	jne	.Ld		;  case tilt_r:
	


.Ld:
	cmp	rdi,tilt_d	; } switch (di) {
	jne	.Lu		;  case tilt_d:
	
.Lu:
	cmp	rdi,tilt_u	;
	jne	.Lbad		;  case tilt_u:

.Lbad:
	mov	r12,[rsp+0]	;
	mov	r13,[rsp+8]	;
	mov	r14,[rsp+16]	;
	mov	r15,[rsp+24]	;
	mov	rsp,rbp		; }
	pop	rbp		; return a;
	ret			;}
	

	extern	empties
	global	anymove
anymove:
	push	rbp		;register uint64_t anymove(register uint8_t di)
	mov	rbp,rsp		;{
	lea	rsp,[rsp-16]	; register uint64_t a;

	mov	[rsp+0],rbx	;
;	mov	[rsp+8],r12	;
	mov	rbx,rdi		;
	
	call	empties		;
	or	rax,0		; if ((a = empties(di)) != 0)  
	jnz	.Lfound		;  return a; // board has empty cells

	mov	edi,tilt_l ;
	mov	rsi,rbx		;
	call	move		;
	xor	rax,rbx		; if ((a = move(tilt_l, di) ^ di) != 0)
	jne	.Lfound		;  return a; // tilting left results in change
	
	mov	edi,tilt_r	;
	mov	rsi,rbx		;
	call	move		;
	xor	rax,rbx		; else if ((a = move(tilt_r, di) ^ di) != 0)
	jne	.Lfound		;  return a;// tilting right results in change
	
	mov	edi,tilt_d	;
	mov	rsi,rbx		;
	call	move		;
	xor	rax,rbx		; else if ((a = move(tilt_d, di) ^ di) != 0)
	jne	.Lfound		;  return a; // tilting down results in change
	
	mov	edi,tilt_u	;
	mov	rsi,rbx		;
	call	move		;
	xor	rax,rbx		; else if ((a = move(tilt_u, di) ^ di) != 0)

.Lfound:
;	mov	r12,[rsp+8]	;
	mov	rbx,[rsp+0]	;  return a; // tilting up results in change
	mov	rsp,rbp		;
	pop	rbp		; return 0; // board is seized up, no moves left
	ret			;}

