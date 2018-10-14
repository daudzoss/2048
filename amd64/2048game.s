%include "macrodef.s"

nybmask	equ  0x0f0f0f0f0f0f0f0f	;const nybmask = 0x0f0f0f0f0f0f0f0f;
maindia	equ  0xf0000f0000f0000f	;const maindia = 0xf0000f0000f0000f;
	
tri0top	equ	0x34		;const tri_top[] = { 0x34,   // bit position
tri0bot	equ	0x1c		;                    0x2c,   // in quadword:
tri1top	equ	0x2c		;                    0x0c,   // * 0 2 5
tri1bot	equ	0x38		;                    0x24,   // * * 1 4
tri2top	equ	0x0c		;                    0x04,   // * * * 3
tri2bot	equ	0x30		;                    0x20 }; // * * * *
tri3top	equ	0x24		;const tri_bot[] = { 0x1c,   // bit position
tri3bot	equ	0x18		;                    0x38,   // in quadword:
tri4top	equ	0x04		;                    0x30,   // * * * *
tri4bot	equ	0x10		;                    0x18,   // 0 * * *
tri5top	equ	0x20		;                    0x10,   // 2 1 * *
tri5bot	equ	0x08		;                    0x08 }; // 5 4 3 *

tilt_r	equ	0x0001		;enum tiltdir { tilt_u = -2,   // bit 0 clear
tilt_l	equ	0xffff		;               tilt_l = -1,   // bit 0 set
tilt_d	equ	0x0002		;               tilt_r = +1,   // bit 0 set
tilt_u	equ	0xfffe		;               tilt_d = +2 }; // bit 0 clear

	section	.data
values:
	db	"       ",0	;char const* values[] = {"       ",
	db	"[   2] ",0	;                        "[   2] ",
	db	"[   4] ",0	;                        "[   4] ",
	db	"[   8] ",0	;                        "[   8] ",
	db	"[  16] ",0	;                        "[  16] ",
	db	"[  32] ",0	;                        "[  32] ",
	db	"[  64] ",0	;                        "[  64] ",
	db	"[ 128] ",0	;                        "[ 128] ",
	db	"[ 256] ",0	;                        "[ 256] ",
	db	"[ 512] ",0	;                        "[ 512] ",
	db	"[1024] ",0	;                        "[1024] ",
	db	"[2048] ",0	;                        "[2048] ",
	db	"[2^12] ",0	;                        "[2^12] ",
	db	"[2^13] ",0	;                        "[2^13] ",
	db	"[2^14] ",0	;                        "[2^14] ",
	db	"[2^15] ",0	;                        "[2^15] "};
newrow:	
	db	10,0		;const char newrow[] = "\n";
cout:
	db	"%c",0		;const char cout[] = "%c";
strout:
	db	"%s",0		;const char strout[] = "%s";
	
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
	xor	al,al		;
	call	printf		;   printf("%s", values[si[i*4+j]]);
	mov	rsi,r12		;
	mov	cl,0xff		;
	shrd	ebx,ecx,8	;
	mov	eax,ebx		;
	inc	eax		;
	jnz	.L2print4x4	;  }
	mov	r12,rsi		;
	lea	rdi,[rel newrow];
	xor	al,al		;
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

transpo:
	push	rbp		;register uint64_t transpo(register uint64_t di)
	mov	rbp,rsp		;{
	mov	rax,maindia	; register uint64_t a = 0xf0000f0000f0000f & di;
	and	rax,rdi		; for (int i = 0; i < 6; i++) {
%assign	i 0
%rep 6
%assign	width 4<<8
%assign	upp width|(tri %+ i %+ top)
%assign low width|(tri %+ i %+ bot)
	bextr	rdx,rdi,upp	;  register uint64_t d;
	shl	rdx,0x3f & low 	;  d = di & ((0xf<<(tri_top[i])) >> tri_top[i]);
	or	rax,rdx		;  a |= d << tri_bot[i];
	bextr	rdx,rdi,low	;
	shl	rdx,0x3f & upp	;  d = di & ((0xf<<(tri_bot[i])) >> tri_bot[i]);
	or	rax,rdx		;  a |= d << tri_top[i];
%assign	i i+1
%endrep
	mov	rsp,rbp		; }
	pop	rbp		; return a;
	ret			;} // transpo()
	
	global	gamewon
gamewon:
	push 	rbp		;register uint64_t gamewon(register uint64_t di,
	mov	rbp,rsp		;                          register uint64_t si)
	xor	rax,rax		;{register uint64_t a = 0;
	mov	rcx,0xf		; for (int i = 0; i < 64; i += 4) {
	and	rdi,rcx		; di &= 0x000000000000000f;//e.g. gamewon(11,x);
%assign	i 0
%rep 16
	mov	rdx,rcx		;
	and	rdx,rsi		;  register uint64_t c = (0xf << i);
	shr	rdx,i		;
	xor	r8,r8		;
	cmp	rdx,rdi		;
	cmovge	r8,rcx		;
	or	rax,r8		;  a |= (si & c >= di << i) ? c : 0;
	shl	rcx,4		; }
%assign i i+4
%endrep
	mov	rsp,rbp		;
	pop	rbp		; return a;
	ret			;} // gamewon()

	global	move
