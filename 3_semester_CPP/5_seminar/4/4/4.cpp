#include <iostream>
#include <string>

using namespace std;

void delete_chars(string &s, char a) {
	int c;
	while ((c = s.find(a)) != string:: npos) {
		s.erase(c, 1);
	}
}
bool isIdentifier(string_view str) {
	string s = (string)str;
	// Количество символов <= 64
	if (s.length() > 64) {
		return 0;
	}

	// Первые символы
	char first = s[0];
	if ( !isalpha(first) && first != '_' && first != '$') {
		return 0;
	}

	// Остальные символы
	// A - Z (65 - 90)
	// a - z (97 - 122)
	// 0 - 9 (48 - 57)
	// _ $
	for (int i = 65; i <= 90; i++) {
		delete_chars(s, (char)i);
	}
	for (int i = 97; i <= 122; i++) {
		delete_chars(s, (char)i);
	}
	for (int i = 48; i <= 57; i++) {
		delete_chars(s, (char)i);
	}
	delete_chars(s, '_');
	delete_chars(s, '$');

	return s == "";
}


int main() {
	string s;
	cin >> s;
	bool istina = isIdentifier(s);
	if (istina) {
		cout << "true";
	}
	else {
		cout << "false";
	}

}