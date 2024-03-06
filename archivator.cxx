#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <map>
#include <fstream>
#include <streambuf>
#include <vector>
#include <algorithm>
#include <cstring>
#include <set>

using namespace std;

//map<char, string> codes;

struct cell {
	long value;
	char ch;
	cell* p1 = NULL;
	cell* p2 = NULL;
	
	const bool operator<(const cell& c) const {
		return value < c.value;
	}
	
	const bool operator>(const cell& c) const {
		return value > c.value;
	}
	
	const bool operator==(const cell& c) const {
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <map>
#include <fstream>
#include <streambuf>
#include <vector>
#include <algorithm>
#include <cstring>
#include <set>

using namespace std;

//map<char, string> codes;

struct cell {
	long value;
	char ch;
	cell* p1 = NULL;
	cell* p2 = NULL;
	
	const bool operator<(const cell& c) const {
		return value < c.value;
	}
	
	const bool operator>(const cell& c) const {
		return value > c.value;
	}
	
	const bool operator==(const cell& c) const {
		return value == c.value;
	}
};

int main(int argc, char* argv[]) {
	string path = "/storage/emulated/0/Cxx/archivator";

	//string path = "C:/Users/0001/Desktop/archivator";
	string p = path + ".cxx";
	string d = path + ".que";
	string q = path + "0.cxx";

	char* p1 = new char[p.length() + 1];
	strcpy(p1, p.c_str());
	char* p2 = new char[d.length() + 1];
	strcpy(p2, d.c_str());
	char* p3 = new char[q.length() + 1];
	strcpy(p3, q.c_str());

	FILE* f = fopen(p1, "rb");
	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET);

	char* data = (char*)malloc(fsize + 1);
	fread(data, fsize, 1, f);
	fclose(f);

	vector<tuple<long, char>> counter(256);

	for (unsigned short c = 0; c < 256; c++) {
		get<1>(counter[c]) = (char)c;
	}
	for (int i = 0; i <= fsize; i++) {
		for (unsigned short c = 0; c < 256; c++) {
			if (data[i] == c)
				get<0>(counter[c])++;
		}
	}

	sort(counter.begin(), counter.end(), std::greater<>());
	for (int i = 0; i < counter.size(); i++) {
		if (get<0>(counter[i]) == 0)
			counter.erase(counter.begin() + i, counter.end());
	}
	/*
	for (int i = 0; i < counter.size(); i++) {
		cout << get<0>(counter[i]) << ' '
			 << get<1>(counter[i]) << ' '
			 << hex << (int)get<1>(counter[i]) << dec << endl;
	}*/

	int size = counter.size();
	
	set<cell> cells;
	for (int i = 0; i < size; i++) {
		cell t{get<0>(counter[i]), get<1>(counter[i])};
		cells.insert(t);
	}
	/*
	for (int i = 0; i < size; i++)
		cout << cells[i].value << endl;
	*/
	for (; size > 1; size--) {
		cell c1, c2;
		c1 = *cells.rbegin();
		cells.erase(prev(cells.end()));
		c2 = *cells.rbegin();
		cells.erase(prev(cells.end()));
		cell c3{ c1.value + c2.value, 0, &c1, &c2 };
		cells.insert(c3);
	}


	/*
	std::ofstream outfile;
	outfile.open(p2, std::ios_base::trunc);//std::ios_base::app
	outfile << data;
	*/
	return 0;
}￼Enter
