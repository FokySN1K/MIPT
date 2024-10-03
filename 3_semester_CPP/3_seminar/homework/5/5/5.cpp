#include <iostream>
#include <string>
#include <string_view>


using namespace std;

int sum_from_string(string_view s) {
	// без проверок
	int sum = 0;
	int id = s.find('[');
	int id_end = s.find(']');
	string a;
	int id_1 = s.find(',');
	if (id + 1 == id_end) {
		// []
		return 0;
	}
	while (true) {
		if (id == 0) { //[10], [10, ...]
			if ((id_1 = s.find(',')) == string::npos) { // [10]
				a = s.substr(1, id_end - 1);
				sum += stoi(a);
				return sum;
			}
			else { // [10, ...]
				a = s.substr(1, id_1 - 1);
				sum += stoi(a);
				id = id_1 + 2;
			}
		}
		else if ((id_1 = s.find(',', id)) != string::npos) { // [..., 10, ...]
			a = s.substr(id, id_1 - id);
			sum += stoi(a);
			id = id_1 + 2;
		}
		else { // [..., 10]
			a = s.substr(id, id_end - id);
			sum += stoi(a);
			id = id_1 + 2;
			break;
		}
		
	}
	return sum;
}

int main() {

	string s;
	while (getline(cin, s)) { // верно ли такое написание?
		cout << sum_from_string(s) << endl;
	}
}