#include "marker.h"

int main()
{
	int size;
	cout << "Enter array size: ";
	cin >> size;

	int count;
	cout << "Enter threads count: ";
	cin >> count;

	MarkerManager m(size, count);
	m.run();

	return 0;
}