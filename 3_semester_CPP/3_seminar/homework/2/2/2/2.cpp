#include <iostream>
#include <string_view>
#include <string>

using namespace std;
string repeat1(string_view s) {
	string k = string(s);
	return k + k;
}
void repeat2(string& s) {
	s += s;
}
void repeat3(string* ps) {
	*ps += *ps ;
}
string* repeat4(string_view s) {
	string* k = new string{repeat1(s)};
	return k;
}



int main() {
	/*string a{ "123" };
	string* s = repeat4(a);
	cout << *s;*/

	string a = "1234";
	repeat3(&a);
}