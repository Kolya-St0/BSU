#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <type_traits>
using namespace std;

struct Element3;
struct Element2;

struct Element1
{
	char Name[50];
	char Addr[50];
	double Price;

	friend istream& operator>>(istream& in, Element1& elem)
	{
		in >> elem.Name >> elem.Addr >> elem.Price;
		return in;
	}

	friend ostream& operator<<(ostream& out, const Element1& elem) 
	{
		out << elem.Name << " | " << elem.Addr<< " | "<< elem.Price;
		return out;
	}

	template <class T>
	Element1& operator = (T& elem)
	{
		strcpy(this->Name, elem.Name);
		strcpy(this->Addr, elem.Addr);
		if constexpr (is_same <T,Element2>::value) {
			Price = 0;
		}
		else {
			this->Price = elem.Price;
		}
		return *this;
	}

	bool operator < (Element1& elem)
	{
		if (strcmp(Addr, elem.Addr) < 0) {
			return true;
		}
		else {
			return false;
		}
	}

	template <class T>
	bool operator == (T& elem) {
		if (strcmp(Name, elem.Name)!= 0 || strcmp(Addr, elem.Addr)!= 0) {
			return false;
		}
		else {
			return true;
		}
	}
};

struct Element2
{
	char Name[50];
	char Addr[50];

	friend istream& operator >> (istream& in, Element2& elem) 
	{
		in >> elem.Name >> elem.Addr;
		return in;
	}

	friend ostream& operator << (ostream& out, Element2& elem) 
	{
		out << elem.Name << " | " << elem.Addr;
		return out;
	}

	template<class T>
	Element2& operator = (T& elem) 
	{
		strcpy(this->Name, elem.Name);
		strcpy(this->Addr, elem.Addr);
		return *this;
	}

	bool operator < (Element2& elem)
	{
		if (strcmp(Name, elem.Name) < 0) {
			return true;
		}
		else {
			return false;
		}
	}

	template <class T>
	bool operator == (T& elem)
	{
		if (strcmp(Name, elem.Name) != 0 || strcmp(Addr, elem.Addr) != 0) {
			return false;
		}
		else {
			return true;
		}
	}
};

struct Element3
{
	char Name[50];
	char Addr[50];
	double Price;

	friend istream& operator >> (istream& in, Element3& elem)
	{
		in >> elem.Name >> elem.Addr >> elem.Price;
		return in;
	}

	friend ostream& operator << (ostream& out, Element3& elem)
	{
		out << elem.Name << " | " << elem.Addr << " | " << elem.Price;
		return out;
	}

	template <class T>
	Element3& operator = (T& elem)
	{
		strcpy(this->Name, elem.Name);
		strcpy(this->Addr, elem.Addr);
		if constexpr (is_same <T, Element2>::value) {
			Price = 0;
		}
		else {
			this->Price = elem.Price;
		}
		return *this;
	}

	bool operator < (const Element3& elem)
	{
		if (strcmp(Name, elem.Name) < 0) {
			return true;
		}
		else {
			return false;
		}
	}

	bool operator > (double& k)
	{
		if (Price > k) {
			return true;
		}
		else {
			return false;
		}
	}

	template <class T>
	bool operator == (T& elem) 
	{
		if (strcmp(Name, elem.Name) != 0 || strcmp(Addr, elem.Addr) != 0) {
			return false;
		}
		else {
			return true;
		}
	}
};

template <typename T>
class MASSIV
{
	int size;
	T* array;

public:

	MASSIV() {
		array = NULL;
		size = 0;
	}

	MASSIV(int n) {
		size = n;
		array = new T[size];
	}

	MASSIV(MASSIV <T>& arr) {
		array = arr;
	}

	~MASSIV() {
		delete[]array;
	}

	int getsize() {
		return size;
	}

	friend istream& operator >> (istream& in, MASSIV& arr)
	{
		int n;
		cout << "Введите размер массива: ";
		in >> n;
		MASSIV x(n);
		arr = x;
		cout << "Введите элементы: ";
		for (int i = 0; i < n; i++) {
			in >> arr[i];
		}
		return in;
	}

	friend ostream& operator << (ostream& out, MASSIV& arr)
	{
		for (int i = 0; i < arr.size; i++) {
			out << arr[i] << endl;
		}
		return out;
	}

	template <class T1>
	MASSIV& operator = (MASSIV <T1>& mas)
	{
		size = mas.getsize();
		array = new T[size];
		for (int i = 0; i < size; i++) {
			array[i] = mas[i];
		}
		return *this;
	}

