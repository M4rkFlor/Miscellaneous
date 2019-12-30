.data
arr: .space 80
str1: .asciiz "Enter array size 0<n<20: "
str2: .asciiz "Input a number: "
err3: .asciiz " must be > 0.\n"
err4: .asciiz " must be < 20.\n"
notPos: .asciiz " is not a positive number.\n"
divErr: .asciiz " is not divisible by 3.\n"
reversed: .asciiz "Reversed Array\n"
newLine: .asciiz "\n"
.text
Begin:   
	li  $v0, 4
	la  $a0, str1 #ask user input
	syscall

	jal readNum
	add $s0, $v0, $0 #save result

	add $a0, $s0, $0 #send readNum val to verifySize
	jal verifySize

	add $t0, $v0, $0 #save result
	beq $0, $t0, Begin #if 0, return Begin else creatArray

	add $a0, $s0, $0 #send readNum val to createArray
	jal createArray

	add $a0, $s0, $0 #send readNum val to printArray
	jal printArray
      
	add $a0, $s0, $0 #send readNum val to reverseArray
	jal reverseArray
	add $a0, $s0, $0 #send readNum val to printArray
	jal printArray

	li $v0, 10 
	syscall #End program
#---------------------readNum---------------------------------
readNum:  
        li  $v0, 5              
	syscall #get int
        jr  $ra
#---------------------verifySize---------------------
verifySize: 
        li  $t1, 20 #max array size
        add $t0, $a0, $0 #save arg
        
        ble $t0, $0, err1 #if <= 0, go to err1 error
        bge $t0, $t1, err2 #if >= 20, go to err2 error
        
        li  $v0, 1 #return 1
        jr $ra
        
    err1:  li  $v0, 1          
            add $a0, $t0, $0
            syscall #print arg
            
            li  $v0, 4
            la  $a0, err3 #print to low
            syscall
            
            li  $v0, 0 #return 0
            jr  $ra
    
    err2:  li  $v0, 1
            add $a0, $t0, $0
            syscall #print entered num
            
            li  $v0, 4
            la  $a0, err4 #print to big
	    syscall
            
            li  $v0, 0 #return 0
            jr  $ra
#---------------------createArray---------------------
createArray:   
        li  $t0, 0 #index
        add $t1, $a0, $0 #load arg to max index
        la $s1, arr #load array
        addi $sp, $sp, -4
        sw  $ra, 0($sp)
        
    Loop:   beq $t0, $t1, ret #if i==size
    
            li 	$v0, 4
            la 	$a0, str2 #printArray "Enter number" string
            syscall
            
            jal readNum #go to readNum to get the number being entered into the array
            
            add $t2, $v0, $0 #save num
            
            add $a0, $t2, $0 #send num as arg
            jal checkNumPositive #check if the num is positive
            
            add $t3, $v0, $0 #save result
            beq $0, $t3, err5 #if result is 0 then not positive
            
            add $a0, $t2, $0 #send num as arg
            jal divisibleBy3
            
            add $t3, $v0, $0 #save result
            beq $0, $t3, err6 #check result

            sw  $t2, 0($s1) #save num
            add $s1, $s1, 4 #inc array location
            add $t0, $t0, 1 #inc index
            
            j Loop
            
    ret:    lw  $ra, 0($sp) #retrive ra
            add $sp, $sp, 4 #dec sp
            jr  $ra #return to main
            
    err5:   li  $v0, 1
            add $a0, $t2, $0        
            syscall #print int
    
            li $v0, 4
            la $a0, notPos
            syscall #print err msg
            
            j Loop
            
    err6:  li  $v0, 1
            add $a0, $t2, $0
            syscall #print int
            
            li  $v0, 4
            la  $a0, divErr
            syscall #print err msg
            
            j Loop
#---------------------Reverse Array---------------------	
reverseArray:
        add $t8, $a0, $0 #save arg (array size)
	li $t6, 0 #index
        li  $t7, 4 #index to adress
        la $t1, arr #head = first index of the array
        li $v0, 4
	la $a0, reversed #print reversed
	syscall
	
        mult $t8, $t7 #mult by 4
        mflo $t9 #offset from the first element
	add $t2, $t9, $t1 #tail = last element
	addi $t2, $t2, -4 #set to last element

	li $t7, 2 #divide by 2
	div $t8, $t7 #divide by 2
	mflo $t9 #save half the array size
	swap:   
		beq $t9, $t6, endSwap #if their index is the same, go to end
        	lw 	$t3, 0($t1) #save head
		lw 	$t4, 0($t2) #save tail
		sw 	$t3, 0($t2) #swap
		sw 	$t4, 0($t1) #swap
		
		add $t1, $t1,4 #inc head
		addi $t2, $t2,-4 #dec tail
		
		add $t6, $t6, 1 #inc index
		j swap

	endSwap:
		jr $ra
#---------------------Display Array---------------------
printArray:
		add $t0, $a0, $0 #save arg (array size)
		la $t1, arr #load adress
		li $t9, 0 #index

	print:	beq $t0, $t9, endPrint #if i=size
		li $v0, 1
		lw $a0, 0($t1) #print element
		syscall

		li $v0, 4
		la $a0, newLine #new line
		syscall

		add $t9, $t9, 1 #inc index
		add $t1, $t1, 4

		j print
	endPrint:
		 jr $ra
#---------------------CheckNum---------------------
checkNumPositive: 
        add $t8, $a0, $0 #save arg
        ble $t8, $0, invalid # if n<=0
        li $v0, 1 #return 1
        jr $ra
    invalid:
            li $v0, 0 #return 0
            jr $ra
#---------------------Divisible by 3---------------------
divisibleBy3: 
        add $t8, $a0, $0 #save arg
        li  $t7, 3 
        div $t8, $t7 #div by 3
        mfhi $t6
        bne $t6, $0, notDivisibleBy3 #if non 0 remainder not divisible
        li  $v0, 1 #return 1
        jr  $ra
        
    notDivisibleBy3:
            li $v0, 0 #load 0 to return
            jr $ra #return to last address
