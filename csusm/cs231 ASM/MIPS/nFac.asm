.data
#write a program to calculate n! where n is 0<=n<=10
str1: .asciiz "enter a number to calculate the factorial of a number between 0 and 10 "
str2: .asciiz "\nThe factorial is: "

err1: .asciiz "\nthe number is not between 0 and 10 enter another number "
.text

main:
li $v0,4
la $a0, str1
syscall #ask

#get input
Input:
li $v0,5
syscall
add $t1,$v0,$zero
add $t2,$t1,$zero #make t2 the same as t1
addi $t2,$t2,-1 # one less 
blt $t1,0,Error
bgt $t1,10,Error
beq $t1,0, Exit

Loop:
beq $t2,0,Exit
mult $t1,$t2
mflo $t1
addi $t2,$t2,-1
j Loop

Exit:
li $v0,4
la $a0,str2
syscall

beq $t1,0,Exit0

li $v0,1
add $a0, $t1,$zero
syscall

li $v0,10
syscall

Exit0:
addi $t1,$t1,1
li $v0,1
add $a0, $t1,$zero
syscall

li $v0,10
syscall

Error:
li $v0,4
la $a0, err1
syscall#ask
j Input