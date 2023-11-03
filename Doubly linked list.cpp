#include <iostream>


template <class T>
class DoubleLinkedList {
private:
    struct cell {
        cell* prev = NULL;
        cell* next = NULL;
        T value;
    };

    cell* front_cell = NULL;
    cell* back_cell = NULL;
    int size = 0;

    cell* searchIndx(int& i) {
        if (size / 2 >= i) {
            cell* t = front_cell;
            for (int iter = 0; iter != i; iter++) {
                t = t->next;
            }
            return t;
        }
        else {
            cell* t = back_cell;
            for (int iter = size - 1; iter != i; iter--) {
                t = t->prev;
            }
            return t;
        }
    }

public:
    DoubleLinkedList() {    }

    static bool IsEmpty() {
        return size == 0;
    }

    int GetSize() {
        return size;
    }

    void push_back(T value) {
        cell* t = new cell;
        (*t).value = value;
        if (size == 0) {
            front_cell = t;
            back_cell = t;
        }
        else {
            (*t).prev = back_cell;
            back_cell->next = t;
            back_cell = t;
        }
        size++;
    }

    void push_front(T value) {
        cell* t = new cell;
        (*t).value = value;
        if (size == 0) {
            front_cell = t;
            back_cell = t;
        }
        else {
            (*t).next = front_cell;
            front_cell->prev = t;
            front_cell = t;
        }
        size++;
    }

    void erase_element(int i) {
        if (i < 0 || i >= size) {
            throw std::out_of_range("");
            exit(1);
        }
        cell* t = searchIndx(i);
        t->prev->next = t->next;
        t->next->prev = t->prev;
        delete t;
    }

    bool pop_back() {
        if (size > 0) {
            cell* t = back_cell->prev;
            delete[] back_cell;
            back_cell = t;
            back_cell->next = NULL;
        }
        else if (size == 0)
            delete back_cell;
        else
            return false;
        size--;
        return true;
    }

    bool pop_front() {
        if (size > 0) {
            cell* t = front_cell->next;
            delete[] front_cell;
            front_cell = t;
            front_cell->prev = NULL;
        }
        else if (size == 0)
            delete front_cell;
        else
            return false;
        size--;
        return true;
    }

    T front() const {
        return front_cell->value; // (*front_cell).value;
    }

    T back() const {
        return back_cell->value;
    }

    const T& operator[](int i) const {
        if (i < 0 || i >= size) {
            throw std::out_of_range("");
            exit(1);
        }
        cell* t = searchIndx(i);
        return t->value;
    }
    
    T& operator[](int i) {
        if (i < 0 || i >= size) {
            throw std::out_of_range("");
            exit(1);
        }
        cell* t = searchIndx(i);
        return t->value;
    }

    void print() {
        if (size == 0)
            return;
        cell* t = front_cell;

        while (t != NULL) {
            std::cout << t->value << std::endl;
            t = t->next;
        }
    }

    void clear() {
        if (size == 0)
            return;
        cell* t1 = front_cell;
        cell* t2;

        while (t1 != NULL) {
            t2 = t1->next;
            delete t1;
            t1 = t2;
        }
        size = 0;
    }

    ~DoubleLinkedList() {
        if (size == 0)
            return;
        cell* t1 = front_cell;
        cell* t2;

        while (t1 != NULL) {
            t2 = t1->next;
            delete t1;
            t1 = t2;
        }
    }
};

using namespace std;

int main() {
    DoubleLinkedList<int> a1, a2;
    for (int i = 111; i <= 999; i += 111)
        a1.push_back(i);
    a2.push_back(3562356);
    cout << a1.front() << endl;
    cout << a1.back() << endl;
    cout << endl;

    a1.print();
    cout << endl;

    a1.pop_back();
    a1.pop_front();

    a1.push_front(100);

    a1.print();
    cout << "size: " << a1.GetSize() << "  " << a2.GetSize() << endl;
    cout << endl;

    for (int i = 0; i < a1.GetSize(); i++)
        cout << a1[i] << endl;
    cout << "___" << endl;

    a1[2] = -99;
    a1.print();
    cout << endl;

    a1.erase_element(2);
    a1.print();
}
