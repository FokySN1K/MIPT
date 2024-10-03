#include <iostream>
#include <thread>
#include <mutex>
#include <fstream>
#include <string>

using namespace std;

ifstream in("C:/Project/MIPT/4_semestr/2/1/invisible_man.txt");
string str = "";
mutex mtx;
bool cont = true;

void read_() {
    while (cont) {
        if (str == "") {
            mtx.lock();
            if (!getline(in, str))
                cont = false;
            mtx.unlock();
        }     
    }
}

void write_() {
    while (cont) {
        if (!str.empty()) {
            mtx.lock();
            for (int i = 0; i < str.size(); i++) {
                str[i] = toupper(str[i]);
            }
            cout << str << endl;
            str = "";
            mtx.unlock();
        }
    }
}

int main()
{
    
    
    // не рассматриваем возможные ошибки
    thread read(read_);
    thread write(write_);




    read.join();
    write.join();


    in.close();
}

