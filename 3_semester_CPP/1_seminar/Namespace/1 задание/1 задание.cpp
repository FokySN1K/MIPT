#include <iostream>
#include <cstdio>

using namespace std;

namespace myspace {
    void print_n_times(const char str[], int n = 10) {
        for (int i = 0; i < n; i++) {
            const char* a = str;
            while (*a != NULL) {
                printf("%c", *a);
                a++;
            }
        }
    }
}

int main()
{
    char str[5] = "1234";
    myspace:: print_n_times(str, 2);
}
