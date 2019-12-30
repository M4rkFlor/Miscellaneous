.data		#start of the data

space:	.asciiz	"\n"
enter:	.byte	'-','-','-','-','-','-','-','-','-','-'
space1:	.asciiz	"\n"
output: .byte   '-','-','-','-','-','-','-','-','-','-' 
space5:	.asciiz	""
str1: .asciiz "Enter 9 charcacters to encrypt "
str2: .asciiz "Your Encrypted message is: "
str3: .asciiz "Your Decrypted message is "


.text		#start of the code
main:
	li $s7,10 #xor Key
	li 	$v0,4
	la 	$a0, str1
	syscall	#print question
	la	$s1,output #output string
	li 	$t0,10 #10 numbers?
	li 	$v0,8 #read string
	la 	$a0, enter #buffer
	li 	$a1,10 #buffer length
	syscall
	li 	$v0,4
	la 	$a0, space
	syscall	#print newline
	
	li 	$v0,4
	la 	$a0, str2
	syscall	#show encryted
	
	#la	$a0,enter
	#li 	$v0,4
	#syscall #print inputed string
	la $s2,enter # copy inputed string

	#li 	$v0,4
	#la 	$a0, space
	#syscall	#new line
#addi $t0,$t0,2
loop: beq $t0,$0,print 
	lb 	$t1,0($s2) #copied inputed word
	#addi	$t1,$t1,10 #offset decrypt
	xor $t1,$t1,$s7 #decrypt with xor key
	sb 	$t1,0($s1) #save the first character to output
	li 	$t1,0 #reset
	addi 	$s2, $s2,1 #increment to next byte in saved string
	addi 	$s1,$s1,1 #increment to next byte in outputed string
	addi 	$t0,$t0,-1 #dec loop counter
	j 	loop

print:
	li 	$v0,4
	la 	$a0,output
	syscall
	
	li 	$v0,4
	la 	$a0, str3
	syscall	#your dec message is :
	
	li 	$v0,4
	la 	$a0, enter
	syscall	
	
exit:	li 	$v0,10
	syscall