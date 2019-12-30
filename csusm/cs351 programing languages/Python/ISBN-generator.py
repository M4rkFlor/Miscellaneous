#Marco Flores
#Python 3.6.8
#function 6 was renamed to avoid naming conflict with func 5

#Python small exercise questions
#Help you getting familiar with Python syntax

#Grading:

#IMPORTANT NOTICE:
#A good practice in coding is to show your customer a working version and tell them
#what new features you want to add next.
#Thus, we require you to submit all your homework as a working version. If you
#only know how to solve 7/10 questions, just submit the 7 that runs without errors.
#For incomplete answers, comment the code out and print a line tell us your progress
#E.g. "Problem 3 is a completed but has run time errors"
#or "problem 5 is incomplete, but I did 75% of the work."

#Complete HW + correct results: 10pt
#Each question has a equal share of the total points
#Code that does not run will have only 2pt.
#No submission: 0%
#Late work is half of your original credit

#Please follow the required input/output and function names

'''
 1. Input: Count
 Output: print Count number of "hello":
            1th hello
           2th hello...
 IMPORTANT: copy to visualizer, observe the behavior
 visualizer keeps tracks of varibles and shows a function frame being created aswell as the automatic return type none
'''
def easy_hello_loop1_for(Count):
    for x in range(Count):
        print("hello")
'''
2.Input: number x,y
 Output: return the smaller value of the two
 Do it by yourself, no system calls like min()
'''
def smaller_value(x,y):
    if x<y:
        return x
    else:
        return y
'''
3. Do not use len(). Write a function to calculate how many elements do you have in your list, and return it
'''
def my_len(lis):
    len=0
    for x in lis:
        len+=1
    return len


'''
4. input: a list with small strings that has 2 letters, 3 letters, or 4 letters
output: return 3 lists, Letter2, Letter3, Letter4 containing small strings
Sample:
input list: ['rt','asdf','ton','er','user']
will give
    Letter2=['rt','er'] 2char
    Letter3=['ton'] 3char
    Letter4=['asdf','user'] 4chars
You can use len() in this question.
'''
def cate_letters(LongStr):
    Letter2 = []
    Letter3 = []
    Letter4 = []
    for x in LongStr:
        if len(x)==2:
            Letter2.append(x)
        elif len(x)==3:
            Letter3.append(x)
        elif len(x)==4:
            Letter4.append(x)
    return Letter2,Letter3,Letter4
'''
5. input: a string with character in it, a string with numbers in it
output: go through the two strings together, print out elements by index
format "the elements at index __ from string1 is __, from string2 is ___"
'''
def two_strings(str1,str2):
    size = len(str1)
    for index in range(size):
        print("the elements at index " + str(index) + " from string1 is " + str1[index] + ", from string2 is " + str2[index])
'''
6. input: a string with character in it, a string with numbers in it
output: go through the two strings together. At index i, if the number in str2 is even, put the letter in str1 into evenStr
if the number is odd, put the letter into oddStr. Return the even/odd strings
Sample: "helloworld" "2435232399"
gives evenStr="heoo" oddStr="llwrld"
'''
def two_strings2(str1,str2):
    size = len(str1)
    evenStr = ""
    oddStr = ""
    for index in range(size):
        if (int(str2[index])%2==0):
            evenStr += str1[index]
        else:
            oddStr += str1[index]
    return evenStr,oddStr
'''
7.
The number 6 is a truly great number. Given two int values, a and b, return True
if either one is 6. Or if their sum or difference is 6.
Note: the function abs(num) computes the absolute value of a number.

love6(6, 4) returns True
love6(4, 5) returns False
love6(1, 5) returns True
'''
def love6(a,b):
    if a==6 or b==6:
        return True
    elif a+b==6 or abs(a-b)==6:
        return True
    else:
        return False
'''
########
#8. ISBN number

#As you know, every book has an unique ISBN number (International Standard Book Number).
#It is a 10-digit (or 13) code that uniquely specifies a book. Since this number is long, the right most digit is actually a "checksum"
#to roughly check if all the digits are correct (not mis-typed etc.) and forming a legit ISBN number. (checksum is also used in other places, like credit card number.)
#The rule is: when adding all the (10 numbers * its position (rightmost be position 1, leftmost be 10)) together, the sum should be divisible by 11.
#For example: ISBN 020131452-5 is legit since:
#               (0*10 + 2*9 + 0*8 + 1*7 + 3*6 + 1*5 + 4*4 + 5*3 + 2*2 + 5*1)%11 = 88%11 = 0 the sum 88 is divisible by 11
#In fact, the cool thing is that the checksum (rightmost 5) is the only single digit number that can satisfy this rule. In other words, if you know the first
#9 digits, you can calculate the checksum (last digit). In this problem, you will be calculte the checksum of an ISBN number.
#########
'''

