#include <iostream>
#include <regex>
#include <fstream>
#include <string>
using namespace std;
bool psrtnumcheck(const string& psrt) {
	regex rgx("^\\d{7}[ABCKEMH]\\d{3}(PB|BI|BA)\\d\\s+[А-Яа-я]+\\s+(?:РУВД)\\s+[А-Яа-я]+$");
	return regex_match(psrt, rgx);
}
void checkresult(string*& psrt, const int& size) {
	for (int i = 0; i < size; i++) {
		if (psrtnumcheck(psrt[i])) {
			psrt[i] += " - правильный номер";
		}
		else {
			psrt[i] += " - неправильный номер";
		}
	}
}
void printstrings(string* psrt,const int& size) {
	for (int i = 0; i < size; i++) {
		cout << psrt[i] << endl;
	}
}
void readfromfile(string filename, string*& psrt, int& size) {
	ifstream in;
	in.open(filename);
	if (!in.is_open()) {
		cout << "Ошибка при открытии файла для чтения" << endl;
	}
	else {
		cout << "Файл для чтения открыт" << endl;
		string temp;
		int k = 0;
		while (getline(in, temp)) {
			k++;
		}
		size = k;
		psrt = new string[size];
		in.clear();
		in.seekg(0, ios::beg);
		for (int i = 0; i < size; i++) {
			getline(in, psrt[i]);
		}
	}
	in.close();
}
void writetofile(string filename, string* psrt,const int& size) {
	ofstream out;
	out.open("2.txt");
	if (!out.is_open()) {
		cout << "Ошибка при открытии файла для записи" << endl;
	}
	else {
	    cout << "Файл для записи открыт" << endl;
		for (int i = 0; i < size; i++) {
			out << psrt[i] << endl;
		}
	}
	out.close();
}
int main() {
	setlocale(LC_ALL, "rus");
	string* psrt = nullptr;
	int size = 0;
	readfromfile("1.txt", psrt, size);
	checkresult(psrt, size);
	printstrings(psrt, size);
	writetofile("2.txt", psrt, size);
	delete[]psrt;
	return 0;
}