.data
	myFloat: .float 3.21212
.text 
	#2 for float
	li $v0, 2
	lwc1 $f12, myFloat
	syscall 