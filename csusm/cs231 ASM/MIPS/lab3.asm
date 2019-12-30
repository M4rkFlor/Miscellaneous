.data
 str1: .asciiz "How many numbers do you want to enter?"
 str2: .asciiz "\nThe sum of the even numbers is "
 .text
 main:
 li $v0,4
 la $a0,str1
 syscall
 li $v0,5
 syscall#stores max loops
 add $t2,$v0,$zero
 li $t1,0 #loop index
 li $t4,0 #store remainder
 li $t5,2#divide evenly
Loop:
beq $t1,$t2,Exit
li $v0,5
syscall
div $v0,$t5
mfhi $t4
beq $t4,$zero,addEven
addi $t1,$t1,1
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
 