.data
	myInt1: .word  1
	myInt2: .word  20
.text 
	# 1 for int/word
	li $v0, 1
	# $s cannot be modified like const
	lw $s0, myInt1($zero)#offset
	lw $s1, myInt2($zero)
	sub $t0,$s1,$s0 # a0 = t1 - t0
	#$a0 is output register we can move a value to $a0
	move $a0,$t0
	syscall 