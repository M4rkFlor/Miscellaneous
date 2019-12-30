//Marco Flores
//g++11
//HashMap
#include <iostream>
#include "hash.h"

using namespace std;

int main() {
	HashMap table(128);
	Entry *e1 = new Entry("Sam", "760-750-4567", 100000);
	Entry *e2 = new Entry("Mary", "760-750-1234", 120000);
	Entry *e3 = new Entry("Jim", "760-750-0000", 70000);
	table.put(e1);
	table.put(e2);
	table.put(e3);

	string key;
	cout << "Type in the search key (use 'q' for quit): ";
	cin >> key;
	while(key != "q") {
		Entry *e = table.get(key);
		if(e != NULL)
			cout << e->getKey() << "'s phone number is " << e->getPhone() << ", and salary is " << e->getSalary() << endl;
		else
			cout << "The key '" << key << "'' is not in the table." << endl;
		cout << "Type in the search key (use 'q' for quit): ";
		cin >> key;
	}
	return 0;
}