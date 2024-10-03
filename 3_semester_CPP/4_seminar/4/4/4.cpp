#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

class Time {
private:
	int mHours, mMinutes, mSeconds;
public:
	Time(int hours, int minutes, int seconds);
	Time(string s);
	Time operator+ (Time b) const;
	int hours() const;
	int minutes() const;
	int seconds() const;
	friend ostream& operator<<(ostream& out, const Time t);
};
vector<Time> getTimesFromString(string_view s);
Time sumTimes(const vector <Time>& v);


int main() {
	vector <Time> times = getTimesFromString("0:0:0 33:11:32 321:21:1");
	{
		for (auto i : times) {
			cout << i << " ";
		}
		cout << endl;
	}
	Time time = sumTimes(times);
	cout << time;

}
vector<Time> getTimesFromString(string_view s) {
	vector<Time> time;
	if (s.size() == 0);
	else {
		string k = string(s.substr(0, 8));
		time.push_back(Time(k));
		int id = 1;
		while (s.find(' ', id + 1) != string::npos) {
			id = s.find(' ', id + 1) + 1;
			k = string(s.substr(id, 8));
			time.push_back(Time(k));
		}
	}
	return time;
}
Time sumTimes(const vector <Time>& v) {
	int h = 0, m = 0, s = 0;
	for (auto i : v) {
		h += i.hours();
		m += i.minutes();
		s += i.seconds();
	}
	Time time = { h, m , s };
	return time;
}


Time:: Time(int hours, int minutes, int seconds) {
	mHours = hours;
	mMinutes = minutes;
	mSeconds = seconds;
}
Time:: Time(string s) {//hh:mm:ss
	string h, m, sec;
	int id = s.find(':');
	h = s.substr(0, id);
	int id1 = s.find(':', id + 1);
	m = s.substr(id + 1, id1 - id - 1);
	id = id1;
	id1 = s.find(':', id + 1);
	sec = s.substr(id + 1, id1 - id - 1);
	mHours = stoi(h);
	mMinutes = stoi(m);
	mSeconds = stoi(sec);
}
int Time:: hours() const{
	return mHours;
}
int Time::minutes() const {
	return mMinutes;
}
int Time::seconds() const {
	return mSeconds;
}
ostream& operator<<(ostream& out, const Time t)
{	
	out << setfill('0') << setw(2);
	out << t.mHours << ":";
	out << setfill('0') << setw(2); 
	out << t.mMinutes << ":";
	out << setfill('0') << setw(2);
	out << t.mSeconds;
	return out;
}

