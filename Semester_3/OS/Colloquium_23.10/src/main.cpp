#include "tasks.h"
#include "list.h"

using namespace std;

int main() {
	//Task 1 - factorials container
	try {
		int n;
		cout << "Enter factorials count: ";
		cin >> n;
		vector<unsigned long long>factorials = Tasks::calc_factorials(n);
		for (auto elem : factorials) {
			cout << elem << " ";
		}
	}
	catch (const string& error) {
		cout << "Error: " << error;
	}

	//Task 2 - delete duplicates
	vector<int> nums = { 1,2,2,3,1,3,4 };
	cout << "\nVector with duplicates: ";
	for (auto elem : nums) {
		cout << elem << " ";
	}
	Tasks::delete_duplicates(nums);
	cout << "\nVector with uniques: ";
	for (auto elem : nums) {
		cout << elem << " ";
	}

	//Task 3 - list recursive reverse
	LinkedList list;
	vector<int>values = { 1,2,3,4,5 };
	list.create(values);
	cout << "\nOriginal list: ";
	list.print();
	list.reverse();
	cout << "\nReversed list: ";
	list.print();
	list.clear();

	return 0;
}