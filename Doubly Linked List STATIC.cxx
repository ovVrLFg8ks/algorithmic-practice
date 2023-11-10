#include <iostream>
using namespace std;
class LinkedList {
    int element;
    LinkedList* next = NULL;
    LinkedList* prev = NULL;
    static LinkedList* head;
    static LinkedList* tail;
    static int counter;

    LinkedList(int n) : element(n) {
        counter++;
    }
    ~LinkedList() {
        counter--;
    }

    static LinkedList* searchIndx(int& i) {
        if (counter / 2 >= i) {
            LinkedList* t = head;
            for (int iter = 0; iter != i; iter++) {
                t = t->next;
            }
            return t;
        }
        else {
            LinkedList* t = tail;
            for (int iter = counter - 1; iter != i; iter--) {
                t = t->prev;
            }
            return t;
        }
    }

public:
    static bool IsEmpty() {
        return counter == 0;
    }
    static inline int get_size() {
        return counter;
    }
    static void print() {
        if (!counter) { 
            cout << "empty!" << endl;
            return;
        }
        LinkedList* p = head;
        cout << "head-> ";
        while (p) {
            cout << p->element << " ";
            p = p->next;
        }
        cout << "<-tail" << endl;
    }

    static bool push_front(int n) {
        LinkedList* p = new LinkedList(n);
        if (!p) return false;
        if (counter == 1) { // there was a bug
            head = p;
            tail = p;
        }
        else {
            head->prev = p;
            p->next = head;
            head = p;
        }
        return true;
    }
    
    static bool push_back(int n) {
        LinkedList* p = new LinkedList(n);
        if (!p) return false;
        if (counter == 1) {
            head = p;
            tail = p;
        }
        else {
            tail->next = p;
            p->prev = tail;
            tail = p;
        }
        return true;
    }

    static bool pop_front() {
        if (IsEmpty()) return false;
        LinkedList* p = head;
        if (head == tail) head = tail = NULL;
        else {
            head = head->next;
            head->prev = NULL;
        }
        delete p;
        return true;
    }

    static bool pop_back() {
        if (IsEmpty()) return false;
        LinkedList* p = tail;
        if (head == tail) head = tail = NULL;
        else {
            tail = tail->prev;
            tail->next = NULL;
        }
        delete p;
        return true;
    }

    static bool delete_list() {
        if (IsEmpty()) return false;

        LinkedList* p1 = head;
        LinkedList* p2;
        while (p1) {
            p2 = p1->next;
            delete p1;
            p1 = p2;
        }
        head = tail = NULL;

        return true;
    }

    static void erase_element(int i) {
        if (i < 0 || i >= counter) {
            throw std::out_of_range("");
            exit(1);
        }
        LinkedList* p = searchIndx(i);
        p->prev->next = p->next;
        p->next->prev = p->prev;
        delete p;
    }

};

LinkedList* LinkedList::head = NULL;
LinkedList* LinkedList::tail = NULL;
int LinkedList::counter = 0;

int main()
{
    LinkedList::push_front(10);
    LinkedList::push_front(20);
    LinkedList::push_back(30);
    LinkedList::print();

    LinkedList::erase_element(1);
    LinkedList::print();

    LinkedList::pop_back();
    LinkedList::print();

    LinkedList::pop_front();
    LinkedList::print();

    return 0;
}
