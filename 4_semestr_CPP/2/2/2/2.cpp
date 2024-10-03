#include <thread>
#include <iostream>
#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <fstream>
#include <string>

using namespace std;
// 2 и 4 задания из 2 дз

template<typename T>
class threadsafe_queue
{
private:
    mutable mutex mut;
    queue<T> data_queue;
    condition_variable data_cond;
public:
    threadsafe_queue()
    {}
    threadsafe_queue(threadsafe_queue const& other)
    {
        lock_guard<mutex> lk(other.mut);
        data_queue = other.data_queue;
    }
    void push(T new_value)
    {
        lock_guard<mutex> lk(mut);
        data_queue.push(new_value);
        data_cond.notify_one();
    }
    void wait_and_pop(T& value)
    {
        unique_lock<mutex> lk(mut);
        data_cond.wait(lk, [this] {return !data_queue.empty(); });
        value = data_queue.front();
        data_queue.pop();
    }
    shared_ptr<T> wait_and_pop()
    {
        unique_lock<mutex> lk(mut);
        data_cond.wait(lk, [this] {return !data_queue.empty(); });
        shared_ptr<T> res(make_shared<T>(data_queue.front()));
        data_queue.pop();
        return res;
    }
    bool try_pop(T& value)
    {
        lock_guard<mutex> lk(mut);
        if (data_queue.empty())
            return false;
        value = data_queue.front();
        data_queue.pop(); return true;
    }
    shared_ptr<T> try_pop()
    {
        lock_guard<mutex> lk(mut);
        if (data_queue.empty())
            return shared_ptr<T>();
        shared_ptr<T> res(make_shared<T>(data_queue.front()));
        data_queue.pop();
        return res;
    }
    bool empty() const
    {
        lock_guard<mutex> lk(mut);
        return data_queue.empty();
    }
};


ifstream in("C:/Project/MIPT/4_semestr/2/1/invisible_man.txt");
threadsafe_queue <string> str;
bool cont = true;


void read_() {
    string st = "";
    while (cont) {
        if (str.empty()) {
            if (getline(in, st))
                str.push(st);
            else
                cont = false;
        }
        st = "";
    }
}

void write_() {
    string st = "";
    while (cont) {

        if (!str.empty()) {
            st = *str.try_pop();
            for (int i = 0; i < st.size(); i++) {
                st[i] = toupper(st[i]);
            }
            cout << st << endl;
            st = "";
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

