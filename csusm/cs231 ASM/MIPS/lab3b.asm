.data
 str1: .asciiz "how many positive numbe ryou want to add that is divisble by 6?"
 str2: .asciiz "\nThe Sum of the positive numbers between 1 and 100 that are devisable by 6, is: "
 str3: .asciiz "\nEnter the numbers u want to add that are divisible by 6 and between 1 and 100"
 error: .asciiz "\n ERROR: "
 error1: .asciiz " is not a positive number. Enter another number.\n"
 error2: .asciiz " is not in the range of 1 to 100. Enter another number.\n" 
 error3: .asciiz " is not divisible by 6. Enter another number.\n"
 
 .text
 main:
 li $v0,4
 la $a0,str1
 syscall
 #name registers used
 li $t1,0 #loop index
 li $t2,0 #stores max loops
 li $t4,0 #store remainder
 li $t5,6 #divide by six
 
 j Input


Loop:
beq $t1,$t2,Exit
li $v0,5
syscall
add $t6,$v0,$zero #store input to check range
div $v0,$t5
mfhi $t4
beq $t4,$zero,addEven
j checkRangeL

j Loop

 Exit:
 li $v0,4
 la $a0,str2
 syscall
 li $v0,1
 add $a0,$t3,$zero
 syscall
 li $v0,10
 syscall
 
 addEven:
 add $t3,$v0,$t3
 addi $t1,$t1,1
 j Loop
 
 Input:
  li $v0,5 #get input
 syscall
 add $t2,$v0,$zero #stores max loops to t2
 j checkRange
 
 checkRange:
  blt $t2,0, Error1 #less than 1
  blt $t2,2, Error2
  bgt $t2,99, Error2 #not between 1-100
  li $v0,4
  la $a0,str3
  syscall
  ##add $t2,$v0,$zero #stores max loops to t2
  j Loop
  
  Error1:
 li $v0,4
 la $a0,error
 syscall
 
 li $v0,1
 add $a0,$t2,$zero
 syscall# show int
 
 li $v0,4
 la $a0,error1
 syscall
 j Input
 
 Error2:
 li $v0,4
 la $a0,error
 syscall
 
 li $v0,1
 add $a0,$t2,$zero
 syscall# show int
 
 li $v0,4
 la $a0,error2
 syscall
 j Input
  
 checkRangeL:
  blt $t6,0, Error1L #less than 1
  blt $t6,2, Error2L
  bgt $t6,99, Error2L #not between 1-100
  ##add $t2,$v0,$zero #stores max loops to t2
  j Error3
  
  
 Error1L:
 li $v0,4
 la $a0,error
 syscall
 
 li $v0,1
 add $a0,$t6,$zero
 syscall# show int
 
 li $v0,4
 la $a0,error1
 syscall
 j Loop
 
 Error2L:
 li $v0,4
 la $a0,error
 syscall
 
 li $v0,1
 add $a0,$t6,$zero
 syscall# show int
 
 li $v0,4
 la $a0,error2
 syscall
 j Loop
 
 Error3:
  li $v0,4
 la $a0,error3
 syscall
 j Loop
 
 
