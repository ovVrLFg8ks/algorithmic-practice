#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <map>
#include <fstream>
#include <streambuf>
#include <vector>
#include <algorithm>
#include <cstring>
#include <set>
#include <bitset>

using namespace std;

#define byte unsigned char

struct cell {
	int32_t value;
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

struct cellHandler {
	cell* val;

	const bool operator<(const cellHandler& c) const {
		return val->value < c.val->value;
	}
};

struct outCell {
	string str;
	char ch;

	const bool operator<(const outCell& c) const {
		return str.length() < c.str.length();
	}
};

string refChars[256];

void destroyTree(cell* root, string str) {
	if (root->p1 == NULL && root->p2 == NULL)
		refChars[(unsigned char)root->ch] = str;
	if (root->p1 != NULL)
		destroyTree(root->p1, str + '0');
	if (root->p2 != NULL)
		destroyTree(root->p2, str + '1');
	delete[] root;
};

void destroyLastTree(cell* root) {
	if (root->p1 != NULL)
		destroyLastTree(root->p1);
	if (root->p2 != NULL)
		destroyLastTree(root->p2);
	delete[] root;
};

int main(int argc, char* argv[]) {
	//string path = "/storage/emulated/0/Cxx/archivator";
	//string path = "C:/Users/0001/Desktop/archivator";
	string path = "C:/Users/0001/Desktop/a";
	string p = path + ".txt";
	string d = path + ".que";
	string q = path + ".tup";

	char* p1 = new char[p.length() + 1];
	strcpy(p1, p.c_str());
	char* p2 = new char[d.length() + 1];
	strcpy(p2, d.c_str());
	char* p3 = new char[q.length() + 1];
	strcpy(p3, q.c_str());

	{	// packing
		FILE* f = fopen(p1, "rb");
		fseek(f, 0, SEEK_END);
		int32_t fsize = ftell(f);
		fseek(f, 0, SEEK_SET);

		char* data = (char*)malloc(fsize + 1);
		fread(data, fsize, 1, f);
		fclose(f);

		vector<tuple<long, char>> counter(256);

		for (unsigned short c = 0; c < 256; c++) {
			get<1>(counter[c]) = (char)c;
		}
		for (int i = 0; i < fsize; i++) {
			byte c = data[i];
			get<0>(counter[c])++;
		}

		sort(counter.begin(), counter.end(), greater<>());
		for (int i = 0; i < counter.size(); i++) {
			if (get<0>(counter[i]) == 0)
				counter.erase(counter.begin() + i, counter.end());
		}

		int size = counter.size();

		multiset<cellHandler> cellsH;
		for (int i = 0; i < size; i++) {
			cell* t = new cell{ get<0>(counter[i]), get<1>(counter[i]) };
			cellHandler th = cellHandler{ t };
			cellsH.insert(th);
		}

		for (; size > 1; size--) {
			cellHandler c1, c2;
			c1 = *cellsH.begin();
			cellsH.erase(cellsH.begin());
			c2 = *cellsH.begin();
			cellsH.erase(cellsH.begin());
			cell* c = new cell{ c1.val->value + c2.val->value, 0, (c1.val), (c2.val) };
			cellHandler c3{ c };
			cellsH.insert(c3);
		}

		destroyTree((*cellsH.begin()).val, "");

		/* how to store file

		DB: length,		path,	symbol
			byte	  bitset	char

		file structure:
		[count][DB][DB][DB][0][data]

		[0]: DB {length:0}
		[count]: int - number of symbols in data
		*/

		ofstream fs(d, ios::out | ios::binary | ios::trunc);

		bitset<8 + 256 + 8 + 1> bitString;
		bitset<8> bit8;
		byte bit8_fillness = 0;

		fs.write(reinterpret_cast<const char*>(&fsize), sizeof fsize);		// [count]
		for (int i = 0; i < 256; i++) {										// [DB]
			if (refChars[i].length() > 0) {
				byte s = refChars[i].length();								// length
				int bsf_size = 8 + s + 8;
				bitset<8> length = s;
				for (int a = 0; a < 8; a++)
					(length[a]) ? bitString.set(a) : bitString.reset(a);

				for (int a = 0; a < s; a++) {								// path
					if (refChars[i][a] == '1')
						bitString.set(a + 8);
					else
						bitString.reset(a + 8);
				}

				char chr = i;												// symbol
				bitset<8> ch = chr;
				for (int a = 0; a < 8; a++)
					(ch[a]) ? bitString.set(a + 8 + s) : bitString.reset(a + 8 + s);

				for (int bsf = 0; bsf < bsf_size; bsf++) {					// writing
					bit8[bit8_fillness] = bitString[bsf];
					bit8_fillness++;
					if (bit8_fillness == 8) {
						unsigned long n = bit8.to_ulong();
						byte c = static_cast<byte>(n);
						fs.write(reinterpret_cast<const char*>(&c), sizeof c);
						bit8_fillness = 0;
					}
				}
			}
		}
		byte s = 0;															// [0]
		int bsf_size = 8;
		bitset<8> length = s;
		for (int a = 0; a < 8; a++)
			(length[a]) ? bitString.set(a) : bitString.reset(a);

		for (int bsf = 0; bsf < bsf_size; bsf++) {
			bit8[bit8_fillness] = bitString[bsf];
			bit8_fillness++;
			if (bit8_fillness == 8) {
				unsigned long n = bit8.to_ulong();
				byte c = static_cast<byte>(n);
				fs.write(reinterpret_cast<const char*>(&c), sizeof c);
				bit8_fillness = 0;
			}
		}

		// data
		for (int i = 0; i < fsize; i++) {
			string str = refChars[data[i]];
			byte bsf_size = str.length();

			for (int a = 0; a < bsf_size; a++) {
				if (str[a] == '1')
					bitString.set(a);
				else
					bitString.reset(a);
			}

			for (int bsf = 0; bsf < bsf_size; bsf++) {						// writing
				bit8[bit8_fillness] = bitString[bsf];
				bit8_fillness++;
				if (bit8_fillness == 8) {
					unsigned long n = bit8.to_ulong();
					byte c = static_cast<byte>(n);
					fs.write(reinterpret_cast<const char*>(&c), sizeof c);
					bit8_fillness = 0;
				}
			}
		}
		unsigned long n = bit8.to_ulong();
		byte c = static_cast<byte>(n);
		fs.write(reinterpret_cast<const char*>(&c), sizeof c);

		fs.close();
	}

	{ // unpacking
		FILE* f = fopen(p2, "rb");
		fseek(f, 0, SEEK_END);
		int32_t fsize = ftell(f);
		fseek(f, 0, SEEK_SET);

		char* data = (char*)malloc(fsize + 1);
		fread(data, fsize, 1, f);
		fclose(f);

		int32_t char_quantity, char_counter = 0;
		memcpy(&char_quantity, data, 4);
		int step = 4, bs_offset = 0;
		cell root;
		cell* current_cell = &root;
		int state = 0;

		bitset<8*36> bsout;
		while (step < fsize) {
			int bsout_fill = 0;
			for (int i = 0; i < 36 && i + step < fsize; i++) {
				bitset<8> bsch = data[i+step];
				for (int a = 0; a < 8; a++)
					bsout[a + bsout_fill] = bsch[a];
				bsout_fill += 8;
			}
			bitset<8> bs_len;
			for (int i = 0; i < 8; i++)
				bs_len[i] = bsout[i + bs_offset];
			unsigned long t = bs_len.to_ulong();
			byte length = static_cast<unsigned char>(t);
			if (length == 0) {
				step += 1;
				break;
			}

			current_cell = &root;
			for (int i = 0; i < length; i++) {
				bool route = bsout[8 + bs_offset + i];
				if (route) {
					if (current_cell->p2 == NULL) {
						cell* t = new cell{0, 0, NULL, NULL};
						current_cell->p2 = t;
					}
					current_cell = current_cell->p2;
				}
				else {
					if (current_cell->p1 == NULL) {
						cell* t = new cell{ 0, 0, NULL, NULL };
						current_cell->p1 = t;
					}
					current_cell = current_cell->p1;
				}
			}
			bitset<8> bs_ch;
			for (int i = 0; i < 8; i++)
				bs_ch[i] = bsout[bs_offset + 8 + length + i];
			t = bs_ch.to_ulong();
			char ch = static_cast<unsigned char>(t);
			current_cell->ch = ch;

			step += 2 + (bs_offset + length) / 8;
			bs_offset = (bs_offset + length) % 8;
		}

		current_cell = &root;
		ofstream outFile;
		outFile.open(p3, ios::out | ios::trunc);
		
		while (true) {
			bitset<8> bsch = data[step++];
			for (int i = bs_offset; i < 8; i++) {
				bool path = bsch[i];
				if (path)
					current_cell = current_cell->p2;
				else
					current_cell = current_cell->p1;
				if (current_cell->p1 == NULL && current_cell->p2 == NULL) {
					outFile.put(current_cell->ch);
					current_cell = &root;
					if (++char_counter == char_quantity)
						goto CLOSE_FILE;
				}
			}
			bs_offset = 0;
		}
		CLOSE_FILE:
		outFile.close();
		//destroyLastTree(&root);
	}
	return 0;
}
