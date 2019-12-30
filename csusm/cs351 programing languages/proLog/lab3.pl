/*Finally, we are ready to see the power of Prolog!*/

/*Prolog is a "sepecialist": it does only few things, but does them very well.*/

/*#################
 * Natual Language Processing Example -- Parser
 * If computer wants to understand a line of code, it will check if this line of code fits into BNF grammar.
 * Similarly, if a computer wants to understand an English sentence, it would want to first check if this line is 
 * a grammatically correct.
 * 
 * 
 * Let us see a short version of English grammar that would define sentences like: a human sees a dog.
 * This is the "BNF grammar" for this sentence:
 * RULE1: Sentence is defined as -> noun_phrase+verb_phrase
 * RULE2: noun_phrase->determiner+noun   (E.g. an apple)
 * RULE3: verb_phrase->verb+noun_phrase
 * RULE4: ver_phrase -> a verb directly  (E.g. looks an apple, or looks)
 * */

/*The following is how we write the grammar into Prolog database:*/
sentence(S):- noun_phrase(Np),verb_phrase(Vp),append(Np,Vp,S). % RULE1
noun_phrase(Np):- determiner(D), noun(N),append(D,N,Np). % RULE2
verb_phrase(Vp):- verb(V),noun_phrase(N),append(V,N,Vp). % RULE3
verb_phrase(Vp):- verb(Vp),append([],Vp,Vp).% RULE4

%define words/token below
determiner([the]). % define determiner the
determiner([a]). % define determiner a

noun([human]). % define noun human
noun([cat]). % define noun cat

verb([sees]). %define verb sees

/*Run query: ?-sentence(NewSen)
 * What will this query give you?*/
/*
NewSen = [the, human, sees, the, human] ;
NewSen = [the, human, sees, the, cat] ;
NewSen = [the, human, sees, a, human] ;
NewSen = [the, human, sees, a, cat] ;
NewSen = [the, human, sees] ;
NewSen = [the, cat, sees, the, human] ;
NewSen = [the, cat, sees, the, cat] ;
NewSen = [the, cat, sees, a, human] ;
NewSen = [the, cat, sees, a, cat] ;
NewSen = [the, cat, sees] ;
NewSen = [a, human, sees, the, human] ;
NewSen = [a, human, sees, the, cat] ;
NewSen = [a, human, sees, a, human] ;
NewSen = [a, human, sees, a, cat] ;
NewSen = [a, human, sees] ;
NewSen = [a, cat, sees, the, human] ;
NewSen = [a, cat, sees, the, cat] ;
NewSen = [a, cat, sees, a, human] ;
NewSen = [a, cat, sees, a, cat] ;
NewSen = [a, cat, sees].
*/

/*Set breakpoint at line 21, run the same query step by step and observe closely.
 * How did this program work? Can you express the process using a graph (on paper, just for your own understanding)?*/
%The program goes through all possible definition combinations and builds it onto a list.

/*The above query shows you how we can generate grammatically correct sentences. 
 *Do all the generated sentances semantically correct?*/
%No because no capitilization and no periods.

/*Why do you need append in every line?*/
%to create the whole sentence

/*Now let us see how can a parser check whether the input line is a grammatically correct sentence.
 * Run query: ?-sentence([a, human, sees, the, cat]).
 * What is the output? 
 * Set breakpoint and go step by step. Can you draw a parse tree following the steps (no need to submit, just for your practice)?*/
%true.

/*We say programming languages are just like human languages all the time without really thinking this through.
 * After the above excercise, can you see the deeper link between natural vs. computer languages? 
 * What are they?
 * Can you link the complier process to the process that your brain *might* use to understand human languages?
 * For those whom has psychology background, this might be an interesting topic to go deeper.*/
%_Yes, computer language only needs to be syntatically correct to give correct results, however Natural languages also need to be sematically correct,
% and follow standard speech conventions to sound natural.


/*###################
 * PL Parser
 * We spent quite some time on parser this semester. 
 * The parsing process (those LL,LR algorithms) seems super hard to write in C++.
 * But Prolog is born for this. See below:*/

/*Let us use the BNF grammar for code like: varA=1+5
 * BNF:
 * Code->identifier equalop math
 * math->int mathop int 
 * 
 * Since the append func can only take 3 parameters, let us modify the BNF:
 * 
 * Code->identifier remaining1
 * remaining1->equalop math
 * math->int remaining2
 * remaining2->mathop int
 * 
 * modify the above grammar to Prolog
 * */

math_code(Code):- identifier(Id),remaining1(R1),append(Id,R1,Code).
remaining1(R1):- equalop(Eo),math(M),append(Eo,M,R1).
remaining2(R2):- mathop(Mo),int(I),append(Mo,I,R2).
math(MathPhrase):- int(I),remaining2(R),append(I,R,MathPhrase).

%define all the tokens below
%____your answer here, multiple lines. integer range 1-5____
identifier([varA]).
int([1]).
int([2]).
int([3]).
int([4]).
int([5]).
equalop([=]).
mathop([+]).
/*Run query: ?-math_code(NewCode).
 * What will this query do?*/
%all valid combinations of syntax

/*What query should you write if you want to check whether VarA=1+5 is a legal line of math_code?*/
%?-math_code([VarA,=,1,+,5]).
%false if casing matters so I made ID a wild card. to make true

/*Set breakpoint and go step by step. Draw a parse tree. (no need to submit, just for your practice)*/