#include "std_thread.h"
#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex cout_mutex;

void min_max(Array* a)
{
	if (a == nullptr || a->array == nullptr || a->size <= 0) {
		cout << "Array is empty" << endl;
		return;
	}
	a->min = a->array[0];
	a->max = a->array[0];
	for (int i = 0; i < a->size; i++) {
		if (a->array[i] > a->max) {
			a->max = a->array[i];
		}
		if (a->array[i] < a->min) {
			a->min = a->array[i];
		}
		this_thread::sleep_for(chrono::milliseconds(7));
	}
	lock_guard<mutex> lock(cout_mutex);
	cout << "min = " << a->min << endl;
	cout << "max = " << a->max << endl;
}

void average(Array* a)
{
	if (a == nullptr || a->array == nullptr || a->size <= 0) {
		cout << "Array is empty" << endl;
		return;
	}
	a->average = 0;
	int sum = 0;
	for (int i = 0; i < a->size; i++) {
		sum += a->array[i];
		this_thread::sleep_for(chrono::milliseconds(12));
	}
	a->average = static_cast<double>(sum) / a->size;
	lock_guard<mutex> lock(cout_mutex);
	cout << "average = " << a->average << endl;
}