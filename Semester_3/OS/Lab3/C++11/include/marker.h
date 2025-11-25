#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <vector>

using namespace std;

class MarkerManager {
	vector<int>array;
	vector<thread>threads;
	int arr_size;
	int th_count;
	condition_variable start_cv;
	mutex mutex_cv;
	bool start_flag;
	vector<bool>stop_flags;
	vector<bool>end_flags;
	vector<bool>resume_flags;
	vector<bool>active_threads;
	vector<condition_variable*>stop_cvs;
	vector<condition_variable*>resume_cvs;

public:
	MarkerManager(int size, int count);
	~MarkerManager();

	void print_array();
	vector<int> get_array();

	void marker(int id);
	
	void start_threads();
	void wait_for_blocking_threads();
	void resume_threads();
	void end_thread(int id);

	void run();
};