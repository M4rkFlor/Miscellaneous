.data
	myInt1: .word  1
	myInt2: .word  20
.text 
	# 1 for int/word
	li $v0, 1
	lw $t0, myInt1($zero)#offset
	lw $t1, myInt2($zero)
	sub $a0,$t1,$t0 # a0 = t1 - t0
	#$a0 is output register
	syscall 