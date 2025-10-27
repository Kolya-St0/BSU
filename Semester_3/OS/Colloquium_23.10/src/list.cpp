#include "list.h"

Node::Node(int data) 
{
	this->data = data;
	next = nullptr;
}

istream& operator >> (istream& in, Node* ptr) 
{
	in >> ptr->data;
	return in;
}

ostream& operator << (ostream& out, const Node* ptr) 
{
	out << ptr->data;
	return out;
}

LinkedList::LinkedList()
{
	head = nullptr;
}

LinkedList::~LinkedList()
{
	clear();
}

int LinkedList::size()
{
	int size = 0;
	Node* current = head;

	while (current != nullptr) {
		size++;
		current = current->next;
	}

	return size;
}

bool LinkedList::empty()
{
	return (head == nullptr);
}

void LinkedList::print()
{
	for (Node* ptr = head; ptr != nullptr; ptr = ptr->next) {
		cout << ptr << " ";
	}
}

vector<int> LinkedList::to_vector()
{
	vector<int> result;
	Node* current = head;
	while (current != nullptr) {
		result.push_back(current->data);
		current = current->next;
	}
	return result;
}

void LinkedList::create(const vector<int>&values)
{
	clear();

	if (values.empty()) {
		return;
	}

	head = new Node(values[0]);
	Node* current = head;
	for (int i = 1; i < values.size(); i++) {
		current->next = new Node(values[i]);
		current = current->next;
	}
}

Node* LinkedList::reverse_rec(Node* node)
{
	if (node == nullptr || node->next == nullptr) {
		return node;
	}

	Node* next = reverse_rec(node->next);
	node->next->next = node;
	node->next = nullptr;

	return next;
}

void LinkedList::reverse()
{
	head = reverse_rec(head);
}

void LinkedList::clear() 
{
	while (head != nullptr) {
		Node* current = head;
		head = head->next;
		delete current;
	}
}