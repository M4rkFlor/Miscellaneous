// Learn more about F# at http://fsharp.org

open System

[<EntryPoint>]
let main argv =
    printfn "Hello World from F#!"
    let expected_value = 1 + 1
    let actual_value = 2
    
    let AssertEquality a b  = if a<>b then printfn "Failed" else printfn "Test Succses"
    AssertEquality expected_value actual_value
    AssertEquality "foo" "foo"

    let x = 50
    AssertEquality x 50
    //lINE 56
    let typeOfX = x.GetType()
    AssertEquality typeOfX typeof<int>
    
    let y = "a string"
    let expectedType = y.GetType()
    AssertEquality expectedType typeof<string>

    let (x:int) = 42
    let typeOfX = x.GetType()
    
    let y:string = "forty two"
    let typeOfY = y.GetType()
    
    AssertEquality typeOfX typeof<int>
    AssertEquality typeOfY typeof<string>

    let x = 20
    let typeOfX = x.GetType()
    
    let y = 20.0
    let typeOfY = y.GetType()
    
    //you don't need to modify these
    AssertEquality typeOfX typeof<int>
    AssertEquality typeOfY typeof<float>
   
   //Line 109
    let mutable a = 100
    a <- 200
    AssertEquality a 200

    //Shadowing has been working this whole time
    let add x y =
        x + y
    
    let result1 = add 2 2
    let result2 = add 5 2
    
    AssertEquality result1 4
    AssertEquality result2 7
    //Line 159
    let quadruple x =
        let double x =
            x * 2
        double(double(x))
    let result = quadruple 4
    AssertEquality result 16
    //line 172
    let sayItLikeAnAuctioneer (text:string) =
        text.Replace(" ", "")//if type annotation removed cant assume what type is
    
    let auctioneered = sayItLikeAnAuctioneer "going once going twice sold to the lady in red"
    AssertEquality auctioneered "goingoncegoingtwicesoldtotheladyinred"
    //Lne 189
    let suffix = "!!!"
    
    let caffinate (text:string) =
        let exclaimed = text + suffix
        let yelled = exclaimed.ToUpper()
        yelled.Trim()
    
    let caffinatedReply = caffinate "hello there"

    AssertEquality caffinatedReply "HELLO THERE!!!"
    
    let add x y =
        x + y
    
    let result = add (add 5 8) (add 1 1)

    AssertEquality result 15
    //Line229
    let add x y =
        x + y
    
    let double x =
        x * 2
    
    let result = double <| add 5 8
    
    AssertEquality result 26

    let sendData data =
        //...pretend we are sending the data to the server...
        ()
    
    let x = sendData "data"
    AssertEquality x () //Don't overthink this

    // ---- parameterless fucntions take unit as their argument -----
    let sayHello() =
        "hello"
    
    let result = sayHello()
    AssertEquality result "hello"

    //Line 280
    // ---- creating tuples -----
    
    let items = ("apple", "dog")
    
    AssertEquality items ("apple", "dog")
    
    //---------------------------------------------------------------
    
    // ---- accessing tuple elements --------------------------------
    
    let items = ("apple", "dog")
     
    let fruit = fst items
    let animal = snd items
     
    AssertEquality fruit "apple"
    AssertEquality animal "dog"

    let items = ("apple", "dog", "Mustang")

    let fruit, animal, car = items
    
    AssertEquality fruit "apple"
    AssertEquality animal "dog"
    AssertEquality car "Mustang"

    let items = ("apple", "dog", "Mustang")
    
    let _, animal, _ = items
    
    AssertEquality animal "dog"
    
    let squareAndCube x =
        (x ** 2.0, x ** 3.0)
    
    let squared, cubed = squareAndCube 3.0
    
    
    AssertEquality squared 9.0
    AssertEquality cubed 27.0
    
    let squareAndCube x =
        (x ** 2.0, x ** 3.0)
                
    let result = squareAndCube 3.0
           
    AssertEquality result (9.0,27.0)
    //Line 357
    let isEven x =
        if x % 2 = 0 then
            "it's even!"
        else
            "it's odd!"
            
    let result = isEven 2        
    AssertEquality result "it's even!"
    
    let result = 
        if 2 = 3 then
            "something is REALLY wrong"
        else
            "math is workng!"
    
    AssertEquality result "math is workng!"

    let isApple x =
        match x with
        | "apple" -> true
        | _ -> false
    
    let result1 = isApple "apple"
    let result2 = isApple ""
    
    AssertEquality result1 true
    AssertEquality result2 false
    
    //407
    let getDinner x = 
        let name, foodChoice = x
        
        if foodChoice = "veggies" || foodChoice ="fish" || 
           foodChoice = "chicken" then
            sprintf "%s doesn't want red meat" name
        else
            sprintf "%s wants 'em some %s" name foodChoice
     
    let person1 = ("Chris", "steak")
    let person2 = ("Dave", "veggies")
    
    AssertEquality (getDinner person1) "Chris wants 'em some steak"
    AssertEquality (getDinner person2) "Dave doesn't want red meat"

    let getDinner x =
        match x with
        | (name, "veggies")
        | (name, "fish")
        | (name, "chicken") -> sprintf "%s doesn't want red meat" name
        | (name, foodChoice) -> sprintf "%s wants 'em some %s" name foodChoice 
        
    let person1 = ("Bob", "fish")
    let person2 = ("Sally", "Burger")
    
    AssertEquality (getDinner person1) "Bob doesn't want red meat"
    AssertEquality (getDinner person2) "Sally wants 'em some Burger"
    //Line 444
    let list = ["apple"; "pear"; "grape"; "peach"]
    
    //Note: The list data type in F# is a singly linked list, 
    //      so indexing elements is O(n). 
     
    AssertEquality list.Head "apple"
    AssertEquality list.Tail ["pear"; "grape"; "peach"]
    AssertEquality list.Length 4
       
    let first = ["grape"; "peach"]
    let second = "pear" :: first
    let third = "apple" :: second
    
    //Note: "::" is known as "cons"
    
    AssertEquality ["apple"; "pear"; "grape"; "peach"] third
    AssertEquality second ["pear";"grape"; "peach"]
    AssertEquality first ["grape"; "peach"]
    
    //yes you can change a linked list 

    let first = ["apple"; "pear"; "grape"]
    let second = first @ ["peach"]
    
    AssertEquality first ["apple"; "pear"; "grape"]
    AssertEquality second ["apple"; "pear"; "grape";"peach"]

    let list = [0..4]
    
    AssertEquality list.Head 0
    AssertEquality list.Tail [1;2;3;4]

    let list = [for i in 0..4 do yield i ]
    AssertEquality list [0;1;2;3;4]

    let list = [for i in 0..10 do if i % 2 = 0 then yield i ]
            
    AssertEquality list [0;2;4;6;8;10]

    //541
    let square x =
        x * x
    
    let original = [0..5]
    let result = List.map square original
    
    AssertEquality original [0;1;2;3;4;5]
    AssertEquality result [0;1;4;9;16;25]

    let isEven x =
        x % 2 = 0
    
    let original = [0..5]
    let result = List.filter isEven original
    
    AssertEquality original [0;1;2;3;4;5]
    AssertEquality result [0;2;4]

    //569
    let isOdd x =
        not(x % 2 = 0)
    
    let original = [0..5]
    let result1, result2 = List.partition isOdd original
    
    AssertEquality result1 [1;3;5]
    AssertEquality result2 [0;2;4]

    let square x =
        x * x
    
    let isEven x =
        x % 2 = 0
    
    (* One way to combine operations is by using separate statements.
       However, this is can be clumsy since you have to name each result. *)
    
    let numbers = [0..5]
    
    let evens = List.filter isEven numbers
    let result = List.map square evens
    
    AssertEquality result [0;4;16]
    //619
    let numbers = [0..5]
    
    let result = List.map square (List.filter isEven numbers)
    
    AssertEquality result [0;4;16]

    let result =
        [0..5]
        |> List.filter isEven
        |> List.map square
    
    AssertEquality result [0;4;16]

    let (|>) x y =
        y x
    
    let result =
        [0..5]
        |> List.filter isEven
        |> List.map square
    
    AssertEquality result [0;4;16]

    let fruits = [| "apple"; "pear"; "peach"|]
    
    AssertEquality fruits.[0] "apple"
    AssertEquality fruits.[1] "pear"
    AssertEquality fruits.[2] "peach"

    
    let fruits = [| "apple"; "pear" |]
    fruits.[1] <- "peach"
    
    AssertEquality fruits [|"apple";"peach"|]

    let numbers = 
        [| for i in 0..10 do 
               if i % 2 = 0 then yield i |]
    
    AssertEquality numbers [|0;2;4;6;8;10|]
    //680
    //skipin .net starting from line 795
    let values = [0..10]
    
    let mutable sum = 0
    for value in values do
        sum <- sum + value
    
    AssertEquality sum 55

    let mutable sum = 1
    
    while sum < 10 do
        sum <- sum + sum
    
    AssertEquality sum 16
     
     //855
    let colors = ["maize"; "blue"]

    let echo = 
        colors
        |> List.map (fun x -> x + " " + x)

    AssertEquality echo ["maize maize";"blue blue"]

    let add x =
        (fun y -> x + y)
    
    (* F#'s lightweight syntax allows you to call both functions as if there
       was only one *)
    let simpleResult = add 2 4
    AssertEquality simpleResult 6

    let addTen = add 10
    let fancyResult = addTen 14
    
    AssertEquality fancyResult 24
    //894
    let add x y = 
        x + y
    
    let addSeven = add 7
    let unluckyNumber = addSeven 6
    let luckyNumber = addSeven 0
    
    AssertEquality unluckyNumber 13
    AssertEquality luckyNumber 7

    let add(x, y) =
        x + y
    
    (* NOTE: "add 5" will not compile now. You have to pass both arguments 
             at once *)
    
    let result = add(5, 40)
    
    AssertEquality result 45
    // goal is 928
    
    let stockData =
        [ "Date,Open,High,Low,Close,Volume,Adj Close";
          "2012-03-30,32.40,32.41,32.04,32.26,31749400,32.26";
          "2012-03-29,32.06,32.19,31.81,32.12,37038500,32.12";
          "2012-03-28,32.52,32.70,32.04,32.19,41344800,32.19";
          "2012-03-27,32.65,32.70,32.40,32.52,36274900,32.52";
          "2012-03-26,32.19,32.61,32.15,32.59,36758300,32.59";
          "2012-03-23,32.10,32.11,31.72,32.01,35912200,32.01";
          "2012-03-22,31.81,32.09,31.79,32.00,31749500,32.00";
          "2012-03-21,31.96,32.15,31.82,31.91,37928600,31.91";
          "2012-03-20,32.10,32.15,31.74,31.99,41566800,31.99";
          "2012-03-19,32.54,32.61,32.15,32.20,44789200,32.20";
          "2012-03-16,32.91,32.95,32.50,32.60,65626400,32.60";
          "2012-03-15,32.79,32.94,32.58,32.85,49068300,32.85";
          "2012-03-14,32.53,32.88,32.49,32.77,41986900,32.77";
          "2012-03-13,32.24,32.69,32.15,32.67,48951700,32.67";
          "2012-03-12,31.97,32.20,31.82,32.04,34073600,32.04";
          "2012-03-09,32.10,32.16,31.92,31.99,34628400,31.99";
          "2012-03-08,32.04,32.21,31.90,32.01,36747400,32.01";
          "2012-03-07,31.67,31.92,31.53,31.84,34340400,31.84";
          "2012-03-06,31.54,31.98,31.49,31.56,51932900,31.56";
          "2012-03-05,32.01,32.05,31.62,31.80,45240000,31.80";
          "2012-03-02,32.31,32.44,32.00,32.08,47314200,32.08";
          "2012-03-01,31.93,32.39,31.85,32.29,77344100,32.29";
          "2012-02-29,31.89,32.00,31.61,31.74,59323600,31.74"; ]
    
    //start your program here
    let mutable greatestDifference = 0.0
    let mutable differenceDate = ""
        

    let findGreatest  =
        for stockDate in stockData do
            let words = stockDate.Split [|','|]
            if words.[0] <> "Date" then
                let difference = abs (float words.[1] - float words.[4]) //open - close
                if difference > greatestDifference then do
                    greatestDifference <- difference
                    differenceDate<-words.[0]
        (differenceDate)
        
    let result = findGreatest //and put your result here to check your work
    
    AssertEquality "2012-03-13" result
    

    let add a b =
        a+b
    let res1 = add 3 6

    let res2 = add 4 3

    AssertEquality res1  9
    AssertEquality res2  7
    

    let addThreeNumbers x y z =
        //create a nested helper function
        let add n =
            fun x -> x+n
        // use the helper function      
        x |> add y |> add z //meaning: send x through a pipe; perform add y; send the result through a pipe; perform add z.

    let Sum3=addThreeNumbers 5 6 7

    AssertEquality Sum3 18
    0 // return an integer exit code