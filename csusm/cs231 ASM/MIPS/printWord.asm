.data
	myInteger: .word 21
.text 
	#1 for integers
	li $v0, 1
	lw $a0, myInteger
	syscall 