#include "employee.h"

using namespace std;

int main(int argc, char* argv[]) {
	string filename = argv[1];
	int count = stoi(argv[2]);
	ofstream out;
	out.open(filename, ios::binary);
	cout << "Enter " << count << " employees" << endl;
	for (int i = 0; i < count; i++) {
		employee e;
		cin >> e.num >> e.name >> e.hours;
		out.write(reinterpret_cast<char*>(&e), sizeof(employee));
	}
	out.close();
	return 0;
}