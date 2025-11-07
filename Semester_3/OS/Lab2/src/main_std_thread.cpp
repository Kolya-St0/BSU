#include <iostream>
#include "std_thread.h"
#include <thread>
#include <mutex>

using namespace std;

int main()
{
	int n;
	cout << "Enter array size: ";
	cin >> n;
	int* a = new int[n];
	cout << "Enter array elements: ";
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}

	Array* th_a = new Array();
	th_a->array = a;
	th_a->size = n;

	thread t_minmax(min_max, th_a);
	thread t_average(average, th_a);

	t_minmax.join();
	t_average.join();

	cout << "Final array: ";
	for (int i = 0; i < n; i++) {
		if (a[i] == th_a->min || a[i] == th_a->max) {
			a[i] = th_a->average;
		}
		cout << a[i] << " ";
	}

	delete[]a;
	delete th_a;
	return 0;
}