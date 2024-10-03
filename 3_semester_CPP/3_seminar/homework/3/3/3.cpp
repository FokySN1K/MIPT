#include <iostream>
#include <string>

using namespace std;

string operator*(string s, int n) {
	string k;
	for (int i = 0; i < n; i++) {
		k += s;
	}
	return k;
}
string operator*(int n, string s) {
	string k;
	for (int i = 0; i < n; i++) {
		k += s;
	}
	return k;
}


int main() {
	string s = "123";
	cout << 3 * s;
}