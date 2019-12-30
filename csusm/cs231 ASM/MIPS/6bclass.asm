.data
itemPrices: .word 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
couponprices: .word 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
.text
main:
li $v0,1
lw $a0,itemPrices
syscall

sw $a0,4(itemPrices)
li $v0,1
lw $a0,4(itemPrices)
syscall

li $v0,10
syscall