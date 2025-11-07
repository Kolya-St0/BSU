#ifndef THREADS_H
#define THREADS_H

struct Array
{
    int* array;
    int size;
    int min;
    int max;
    double average;
};

void min_max(Array* a);
void average(Array* a);      
#endif