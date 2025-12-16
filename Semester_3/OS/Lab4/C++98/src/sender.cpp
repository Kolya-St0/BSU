#include "ring_queue.h"
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "Wrong input data" << endl;
        return 0;
    }

    string filename = argv[1];
    int id = stoi(argv[2]);

    HANDLE hmap = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, "GlobalRingQueue");
    if (!hmap) {
        cout << "Failed to open shared memory" << endl;
        return 1;
    }

    RingQueue* ring_queue = static_cast<RingQueue*>(MapViewOfFile(hmap, FILE_MAP_ALL_ACCESS,
        0, 0, sizeof(RingQueue)));
    if (!ring_queue) {
        cout << "Failed to open shared memory" << endl;
        return 1;
    }

    HANDLE hmutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, "FileAccessMutex");
    HANDLE hsem_free = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "SemaphorFree");
    HANDLE hsem_full = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "SemaphorFull");

    if (!hmutex || !hsem_free || !hsem_full) {
        cout << "Failed to open sync objects" << endl;
        return 1;
    }

    string ready_event = "SenderReady" + to_string(id);
    HANDLE hready = OpenEvent(EVENT_ALL_ACCESS, FALSE, ready_event.c_str());
    if (!hready) {
        cout << "Failed to open ready event" << endl;
        return 1;
    }
    SetEvent(hready);
    cout << "Sender (" << id << ") ready" << endl;

    while (true) {
        string cmd;
        cout << "Enter command (send|exit): ";
        cin >> cmd;

        if (cmd == "exit") {
            break;
        }
        if (cmd == "send") {
            cout << "Enter message(max length - 20 symbols): ";
            string msg;
            cin.ignore();
            getline(cin, msg);
            if (msg.size() > max_msg_length) {
                msg = msg.substr(0, 20);
            }
            WaitForSingleObject(hsem_free, INFINITE);
            WaitForSingleObject(hmutex, INFINITE);

            fstream file(filename, ios::binary | ios::in | ios::out);
            if (!file) {
                cout << filename << " open failed" << endl;
                ReleaseMutex(hmutex);
                ReleaseSemaphore(hsem_free, 1, NULL);
                continue;
            }

            file.seekp(ring_queue->back * max_msg_length);
            char msg_ext[max_msg_length] = { 0 };
            strncpy(msg_ext, msg.c_str(), max_msg_length - 1);
            file.write(msg_ext, max_msg_length);
            ring_queue->back = (ring_queue->back + 1) % ring_queue->max_size;
            file.close();

            cout << msg << " - sent to " << filename << endl;

            ReleaseMutex(hmutex);
            ReleaseSemaphore(hsem_full, 1, NULL);
        }
        else {
            cout << "Unknown comand, repeat input" << endl;
        }
    }

    UnmapViewOfFile(ring_queue);
    CloseHandle(hmap);
    CloseHandle(hmutex);
    CloseHandle(hsem_free);
    CloseHandle(hsem_full);

    return 0;
}