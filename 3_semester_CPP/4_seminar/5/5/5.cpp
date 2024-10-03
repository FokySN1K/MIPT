#include <iostream>
#include <vector>

using namespace std;

template <class T>
T max_element(vector <T> v) {
	T max = v[0];
	for (auto i : v) {
		if (max < i) {
			max = i;
		}
	}
	return max;
}
int main() {
	vector <int> v = { 1, 2, 3, 4 };
	cout << max_element(v);

}