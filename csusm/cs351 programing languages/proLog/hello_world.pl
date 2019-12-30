/*References:
 * https://www.doc.gold.ac.uk/~mas02gw/prolog_tutorial/prologpages/
 * 
 * */

/************
 * Facts
 * Always start with lowercase letter, end with full stop
 * You could use _ in facts (names), but please avoid math operators
*/

thanksgivingsoon.
sunny.
wanttoplay.

/*These are all facts. This whole page is your database for your facts & rules.
You can also ask questions/query about your database.*/

/*Now, on the right side, after the ?- ask your first query:
 * sunny.
 * Hit run and see if the answer is yes it is true
 * the ?- means asking a question, it is already provided by this complier. 
 * You would need to write it in other compliers in format: ?- sunny.
*/

/*Now, ask query: ?- raining.
 * What is the output? */
/*ERROR: Undefined procedure: raining/0 (DWIM could not correct goal)*/

/*You can defind facts with arguments. (just like a function with input variables)
 * It is just relationship between items.
 * Relation names must begin with lowercase letter as well.*/

likes(mary,food).
likes(mary,wine).
likes(john,wine).
likes(john,mary).

/*Ask query: ?- likes(mary,food).*/

/*true.*/

/*OK, some KOANS about facts: */

eats(fred,oranges).                           /* "Fred eats oranges" */
eats(fred,"T-bone steaks").                   /* "Fred eats T-bone steaks" */
eats(fred,apples).                           /* "Tony eats apples" */
eats(john,apples).                         /* "John eats apples" */

/*Ask some queries on the right side:
 * Does Fred eats T-bone steaks?
 * eats(fred,"T-bone steaks").
 * ?- eats(tony,pears). means what? does tony eat pears. What is the result?*/

/*
true.
false.
*/

/*You can also link up two sentances with ,
 * Try query:
 * ?- eats(fred,X),
 * X=oranges
 * What is the output? What is the meaning of this query? what can fred eat*/
/*
X = oranges ;
X = "T-bone steaks" ;
X = apples.
*/

age(ian,2).                   /*  Ian is 2 */

/*will query ?- age(ian, two). give yes? NO Why? because Ian is 2 not two*/

/*false. 2 is not two*/

/*************
 * Variables
 * With only the facts, we cannot really do anything productive with this PL.
 * Just like other PLs, we need variables.
 * Variables have to start with a CAPITAL letter
 * The process of matching items with variables is known as unification.*/
/*
 * X: vairable X
 * Myvar: another legal variable
 * Myvar_current: also ok*/

/*What is the result of query ?- eats(fred,FoodX). ?
 *Make sure you press next button to see all the results.
 *In other editors, you would type ; to represent show next result.*/

/*
FoodX = oranges ;
FoodX = "T-bone steaks" ;
FoodX = apples.
*/

/***********
 * Rules
 * Each rule can have several variations -- clauses.
 * Rules provide ways to get inferences about facts.
 */

/*Operator :- means if*/
mortal(X) :- 
    human(X).  /*X is mortal if X is human*/
human(petter).  /*give a fact that petter is a human*/

/*?- mortal(petter)*/ /*Ask query: is petter mortal?*/
/*What is the result of your query?*/
/*true.*/

/*?- mortal(x)*/ /*Ask query: who is mortal?*/
/*X = petter.*/ /*What is the result of your query?*/

/*One rule can have several variations.
 * The following example shows 3 ways that some thing is fun*/

fun(X) :-                      /* an item is fun if */ 
        red(X),                /* the item is red */
        car(X).                /* and it is a car */
fun(X) :-                      /*  or an item is fun if */
        blue(X),               /* the item is blue */
        bike(X).               /* and it is a bike */
fun(ice_cream).                /* and ice cream is also fun. */

/*Together with some facts:*/
car(vw_beatle).
car(ford_escort).
bike(harley_davidson).
red(vw_beatle).
red(ford_escort).
blue(harley_davidson).

/*?- fun(harley_davidson)*/ /*Ask query: is harley_davidson fun?*/
/*true.*/ /*What is the result of your query?*/
/*What are the logical steps that Prolog took to find the answer for you?
 * Hint: start matching from the first fun clause.*/
/* is harley_davidson red and car -> no
is harley_davidson blue and bike -> yes
true.*/

/*?- fun(X).*/ /*Ask query: What is fun?*/
/*
X = vw_beatle ;
X = ford_escort ;
X = harley_davidson ;
X = ice_cream.
*/
/****************
 * Recursion
 */
/*some facts:*/
move(home,taxi,halifax). /*we can move from home to hallifxa by taxi*/
move(halifax,train,gatwick). /*_we can move from hallifxa to gatwick by train*/
move(gatwick,plane,rome). /*we can move from gatwick to rome by plane*/

/*on_route is a recursive predicate*/
on_route(rome).
on_route(Place):-       /*what does this mean?*/ /*A Place is on_route to rome if */
	move(Place,_Method,NewPlace), /*can we move from X to Y*/
	on_route(NewPlace).  /*is y ROME otherwise look for route to rome.*/

/* Query ?- on_route(home). is asking whether you can reach rome from home*/
/*What are the steps that Prolog can use to find the answer for you?*/
/*checks all possibilities and eventualy finds a way or not.*/

/*Change _Method to Method, what will happen?*/
/*By adding _ in front of a variable, we make it an anonymous variable and let the complier know 
 * this var is not important so stop complaining about it.
 * Does this remind you of some thing from F#? yes the wild card _*/

/*****************
 * List
 */
/*[a,b,c,d,e,f,g]. /*a list with simple facts*/
/*[ ]*/ /*an empty list*/
/*[ dan,bob,joey ]*/ /*a list with 3 names as facts*/

/*Just like F#, list in Prolog matches Head and Tail.*/
p([H|T], H, T). /*bind/unify list [...] with head item H, and tail item T*/
/*dose [a,b,c] have heqad and tail*/ /*What is the meaning of query ?-p([a,b,c], X, Y). ?*/
/*
X = a,
Y = [b, c].
*/ /*Output?*/

/*write queries to cut H and T out from the above 3 lists. WHich 3?*/
/*[a,b,c,d,e,f,g] = [A|B].*/

/*Search an item from a list, write down the meaning of each line:*/
inList(Item,[Item|Rest]). /*item is in list*/
inList(Item,[IgnoreHead|Tail]) :- /*item in list is inList if */
    	inList(Item,Tail). /*iteam is in list*/

/*Write a query that test if apple is in the list [apple, pear, banana]*/
/* ?- inList(apple,[apple, pear, banana]).*/
/*What are the steps that Prolog can use to find the answer for you?*/
/*Attempts all soluions*/
/*Write a query that test if apple is in the list [pear, apple, banana]*/
/*?- inList(apple,[pear, apple, banana]).*/
/*What are the steps that Prolog can use to find the answer for you?*/
/*tries all posibliteis*/

/*Does this example reminds you of some thing from F#?*/
/*tail recursion*/