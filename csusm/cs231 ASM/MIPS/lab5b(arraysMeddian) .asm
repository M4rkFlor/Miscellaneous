.data
str1: .asciiz "\nEnter the number of elements: "
str2: .asciiz "Enter number "
str3: .asciiz "\nThe median of the array is:\n"
tab: .asciiz ":\t"
newLine: .asciiz "\n"
err1: .asciiz "\nError array can’t have more than 10 elements, try again!!\n"
err2: .asciiz "number not positive\n"
list: .word 0,0,0,0,0,0,0,0,0,0,0
.text

main:
#registers used
li $t0,0 #t0 array size
li $t1,0 #t1 index
li $t2,0 #t2 memory index by 4
li $s0,0 #s0 array pointer
li $t3,2 #divde by 2
li $t4,0 #divide result
#main
li $v0,4
la $a0,str1
syscall#tell user to input

j inputLoop


inputLoop:
li $v0,5
syscall
add $t0,$v0,$zero
bgt $t0,10,Error1
blt $t0,1,Error2
j FillArray 

FillArray:
beq $t1,$t0,Exit
li $v0,4
la $a0,str2
syscall#tell user to input

addi $t1,$t1,1 #increase by one 
li $v0,1
add $a0,$t1,$zero
syscall#display index t1
addi $t1,$t1,-1 #decrease by one

li $v0,4
la $a0,tab
syscall#tab spacing

li $v0,5
syscall #get input

#save to array index
sw $v0,list($t2)

addi $t1,$t1,1 #increment index
addi $t2,$t2,4 #increment memory index
j FillArray

#Errors
Error1:
li $v0,4
la $a0,err1
syscall
j inputLoop

Error2:
li $v0,4
la $a0,err2
syscall
j inputLoop

Exit:
li $v0,4
la $a0,str3
syscall#median is 

addi $t2,$t2,-4 #reduce by 4 becuse adeed 4 on last loop
addi $t1,$t1,-1 #reduce by 1 becuse adeed 1 on last loop
j FindMedian

#t0 array size
#t1 index
#t2 memory index by 4
#s0 array pointer
FindMedian:
#new
div $t1,$t3
mfhi $t3 #overwite t3 with remiander
mflo $t4 #divide output
beq $t3,0,Odd
#EVEN HERE
addi $t5,$t4,1
add $t4,$t4,$t4
add $t4,$t4,$t4 #add 4 times equal to mult4
add $t5,$t5,$t5
add $t5,$t5,$t5 #add 4 times equal to mult4

lw $t6,list($t4)
lw $t7,list($t5)
add $t6,$t7,$t6
addi $t7,$zero,2
div $t6,$t7
mflo $a0
li $v0,1
syscall
j Terminate

Odd:
#t4 is now index median
add $t4,$t4,$t4
add $t4,$t4,$t4 #add 4 times equal to mult4
li $v0,1
lw $a0,list($t4)
syscall
j Terminate



Terminate:
li $v0,10
syscall