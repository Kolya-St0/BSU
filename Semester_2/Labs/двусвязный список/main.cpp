#include "header.h"

int main() {
	setlocale(LC_ALL, "rus");
	LinkedList list;
	list.push_front("Sony", 60, 349.99);
	list.push_back("Panasonic", 90, 529.99);
	list.push_front("TOSHIBA", 50, 299.99);
	list.insert("Sealgate", 120, 699.99, 2);
	cout << list << endl;
	list.readfromfile("1.txt");
	cout << list << endl;
	list.sort("name");
	cout << list << endl;
	list.erase(2);
	cout << list<<endl;
	list.pop_front();
	cout << list << endl;
	list.pop_back();
	cout << list << endl;
	list.writetofile("2.txt");
	return 0;
}