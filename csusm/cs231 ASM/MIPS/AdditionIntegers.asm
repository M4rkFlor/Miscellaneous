.data
	myInt1: .word  5
	myInt2: .word  25
.text 
	
	#lw $t0, myInt1($zero)#offset
	#lw $t1, myInt2($zero)
	li $t1,10
	li $s2,0
	
	
	LOOP: slt $t2, $0, $t1		#$t2 =1	
	beq $t2, $0, DONE		#no branch
	subi $t1, $t1, 1			#$t1=9
	addi $s2, $s2, 2		#$s2=2
	j LOOP
	DONE:

	# 1 for int/word
	li $v0, 1
	add $a0,$zero,$s2
	#$a0 is output register
	syscall