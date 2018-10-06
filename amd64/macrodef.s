%macro	cmov	3
	j%1	%%equal
	mov	%2,%3
%%equal:	
%endmacro

%macro	bextr	3
	mov	%1,%2
	shr	%1,%3&0x3f
	and	%1,(1<<(%3>>8))-1
%endmacro
	

