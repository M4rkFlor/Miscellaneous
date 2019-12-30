//INSTRUCTION
//Look for ** to complete this program 
//The output should match my hw1stackDemo.out 

//=========================================================
//HW#: HW1P1 stack
//Your name: Marco Flores
//Complier:  g++ version 8.1.0 Target: i686-w64-mingw32 (i686-posix-dwarf-rev0, Built by MinGW-W64 project)
//File type: client program
//===========================================================

using namespace std;

#include <iostream>

#include <string>

#include "stack.h"

//Purpose of the program: Evalulate Post-fix expressions
//Algorithm: Stack
int main() {
  stack postfixstack; // integer stack
  string expression; // user entered expression

  cout << "type a postfix expression: ";
  cin >> expression;

  int i = 0; // character position within expression
  char item; // one char out of the expression

  int box1; // receive things from pop
  int box2; // receive things from pop

  bool error =false;
  while (expression[i] != '\0') {
    try {
      item = expression[i]; // current char

      //2.  if it is an operand (number), 
      //    push it (you might get Overflow exception)
      if (isdigit(item)) {
        int temp = (int)item - 48;//48 is ofset to digits on ascii table
        postfixstack.push(temp);
      }
      //3.  else if it is an operator,
      //    pop the two operands (you might get Underflow exception), and
      //	apply the operator to the two operands, and
      //    push the result.
      else if ((item == '+') || (item == '-') || (item == '*')) {
        postfixstack.pop(box1);
        postfixstack.pop(box2);
        int result = 0;
        //cases for different operators follow:
        if (item == '-') result = box2 - box1;
        else if (item == '+') result = box2 + box1;
        else if (item == '*') result = box2 * box1;
        // also do the + and * cases 
        // Finally push the result
        postfixstack.push(result);
      } else throw "invalid item";
    } // this closes try

    // Catch exceptions and report problems and quit the program now. 
    // Error messages describe what is wrong with the expression.
    catch (stack::Overflow)
    {
      error =true;
      cout << "The Stack is Full "<<endl;
      break;
    } catch (stack::Underflow) // for too few operands
    {
      error =true;
      cout << "UnderFlow "<<endl;
      break;
    } catch (char const * errorcode) // for invalid item
    {
      error =true;
      cout << "error code: "<< errorcode;
      break;
    }
    i++;// go back to the loop after incrementing i
  } // end of while

 // additional logic to format output occordingly
  if(!error){

  // If anything is left on the stack, an incomplete expression was found.
  // Inform the user.
  //**
  // After the loop successfully completes: 
  // The result will be at the top of the stack. Pop it and show it.
  //**
      postfixstack.pop(i);
  if(!postfixstack.isEmpty()){
    cout<<"An incomplete expression was found."<<endl;
  }else
  {
      cout<<"Result: "<<i<<endl;
  }
  
  }
} // end of the program 