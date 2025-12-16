#pragma once

const int max_msg_length = 20;

struct RingQueue {
    int front;
    int back;
    int max_size;

    RingQueue() : front(0), back(0), max_size(0) {};
};