#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

template <class T>
//include diff between char, string, int/float/double
void printPairVector(vector <pair<T, T>> v) {
	cout << "{";
	for (auto i : v) {
		cout << "{" << i.first << ", " << i.second << "}";
		if (i != v[v.size() - 1]) {
			cout << ", ";
		}
	}
	cout << "}" << endl;
}

template <class T>
vector <pair<T, T>> elements(vector <T> vec) {
	vector <pair<T, T>> v;
	for (int i = 0; i < vec.size(); i = i + 2) {
		if (i == vec.size() - 1 && i%2 == 0) {
			// include try, catch, throw 
			v.push_back(make_pair(vec[i], "0"));
		}
		else {
			v.push_back(make_pair(vec[i], vec[i + 1]));
		}
	
	}
	return v;
}



int main() {
	string type;
	vector <string> a = { "1234", "124", "12"};
	auto v = elements(a);
	printPairVector(v);
}