#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void print_vec(vector <int> vec) {
    for (auto i : vec) {
        cout << i << " ";
    }
    cout << endl;
}
bool comp(int a, int b) {
    return a > b;
}

int main()
{
    vector <int> vec;
    int len, num;
    cin >> len;
    int max_index, max;
    for (int i = 0; i < len; i++) {
        cin >> num;
        vec.push_back(num);
        if (i == 0) {
            max = num;
            max_index = i;
        }
        else {
            if (max < num) {
                max_index = i;
                max = num;
            }
        }
    }
    sort(vec.begin(), vec.begin() + max_index);
    sort(vec.begin() + max_index, vec.end(), comp);
    print_vec(vec);
}
