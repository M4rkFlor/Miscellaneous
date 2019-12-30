//INSTRUCTION
//Look for ** to complete this program 
//The string output should match my hw1queueDemo.out 
//except for the trace messages

//=========================================================
//HW#: HW1P1 queue
//Your name: Marco Flores
//Complier:  g++ 
//File type: client program
//===========================================================

using namespace std;

#include <iostream>
#include <string>
#include "queue.h"

//Purpose of the program: Generate all strings using A, B, and C as the letters.
//Algorithm: Queue
int main()
{
  queue Q;//initialize Queue
  enum Letters{A,B,C};//enum for comprehensive programing
  short index=0;
  string front = "";//hold the value removed form front of queue
  string outputString=""; //holds the final result
  while(true)
    {
      try
	    {
        switch(index%3){
          case A:
            Q.add(front + "A");
            outputString += front + "A\n";
            break;
          case B:
            Q.add(front + "B");
            outputString += front + "B\n";
            break;
          case C:
            Q.add(front + "C");
            outputString += front + "C\n";
            break;
        }
        index++;
        if(index%3==0){
          Q.remove(front);
        }
        
        
      }
      catch(queue::Overflow){
        cout<<"The generated strings are:\n"<<outputString<<endl;
        cout<<"Overflow"<<endl;
        Q.displayAll();
        break;
      }
      catch(queue::Underflow){
        cout<<"Underflow"<<endl;
      }
    }
}

