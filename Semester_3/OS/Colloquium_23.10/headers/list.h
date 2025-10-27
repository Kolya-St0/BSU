#pragma once
#include<iostream>
#include<vector>

using namespace std;

struct Node {
	int data;
	Node* next;

public:
	Node(int data);

	friend istream& operator >> (istream& in, Node* ptr);
	friend ostream& operator << (ostream& out, const Node* ptr);
};

class LinkedList {
	Node* head;

public:
	LinkedList();
	~LinkedList();

	int size();
	bool empty();
	void print();
	vector<int>to_vector();

	void create(const vector<int>&values);
	void reverse();
	void clear();

private:
	Node* reverse_rec(Node* node);
};