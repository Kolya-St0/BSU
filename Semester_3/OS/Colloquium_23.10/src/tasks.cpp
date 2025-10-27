#include "tasks.h"

using namespace std;

vector<unsigned long long> Tasks::calc_factorials(int n)
{
    if (n < 0) {
        throw string("n must be positive");
    }
    if (n > 20) {
        throw string("Factorial overflow");
    }

	vector<unsigned long long>factorials(n + 1);
	factorials[0] = 1;
	for (int i = 1; i < n + 1; i++) {
		factorials[i] = factorials[i - 1] * i;
	}
	return factorials;
}

void Tasks::delete_duplicates(vector<int>& dupl)
{
    for (int i = 0; i < dupl.size(); i++) {
        for (int j = i + 1; j < dupl.size(); ) {
            if (dupl[i] == dupl[j]) {
                dupl.erase(dupl.begin() + j);
            }
            else {
                j++;
            }
        }
    }
}