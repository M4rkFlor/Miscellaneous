.data
str1: .asciiz "\n Input a number in decimal form: "
line: .asciiz "===================================================\n"
str2: .asciiz "\n The number in binary is: \n "
.text
main:	
la 	$a0, str1
li	$v0, 4
syscall	#input number string
li	$v0, 5
syscall #get input
add	$a0, $v0, $0 #user input in $a0		
jal	BaseChange
j	exit

BaseChange:	
li	$t4, 0 #stack index
li	$s1, 2 #divide by 2
add $s0, $0,$a0 
		
toBin:	
beq	$s0, $0, print #remainder 0
div	$s0, $s1 #div 2
mfhi	$t1 #reminder
mflo	$s0 #dividen overwrite s0 to lower dividen
addi	$sp, $sp, -4
sw	$t1, 0($sp) #add remainder to stack
addi	$t4, $t4, 1 #inc stackindex
j	toBin

print:		
la 	$a0, line
li	$v0, 4
syscall #print line 
la 	$a0, str2
li	$v0, 4
syscall #print the number is:

zeros:
li	$t5, 32
sub	$t5, $t5, $t4 #num zeros

printZeros:
beq	$t5, $0, readstack #pop after leading 0s
la	$a0, ($0)	
li	$v0, 1
syscall #print 0
addi	$t5, $t5, -1 #dec num 0s
j	printZeros

readstack:		
li	$s5, 0
beq 	$t4, $0, terminatesub #t4 stack index
lw	$a0, 0($sp) #get stack num
addi	$sp, $sp, 4
li	$v0, 1
syscall #print int
addi	$t4, $t4, -1 #dec stack index
j	readstack	

terminatesub:
jr	$ra

exit:
li $v0, 10 #exit
syscall #exit
