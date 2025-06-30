#pragma once
#include<iostream>
using namespace std;

struct Node {
	string name;
	int volume;
	double price;
	Node* next;
	Node* prev;
public:
	Node();
	Node(string fname, int fvolume, double fprice);
	friend istream& operator >> (istream& in, Node* ptr);
	friend ostream& operator << (ostream& out, const Node* ptr);
};

class LinkedList {
	Node* head;
	Node* tail;
public:
	LinkedList();
	~LinkedList();

	Node* getat(int index);
	Node* operator[](int index);
	friend ostream& operator<<(ostream& out, LinkedList& list);

	void push_front(string name, int volume, double price);
	void push_back(string name, int volume, double price);
	void insert(string name, int volume, double price, int index);

	void pop_front();
	void pop_back();
	void erase(int index);
	void clear();

	bool compare(Node* node1, Node* node2, string& field);
	void sort(string field);

	void readfromfile(string filename);
	void writetofile(string filename);
};
