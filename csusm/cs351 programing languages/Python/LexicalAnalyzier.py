'''
BNF for var def code with format:

New bnf:
exp -> id = math ;
math ->  multi + math | multi
multi -> (int||float * multi) || (int|float)
'''
from anytree import Node, RenderTree #pip install anytree 
 
class ParserClass:
    #def __init__(self, tokens):
    #    #Mytokens=[("id","myvar"),("op","="),("int","5"),("op","+"),("int","6"),("op","*"),("float","2.3"),("sep",";")]
    #    self.inToken = ("Type","Value")
    #    self.Mytokens = tokens
 
    def printT(self,outString):
        self.treeOutput.insert(END,str(outString) + "\n")
 
    def accept_token(self):
        try:
            self.inToken=self.Mytokens.pop(0)
        except:
            self.printT("Not enough tokens, possibly missing terminiators ':' or ';'")
    

    def print_exp(self): #BNF: p_xpr => print ( string_Literal ) ;
        self.rootNode = Node("print_expression")
        if(self.inToken[1]=="print"):
            Node("print",parent=self.rootNode)
            self.accept_token()
        else:
            self.printT("Error: expected Keyword 'print'")
            return
        if(self.inToken[1]=="("):
            Node("(",parent=self.rootNode)
            self.accept_token()
        else:
            self.printT("Error: expected Seperator '('")
            return
        if(self.inToken[0]=="String_literal"):
            Node("String_literal",parent=self.rootNode)
            self.accept_token()
        else:
            self.printT("Error: expected String_literal")
            return
        if(self.inToken[1]==")"):
            Node(")",parent=self.rootNode)
            self.accept_token()
        else:
            self.printT("Error: expected Seperator ')'")
            return
        if(self.inToken[1]==";"):
            Node(";",parent=self.rootNode)
        else:
            self.printT("Error: expected Seperator ';'")
            return


    def comparison_exp(self,compareNode):#BNF: comparison_exp -> (identifier|Float_literal|Int_literal) > (identifier|Float_literal|Int_literal)
        if(self.inToken[0]=="Identifier"):
            Node("Identifier",parent=compareNode,nodeValue=self.inToken[1])
            self.accept_token()
        elif(self.inToken[0]=="Float_literal"):
            Node("Float_literal",parent=compareNode,nodeValue=self.inToken[1])
            self.accept_token()
        elif(self.inToken[0]=="Int_literal"):
            Node("Int_literal",parent=compareNode,nodeValue=self.inToken[1])
            self.accept_token()
        else:
            self.printT("Error: expected Identifier,Float_literal, or Int_literal")
            return
        if(self.inToken[1]==">"):
            Node(">",parent=compareNode)
            self.accept_token()
        else:
            self.printT("Error: expected Operator '>'")
            return
        if(self.inToken[0]=="Identifier"):
            Node("Identifier",parent=compareNode,nodeValue=self.inToken[1])
            self.accept_token()
        elif(self.inToken[0]=="Float_literal"):
            Node("Float_literal",parent=compareNode,nodeValue=self.inToken[1])
            self.accept_token()
        elif(self.inToken[0]=="Int_literal"):
            Node("Int_literal",parent=compareNode,nodeValue=self.inToken[1])
            self.accept_token()
        else:
            self.printT("Error: expected Identifier,Float_literal, or Int_literal")
            return

    def if_exp(self): #BNF: if_exp -> if ( comparison_exp ) : 
        self.rootNode = Node("if_expression")
        if(self.inToken[1]=="if"):
            Node("if",parent=self.rootNode)
            self.accept_token()
        else:
            self.printT("Error: expected Keyword 'if'")
            return
        if(self.inToken[1]=="("):
            Node("(",parent=self.rootNode)
            self.accept_token()
        else:
            self.printT("Error: expected Seperator '('")
            return
        compareNode = Node("comparison_exp",parent=self.rootNode)
        self.comparison_exp(compareNode)
        if(self.inToken[1]==")"):
            Node(")",parent=self.rootNode)
            self.accept_token()
        else:
            self.printT("Error: expected Seperator ')'")
            return
        if(self.inToken[1]==":"):
            Node(":",parent=self.rootNode)
        else:
            self.printT("Error: expected Seperator ':'")
            return

    def multi(self,mathNode): #bnf: (int|float|Identifier) || ((int|float|Identifier) * multi)
        multiNode = Node("Multi",parent=mathNode,)
        if(self.inToken[0]=="Float_literal"):
            Node("Float_literal",parent=multiNode,nodeValue=self.inToken[1])
            self.accept_token()
        elif(self.inToken[0]=="Int_literal"):
            Node("Int_literal",parent=multiNode,nodeValue=self.inToken[1])
            self.accept_token()
        elif(self.inToken[0]=="Identifier"):
            Node("Identifier",parent=multiNode,nodeValue=self.inToken[1])
            self.accept_token()
        else:
            self.printT("error, math/multi expression expects float,Int_literal or Identifier")
 
        if(self.inToken[1]=="*"):
                Node("*",parent=multiNode)
                self.accept_token()
                self.multi(multiNode)
    
    def math(self,mathNode): #bnf: multi + math | multi
        self.multi(mathNode) 
        if(self.inToken[1]=="+"):
            Node("+",parent=mathNode)
            self.accept_token(),
            childMathNode = Node("Math",parent=mathNode)
            self.math(childMathNode)
    
    def exp(self): #bnf: exp => id = math | keyword id = math ;
        self.rootNode = Node("Expression")
        if(self.inToken[0]=="Keyword"): #should seperate data type keywords and logical keywowrds
            Node("Keyword",parent=self.rootNode)
            self.rootNode.name = "Initialization Expression"
            self.accept_token()
        if(self.inToken[0]=="Identifier"):
            Node("Identifier",parent=self.rootNode)
            self.accept_token()
        else:
            self.printT("missing identifier at the begginging of the expression!\n")
            return
    
        if(self.inToken[1]=="="):
            Node("=",parent=self.rootNode,nodeValue=self.inToken[1])
            self.accept_token()
        else:
            self.printT("expect = as the second element of the expression! No operation taken")
            return
        
        mathNode = Node("Math",parent=self.rootNode)
        self.math(mathNode)
 
    def parser(self,tokensToParse,treeOutBox,LineNumber):
        self.treeOutput = treeOutBox
        self.Mytokens = tokensToParse
        self.inToken=self.Mytokens.pop(0)
        if(self.inToken[1]=="int" or self.inToken[1]=="float" or self.inToken[0]=="Identifier"):
            self.exp()
            if(self.inToken[1]==";"):
                Node(";",parent=self.rootNode)
                self.printT("\nLine: " + str(LineNumber) + " parse tree building success!")
                self.printT(RenderTree(self.rootNode).by_attr())
            else:
                self.printT("Invalid syntax parse tree Failed at Line: " + str(LineNumber))
                return False
        elif(self.inToken[1]=="if"):
            self.if_exp()
            if(len(self.Mytokens)==0):
                self.printT("\nLine: " + str(LineNumber) + " parse tree building success!")
                self.printT(RenderTree(self.rootNode).by_attr())
            else:
                self.printT("Invalid syntax parse tree Failed at Line: " + str(LineNumber))
                return False
        elif(self.inToken[1]=="print"):
            self.print_exp()
            if(len(self.Mytokens)==0):
                self.printT("\nLine: " + str(LineNumber) + " parse tree building success!")
                self.printT(RenderTree(self.rootNode).by_attr())
            else:
                self.printT("Invalid syntax parse tree Failed at Line: " + str(LineNumber))
                return False
        else:
            self.printT("Invalid statement at Line: " + str(LineNumber))
            return False
        return True

 
