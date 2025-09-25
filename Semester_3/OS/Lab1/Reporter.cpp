#include "employee.h"

using namespace std;

int main(int argc, char* argv[]) {
	string inputname = argv[1];
	string outputname = argv[2];
	double salary = stod(argv[3]);
	ifstream in;
	in.open(inputname, ios::binary);
	ofstream out;
	out.open(outputname);
	employee e;
	while (in.read(reinterpret_cast<char*>(&e), sizeof(employee))) {
		out << e.num << " " << e.name << " " << e.hours << " " << e.hours * salary << endl;
	}
	in.close();
	out.close();
	return 0;
}