//Marco Flores
//g++11
//HashMap

#include "hash.h"
HashMap::HashMap(int size) {//constructor
    this->size = size;         
		table = new Entry*[size];            
		for (int i = 0; i < size; i++){
            table[i] = nullptr;//inconsistint intialinzing this to nullptr, since we could use new Entry("empty","empty",0); instead, howver nullptr is more effient in space complextity.
        }
}

HashMap::~HashMap(){//destructor
    for (int i = 0; i < size; i++)                  
		if (table[i] != nullptr)                        
			delete table[i];//delete all elemets in the table            
	delete[] table;//delete data of array calling each of their destructor, however Entry class has no destructor so it dosent realy matter that it is delete[].
}
//impliments DJB2 hash
unsigned long HashMap::myHash(string str){
    const char* cstr = str.c_str();//convert to cstring to c style string manipulation
    unsigned long hash = 5381;//Magic starting number
    int c;
    while(c = *cstr++)
        hash=hash*33+c;//hash gets large fast that is why it is unsigned long
    return hash;  //return the calculated hash
}
void HashMap::put(Entry *e){
    string key = e->getKey();       
	int index = myHash(key) % size; //calculate index           
	int startIndex = index;            
	while (table[index] != nullptr && table[index]->getKey() != key && table[index]->getKey() != "empty") {          
		index = (index + 1) % size;
		if(index == startIndex) throw Overflow();//searched the whole arrary and no empty space found
	}
	table[index] = e; //insert element to table
}
Entry* HashMap::get(string key){
    int index = myHash(key) % size;  //calculate index         
	int startIndex = index;            
	while (table[index] != nullptr && table[index]->getKey() != key) {                  
		index = (index + 1) % size;                  
		if(index == startIndex)	return nullptr; //searched the whole arrary and element not found ,return null  
	}            
	return table[index];
}
Entry* HashMap::remove(string key){
    int index = myHash(key) % size;//calculate index          
	int startIndex = index;            
	while (table[index] != nullptr && table[index]->getKey() != key) {                  
		index = (index + 1) % size;                  
		if(index == startIndex)	return nullptr;//searched the whole arrary and element not found nothing to delete           
	}            
	Entry *e = table[index];
	delete e;
	table[index] = new Entry("empty","empty",0);//could be nullptr but code above explicity checks if key is "empty" and treats it as null
	return e;

}