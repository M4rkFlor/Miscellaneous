.data
str1: .asciiz  "Please input a temperature in Celsius: "
str2: .asciiz  "\nThe temperature in Fahrenheit is "
conversionfactor: .float 1.8
offset: .float 32
newLine: .asciiz "\n"
.text
main:
li $v0,4
la $a0,str1
syscall #ask enter
li $v0,5
syscall #read float stored in $f0
mtc1 $v0,$f12
cvt.s.w $f12,$f12
#user input in f12
#celcius × 1.8 + 32 = F
l.s $f1,conversionfactor
l.s $f2,offset
mul.s $f12,$f12,$f1
add.s $f12,$f12,$f2
li $v0,4
la $a0,str2
syscall #tell answer
#print float here
li $v0,2
syscall #print float $f12 arg

li $v0,10
syscall #end program