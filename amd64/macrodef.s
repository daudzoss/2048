%macro	cmov	3
	j%1	%%equal
	mov	%2,%3
%%equal:	
%endmacro

%macro	bextr	3
	mov	%1,%2
	shr	%1,(%3)&0x3f
	and	%1,(1<<((%3)>>8))-1
%endmacro

	section	.data
aNRcd:	db	"rax=0x%lX",9,"r%ld=0x%lX",9,"rcx=0x%lX",9,"rdx=0x%lX",10,0
%macro	printAnrCD 1
	lea	rsp,[rsp-80]
	mov	[rsp+0],rax
	mov	[rsp+8],rbx
	mov	[rsp+16],rcx
	mov	[rsp+24],rdx
	mov	[rsp+32],rsi
	mov	[rsp+40],rdi
	mov	[rsp+48],r8
	mov	[rsp+56],r9
	mov	[rsp+64],r10
	mov	[rsp+72],r11
	mov	rdi,aNRcd
	mov	rsi,[rsp+0];rax
	mov	rdx,%1
	mov	rcx,r%1
	mov	r8,[rsp+16];rcx
	mov	r9,[rsp+24];rdx
	xor	al,al
	call	printf
	mov	rax,[rsp+0]
	mov	rbx,[rsp+8]
	mov	rcx,[rsp+16]
	mov	rdx,[rsp+24]
	mov	rsi,[rsp+32]
	mov	rdi,[rsp+40]
	mov	r8,[rsp+48]
	mov	r9,[rsp+56]
	mov	r10,[rsp+64]
	mov	r11,[rsp+72]
	mov	rsp,rbp
%endmacro
	
