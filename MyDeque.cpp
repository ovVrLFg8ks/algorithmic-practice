#include <iostream>
#include <cstring>

template <class T>
class Deque {
private:
    int elements = 0;
    int mem_size = 8;
    int start = 0;
    T* buffer = NULL;

    bool extend() {
        mem_size *= 2;
        T* newBuffer = new T[mem_size];
        if (!newBuffer) return false;
        for (int i = start, z = 0; z < elements; i++, z++) {
            newBuffer[z] = buffer[i % (mem_size / 2)];
        }
        delete[] buffer;
        buffer = newBuffer;
        start = 0;
        return true;
    }

public:
    Deque() {
        buffer = new T[mem_size];
    }

    Deque(const Deque& deq) :
        buffer(new T[deq.mem_size]), start(deq.start),
        elements(deq.elements), mem_size(deq.mem_size) {
        memcpy(buffer, deq.buffer, elements * sizeof(T));
    }

    void operator=(const Deque& d) {
        if (buffer) {
            if (mem_size != d.mem_size) {
                delete[] buffer;
                mem_size = d.mem_size;
                buffer = new T[mem_size];
            }
        }
        else {
            mem_size = d.mem_size;
            buffer = new T[mem_size];
        }
        elements = d.elements;
        memcpy(buffer, d.buffer, elements / sizeof(T));
    }

    bool isFull() const {
        return (mem_size == elements) ? true : false;
    }

    T front() const {
        if (elements)
            return buffer[(start + (elements - 1)) % mem_size];
        else
            throw std::out_of_range("");
    }

    T back() const {
        if (elements)
            return buffer[start];
        else
            throw std::out_of_range("");
    }

    bool push_back(T& val) {
        if (mem_size == elements) {
            if (!extend())
                return false;
        }
        buffer[(start + elements) % mem_size] = val;
        elements++;
        return true;
    }

    bool push_front(T& val) {
        if (mem_size == elements) {
            if (!extend())
                return false;
        }
        start--;
        if (start < 0) start += mem_size;
        buffer[start] = val;
        elements++;
        return true;
    }

    int size() const {
        return elements;
    }

    T pop_back() {
        if (elements) {
            elements--;
            return buffer[start++ % mem_size];
        }
        else
            throw std::out_of_range("");
    }

    T pop_front() {
        if (elements)
            return buffer[(start + (--elements)) % mem_size];
        else
            throw std::out_of_range("");
    }

    void print() const {
        for (int i = 0; i < elements; i++) {
            std::cout << i << ": " << buffer[(start + i) % mem_size] << std::endl;
        }
    }

    ~Deque() {
        delete[] buffer;
    }
};

using namespace std;

int main() {
    Deque<int> a;

    for (int i = 1; i < 21; i++) {
        if (i % 2)
            a.push_front(i);
        else
            a.push_back(i);
    }

    a.print(); cout << a.back() << "  " << a.front() << endl;

    for (int i = 1; i < 21; i++) {
        if (i % 2)
            cout << a.pop_back() << endl;
        else
            cout << a.pop_front() << endl;
    }

    return 0;
}
