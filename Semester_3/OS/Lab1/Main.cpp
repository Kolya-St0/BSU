#include "employee.h"

using namespace std;

void print_file_bin(string filename)
{
	cout << endl << filename << endl;
	ifstream in;
	in.open(filename, ios::binary);
	employee e;
	while (in.read(reinterpret_cast<char*>(&e), sizeof(employee))) {
		cout << e.num << " " << e.name << " " << e.hours << endl;
	}
	cout << endl;
	in.close();
}

void print_file_txt(string filename)
{
	cout << endl << filename << endl;
	ifstream in;
	in.open(filename);
	string temp;
	while (getline(in, temp)) {
		cout << temp << endl;
	}
	cout << endl;
	in.close();
}

void run_and_wait(string process)
{
	char process_name[100];
	strcpy(process_name, process.c_str());
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	if (!CreateProcess(NULL, process_name, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
		cout << "Process creation failed with error code " << GetLastError() << endl;
		return;
	}
	WaitForSingleObject(pi.hProcess, INFINITE);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}

int main() {
	string bin_filename;
	int count;
	cout << "Input bin file name and records count: ";
	cin >> bin_filename >> count;
	string creator = "Creator.exe " + bin_filename + " " + to_string(count);
	run_and_wait(creator);
	print_file_bin(bin_filename);

	string txt_filename;
	double salary;
	cout << "Input txt file name and pay per hour: ";
	cin >> txt_filename >> salary;
	string reporter = "Reporter.exe " + bin_filename + " " + txt_filename + " " + to_string(salary);
	run_and_wait(reporter);
	print_file_txt(txt_filename);

	return 0;
}
