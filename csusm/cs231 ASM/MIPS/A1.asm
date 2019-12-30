# Write a program that in the main routine ask the user input n numbers(2<n<11) and pass n
# to FillArray to stores numbers in the array. Main passes the pointer to PrintArray Function to
# print the array, to SortArray to sort the array and to PrintArray again to print the sored array
.data
myArray: .word 0,0,0,0,0,0,0,0,0,0 #array size 10
str1: .asciiz "How many numbers do you want to enter (2<n<11): "
str2: .asciiz "\nEnter a number: "
err: .asciiz "number not in range (2<n<11)\n"
.text
Main:
li $s4,4 # byte value 4
li $v0,4
la $a0,str1
syscall #ask user to enter n
li $v0,5
syscall
addi $a0,$v0,0
addi $s0,$v0,0 #global array size
ble $a0,2,err1
bge $a0,11,err1 # 2 < n < 11
jal FillArray
jal PrintArray
jal SortArray
jal PrintArray
li $v0,10
syscall

SortArray:
li $t0,0 # i
li $t4,0 # i + 1
addi $t1,$s0,-1 # n - 1
li $t2,0 #[i]
li $t3,0 #[i+1]
li $t5,0
li $t6,0
li $t7,0 
#SORT AGAIN
li $s7,0 #j
li $s6,0 #n^2
mult $s0,$s0
mflo $s6
#n-1 LOopSort
SortAgain:
#if j =0 , beq j==n^2 j++
beq $s7,$s6,DoneSorting
addi $s7,$s7,1

LoopSort:
beq $t0,$t1,ExitLoopSort #i=0; beq i==n-1 ; i++
mult $t0,$s4
mflo $t5
lw $t2,myArray($t5)
addi $t4,$t0,1
mult $t4,$s4
mflo $t6
lw $t3,myArray($t6)
bgt $t2,$t3,Swap # if [i]>[i+1] swap
addi $t0,$t0,1
j LoopSort

ExitLoopSort:
li $t0,0 # i
li $t4,0 # i + 1
addi $t1,$s0,-1 # n - 1
li $t2,0 #[i]
li $t3,0 #[i+1]
li $t5,0
li $t6,0
li $t7,0
j SortAgain

Swap:
sw $t3,myArray($t5)
sw $t2,myArray($t6)
addi $t0,$t0,1
j LoopSort

DoneSorting:
jr $ra

FillArray:
add $t2,$a0,$zero
li $t1,0
Loop:
beq $t1,$t2,endFill
li $v0,4
la $a0,str2
syscall #ask to enter
li $v0,5
syscall
add $t0,$t1,$t1
add $t0,$t0,$t0 # mult $a0 by 4
sw $v0 myArray($t0)
addi $t1,$t1,1
j Loop
endFill:
li $t0,0 #reset for future use
li $t1,0
li $t2,0
jr $ra

PrintArray:
beq $t0,$s0,endPrint
mult $t0,$s4
mflo $a0
lw $a0,myArray($a0)
li $v0,1
syscall
addi $t0,$t0,1
j PrintArray
endPrint:
li $t0,0
jr $ra

err1:
li $v0,4
la $a0,err
syscall #not in range
j Main