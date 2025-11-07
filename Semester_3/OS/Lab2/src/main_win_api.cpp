#include <iostream>
#include "Windows.h"

using namespace std;

HANDLE hmutex = CreateMutex(NULL, FALSE, NULL);

struct Array 
{
	int* array;
	int size;
	int min;
	int max;
	double average;
};

DWORD WINAPI min_max(LPVOID _a)
{
	Array* a = static_cast<Array*>(_a);
	a->min = a->array[0];
	a->max = a->array[0];
	for (int i = 0; i < a->size; i++) {
		if (a->array[i] > a->max) {
			a->max = a->array[i];
		}
		if (a->array[i] < a->min) {
			a->min = a->array[i];
		}
		Sleep(7);
	}
	WaitForSingleObject(hmutex, INFINITE);
	cout << "min = " << a->min << endl;
	cout << "max = " << a->max << endl;
	ReleaseMutex(hmutex);
	return 0;
}

DWORD WINAPI average(LPVOID _a)
{
	Array* a = static_cast<Array*>(_a);
	a->average = 0;
	int sum = 0;
	for (int i = 0; i < a->size; i++) {
		sum += a->array[i];
		Sleep(12);
	}
	a->average = static_cast<double>(sum) / a->size;
	WaitForSingleObject(hmutex, INFINITE);
	cout << "average = " << a->average << endl;
	ReleaseMutex(hmutex);
	return 0;
}

int main()
{
	if (hmutex == 0) {
		cout << "Mutex creation failed with error code - " << GetLastError();
		return 0;
	}

	int n;
	cout << "Enter array size: ";
	cin >> n;
	int* a = new int[n];
	cout << "Enter array elements: ";
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}

	Array *th_a = new Array();
	th_a->array = a;
	th_a->size = n;

	HANDLE hmin_max = CreateThread(NULL, 0, min_max, th_a, 0, NULL);
	if (hmin_max == 0) {
		cout << "Thread min_max creating error code - " << GetLastError();
		return 0;
	}

	HANDLE haverage = CreateThread(NULL, 0, average, th_a, 0, NULL);
	if (haverage == 0) {
		cout << "Thread average creating error code - " << GetLastError();
		return 0;
	}

	WaitForSingleObject(hmin_max, INFINITE);
	WaitForSingleObject(haverage, INFINITE);
	
	CloseHandle(hmin_max);
	CloseHandle(haverage);

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