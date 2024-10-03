#include <iostream>
#include <vector>
#include <span>

using namespace std;
vector <int> lastDigits1(const vector<int>& v) {
	vector <int> v1;
	for (int i : v) {
		v1.push_back(i % 10);
	}
	return v1;
	
}
void lastDigits2(vector<int>& v) {
	for (int i = 0; i < v.size(); i++) {
		v[i] = v[i] % 10;
	}
}
void lastDigits3(vector<int>* v) {
	for (int i = 0; i < v->size(); i++) {
		(*v)[i] = (*v)[i] % 10;
	}

}
void lastDigits4(span<int> p) {
	for (int i = 0; i < p.size(); i++) {
		p[i] = p[i] % 10;
	}

}
void printVector(const vector<int>& v) {
	for (auto i : v) {
		cout << i << " ";
	}
	cout << endl;
}

int main() {
	vector <int> v = { 12, 23, 34, 45};
	{
		vector<int> v1 = lastDigits1(v);
		printVector(v1);
	}
	{
		vector<int> v1 = v;
		lastDigits2(v1);
		printVector(v1);
	}
	{
		vector<int> v1 = v;
		lastDigits3(&v1);
		printVector(v1);
	}
	{
		span<int> v1 = v;
		lastDigits4(v1);
		printVector(v); // !!!
	}

}