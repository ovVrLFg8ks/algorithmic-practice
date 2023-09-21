#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

class String {

private:
    char* buffer = NULL;
    int size = 0;

    String(int _size) : buffer(new char[_size + 1]), size(_size) {}

public:
    String() = default;

    String(const String& str) :
        buffer(new char[str.size + 1]), size(str.size) {
        strcpy(buffer, str.buffer);
    }

    String(const char* p) :
        buffer(new char[strlen(p) + 1]), size(strlen(p)) {
        strcpy(buffer, p);
    }

    ~String() {
        delete[] buffer;
    }

    char& operator[](int i) {
        if (i < 0 || i >= size) {
            throw std::out_of_range(""); 
            exit(1);
        }
        return buffer[i];
    }

    const char& operator[](int i) const {
        if (i < 0 || i >= size) {
            throw std::out_of_range("");
            exit(1);
        }
        return buffer[i];
    }

    String operator+(const String str) const {
        String out(size + str.size);
        strcpy(out.buffer, buffer);
        strcat(out.buffer, str.buffer);
        return out;
    }

    String& operator+=(const String str) {
        size += str.size;
        char* newbuffer = new char[size + 1];
        strcpy(newbuffer, buffer);
        strcat(newbuffer, str.buffer);
        delete[] buffer;
        buffer = newbuffer;

        // I'll leave it here to remember how to display the address of an array
        //cout << (void*)&buffer[0] << endl << (void*)&newbuffer[0] << endl;
        //printf("%p\n%p", buffer[0], newbuffer[0]);
        return *this;
    }

    String& operator+=(const char* str) {
        size += strlen(str);
        char* newbuffer = new char[size + 1];
        strcpy(newbuffer, buffer);
        strcat(newbuffer, str);
        delete[] buffer;
        buffer = newbuffer;
        return *this;
    }

    String& operator=(const String& str) {
        if (this != &str) {
            if (size < str.size) {
                delete[] buffer;
                buffer = new char[str.size + 1];
            }
            strcpy(buffer, str.buffer);
            size = str.size;
        }
        return *this;
    }

    bool operator==(const String& str) const {
        return  strcmp(buffer, str.buffer) == 0;
    }
    bool operator!=(const String& str) const {
        return  strcmp(buffer, str.buffer) != 0;
    }
    bool operator>(const String& str) const {
        return  strcmp(buffer, str.buffer) > 0;
    }
    bool operator<(const String& str) const {
        return  strcmp(buffer, str.buffer) < 0;
    }

    friend std::ostream& operator<<(std::ostream& out, const String& str) {
        printf("%s", str.buffer);
        //printf("%s {%d}", str.buffer, str.size);
        return out;
    }
    
    friend std::istream& operator>>(std::istream& in, String& str) {
        str = "";
        char ch;
        const int step = 16;
        char* newbuffer = new char[step];
        int i = 0;
        while ((ch = getc(stdin)) != '\n') {
            if (i == step - 1) {
                newbuffer[i] = '\0';
                str += newbuffer;
                i = 0;
            }
            newbuffer[i++] = ch;
        }
        newbuffer[i] = '\0';
        str += newbuffer;
        delete[] newbuffer;
        return in;
    }
};

using namespace std;

int main() {
    String str1 = "ABCDEF", str2 = "abcd", str3 = "ZXcvB";
    String str4 = str1 + str2;
    cout << str4 << endl;
    str4 += str3;
    cout << str4 << endl;

    for (int i = 0; i < 3; i++) {
        cin >> str4;
        cout << str4 << endl;
    }

    return 0;
}

