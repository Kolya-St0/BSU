#include<iostream>
using namespace std;
class Human {
protected:
	static int count;	
	const int id;
public:
	Human() : id(count+1) {
		count++;
	}
	~Human() {
		count--;
	}
	virtual void printinfo() = 0;
	static int getcount() {
		return count;
	}
};
int Human::count = 0;
class Student : public Human {
protected:
	int age;
	string name;
	int course;
	int group;
public:
	Student(){}
	Student(int s_age, string s_name, int s_course, int s_group) {
		age = s_age;
		name = s_name;
		course = s_course;
		group = s_group;
	}
	Student(const Student& s) {
		age = s.age;
		name = s.name;
		course = s.course;
		group = s.group;
	}
	~Student(){}
	void printinfo() override {
		cout << "ID студента: " << id << endl;
		cout << "Возраст: " << age << "; Имя: " << name << "; Курс: " << course << "; Группа: " << group <<";" << endl;
	}
	void changeage(int new_age) {
		age = new_age;
	}
	void changecourse(int new_course) {
		course = new_course;
	}
};
class Master_student : public Student {
protected:
	string diploma;
public:
	Master_student() {}
	Master_student(int s_age, string s_name, int s_course, int s_group,string s_diploma) {
		age = s_age;
		name = s_name;
		course = s_course;
		group = s_group;
		diploma = s_diploma;
	}
	Master_student(const Master_student& s) {
		age = s.age;
		name = s.name;
		course = s.course;
		group = s.group;
		diploma = s.diploma;
	}
	~Master_student(){}
	void printinfo() override {
		cout << "ID студента: " << id << endl;
		cout << "Возраст: " << age << "; Имя: " << name << "; Курс: " << course << "; Группа: " << group << "; Диплом: "<<diploma << endl;
	}
};
int main() {
	setlocale(LC_ALL, "rus");
	Student st1(17,"Владимир", 1, 7);
	Student st2(st1);
	Master_student st3(23, "Ярик", 6, 1, "Мастер физических наук");
	st1.printinfo();
	st2.changeage(22);
	st2.changecourse(4);
	st2.printinfo();
	st3.printinfo();
	cout << "Число студентов: " << Human::getcount();
	return 0;
}