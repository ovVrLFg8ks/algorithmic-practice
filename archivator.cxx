#include <iostream>
#include <map>
#include <fstream>
#include <streambuf>
#include <vector>

using namespace std;

//map<char, string> codes;

struct cell {
	char ch;
	long value;
	cell* p1 = NULL;
	cell* p2 = NULL;

	//cell(char c, long val, cell* left, cell* right) : ch(c), value(val), p1(left), p2(right) {}
	//cell(char c, long val) : ch(c), value(val) {}
	
};
/*
class Tree {
private:
	int size = 0;
#include <iostream>
#include <map>
#include <fstream>
#include <streambuf>
#include <vector>

using namespace std;

//map<char, string> codes;

struct cell {
	char ch;
	long value;
	cell* p1 = NULL;
	cell* p2 = NULL;

	//cell(char c, long val, cell* left, cell* right) : ch(c), value(val), p1(left), p2(right) {}
	//cell(char c, long val) : ch(c), value(val) {}
	
};
/*
class Tree {
private:
	int size = 0;
	cell root;
public:
	Tree() {

	};
	
	void addToTree(cell c) {
		
	}
};
*/
int main(int argc, char *argv[]) {
	string path = "/storage/emulated/0/Cxx/archivator";

	//string path = "C:/Users/0001/Desktop/archivator"
	string p = path + ".cxx";
	string d = path + ".que";
	string q = path + "0.cxx";
	
	char* p1 = new char [p.length()+1];
	strcpy (p1, p.c_str());
	char* p2 = new char [d.length()+1];
	strcpy (p2, d.c_str());
	char* p3 = new char [q.length()+1];
	strcpy (p3, q.c_str());
	
	FILE *f = fopen(p1, "rb");
	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET);
	
	char *data = (char*)malloc(fsize + 1);
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
	
	sort(counter.begin(),counter.end(), std::greater<>());
	for (int i = 0; i < counter.size(); i++) {
		if (get<0>(counter[i]) == 0)
			counter.erase(counter.begin()+i, counter.end());
	}
	/*
	for (int i = 0; i < counter.size(); i++) {
		cout << get<0>(counter[i]) << ' ' 
			 << get<1>(counter[i]) << ' ' 
			 << hex << (int)get<1>(counter[i]) << dec << endl; 
	}*/
	
	int size = counter.size();

	vector<cell> cells(size);
	for (int i = 0; i < size; i++) {
		cell t;//{get<1>(counter[i]), get<0>(counter[i])};
		t.ch = get<1>(counter[i]);
		t.value = get<0>(counter[i]);
		cells.push_back(t);
		//cells.push_back(cell{get<1>(counter[i]), get<0>(counter[i])});
	
	}
		//cells.push_back(cell(get<1>(counter[i]), get<0>(counter[i])));
	
	for (int i = 0; i < size; i++)
		cout << cells[i].value << endl;
	/*
	std::ofstream outfile;
	outfile.open(p2, std::ios_base::trunc);//std::ios_base::app
	outfile << data; 
	*/
	return 0;
}￼Enter
