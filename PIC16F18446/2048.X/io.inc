;;; shared by all 
io_isr
	

io_brd
	
;;; each job needs its own task code due to hard-coding the port number :(
	macro	port,rate,flag,hb,pin
	local	iodecl
iodecl
	zOS_INP	port,rate,flag,hb,pin,io_isr
	endm
	
