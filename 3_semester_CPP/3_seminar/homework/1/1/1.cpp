#include <iostream>
using namespace std;

void change(string &a) {
    if (isupper(a[0])) {
        a[0] = tolower(a[0]);
    }
    else {
        a[0] = toupper(a[0]);
    }
}

int main()
{
    string a = "1234";
    change(a);
    cout << a;
}

