#include <iostream>
using namespace std;

int cube(int a) {
    return a * a * a;
}
void cube(int& a) {
    a = a * a * a;
}
void count_letters(char str[], int& n_letters, int& n_digits, int& n_other) {
    n_letters = 0, n_digits = 0, n_other = 0;
    while (*str) {
        if (isalpha(*str)) {
            n_letters++;
        }
        else if (isdigit(*str)) {
            n_digits++;
        }
        else {
            n_other++;
        }
        str++;
    }

}

int main()
{
    int b1 = 10;
    cube(b1);
    //cout << b1;
    int a, b, c;
    char str[5] = "1234";
    count_letters(str, a, b, c);
    cout << str << " " << a << b << c;
}
