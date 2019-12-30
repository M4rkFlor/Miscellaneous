//INSTRUCTION:
//Use the provided text to help create llist.cpp
//based on Yoshii  CS311  Notes-6A

//- Make sure PURPOSE and PARAMETER comments are given
//- Make sure all if-then-else are commented describing which case it is
//- Make sure all local variables are described fully with their purposes
//EMACS HINT:
//  control-K cuts and control-Y pastes
//  Esc X replace-str does string replacements
//  Esc > goes to the end of the file; Esc < to the beginning
//  Tab on each line will indent perfectly for C++

// ====================================================
//HW#: HW3P1 llist
//Your name: Marco Flores
//Complier:  g++
//File type: llist implementation file
//=====================================================

using namespace std;

#include<iostream>
#include"llist.h" 

llist::llist(){//Constructor
Front=Rear=nullptr,Count=0; //- initialize Front and Rear to be NULL and Count = 0. 
}//- This does not create any node.  The new list is empty.

  
llist::~llist(){//Destructor
cout<<"calling the llist Destructor."<<endl;//- Please place a cout in this function "calling the llist desctructor."
el_t temp;
while(!isEmpty()){//- while the list is not empty, call deleteFront repeatedly to delete all nodes.
  deleteFront(temp);
}
}
bool llist::isEmpty(){
  if (Front==nullptr && Rear==nullptr && Count==0){//if Front and Rear are both pointing to NULL and Count is 0.
    return true; //(all 3 conditions must be checked)
  }
  else return false;
}
  
void llist::displayAll(){ 
  if(isEmpty()){//- Special case: if the list is empty, display [ empty ] ).
    cout<<"[ empty ]"<<endl;
  }else{//- Regular:
  Node* nodePtr = Front;
  cout<<"[ ";
    while(nodePtr!=nullptr){// displays each element of the list horizontally starting from Front in [ ].
      cout<< nodePtr->Elem;
      nodePtr=nodePtr->Next;
      if(nodePtr!=nullptr){
        cout<<",";
      }else{
        cout<<" ]"<<endl;
      }
    }
  }
}

void llist::addRear(el_t NewNum){
 // 2 cases:
  if(isEmpty()){ //- Special case: if this is going to be the very first node, you must
   Node* newNode = new Node;//create a new node and 
   Front=Rear=newNode;//make Front and Rear point to it. 
   newNode->Elem=NewNum;//Place NewNum and
   Count++;//Count is updated.
  }
  else{
    Rear->Next = new Node;//Regular: adds a new node at the rear and
    Rear = Rear->Next;
    Rear->Elem = NewNum;//puts NewNum in the Elem field of this new node.
    Rear->Next = nullptr;
    Count++; //Count is updated.
  }
}


void llist::addFront(el_t NewNum){
 // 2 cases:
  if(isEmpty()){ //- Special case: if this is going to be the very first node, you must
   Node* newNode = new Node;//create a new node and 
   Front=Rear=newNode;//make Front and Rear point to it. 
   newNode->Elem=NewNum;//Place NewNum and
   Count++;//Count is updated.
  }
  else{
    Node* newNode = new Node;//Regular: add a new node to the front of the list and 
    newNode->Next = Front;//set next node
    Front = newNode;//change the front to new node
    Front->Elem = NewNum;//set the elem
    Count++; //Count is updated.
  }
}


void llist::deleteFront(el_t& OldNum){
//3 cases:
  if(isEmpty()){ //- Error case: if the List is empty, throw Underflow
    throw Underflow();
  }
  else if(Count==1){// Special case: if currently only one Node,
   OldNum = Front->Elem;//give back the front node element through OldNum (pass by reference) and
   delete Front,Rear;
   Front=Rear=nullptr;// make sure both Front and Rear become NULL. 
   Count--;//Count is updated.
  }else{ //Regular case:
  OldNum = Front->Elem;//Regular: give back the front node element through OldNum (pass by reference)
  Node *Second = Front->Next;// know the second node
  delete Front;// and also removes the front node.  
  Front = Second;
  Count--;//Count is updated.
  }
}


void llist::deleteRear(el_t& OldNum){
 //3 cases:
  if(isEmpty()){ //- Error case: if the List is empty, throw Underflow
    throw Underflow();
  }
  else if(Count==1){// Special case: if currently only one Node,
   OldNum = Rear->Elem;//give back the rear node element through OldNum (pass by reference) and
   delete Front,Rear;
   Front=Rear=nullptr;// make sure both Front and Rear become NULL. 
   Count--;//Count is updated.
  }else{ //Regular case:
  OldNum = Rear->Elem;//Regular: give back the rear node element through OldNum (pass by reference)
  Node *p =Front; //holds previous node
  while(p->Next!=Rear){//Make p go to the one right before rear (using while)
    p=p->Next;
  }
  delete Rear;// and also remove the rear node.
  Rear = p; //set rear to node before deleted
  Rear->Next=nullptr;
  Count--;//Count is updated.
  }
}


void llist::deleteIth(int I, el_t& OldNum){
 //4 cases:
 if(I>Count||I<1){//Error case: If I is an illegal value (i.e. > Count or < 1) throw OutOfRange.
  throw OutOfRange();
 }else if(I == 1 || I == Count){//- Special cases: this should simply call deleteFront when I is 1 or deleteRear when I is Count
  if(I==Count){
    deleteRear(OldNum);
  }else{
    deleteFront(OldNum);
  }
 }else{ //Regular: delete the Ith node (I starts out at 1).  Count is updated.
  Node *p1 = Front;//previous node,the node before Ith Node
for (int i = 1; i<(I-1); i++) // Move p1 to (k-1)th node, the node before Ith Node
		p1 = p1->Next;        
Node *p2 = p1->Next;//Ith Node
OldNum=p2->Elem;//set Oldnum
p1->Next = p2->Next;//Break connection
delete p2;//Delete Ith Node
Count--;
 }
}


void llist::addbeforeIth(int I, el_t newNum){
//4 cases:
if(I>Count+1||I<1){//-  Error case: If I is an illegal value (i.e. > Count+1 or < 1) throw OutOfRange.
  throw OutOfRange();
}else if(I == 1){//-  Special cases: this should simply call
  addFront(newNum);//addFront when I is 1
}else if(I == (Count+1)){
  addRear(newNum);//or addRear when I is Count+1
}
else{//-  Regular: add right before the Ith node. Cout if updated.
  Node *p1, *p2;  // p1 for pointing to (I-1)th node, p2 for pointing to Ith node.      
  Node *p = new Node; p->Elem = newNum;//create new node with newNum
  p1 = Front;//set node to begining
  for (int i = 1; i<(I-1); i++) // Move p1 to (I-1)th node            
  		p1 = p1->Next;        
  p2 = p1->Next;   // Point p2 to Ith node        
  p1->Next = p;   // (I-1)th node points to the inserted node p        
  p->Next = p2;   // the adding node p points to p2        
  Count++;//update Count
}
}