#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <algorithm>
#include "Number.h"
using namespace std;


void fibonachi(int n);
void factorial(int n);
void num_grad(long long n);
void num_grad(const char* s);

int main()
{
   /* char* s = (char*)calloc(sizeof(char), 3);
    s[0] = 49;
    cout << (int)s[0];
   */
    //Number a = "11114", b = "256";
    //factorial(1000);
    char s[] = "90560792656972947582439785608972465789628974587264056284658721771";
    num_grad("1431234");
}


void fibonachi(int n) {
    if (n == 0) {
        cout << 0;
    }
    else if (n == 1 || n == 2) {
        cout << 1;
    }
    else {
        Number sum_1 = "1", sum_2 = "1";
        for (int i = 3; i <= n; i++) {
            if (i % 2) {
                sum_1 += sum_2;
            }
            else {
                sum_2 += sum_1;
            }
        }
        if (n % 2) {
            cout << sum_1;
        }
        else {
            cout << sum_2;
        }

    }
}
void factorial(int n) {
    if (n == 0) {
        cout << 1;
    }
    else {
        Number result = 1;
        for (int i = 1; i <= n; i++) {
            Number a = {i};
            result *= a;
        }
        cout << result << endl;
    }
}
void num_grad(long long n) {
    Number x = n;
    Number unit = 1;
    Number third = 3;
    long long steps = 0;
    Number max = x;
    while (x.get_size() != 1 || (int)x[0] != 1) {
        steps++;
        if (isEven(x)) {
            x.divide_by_2();
        }
        else {
            x = third * x + unit;
        }
        if (max < x) {
            max = x;
        }
    }
    cout << "n = " << n << " steps = " << steps << " max = " << max << endl;
}
void num_grad(const char* s) {
    Number x = s;
    Number unit = 1;
    Number third = 3;
    long long steps = 0;
    Number max = x;
    while (x.get_size() != 1 || (int)x[0] != 1) {
        steps++;
        if (isEven(x)) {
            x.divide_by_2();
        }
        else {
            x = third * x + unit;
        }
        if (max < x) {
            max = x;
        }
    }
    cout << "n = " << s << " steps = " << steps << " max = " << max << endl;
}