	T& operator [](int index)
	{
		return array[index];
	}

	void readfromfile(string filename)
	{
		ifstream in;
		in.open(filename);
		if (!in.is_open()) {
			cout << "Ошибка при открытии файла для чтения" << endl;
		}
		else {
			cout << "Файл для чтения (" << filename << ") открыт" << endl;
			string temp;
			size = 0;
			while (getline(in, temp)) {
				size++;
			}
			array = new T[size];
			in.clear();
			in.seekg(0, ios::beg);
			int i = 0;
			while (!in.eof() && i < size) {
				in >> array[i];
				i++;
			}
		}
		in.close();
	}

	void writetofile(string filename)
	{
		ofstream out;
		out.open(filename);
		if (!out.is_open()) {
			cout << "Ошибка при открытии файла для записи" << endl;
		}
		else {
			cout << "Файл для записи (" << filename << ") открыт" << endl;
			for (int i = 0; i < size; i++) {
				out << array[i] << endl;
			}
		}
		out.close();
	}

	void writetofilebin(string filename) {
		ofstream out;
		out.open(filename, ios::binary);
		if (!out.is_open()) {
			cout << "Ошибка при открытии бинарного файла для записи" << endl;
		}
		else {
			cout << "Бинарный файл для записи (" << filename << ") открыт" << endl;
			for (int i = 0; i < size; i++) {
				out.write((char*)&array[i], sizeof(T));
			}
		}
		out.close();
	}

	void readfromfilebin(string filename) {
		ifstream in;
		in.open(filename, ios::binary);
		if (!in.is_open()) {
			cout << "Ошибка при открытии бинарного файла для чтения" << endl;
		}
		else {
			cout << "Бинарный файл для чтения (" << filename << ") открыт" << endl;
			T temp;
			size = 0;
			while (in.read((char*)&temp, sizeof(T))) {
				size++;
			}
			in.clear();
			in.seekg(0, ios::beg);
			array = new T[size];
			for (int i = 0; i < size; i++) {
				in.read((char*)&array[i], sizeof(T));
			}
		}
		in.close();
	}

	template <class T1, class T2>
	void substraction(MASSIV <T1>& mas1, MASSIV <T2>& mas2)
	{
		size = 0;
		bool check;
		for (int i = 0; i < mas1.getsize(); i++) {
			check = false;
			for (int j = 0; j < mas2.getsize(); j++) {
				if (mas1[i] == mas2[j]) {
					check = true;
				}
			}
			if (!check) {
				size++;
			}
		}
		array = new T[size];
		int k = 0;
		for (int i = 0; i < mas1.getsize(); i++) {
			check = false;
			for (int j = 0; j < mas2.getsize(); j++) {
				if (mas1[i] == mas2[j]) {
					check = true;
				}
			}
			if (!check) {
				array[k] = mas1[i];
				k++;
			}
		}
	}
	void sort();
	template <typename T> friend void search(MASSIV<T>&, double&);
};

template <typename T>
void search(MASSIV<T>&mas, double& k) {
	for (int i = 0; i < mas.size; i++) {
		if (mas.array[i] > k) {
			cout << mas.array[i] << endl;
		}
	}
}

template <typename T>
void MASSIV<T>::sort() {
	T temp;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size - 1 - i; j++) {
			if (array[j + 1] < array[j]) {
				temp = array[j + 1];
				array[j + 1] = array[j];
				array[j] = temp;
			}
		}
	}
}

int main() {
	setlocale(LC_ALL, "rus");
	srand(time(0));
	MASSIV <Element1> mas1;
	mas1.readfromfile("1_чтение.txt");
	mas1.sort();
	mas1.writetofile("1_запись.txt");
	MASSIV<Element2> mas2;
	mas2.readfromfile("2_чтение.txt");
	mas2.writetofile("2_запись.txt");
	MASSIV<Element3> mas3;
	mas3.substraction(mas1, mas2);
	mas3.writetofile("3_запись.txt");
	double k;
	cout << "Введите k для вывода студентов с большей задолженностью: ";
	cin >> k;
	search(mas3,k);
	mas3.writetofilebin("3bin_запись.bin");
	MASSIV<Element3> mas4;
	mas4.readfromfilebin("3bin_запись.bin");
	cout << mas4;
	MASSIV<char>mas5;
	cin >> mas5;
	mas5.sort();
	cout << mas5;
	return 0;
}