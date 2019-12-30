// Learn more about F# at http://fsharp.org
//Marco Flores
(*
open System

[<EntryPoint>]
let main argv =
    printfn "Hello World from F#!"

    0 // return an integer exit code
*)


//Q0 AssertEquality using match…with
let AssertEquality inputTuple =
  match inputTuple with
  |(a,b) when a=b -> printfn("Equal")
  |_ -> printfn("Not Equal")


//NOTE: all the below questions require Tail Recursion + Match with

//Q1 remember the example from PPT: grab the even numbers out from a list
let rec getEven mylis accumulator=
  match mylis with
  | [] -> accumulator
  | head::tail when head%2=0 -> getEven tail (head::accumulator)
  |_::tail -> getEven tail accumulator
let mylis=[1..6]
let result=getEven mylis []
printfn "Q1..."
AssertEquality (result, [6;4;2])
let result1=result |> List.rev
AssertEquality (result1, [2;4;6])

//make sure the recursive function call is the VERY LAST step of your calculation to avoid stack overflow
//Always use a result accumulator to remember the result of each step
//getEven tail (head::accumulator) instead of head::getEven tail

//Q2 modify Q1 so that you can put the reverse the result list in the function call directly
let rec getEven2 mylis accumulator=
  match mylis with
  |[]->accumulator |> List.rev
  |head::tail when head%2=0 -> getEven2 tail (head::accumulator)
  |_::tail->getEven2 tail accumulator
let result2=getEven2 mylis []
printfn "Q2..."
AssertEquality (result2, [2;4;6])

//Q3 modify Q2 and create the below function which will grab the odd numbers out from a list
let rec getOdd lis accumulator =
  match lis with
  |[]->accumulator |> List.rev
  |head::tail when head%2<>0 -> getOdd tail (head::accumulator)
  |_::tail->getOdd tail accumulator
let result3=getOdd mylis []
printfn "Q3..."
AssertEquality (result3, [1;3;5])

//Q4 Get the sum of all the even numbers in a list
let rec getEvenSum mylis sumAcc=
  match mylis with
  |[]->sumAcc
  |head::tail when head%2=0-> getEvenSum tail sumAcc+head
  |head::tail->getEvenSum tail sumAcc
let result4=getEvenSum mylis 0
printfn "Q4..."
AssertEquality (result4, 12)

//Q5 calculate the square of each number in the input list
let rec getSqr mylis sqrLis=
  match mylis with
  |[]->sqrLis|>List.rev
  |head::tail->getSqr tail ((head*head)::sqrLis)
let result5=getSqr mylis []
printfn "Q5..."
AssertEquality (result5, [1;4;9;16;25;36])

//Q6 Calculate factorial of n
//n! = 1*2*3*...*(n-1)*n
let rec factorial n ftRes=
  match n with 
  | 0 -> ftRes
  | 1 -> ftRes //this line is unnesasary in my impleimnattion
  | _ -> factorial (n-1) (ftRes*n) 

let result6=factorial 5 1
printfn "Q6..."
AssertEquality (result6, 120)

//Q7 You can merge the 2 "if statements" of the pattern 0 and 1 together like below:
let rec factorial1 n ftRes=
  match n with 
  | 0 | 1 -> ftRes
  | _ -> factorial (n-1) (ftRes*n) 

let result7=factorial1 5 1
printfn "Q7..."
AssertEquality (result7, 120)

//Q8 to help user call this function easier by using "factorial 5" instead of "factorial1 5 1" 
//(so that the API user do not need to worry about giving us the accumulator as the second func input),
//we can wrap the recursive function call inside of regular function that looks nicer
let nicer_factorial n = 
  let rec factorial1 n ftRes=
    match n with 
    | 0 | 1 -> ftRes
    | _ -> factorial (n-1) (ftRes*n)
  factorial1 5 1

let result8=nicer_factorial 5
printfn "Q8..."
AssertEquality (result8, 120)

(*
Part2 Job Simulator with Queue
Since queue is very similar to stack, you can use the stack calculator to get you started.
You know how to write a stack now. Could you implement a Queue using F# stack? The goal of this question is a Queue Task Manager. Remember using the pattern matching and tail recursion whenever possible.
You need to first generate a list of random numbers (google how to do this). Write a function that would create a list with jobCount numbers in it. 
Sample random number list: 3,4,6,1,2,9,5,6
let create_job_list jobCount resultLis =
___ 
Print out the whole list for easier debugging.
Implement a Queue type that has enqueue and dequeue functions.
Go through the list :
is an even number, dequeuer a task from the Queue and print out which task is done with format “Completed task No. 4”
--- else, push the new task into the queue with a printout notice “Added task No. 3 to the job queue”
---if the queue is empty, and you get an even number, print out a notice “No more job to do right now.”
*)
let create_job_list jobCount =
    let rand = System.Random()
    [for i in 1..jobCount do yield rand.Next()%10]
let resultList = create_job_list 5
let printJobs= lazy(
    for x in resultList do
        printfn "%d" x
    )
printfn "The Jobs are"
printJobs.Force()
type Queue (list:List<int>) = 
   new(jobSize:int) = Queue(create_job_list jobSize)
   member val Q = list with get, set
   member this.Enqueue (num:int)= 
    printfn "Added task No. %d to the job queue" num
    this.Q <- this.Q@[num]
   member this.Dequeue = 
    if this.Q.Length = 0 then printfn "No more job to do right now."
    else
    let head = this.Q.Head
    this.Q <- this.Q.Tail
    printfn "Completed task No. %d" head

//let p = Queue(resultList) //initalize Q with random list
let p = Queue(0) //initalize Q with nothing
let rec JobSim lis =
    match lis with
    |[]-> printfn "JobSim Completed"
    |head::tail when head%2=0 -> 
        p.Dequeue
        JobSim tail
    |head::tail->
        p.Enqueue head
        JobSim tail

JobSim resultList