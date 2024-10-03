#include <iostream>
#include <string>

using namespace std;

void move_probels(string& s) {
	int sum_problem = 0;
	string str = "";
	for (int i = 0; i < s.length(); i++) {
		if (s[i] != ' ') {
			str += s[i];
		}
		else {
			sum_problem += 1;
		}
	}
	while ((sum_problem--) != 0) {
		str += ' ';
	}
	s = str;

}


int main() {
	string s = "cats  and dogs";
	move_probels(s);
	cout << s << "!" << endl;
}