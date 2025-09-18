// OS_1.cpp: определяет точку входа для приложения.
//

#include "employee.h"

using namespace std;

void print_creator(string filename)
{
	cout << endl;
	ifstream in;
	in.open(filename, ios::binary);
	employee e;
	while (in.read(reinterpret_cast<char*>(&e), sizeof(employee))) {
		cout << e.num << " " << e.name << " " << e.hours << endl;
	}
	in.close();
}

void print_txt(string filename)
{
	cout << endl;
	ifstream in;
	in.open(filename);
	string temp;
	while (getline(in, temp)) {
		cout << temp << endl;
	}
	in.close();
}

int main() {
	string bin_filename;
	int count;
	cin >> bin_filename >> count;
	string process_temp = "Creator.exe " + bin_filename + " " + to_string(count);
	char process[50];
	strcpy(process, process_temp.c_str());

	STARTUPINFO siCreator;
	PROCESS_INFORMATION piCreator;
	ZeroMemory(&siCreator, sizeof(siCreator));
	siCreator.cb = sizeof(siCreator);
	ZeroMemory(&piCreator, sizeof(piCreator));
	if (!CreateProcess(NULL, process, NULL, NULL, FALSE, 0, NULL, NULL, &siCreator, &piCreator)) {
		cout << ":(";
		return 1;
	}
	WaitForSingleObject(piCreator.hProcess, INFINITE);
	CloseHandle(piCreator.hProcess);
	CloseHandle(piCreator.hThread);
	print_creator(bin_filename);

	double salary;
	string txt_filename;
	cin >> txt_filename >> salary;
	process_temp = "Reporter.exe " + bin_filename + " " + txt_filename + " " + to_string(salary);
	strcpy(process, process_temp.c_str());

	STARTUPINFO siReporter;
	PROCESS_INFORMATION piReporter;
	ZeroMemory(&siReporter, sizeof(siReporter));
	siReporter.cb = sizeof(siReporter);
	ZeroMemory(&piReporter, sizeof(piReporter));
	if (!CreateProcess(NULL, process, NULL, NULL, FALSE, 0, NULL, NULL, &siReporter, &piReporter)) {
		cout << ":(";
		return 1;
	}
	WaitForSingleObject(piReporter.hProcess, INFINITE);
	CloseHandle(piReporter.hProcess);
	CloseHandle(piReporter.hThread);

	print_txt(txt_filename);
	return 0;
}