move:	
	push	rbp		;register uint64_t move(register uint8_t di,
	mov	rbp,rsp		;                       register uint64_t si) {
	mov	rax,nybmask	; register uint64_t a = 0xf0f0f0f0f0f0f0f, c, d;
	mov	rcx,rsi		; register uint64_t r[4];
	shr	rcx,4		; // upper two rows:
	and	rcx,rax		; c = (si >> 4) & a;
	mov	rdx,rsi		; // lower two rows:
	and	rdx,rax		; d = si & a;
	mov	rax,rsi		; a = si;// default return value is si unchanged

	shld	r8,rcx,32	; r[0] = 0x00000000ffffffff & (c >> 32);
	mov	r9,rcx		; r[1] = 0x00000000ffffffff & c;
	shld	r10,rdx,32	; r[2] = 0x00000000ffffffff & (d >> 32);
	mov	r11,rdx		; r[3] = 0x00000000ffffffff & d;
	cmp	di,tilt_d	; if (di > tilt_d) return a;
	jg	.Lbad		; switch (di) {
	jne	.Lu		;  case tilt_d:
	mov	rdi,rsi		;
	call	transpo		;
	mov	di,tilt_r	;
	mov	rsi,rax		;
	call	move		;
	mov	rdi,rax		;
	call	transpo		;   return transpo(move(tilt_r, transpo(si)));
	jmp	.Lbad		;
.Lu:
	cmp	di,tilt_u	;  case tilt_u:
	jne	.Lr		;
	mov	rdi,rsi		;
	call	transpo		;
	mov	di,tilt_l	;
	mov	rsi,rax		;
	call	move		;
	mov	rdi,rax		;
	call	transpo		;
	jmp	.Lbad		;   return transpo(move(tilt_l, transpo(si)));
.Lr:
	cmp	di,tilt_r	;
	jne	.Ll		;  case tilt_r: // perform a left-tilt but first
	bswap	r8d		;   for (int i = 0; i < 4; i++) // flip columns
	bswap	r9d		;    r[i] = (r[i] << 24) & 0xff000000 |
	bswap	r10d		;           (r[i] << 8)  & 0x00ff0000 |
	bswap	r11d		;           (r[i] >> 8)  & 0x0000ff00 |
	jmp	.L_l_r		;           (r[i] >> 24) & 0x000000ff;
.Ll:
	cmp	di,tilt_l	;
	jne	.Lbad		;  case tilt_l: // first bias left to remove 0s
.L_l_r:
%assign	i 8
%rep 4
	mov	edx,r %+ i %+ d	;   for (int i = 0; i < 4; i++) { // each row
%assign j 0
%rep 4
	mov	ecx,edx		;    d = r[i] & 0xffffffff; // working row copy
%rep 3-j
	shld	rcx,rdx,32	;    for (int j = 0; j < 4; j++) { // each col
	ror	rcx,32		;     for (int k = 0; k < 4-j; k++) // up to 4x
	rol	ecx,8		;      if (d & 0x00000000ff000000 == 0) // slide
	or	cl,0		;       d = ((d>>32)<<32) | ((d&0xffffffff)<<8);
	cmovz	rdx,rcx		;     d <<= 8; // preserve just-processed byte
%endrep
	shl	rdx,8		;    }

%assign j j+1
%endrep	
	shr	rdx,32		;    r[i] = d >> 32; // bias 32 bits right again
	mov	r %+ i,rdx	;   }
%assign i i+1
%endrep
	
	mov rsi,0xffffffffff000000 ;   for (int i = 8; i < 12; i++) // each row
%assign i 8
%rep 4
%assign j 0
%rep 3
	mov	rax,r %+ i	;    for (int j = 0; j < 3; j++) { // left 3 col
	sub	rax,rsi		;
	mov	ecx,esi		;
	and	ecx,r %+ i %+ d	;     c = r[i] & 0xff000000; // leftmost byte
	mov	edx,esi		;
	shr	edx,8		;
	and	edx,r %+ i %+ d	;     d = r[i] & 0x00ff0000; // next byte right
	cmovz	rax,r %+ i	;
	shl	edx,8		;     if (c == d << 8) {// coalesce them into 1,
	xor	ecx,edx		;      r[i] += 0x0000000100000000; // incr power
	cmovz	r %+ i,rax	;      r[i] = (0xffffffff00000000 & r[i]) |
	setz	cl		;            ((0x0000000000ffffff & r[i]) << 8);
	and	edx,esi		;
	setnz	dl		;
	and	cl,dl		;     }
	shl	cl,3		;
	shl	r %+ i,8	;     r[i] <<= 8;// preserve this processed byte
	mov	eax,r %+ i %+ d	;
	shl	eax,cl		;
	shl	rax,32		;
	shr	r %+ i,32	;
	shld	r %+ i,rax,32	;    }
%assign j j+1
%endrep
	shr	r %+ i,24;[sic]	;   r[i] >>= 24; // bias into low 32 bits, done
%assign i i+1
%endrep
	cmp	di,tilt_r	;   if (di == tilt_r)
	jne	.Lmoved		;    for (int i = 0; i < 4; i++) // de-flip cols
	bswap	r8d		;     r[i] = (r[i] << 24) & 0xff000000 |
	bswap	r9d		;            (r[i] << 8)  & 0x00ff0000 |
	bswap	r10d		;            (r[i] >> 8)  & 0x0000ff00 |
	bswap	r11d		;            (r[i] >> 24) & 0x000000ff;
.Lmoved:
	shl	r8d,4		;   // convert 4x4-byte grid back to 16 nybbles
	or	r8d,r10d	;
	shl	r8,32		;   r[0] = (r[0] << 4) | r[2];
	shl	r9d,4		;
	or	r9d,r11d	;   r[1] = (r[1] << 4) | r[3];
	mov	rax,r8		;
	or	rax,r9		;   a = (r[0] << 32) | r[1];

.Lbad:
	mov	rsp,rbp		;   return a; 
	pop	rbp		; }
	ret			;} // move()
	

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
	ret			;} // anymove()

