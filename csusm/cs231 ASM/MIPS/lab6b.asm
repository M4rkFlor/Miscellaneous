.data
arr:	.word 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
arr2:	.word 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
in:	.asciiz "\nPlease enter the number of items you are purchasing: "
in2:    .asciiz "\nPlease enter the number of coupons that you want to use: "
out1:   .asciiz "\nPlease enter the price of item "
out1a:  .asciiz ": "
out3: 	.asciiz "\nPlease enter the amount of coupon "
out4:	.asciiz "\nYour total charge is:  $"
out5: 	.asciiz "\nThank you for shopping with us."
err0a:	.asciiz "\nToo few items!"
err0b:	.asciiz "\nSorry too many items to purchase!"
err1:	.asciiz "\nToo many coupons!!"
err2:   .asciiz "\nThis coupon is not acceptable"
.text
main:
	li $s0, 0
	li $s1, 20
	li $v0, 4
	la $a0, in
	syscall 	#ask the user to enter a number
	li $v0, 5
	syscall	#get user input	
	ble $v0, $s0, err_1 #error check to see if amount of items is <= 20
	bge $v0, $s1, err_2
	add $a0, $0, $v0#num items
	add $t9, $0, $v0#num items
	jal FillPriceArray #fill array with user input returns v1
	add $t6,$v1,$zero
main2:
	li $v0, 4
	la $a0, in2
	syscall #ask the user to enter number of coupons
	li $v0, 5
	syscall #get user input
	bgt $v0, $t9, err_3 #error check to see coupons are <= number of items
	add $a0, $0, $v0#num co
	jal FillPriceCoupon #returns v0
	add $t7,$v0,$zero
	sub $t6,$t6,$t7 #find differ
	#finds the sum of all items with coupons
	#j sum
	li $v0,4
		la $a0, out4
		syscall
		
		add $a0,$t6,$0
		li $v0,1
		syscall
		
		li $v0, 4
		la $a0, out5
		syscall
		
		j end	
	
end:	#end program
	li $v0, 10
	syscall
	
	
FillPriceArray: 
	add $s3, $a0, $0#store userInput
	li $t0, 1 #loop counter
	la $s2, arr #declare array and memory register for first element
	li $s7, 0 #sum total
	loop1:
		beq $s3, $0, exit1 #run loop until we reach user input
		li $v0, 4 #get user prices and print
		la $a0, out1
		syscall
		add $a0, $t0, $0
		li $v0, 1
		syscall
		li $v0, 4
		la $a0, out1a
		syscall
		li $v0, 5
		syscall
		#store price into array
		add $t1, $v0, $0	
		sw $t1, 0($s2)
		add $s7, $t1,$s7 #add total
		#increase counter
		add $s2, $s2, 4
		add $t0, $t0, 1
		addi $s3, $s3, -1
		j loop1
	exit1:
		add $v1, $s7,$0
		jr $ra
FillPriceCoupon: 
	add $s4, $a0, $0 #store userInput
	li $t0, 1 #loop counter
	li $t3, 10 
	la $s5, arr2 #declare array and memory register for first element
	la $s2, arr
	loop2:	
		#run loop until we reach user input
		beq $s4, $0, exit2
	
		#get user prices and print
		li $v0, 4
		la $a0, out3
		syscall
		
		add $a0, $t0, $0
		li $v0, 1
		syscall
	
		li $v0, 4
		la $a0, out1a
		syscall
		
		li $v0, 5
		syscall
	
		#start comparision of coupon to price
		add $t1, $v0, $0
		
		lw $t2, 0($s2)
		
		#if coupon is greater than 10 or item give error
		bge $t1, $t2, err_4
		bge $t1, $t3, err_4
	
		#store coupon into array	
		sw $t1, 0($s5)	
		add $t8,$t1,$t8 #get sum of coupons
		#increase counter
		addi $s5, $s5, 4
		addi $s2, $s2, 4
		add $t0, $t0, 1
		addi $s4, $s4, -1
	
		j loop2
	
	addZero:
	
		sw $0, 0($s5)
		addi $s5, $s5, 4
		addi $s2, $s2, 4
		add $t0, $t0, 1
		addi $s4, $s4, -1
		
		j loop2
	
	exit2: 	
		add $v0,$t8,$0
		jr $ra
		
sum:
	#load arrays to start finding some
	la $s2, arr
	la $s5, arr2
	
	loop3:
		beq $t9, $0, printSum
		lw $t0, 0($s2)
		lw $t1, 0($s5)
		
		#subtract coupon price from item, add to sum
		sub $t2, $t0, $t1
		add $s6, $t2, $s6
		
		#increment counters
		addi $t9, $t9, -1
		add $s2, $s2, 4
		add $s5, $s5, 4
		
		j loop3
		
	printSum:
		li $v0, 4
		la $a0, out4
		syscall
		
		add $a0, $s6, $0
		li $v0, 1
		syscall
		
		li $v0, 4
		la $a0, out5
		syscall
		
		j end	

err_1:	
	li $v0, 4
	la $a0, err0a
	syscall
	
	j main

err_2:
	li $v0, 4
	la $a0, err0b
	syscall
	
	j main
	
err_3:
	li $v0, 4
	la $a0, err1
	syscall
	
	j main2

err_4:
	li $v0, 4
	la $a0, err2
	syscall
	
	j addZero
