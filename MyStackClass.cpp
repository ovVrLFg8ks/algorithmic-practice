#include <iostream>

using namespace std;

template <class T>
class Stack {
private:
    int start_size = 8;
    int mem_size = start_size;
    int elements = 0;
    T* data = NULL;
    int element_size = sizeof(T);

    T& operator[](int i) {
        if (i < 0 || i >= elements) {
            throw out_of_range("");
            exit(1);
        }
        return data[i];
    }

public:
    Stack() {
        data = (T*)malloc(element_size * start_size);
    }

    Stack(int size) : start_size(size) {
        data = (T*)malloc(element_size * start_size);
    }

    Stack(const Stack& st) : data(new T[st.mem_size]),
        elements(st.elements),
        mem_size(st.mem_size) {
        memcpy(data, st.data, elements * element_size);
    }

    void operator=(const Stack& st) {
        if (data) {
            if (st.mem_size > mem_size) {
                delete[] data;
                mem_size = st.mem_size;
                data = new T[mem_size];
            }
        }
        else {
            mem_size = st.mem_size;
            data = new T[mem_size];
        }

        elements = st.elements;
        memcpy(data, st.data, elements * element_size);
    }

    void shrink() {
        mem_size = elements;
        T* new_data = (T*)malloc(element_size * mem_size);
        memcpy(new_data, data, elements * element_size);

        delete[] data;
        data = new_data;
    }

    bool push(T var) {
        if (elements == mem_size) {
            mem_size *= 2;
            T* new_data = (T*)malloc(element_size * mem_size);
            if (!new_data) return false;
            memcpy(new_data, data, elements * element_size);

            delete[] data;
            data = new_data;
        }
        data[elements++] = var;
        return true;
    }

    T pop() {
        if (elements)
            return data[--elements];
        else
            exit(2);
    }

    T top() {
        if (elements) {
            return data[elements - 1];
        }
        else {
            exit(2);
        }
    }

    int size() {
        return elements;
    }

    bool empty() const {
        return (elements) ? true : false;
    }

    void print() {
        for (int i = elements - 1; i >= 0; i--)
            cout << data[i] << endl;
    }

    void numprint() {
        for (int i = size() - 1; i >= 0; i--)
            cout << i << ": " << pop() << endl;
    }

    ~Stack() {
        delete[] data;
    }

    int raw_size() {
        return mem_size;
    }

    bool IsFull() {
        return (elements == mem_size);
    }
};

int main() {
    Stack<int> a;
    int iters = 32;
    Stack<int> c;
    Stack<int> d;

    for (int i = 0; i < 4; i++) {
        c.push(i);
    }

    for (int i = 0; i < iters; i++) {
        a.push(i);
    }

    for (int i = c.size() - 1; i >= 0; i--) {
        cout << i << ": " << c.pop() << endl;
    }

    cout << endl;
    c = a;
    d = a;

    c.print();
    d.numprint();

    return 0;
}

