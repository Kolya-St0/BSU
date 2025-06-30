#include "header.h"
#include <fstream>

Node::Node() {
	name = "";
	volume = 0;
	price = 0.0;
	next = prev = nullptr;
}

Node::Node(string fname, int fvolume, double fprice) {
	name = fname;
	volume = fvolume;
	price = fprice;
	next = prev = nullptr;
}

istream& operator >> (istream& in, Node* ptr) {
	in >> ptr->name >> ptr->volume >> ptr->price;
	return in;
}

ostream& operator << (ostream& out, const Node* ptr) {
	out << ptr->name << " | " << ptr->volume << "GB | " << ptr->price << "Р";
	return out;
}


LinkedList::LinkedList() {
	head = tail = nullptr;
}

LinkedList::~LinkedList() {
	clear();
}

Node* LinkedList::getat(int index) {
	Node* ptr = head;
	int n = 0;
	while (n != index && ptr != nullptr) {
		ptr = ptr->next;
		n++;
	}
	return ptr;
}

Node* LinkedList::operator[](int index) {
	return getat(index);
}

ostream& operator<<(ostream& out, LinkedList& list) {
	for (Node* ptr = list.head; ptr != nullptr; ptr = ptr->next) {
		out << ptr << endl;
	}
	return out;
}

void LinkedList::push_front(string name, int volume, double price) {
	Node* ptr;
	ptr = new Node(name, volume, price);
	ptr->next = head;
	if (head != nullptr) {
		head->prev = ptr;
	}
	if (tail == nullptr) {
		tail = ptr;
	}
	head = ptr;
}

void LinkedList::push_back(string name, int volume, double price) {
	Node* ptr;
	ptr = new Node(name, volume, price);
	ptr->prev = tail;
	if (tail != nullptr) {
		tail->next = ptr;
	}
	if (head == nullptr) {
		head = ptr;
	}
	tail = ptr;
}

void LinkedList::insert(string name, int volume, double price, int index) {
	Node* newptr;
	newptr = new Node(name, volume, price);
	if (index == 0) {
		newptr->next = head;
		if (head != nullptr) {
			head->prev = newptr;
		}
		head = newptr;
		if (tail == nullptr) {
			tail = newptr;
		}
		return;
	}
	Node* ptr = head;
	int n = 0;
	while (n != index && ptr != nullptr) {
		ptr = ptr->next;
		n++;
	}
	if (ptr == nullptr) {
		return;
	}
	newptr->next = ptr;
	newptr->prev = ptr->prev;
	ptr->prev->next = newptr;
	ptr->prev = newptr;
}

void LinkedList::pop_front() {
	if (head == nullptr) {
		return;
	}
	Node* ptr = head->next;
	if (ptr != nullptr) {
		ptr->prev = nullptr;
	}
	else {
		tail = nullptr;
	}
	delete head;
	head = ptr;
}

void LinkedList::pop_back() {
	if (tail == nullptr) {
		return;
	}
	Node* ptr = tail->prev;
	if (ptr != nullptr) {
		ptr->next = nullptr;
	}
	else {
		head = nullptr;
	}
	delete tail;
	tail = ptr;
}

void LinkedList::erase(int index) {
	Node* ptr = getat(index);
	if (ptr == nullptr) {
		return;
	}
	if (ptr->prev == nullptr) {
		pop_front();
		return;
	}
	if (ptr->next == nullptr) {
		pop_back();
		return;
	}
	ptr->prev->next = ptr->next;
	ptr->next->prev = ptr->prev;
	delete ptr;
}

void LinkedList::clear() {
	while (head != nullptr) {
		pop_front();
	}
}

bool LinkedList::compare(Node* node1, Node* node2, string& field) {
	if (field == "name") {
		return node1->name > node2->name;
	}
	if (field == "volume") {
		return node1->volume > node2->volume;
	}
	if (field == "price") {
		return node1->price > node2->price;
	}
	return false;
}

void LinkedList::sort(string field) {
	Node* ptr = head;
	Node* newptr = ptr;
	while (newptr != tail) {
		while (ptr != tail) {
			if (compare(ptr, ptr->next, field)) {
				swap(ptr->name, ptr->next->name);
				swap(ptr->volume, ptr->next->volume);
				swap(ptr->price, ptr->next->price);
			}
			ptr = ptr->next;
		}
		ptr = head;
		newptr = newptr->next;
	}
}

void LinkedList::readfromfile(string filename) {
	ifstream in;
	in.open(filename);
	if (!in.is_open()) {
		cout << "Ошибка при открытии файла для чтения" << endl;
	}
	else {
		Node* ptr = new Node;
		while (!in.eof()) {
			in >> ptr;
			push_back(ptr->name, ptr->volume, ptr->price);
		}
		delete ptr;
	}
	in.close();
}

void LinkedList::writetofile(string filename) {
	ofstream out;
	out.open(filename);
	if (!out.is_open()) {
		cout << "Ошибка при открытии файла для записи" << endl;
	}
	else {
		Node* ptr = head;
		while (ptr != nullptr) {
			out << ptr << endl;
			ptr = ptr->next;
		}
	}
	out.close();
}