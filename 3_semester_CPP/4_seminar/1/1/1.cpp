#include <iostream>
#include <vector>
#include <string>
using namespace std;



vector <int> string_to_vector(string_view s) {
	// без проверок
	vector <int> v;
	int id = s.find('{');
	int id_end = s.find('}');
	string a;
	int id_1 = s.find(',');
	if (id + 1 == id_end) {
		return v;
	}
	while (true) {
		if (id == 0) { //[10], [10, ...]
			if ((id_1 = s.find(',')) == string::npos) { // [10]
				a = s.substr(1, id_end - 1);
				v.push_back(stoi(a));
				return v;
			}
			else { // [10, ...]
				a = s.substr(1, id_1 - 1);
				v.push_back(stoi(a));
				id = id_1 + 2;
			}
		}
		else if ((id_1 = s.find(',', id)) != string::npos) { // [..., 10, ...]
			a = s.substr(id, id_1 - id);
			v.push_back(stoi(a));
			id = id_1 + 2;
		}
		else { // [..., 10]
			a = s.substr(id, id_end - id);
			v.push_back(stoi(a));
			id = id_1 + 2;
			break;
		}

	}
	return v;
}
int sumEven(const vector<int>& v) {
    int sum = 0;
    for (int i : v) {
        sum += i;
    }
    return sum;
}



int main()
{
    vector<int> v;
	string s;
	getline(cin, s);
	v = string_to_vector(s);
	cout << sumEven(v);
}
