#include "marker.h"

MarkerManager::MarkerManager(int size, int count)
{
	arr_size = size;
	th_count = count;
	array.resize(arr_size, 0);
	threads.resize(th_count);
	stop_events.resize(th_count);
	end_events.resize(th_count);
	resume_events.resize(th_count);
	active_threads.resize(th_count, true);

	InitializeCriticalSection(&critical_section);
	start_event = CreateEvent(NULL, TRUE, FALSE, NULL);	
	for (int i = 0; i < th_count; i++) {
		stop_events[i] = CreateEvent(NULL, TRUE, FALSE, NULL);
		end_events[i] = CreateEvent(NULL, FALSE, FALSE, NULL);
		resume_events[i] = CreateEvent(NULL, FALSE, FALSE, NULL);
	}
}

MarkerManager::~MarkerManager()
{
	for (int i = 0; i < th_count; i++) {
		WaitForSingleObject(threads[i], INFINITE);
		CloseHandle(threads[i]);
	}

	DeleteCriticalSection(&critical_section);
	CloseHandle(start_event);

	for (int i = 0; i < th_count; i++) {
		CloseHandle(stop_events[i]);
		CloseHandle(end_events[i]);
		CloseHandle(resume_events[i]);
	}
}

void MarkerManager::print_array()
{
	EnterCriticalSection(&critical_section);
	cout << "Array: ";
	for (int i = 0; i < arr_size; i++) {
		cout << array[i] << " ";
	}
	cout << endl;
	LeaveCriticalSection(&critical_section);
}

vector<int> MarkerManager::get_array()
{
	return array;
}

DWORD WINAPI MarkerManager::marker(LPVOID param)
{
	MarkerThread* temp = static_cast<MarkerThread*>(param);
	temp->m->marker_work(temp->thread_id);
	delete temp;
	return 0;
}

void MarkerManager::marker_work(int id)
{
	WaitForSingleObject(start_event, INFINITE);
	srand(id);

	bool working = true;
	int rand_ind, marked_count = 0;
	while (working) {
		EnterCriticalSection(&critical_section);
		rand_ind = rand() % arr_size;
		if (array[rand_ind] == 0) {
			Sleep(5);
			array[rand_ind] = id;
			marked_count++;
			Sleep(5);
			LeaveCriticalSection(&critical_section);
		}
		else {
			cout << "Marker thread (" << id << ") stopped, marked " << marked_count 
				<< " elements, blocked at index " << rand_ind << endl;
			LeaveCriticalSection(&critical_section);
			SetEvent(stop_events[id - 1]);

			HANDLE wait_events[2] = { end_events[id - 1], resume_events[id - 1] };
			DWORD result = WaitForMultipleObjects(2, wait_events, FALSE, INFINITE);

			if (result == WAIT_OBJECT_0) {
				EnterCriticalSection(&critical_section);
				for (int i = 0; i < arr_size; i++) {
					if (array[i] == id) {
						array[i] = 0;
					}
				}
				working = false;
				LeaveCriticalSection(&critical_section);
			}
			else if (result == WAIT_OBJECT_0 + 1) {
				EnterCriticalSection(&critical_section);
				ResetEvent(stop_events[id - 1]);
				marked_count = 0;
				cout << "Marker thread (" << id << ") resumed work" << endl;
				LeaveCriticalSection(&critical_section);
			}
		}
	}
}



void MarkerManager::start_threads()
{
	for (int i = 0; i < th_count; i++) {
		MarkerThread* temp = new MarkerThread(i + 1, this);
		threads[i] = CreateThread(NULL, 0, marker, temp, 0, NULL);
		if (threads[i] == NULL) {
			cout << "Thread (" << i + 1 << ") failed to create" << endl;
		}
	}
	SetEvent(start_event);
}

void MarkerManager::wait_for_blocking_threads()
{
	vector<HANDLE>curr_stop_events;
	for (int i = 0; i < th_count; i++) {
		if (active_threads[i]) {
			curr_stop_events.push_back(stop_events[i]);
		}
	}
	if (!curr_stop_events.empty()) {
		WaitForMultipleObjects(curr_stop_events.size(), curr_stop_events.data(), TRUE, INFINITE);
	}
}

void MarkerManager::resume_threads()
{
	for (int i = 0; i < th_count; i++) {
		if (active_threads[i]) {
			SetEvent(resume_events[i]);
		}	
	}
}

void MarkerManager::end_thread(int id)
{
	SetEvent(end_events[id - 1]);
	WaitForSingleObject(threads[id - 1], 500);
	active_threads[id - 1] = false;
}

void MarkerManager::run()
{
	cout << "Starting. " << th_count << " marker threads creating" << endl;
	start_threads();
	int active_th_count = th_count;
	while (active_th_count > 0) {
		cout << active_th_count << " marker threads are now active. Waiting for blocking" << endl;
		wait_for_blocking_threads();
		cout << "All threads were blocked" << endl;
		print_array();

		int ending_th_id;
		while (true) {
			cout << "Enter thread id (1 - " << th_count << ") to end it : ";
			cin >> ending_th_id;
			if (ending_th_id < 1 || ending_th_id > th_count) {
				cout << "No such id, enter number from 1 to " << th_count << endl;
				continue;
			}
			if (!active_threads[ending_th_id - 1]) {
				cout << "This thread was already ended" << endl;
				continue;
			}
			cout << "Ending marker thread (" << ending_th_id << ")" << endl;
			end_thread(ending_th_id);
			active_th_count--;
			break;
		}

		cout << "Array after marker thread (" << ending_th_id << ") ended: " << endl;
		print_array();

		if (active_th_count > 0) {
			cout << "Resuming remaining " << active_th_count << " threads" << endl;
			resume_threads();
			Sleep(500);
		}
	}

	cout << "All " << th_count << " marker threads were ended" << endl;
	cout << "Final array: " << endl;
	print_array();
}

MarkerThread::MarkerThread(int id, MarkerManager* handler)
{
	thread_id = id;
	m = handler;
}