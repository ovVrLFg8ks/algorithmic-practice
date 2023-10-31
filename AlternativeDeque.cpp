#include <iostream>
#include <stack>

using namespace std;

template <class T>
class AltDeque {
private:
    bool r_act = false;
    stack<T> left;  stack<T> right;

    void l_to_r() {
        while (left.size() > 0) {
            right.push(left.top());
            left.pop();
        }
        r_act = true;
    }

    void r_to_l() {
        while (right.size() > 0) {
            left.push(right.top());
            right.pop();
        }
        r_act = false;
    }

public:
    AltDeque() { }

    void push_back(T& val) {    // PUSH //
        if (r_act)
            r_to_l();
        left.push(val);
    }

    void push_front(T& val) {
        if (!r_act)
            l_to_r();
        right.push(val);
    }                           //  //  //


    T pop_back() {              // POP  //
        if (r_act)
            r_to_l();
        T out = left.top();
        left.pop();
        return out;
    }

    T pop_front() {
        if (!r_act)
            l_to_r();
        T out = right.top();
        right.pop();
        return out;
    }                           //  //  //


    T back() {                  // ACC  // 
        if (r_act)
            r_to_l();
        return left.top();
    }

    T front() {
        if (!r_act)
            l_to_r();
        return right.top();
    }                           //  //  //


    int size() const {
        return (r_act) ? right.size() : left.size();
        if (r_act)
            return right.size();
        else
            return left.size();
    }
};

int main() {
    AltDeque<int> a;

    for (int i = 1; i < 21; i++) {
        if (i % 2)
            a.push_front(i);
        else
            a.push_back(i);
    }

    cout << a.size() << "  " << a.back() << "  " << a.front() << endl;

    AltDeque<int> b;
    b = a;

    for (int i = 1; i < 21; i++) {
        cout << a.pop_front() << endl;
    }

    cout << "######" << endl;

    for (int i = 1; i < 21; i++) {
        cout << b.pop_front() << endl;
    }

    return 0;
}
