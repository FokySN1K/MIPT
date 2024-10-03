#include <iostream>
#include <string>

using namespace std;

bool is_upper_word(const string &word) {
	string s = word;
	for (int i = 0; i < s.length(); i++) {
		s[i] = (char)toupper(s[i]);
	}

	return s == word;
}



int main() {
	string word;
	cin >> word;
	if (is_upper_word(word)) {
		cout << "true" << endl;
	}
	else {
		cout << "false" << endl;
	}
}