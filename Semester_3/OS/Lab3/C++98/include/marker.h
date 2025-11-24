#include <iostream>
#include <Windows.h>
#include <vector>

using namespace std;

class MarkerManager {
	vector<int>array;
	vector<HANDLE>threads;
	int arr_size;
	int th_count;
	mutable CRITICAL_SECTION critical_section;
	HANDLE start_event;
	vector<HANDLE>stop_events;
	vector<HANDLE>end_events;
	vector<HANDLE>resume_events;
	vector<bool>active_threads;

public:
	MarkerManager(int size, int count);
	~MarkerManager();

	void print_array();
	vector<int> get_array();

	static DWORD WINAPI marker(LPVOID param);
	void marker_work(int id);
	
	void start_threads();
	void wait_for_blocking_threads();
	void resume_threads();
	void end_thread(int id);

	void run();
};

struct MarkerThread {
	int thread_id;
	MarkerManager* m;

	MarkerThread(int id, MarkerManager* handler);
};