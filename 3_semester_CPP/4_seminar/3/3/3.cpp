#include <iostream>
#include <vector>

using namespace std;

vector<pair<int, int>> factorization(int n) {
	vector<pair<int, int>> v;
	int k = n;
	int i = 2;
	int sum = 0;
	while(k != 1){
		sum = 0;
		while (k % i == 0) {
			k /= i;
			sum++;
			
		}
		if (sum > 0) {
			v.push_back(make_pair(i, sum));
		}
		i++;
	}
	return v;
}
void printPairVector(vector <pair<int, int>> v) {
	cout << "{";
	for (auto i : v) {
		cout << "{" << i.first << ", " << i.second << "}";
		if (i != v[v.size() - 1]) {
			cout << ", ";
		}
	}
	cout << "}" << endl;
}
int main() {
	vector <pair<int, int>> v = factorization(12341);
	printPairVector(v);
	cout << v.size();
}