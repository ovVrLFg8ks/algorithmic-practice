#include <iostream>
#include <thread>
#include <cstdlib>
#include <list>
#include <ctime>
#include <chrono>

using namespace std;

void t(int val, list<int>* l) {
	this_thread::sleep_for(chrono::milliseconds(val));
	l->push_back(val);
}

int main(int argc, char *argv[]) {
	int n = 256;
	int arr[n];
	thread thr[n];
	srand(time(NULL));
	list<int> lst;
	
	for (int i = 0; i < n; i++) {
		arr[i] = rand() % 100;
		cout << arr[i] << ' ';
	}
	cout << endl << endl;
	
	auto t1 = chrono::high_resolution_clock::now();
	for (int i = 0; i < n; i++) {
		thr[i] = thread(t, arr[i], &lst);
	}
	for (int i = 0; i < n; i++) {
		thr[i].join();
	}
	auto t2 = chrono::high_resolution_clock::now();
	
	for (auto i : lst) {
		cout << i << ' ';
	}
	chrono::duration<double, std::milli> ms_double = t2 - t1;
	cout << endl << ms_double.count() << "ms";
	return 0;
}