#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Tasks {
public:
	static vector<unsigned long long>calc_factorials(int n);
	static void delete_duplicates(vector<int>& dupl);
};