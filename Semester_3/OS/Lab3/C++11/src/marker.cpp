#include "marker.h"

MarkerManager::MarkerManager(int size, int count)
{
	arr_size = size;
	th_count = count;
	array.resize(arr_size, 0);
	threads.resize(th_count);
	start_flag = false;
	stop_flags.resize(th_count, false);
	end_flags.resize(th_count, false);
	resume_flags.resize(th_count, false);
	active_threads.resize(th_count, true);
	stop_cvs.resize(th_count);
	resume_cvs.resize(th_count);

	for (int i = 0; i < th_count; i++) {
		stop_cvs[i] = new condition_variable();
		resume_cvs[i] = new condition_variable();
	}
}

MarkerManager::~MarkerManager()
{
	for (int i = 0; i < th_count; i++) {
		if (threads[i].joinable()) {
			threads[i].join();
		}
		delete stop_cvs[i];
		delete resume_cvs[i];
	}
}

void MarkerManager::print_array()
{
	lock_guard<mutex>lock(mutex_cv);
	cout << "Array: ";
	for (int i = 0; i < arr_size; i++) {
		cout << array[i] << " ";
	}
	cout << endl;
}

vector<int> MarkerManager::get_array()
{
	return array;
}

void MarkerManager::marker(int id)
{
	unique_lock<mutex>lock(mutex_cv);
	start_cv.wait(lock, [this]{ return start_flag; });
	lock.unlock();

	srand(id);

	bool working = true;
	int rand_ind, marked_count = 0;
	while (working) {
		unique_lock<mutex>lock(mutex_cv);
		rand_ind = rand() % arr_size;
		if (array[rand_ind] == 0) {
			this_thread::sleep_for(chrono::milliseconds(5));
			array[rand_ind] = id;
			marked_count++;
			this_thread::sleep_for(chrono::milliseconds(5));
		}
		else {
			cout << "Marker thread (" << id << ") stopped, marked " << marked_count 
				<< " elements, blocked at index " << rand_ind << endl;	

			stop_flags[id - 1] = true;
			stop_cvs[id - 1]->notify_one();

			resume_cvs[id - 1]->wait(lock, [this, id] { return resume_flags[id - 1] || end_flags[id - 1]; });

			if (end_flags[id - 1]) {
				for (int i = 0; i < arr_size; i++) {
					if (array[i] == id) {
						array[i] = 0;
					}
				}
				working = false;
			}
			else if (resume_flags[id - 1]) {
				stop_flags[id - 1] = false;
				resume_flags[id - 1] = false;
				marked_count = 0;
				cout << "Marker thread (" << id << ") resumed work" << endl;
			}
		}
	}
}

void MarkerManager::start_threads()
{
	for (int i = 0; i < th_count; i++) {
		threads[i] = thread(&MarkerManager::marker, this, i + 1);
	}

	start_flag = true;
	start_cv.notify_all();
}

void MarkerManager::wait_for_blocking_threads()
{
	for (int i = 0; i < th_count; i++) {
		if (active_threads[i]) {
			unique_lock<mutex> lock(mutex_cv);
			stop_cvs[i]->wait(lock, [this, i] { return stop_flags[i]; });
		}
	}
}

void MarkerManager::resume_threads()
{
	for (int i = 0; i < th_count; i++) {
		if (active_threads[i] && stop_flags[i]) {
			resume_flags[i] = true;
			resume_cvs[i]->notify_one();
		}	
	}
}

void MarkerManager::end_thread(int id)
{
	end_flags[id - 1] = true;
	resume_cvs[id - 1]->notify_one();

	if (threads[id - 1].joinable()) {
		threads[id - 1].join();
	}

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
			this_thread::sleep_for(chrono::milliseconds(500));
		}
	}

	cout << "All " << th_count << " marker threads were ended" << endl;
	cout << "Final array: " << endl;
	print_array();
}