'''
Helper function 1: check_legit_ISBN
Input: a list with 10 single digit number in it
Output: return "Legit" if the 10 digits form a legit ISBN number
        return "Not Legit" otherwise

Sample: [0,2,0,1,3,1,4,5,2,5] should return "Legit"
        [0,2,0,1,3,1,4,5,2,3] should return "Not Legit"

'''
def check_legit_ISBN(ISBNLis):
    #ISBN is always 10 chracters
    if (ISBNLis[0]*10 + ISBNLis[1]*9 + ISBNLis[2]*8 + ISBNLis[3]*7 + ISBNLis[4]*6 + ISBNLis[5]*5 + ISBNLis[6]*4 + ISBNLis[7]*3 + ISBNLis[8]*2 + ISBNLis[9]*1)%11 == 0:
        return "Legit"
    else:
        return "Not Legit"

'''
Helper func 2: format output
input: a list with 10 numbers in it
output: format it to the correct ISBN format and return it
Sample:
[0,2,0,1,3,1,4,5,2,5] will become: "ISBN 020131452-5"
'''
def format_ISBN(ISBNLis):
    ISBNstr = "ISBN "
    for x in range(10):
        if x==9:
            ISBNstr += "-"
            if ISBNLis[x] == 10:
                ISBNstr += "X" #roman numeral for 10
                return ISBNstr
        ISBNstr += str(ISBNLis[x])
    return ISBNstr


'''
Helper func 3: checksum_ISBN
Input: a list with 9 single digit number in it (first 9 digit in ISBN)
Output: print out: "The correct checksum digit is:__. Now we have a legit ISBN: _____"
Hint: just loop through 0-9, test every one with helper func1 to find out the one checksum that forms a legit ISBN
with the correct ISBN in lis (10 numbers), call helper func2 to format it correctly. Then print the final result.
'''
def checksum_ISBN(partISBN):
    #for loops shouldnt be used if can be avoided
    checksumNumber = (11 - ((partISBN[0]*10 + partISBN[1]*9 + partISBN[2]*8 + partISBN[3]*7 + partISBN[4]*6 + partISBN[5]*5 + partISBN[6]*4 + partISBN[7]*3 + partISBN[8]*2) % 11))%11
    partISBN.append(checksumNumber)
    #print(check_legit_ISBN(partISBN))
    print("The correct checksum digit is:"+ str(checksumNumber) +". Now we have a legit ISBN: " + format_ISBN(partISBN))
'''
Main Func: Generate a ISBN by:
---add 9 random nunmbers into a list
---call helper func 3 to find the checksum

---Generate 10 good ISBN number with one function call
'''
import random
def generate_ten_ISBN():
    for i in range(10):
        isbnList = []
        for x in range(9):
            isbnList.append(random.randint(0,9))
        checksum_ISBN(isbnList)



#Test Methods

easy_hello_loop1_for(3) #1

print(smaller_value(50,20)) #2

thislist = ["a", "b", "c", "d", "e", "f", "g"] #3
print(my_len(thislist))

mylist = ['rt','asdf','ton','er','user'] #4
print(cate_letters(mylist))

str1="123" #5
str2="abc"
two_strings(str1,str2)

s1  = "helloworld" #6
s2 = "2435232399"
print(two_strings2(s1,s2))

print(love6(6, 4)) #7
print(love6(4, 5))
print(love6(1, 5))


#8
list1 = [0,2,0,1,3,1,4,5,2,5] #helper fun 1
list2 = [0,2,0,1,3,1,4,5,2,3]
print(check_legit_ISBN(list1)) #should return "Legit"
print(check_legit_ISBN(list2)) #should return "Not Legit"

isbnList = [0,2,0,1,3,1,4,5,2,5] #helper func 2
print(format_ISBN(isbnList))

generate_ten_ISBN() #uses helper func 3