####
from tkinter  import *
from tkinter import messagebox
 
#1f1f1f bg
#121212 input
#303030 button
#264f78 highlight
 
class MyFirstGUI:
    def __init__(self, master):
        self.processingLine = 0
        self.master = master
        master.title("Lexical Analyzer for TinyPie")
        master.configure(background="#1f1f1f")
        
        #col-0
        Label(master, text="Source Code Input: ", background="#1f1f1f", fg="white").grid(row=0,column=0,sticky=W, padx=(30,60), pady=(10,0))
 
        self.sourceEntry = Text(master, width=50, height=18, bg="#121212", fg="white",insertbackground="white",selectbackground="#264f78")
        self.sourceEntry.grid(row=1, column=0, sticky="NEWS", padx=(30,60))
        #self.sourceEntry.bind("<Return>",self.NextLine)
        
        Label(master, text="Current Processing Line: ", background="#1f1f1f", fg="white").grid(row=2,column=0,sticky=W, padx=(30,60), pady=(10,0))
        
        self.linenumber = Entry()
        self.linenumber.grid(row=2,column=0,sticky=E, padx=(30,60), pady=(10,0))
        self.linenumber.insert(0,self.processingLine)
 
        Button(master, text="Next Line", background="#303030", fg="white", command=self.NextLine).grid(row=3,column=0, sticky=E, padx=(30,60), pady=(10,25))
 
        #col-1
        Label(master, text="Lexical Analyzed Result: ", background="#1f1f1f", fg="white").grid(row=0,column=1,sticky=W, padx=30, pady=(10,0))
 
        self.sourceOutput = Text(master, width=50, height=18, bg="#121212", fg="white",insertbackground="white",selectbackground="#264f78")
        self.sourceOutput.grid(row=1, column=1, sticky="NEWS", padx=30)
 
        #col-2
        Label(master, text="Tree Result: ", background="#1f1f1f", fg="white").grid(row=0,column=2,sticky=W, padx=30, pady=(10,0))
 
        self.treeOutput = Text(master, width=50, height=18, bg="#121212", fg="white",insertbackground="white",selectbackground="#264f78")
        self.treeOutput.grid(row=1, column=2, sticky="NEWS", padx=30)
 
        Button(master, text="Quit", background="#303030", fg="white", command=self.close).grid(row=3,column=2, sticky=E, padx=30,pady=(10,25))
        
        #configure all
        self.master.grid_columnconfigure(0,weight=1)
        self.master.grid_columnconfigure(1,weight=1)
        self.master.grid_columnconfigure(2,weight=1)
        self.master.grid_rowconfigure(1,weight=1)
 
    def CutOneLineTokens (self,inStr,isString=False):
        print(inStr)
        Output = ""
        tokenList = []
        Keywords = re.compile(r'\s*((print)|(if)|(else)|(int)|(float)) *')
        Operators = re.compile(r'\s*(=|\+|>|\*) *')
        Separators = re.compile(r'\s*(\(|\)|:|“|”|;\s*) *')
        Identifiers = re.compile(r'\s*(\t*| *)([A-Z]|[a-z])+\d*')
        #Literal = re.compile(r'(\s*\d+|("|“).*("|”))')
        String_literal = re.compile(r'\s*("|“).*("|”)')
        Float_literal = re.compile(r'\s*\d+\.\d+') #match float before int
        Int_literal = re.compile(r'\s*\d+')
 
         #crash prevention
        while(len(inStr)>0):
            nothingMatches = True
            if(Keywords.match(inStr) != None ):
                Output = Output + "<Keyword," + Keywords.match(inStr).group().strip() + ">" + "\n"
                tokenList.append(("Keyword",Keywords.match(inStr).group().strip()))
                inStr = inStr[Keywords.match(inStr).span()[1]:]
                nothingMatches = False
                print(inStr)
            if(Identifiers.match(inStr) != None ):
                Output = Output + "<Identifier," + Identifiers.match(inStr).group().strip() + ">" + "\n"
                tokenList.append(("Identifier",Identifiers.match(inStr).group().strip()))
                inStr = inStr[Identifiers.match(inStr).span()[1]:]
                nothingMatches = False
                print(inStr)
            if(Operators.match(inStr) != None ):
                Output = Output + "<Operator," + Operators.match(inStr).group().strip() + ">" + "\n"
                tokenList.append(("Operator",Operators.match(inStr).group().strip()))
                inStr = inStr[Operators.match(inStr).span()[1]:]
                nothingMatches = False
                print(inStr)
            if(Separators.match(inStr) != None ):
                Output = Output + "<Separator," + Separators.match(inStr).group().strip() + ">" + "\n"
                tokenList.append(("Separator",Separators.match(inStr).group().strip()))
                inStr = inStr[Separators.match(inStr).span()[1]:]
                nothingMatches = False
                print(inStr)
            if(String_literal.match(inStr) != None ):
                Output = Output + "<String_literal," + String_literal.match(inStr).group().strip() + ">" + "\n"
                tokenList.append(("String_literal",String_literal.match(inStr).group().strip()))
                inStr = inStr[String_literal.match(inStr).span()[1]:]
                nothingMatches = False
                print(inStr)
            if(Float_literal.match(inStr) != None ):
                Output = Output + "<Float_literal," + Float_literal.match(inStr).group().strip() + ">" + "\n"
                tokenList.append(("Float_literal",Float_literal.match(inStr).group().strip()))
                inStr = inStr[Float_literal.match(inStr).span()[1]:]
                nothingMatches = False
                print(inStr)
            if(Int_literal.match(inStr) != None ):
                Output = Output + "<Int_literal," + Int_literal.match(inStr).group().strip() + ">" + "\n"
                tokenList.append(("Int_literal",Int_literal.match(inStr).group().strip()))
                inStr = inStr[Int_literal.match(inStr).span()[1]:]
                nothingMatches = False
                print(inStr)
            if nothingMatches:
                print("Invalid Phrase")
                if isString:
                    return ""
                else:
                    return []
        print(Output)
        print(tokenList)
        if isString :
            return Output
        else:
            return tokenList
    def close(self):
        self.master.destroy()
    def NextLine(self,event=None):
        #self.sourceOutput.insert(END, self.sourceEntry.get(self.processingLine,lineEnd))
        text = self.sourceEntry.get('1.0', END).splitlines()
        try:
            self.processingLine = int(self.linenumber.get())
        except :
            messagebox.showerror("Error", "Not a Number")
        if  -len(text)<=self.processingLine and self.processingLine<len(text):
            ### new stuff here
            self.sourceOutput.insert(END,self.CutOneLineTokens(text[self.processingLine],True)+"\n") ###call bnf with token here
            isSuccessfull = ParserClass().parser(self.CutOneLineTokens(text[self.processingLine]),self.treeOutput,self.processingLine)
            if(isSuccessfull):
                self.processingLine+=1
            self.linenumber.delete(0,END)
            self.linenumber.insert(0,self.processingLine)
            
root = Tk()
my_gui = MyFirstGUI(root)
root.mainloop()

##Verified working with
'''
float mathresult1 = 5*4.3 + 2.1;
float mathresult2 = 4.1 + 2*5.5;
if (mathresult1 > mathresult2):
    print(“I just built some parse trees”);
'''