//INSTRUCTION
//Look for **
//Fill in the function body
//When done, compile queue.cpp to make sure it has no syntax errors

//=========================================================
//HW#: HW1P1 queue
//Your name: Marco Flores
//Complier:  g++
//File type: .cpp
//===========================================================

using namespace std;
#include <iostream>
#include "queue.h"  

// constructor 
queue::queue()
{
    front = -1; //initilaize values
    rear =  -1;
    count = 0;
}

//destructor 
queue::~queue()
{
}

// PURPOSE: returns true if queue is empty, otherwise false
bool queue::isEmpty()
{
    if(count==0){
        return true;
    }
    else{
        return false;
    }
}

// PURPOSE: returns true if queue is full, otherwise false
bool queue::isFull()
{
    if(count==MAX_SIZE){
        return true;
    }
    else{
        return false;
    }
}

// PURPOSE: if full, throws an exception Overflow
// if not full, enters an element at the rear 
// PAREMETER: provide the element (newElem) to be added
void queue::add(el_t newElem)
{
    if(isFull()){
        throw Overflow();
    }else{
        rear++;//need to increase rear first
        if(isEmpty()){
            front++;
        }
        else{
            if(rear==MAX_SIZE){
                rear=0;
            }
        }
        count++;
        el[rear] = newElem;
    }
}

// PURPOSE: if empty, calls an emergency exit routine
// if not empty, removes the front element to give it back 
// PARAMETER: provide a holder (removedElem) for the element removed (pass by ref)
void queue::remove(el_t& removedElem)
{
    if(isEmpty()){
        throw Underflow();
    }else{
        removedElem = el[front]; //save element before deleting
        front++;//removes by incresing
        if(front==MAX_SIZE){
                front=0;
            }
        count--;
    }
}

// PURPOSE: if empty, throws an exception Underflow
// if not empty, give back the front element (but does not remove it)
//PARAMETER: provide a holder (theElem) for the element (pass by ref)
void queue::frontElem(el_t& theElem)
{
    if(isEmpty()){
        throw Underflow();
    }
    else{
        theElem = el[front];
    }
}

// PURPOSE: returns the current size to make it 
// accessible to the client caller
int queue::getSize()
{
    return count;
}

// PURPOSE: display everything in the queue horizontally from front to rear
// enclosed in []
// if empty, displays [ empty ]
void queue::displayAll()
{
    if(isEmpty()){
        cout<<"[ empty ]"<<endl;
    }else{
        if(front>rear){
            for(int i=front;i<MAX_SIZE;i++){
                cout<<el[i]<<endl;
            }
            for(int i = 0;i<=rear;i++){
                cout<<el[i]<<endl;
            }
        }else{
            for(int i=front;i<=rear;i++){
                cout<<el[i]<<endl;
            }
        }
    }
}

// PURPOSE: if empty, throws an exception Underflow
//if queue has just 1 element, does nothing
//if queue has more than 1 element, moves the front one to the rear by
//doing remove followed by add.
void queue::goToBack()
{
    if(isEmpty()){
        throw Underflow();
    }
    else if(count==1){
        return;
    }else{
        //push front to back
        el_t temp;//used to pass by reference
        remove(temp);
        add(temp);
    }
}