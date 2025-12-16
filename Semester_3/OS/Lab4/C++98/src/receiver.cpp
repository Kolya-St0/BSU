#include "ring_queue.h"
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>
#include <vector>

using namespace std;

int main() {
    string filename;
    cout << "Enter filename: ";
    cin >> filename;

    int count;
    cout << "Enter messages count: ";
    cin >> count;

    int send_num;
    cout << "Enter Sender processes number: ";
    cin >> send_num;

    ofstream out;
    out.open(filename, ios::binary);
    if (!out) {
        cout << "Failed to open " << filename << endl;
        return 1;
    }
    out.close();

    HANDLE hmap = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0,
        sizeof(RingQueue), "GlobalRingQueue");

    if (!hmap) {
        cout << "Failed to create shared memory" << endl;
        return 1;
    }

    RingQueue* ring_queue = static_cast<RingQueue*>(MapViewOfFile(hmap, FILE_MAP_ALL_ACCESS,
        0, 0, sizeof(RingQueue)));

    if (!ring_queue) {
        cout << "Failed to create shared memory" << endl;
        CloseHandle(hmap);
        return 1;
    }

    ring_queue->front = 0;
    ring_queue->back = 0;
    ring_queue->max_size = count;

    HANDLE hmutex = CreateMutex(NULL, FALSE, "FileAccessMutex");
    HANDLE hsem_free = CreateSemaphore(NULL, count, count, "SemaphorFree");
    HANDLE hsem_full = CreateSemaphore(NULL, 0, count, "SemaphorFull");

    vector<HANDLE> ready_events;
    for (int i = 1; i <= send_num; i++) {
        string ready_event = "SenderReady" + to_string(i);
        HANDLE hready = CreateEvent(NULL, TRUE, FALSE, ready_event.c_str());
        if (!hready) {
            cout << "Failed to create ready event for Sender (" << i << ")" << endl;
            return 1;
        }
        ready_events.push_back(hready);
    }

    for (int i = 0; i < send_num; i++) {
        string cmd = "Sender.exe " + filename + " " + to_string(i + 1);
        STARTUPINFO si;
        PROCESS_INFORMATION pi;
        ZeroMemory(&si, sizeof(STARTUPINFO));
        si.cb = sizeof(STARTUPINFO);
        if (!CreateProcess(NULL, const_cast<char*>(cmd.c_str()), NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
            cout << "Failed to create sender " << i << endl;
            return 1;
        }
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }

    cout << "Waiting for ready signal from all " << send_num << " Senders" << endl;
    WaitForMultipleObjects(send_num, ready_events.data(), TRUE, INFINITE);
    cout << "All " << send_num << " senders ready" << endl;

    while (true) {
        string cmd;
        cout << "Enter command (read|exit): ";
        cin >> cmd;

        if (cmd == "exit") {
            break;
        }

        if (cmd == "read") {
            WaitForSingleObject(hsem_full, INFINITE);
            WaitForSingleObject(hmutex, INFINITE);

            fstream file(filename, ios::binary | ios::in | ios::out);
            if (!file) {
                cout << filename << " open failed" << endl;
                ReleaseMutex(hmutex);
                ReleaseSemaphore(hsem_free, 1, NULL);
                break;
            }

            else {
                file.seekg(ring_queue->front * max_msg_length);
                char message[max_msg_length] = { 0 };
                file.read(message, max_msg_length);

                cout << "Received: " << message << endl;

                file.seekp(ring_queue->front * max_msg_length);
                string msg_empty(max_msg_length, '\0');
                file.write(msg_empty.c_str(), max_msg_length);
                ring_queue->front = (ring_queue->front + 1) % ring_queue->max_size;

                file.close();
            }
            ReleaseMutex(hmutex);
            ReleaseSemaphore(hsem_free, 1, NULL);
        }
        else {
            cout << "Unknown command, repeat input" << endl;
        }
    }

    for (int i = 0; i < send_num; i++) {
        CloseHandle(ready_events[i]);
    }

    UnmapViewOfFile(ring_queue);
    CloseHandle(hmap);
    CloseHandle(hmutex);
    CloseHandle(hsem_free);
    CloseHandle(hsem_full);

    return 0;
}