#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


void print_vec(vector <string> vec) {
	for (auto i : vec) {
		cout << i << " ";
	}
	cout << endl;
}
void all_reverse(vector <string> &vec) {
	reverse(vec.begin(), vec.end());
	for (int i = 0; i < vec.size(); i++) {
		reverse(vec[i].begin(), vec[i].end());
	}
}
int main() {
	int len;
	string word;
	vector <string> vec;
	cin >> len;
	for (int i = 0; i < len; i++) {
		cin >> word;
		vec.push_back(word);
	}
	all_reverse(vec);
	print_vec(vec);
}