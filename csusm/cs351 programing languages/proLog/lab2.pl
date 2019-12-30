/*#################################
 * Append lists using recursion
 * 
 * Similar to F#, prolog lists can be cut to Head (first element) and Tail (remaining list)
 * Prolog works backwards...similar to F# recursion in some ways. You will see it in the following example.
 * 
 * Complete the Koans. Get the query: ?-my_append([1,2,5],[3,4],Result). work.
 * Set a breakpoint to the second my_append func, hit run, watch the code go step by step.
 */

/*
%Define the terminal case of the recursion: 
my_append([],List2,List2). % append an empty list to List2 results List2
%Define recursive calls:
my_append(List1,List2,ResList) :- %append List1 to List2 results ResList
	List1=[Head|Tail],    %cut List1 into Head and Tail
    my_append(Tail,List2,ResTemp), %Solve smaller question recursivly: append Tail to List2, the results will be in ResTemp
    write('Head is'),
    write(Head),
    write(". It is added to:"),
    write(ResTemp),
    nl,
    ResList = [Head|ResTemp]. %Add Head and ResTemp together to find the complete merged list
    
*/
/*Comment out above code when you are done with this question*/


/*#################################
 * Change for a dollar
 * How many nickles do you need to add to 1 dollar.
 * 
 * Make query: ?-change([0,2,3,2,Remaining]). work and give you the solution.
 * Complete Koans, set breakpoint, and observe code execution step by step.
*/
/*
change([Half,Quater,Dime,Nickel,RemainingChange]) :- 
    member(Half,[0,1,2]),    %Make sure the number of half dollars is 0,1 or 2 (total <= 1 dollar). If not, member() will return false
    member(Quater,[0,1,2,3,4]),     %Make sure the number of  quaters is 0,1,2,3,4 (total <=  1 dollar).
    member(Dime,[0,1,2,3,4,5,6,7,8,9,10]) ,    %dimes
    member(Nickel,[0,1,2,3,4,5,6,7,8,9,10,      %nickels
               11,12,13,14,15,16,17,18,19,20]),  
    SumInNickel is 50*Half + 25*Quater + 10*Dime + 5*Nickel, %Add up the current total value
    SumInNickel =< 100, %make sure the current value is less than 1 dollar
    RemainingChange is (100-SumInNickel)/5. %remianing nickles needed to get 1 dollar
*/
/*Comment out above code when you are done with this question*/

/*#################################
 * Hanoid Tower
 * Understand the puzzle: https://www.youtube.com/watch?v=5_6nsViVM00&t=74s
 * N is the number of plates you have for this game
 * X, Y, Z are variables holding left/right/center bars.
 * 
 * Understand the following code and write down comments explaining what the code is doing
 * Ask query and watch prolog solve puzzle for you: ?-move(3,left,right,center).
 * Set breakpoint on the line "N>1", run the same query and watch function calls.
 */
/*
move(1,X,Y,_) :-  %__Your comments here__
    write('Move top disk from '), 
    write(X), 
    write(' to '), 
    write(Y), 
    nl. 
move(N,X,Y,Z) :- 
    N>1, 
    M is N-1, %_decrement number of moves
    move(M,X,Z,Y), %left to center
    move(1,X,Y,_), %move left to right
    move(M,Z,Y,X).  %move center to right
*/
/*Comment out above code when you are done with this question*/

/*Optional challenge Question:
 * Define a family tree
 * Draw a small family tree and define who is who's parent.
 * 
 * Write a predicate(function) that would find out who is who's child by referencing your facts.
 * Write a predicate that would define the sibling relationship
 * Write a predicate that would define the grandparrent relationship
 * Write a predicate that would define the ancestor relationship
 * 
 *
parent(joe,bob).
parent(bob,ann).
parent(ann,phill).
parent(joe,zac).
parent(zac,jen).
parent(joe,san).
parent(san,anny).
parent(anny,jon).
parent(jon,ted).
parent(ted,dan).

children(Parent) :- 
    parent(Parent,X),
    write(X),nl.
sibling(child1,child2) :-
    parent(X,child1),
    parent(X,child2),
    write(X),nl.
 */