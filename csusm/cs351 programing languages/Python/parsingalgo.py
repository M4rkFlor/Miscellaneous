'''
BNF for var def code with format:

myvar= 5+6*2.3;

New bnf:
exp -> id = math;
math ->  multi + math | multi
multi -> (int||float * multi) || (int|float)
Note that this is just a shortened example code for demostration only. The final tree misses internal nodes like int or float, since we are not doing word level BNF here.
'''
Mytokens=[("id","myvar"),("op","="),("int","5"),("op","+"),("int","6"),("op","*"),("float","2.3"),("sep",";")]
inToken = ("empty","empty")

def accept_token():
    global inToken
    print("     accept token from the list:"+inToken[1])
    inToken=Mytokens.pop(0)

def multi():
    #bnf: (int|float) || ((int|float) * multi)
    print("\n----parent node multi, finding children nodes:")
    global inToken
    if(inToken[0]=="float"):
        print("child node (internal): float")
        print("   float has child node (token):"+inToken[1])
        accept_token()
    elif(inToken[0]=="int"):
        print("child node (internal): int")
        print("   int has child node (token):"+inToken[1])
        accept_token()
    else:
        print("error, multi expects float or int")
    
    if(inToken[1]=="*"):
            print("child node (token):"+inToken[1])
            accept_token()
            print("child node (internal): multi")
            multi()

def math():
    #bnf: multi + math | multi
    print("\n----parent node math, finding children nodes:")
    global inToken
    multi() 
    if(inToken[1]=="+"):
        print("child node (token):"+inToken[1])
        accept_token()
        math()
    

def exp():
    print("\n----parent node exp, finding children nodes:")
    global inToken
    typeT,token=inToken
    if(typeT=="id"):
        print("child node (internal): identifier")
        print("   identifier has child node (token):"+token)
        accept_token()
    else:
        print("expect identifier as the first element of the expression!\n")
        return

    if(inToken[1]=="="):
        print("child node (token):"+inToken[1])
        accept_token()
    else:
        print("expect = as the second element of the expression!")
        return

    print("Child node (internal): math")
    math()
        
def main():
    global inToken
    inToken=Mytokens.pop(0)
    exp()
    if(inToken[1]==";"):
        print("\nparse tree building success!")
    return
main()
