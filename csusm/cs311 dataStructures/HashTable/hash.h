#ifndef HASH_H
#define HASH_H
//Marco Flores
//g++11
//HashMap
#include <string>

using namespace std;

class Entry {//Element stored in HashMap
		string name;//private fields
		string phone;
		float salary;
  public:
		Entry(string name, string phone, float salary) {//constructor
			this->name = name;
			this->phone = phone;
			this->salary = salary;
		}
		//Implementation should be in hash.cpp or this file should be .hpp but whatever.
		string getKey() { return name; }//getters and setters
		string getPhone() {  return phone; }
		float getSalary() { return salary; }
		void setKey(string str) { name = str; }
};

class HashMap {
  public:      
	class Overflow{};
	HashMap(int size);//constructor
	~HashMap();//destructor
	unsigned long myHash(string str);//hash-function
	void put(Entry *e);//inserts element into hasmap
	Entry* get(string key);//finds element by key from hashmap and returns key with corresponding data
	Entry* remove(string key);//removes element by key from hashmap
  protected:
  	Entry **table;
	int size;
};
#endif