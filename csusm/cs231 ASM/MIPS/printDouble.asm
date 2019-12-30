.data
	myDouble: .double  2.12345
	zero: .double  0.0
.text 
	#3 for double
	li $v0, 3
	ldc1 $f0, myDouble
	ldc1 $f2, zero
	add.d $f12,$f0,$f2
	syscall 