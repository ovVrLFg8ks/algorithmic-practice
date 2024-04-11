#include <iostream>

template <class T>
class set {
private:
    struct cell {
        cell* up;
        T value;
        cell* dL;
        cell* dR;
    };
    cell* current_cell;
    cell* root;
    int _size = 0;
public:
    set() {
        root = new cell{};
    }

    void insert(const T value) {
        if (!_size) {
            root->value = value;
            _size++;
            return;
        }
        current_cell = root;
        while (true) {
            if (current_cell->value > value) {
                if (current_cell->dL != NULL)
                    current_cell = current_cell->dL;
                else {
                    cell* t = new cell{ current_cell, value, NULL, NULL };
                    current_cell->dL = t;
                    _size++;
                    return;
                }
            }
            else if (current_cell->value < value) {
                if (current_cell->dR != NULL)
                    current_cell = current_cell->dR;
                else {
                    cell* t = new cell{ current_cell, value, NULL, NULL };
                    current_cell->dR = t;
                    _size++;
                    return;
                }
            }
            else
                return;
        }
    }

    void erase(const T value) {
        if (!contains(value))
            return;
        erase();
    }

    int size() const {
        return _size;
    }

    void print() {
        print(root);
        std::cout << std::endl;
    }

    bool contains(const T value) {
        current_cell = root;
        if (!_size)
            return false;
        while (true) {
            if (current_cell->value > value) {
                if (current_cell->dL != NULL)
                    current_cell = current_cell->dL;
                else
                    return false;
            }
            else if (current_cell->value < value) {
                if (current_cell->dR != NULL)
                    current_cell = current_cell->dR;
                else
                    return false;
            }
            else
                return true;
        }
    }

    void clear() {
        deleteCells(root);
        root = new cell{};
    }

    ~set() {
        deleteCells(root);
    }

private:
    void erase() {
        int nodeState = 1;
        if (current_cell->dL)
            nodeState *= 3;
        if (current_cell->dR)
            nodeState *= 5;
        if (current_cell->up)
            nodeState *= 7;

        _size--;
        if (nodeState == 1) {
            delete current_cell;
            return;
        }
        if (!(nodeState % 7)) { // if have parent
            cell* parent = current_cell->up;
            if (!(nodeState % 15)) { // both chld
                cell* c = current_cell->dR; // not C28182 due to nodeState states that cell have children
                while (c->dL != NULL)
                    c = c->dL;
                current_cell->value = c->value;
                _size++;
                current_cell = c;
                erase();
                return;
            }
            if (!(nodeState % 3)) { // left chld
                current_cell->dL->up = current_cell->up;
                if (parent->dL == current_cell)
                    parent->dL = current_cell->dL;
                else
                    parent->dR = current_cell->dL;
                delete current_cell;
                return;
            }
            if (!(nodeState % 5)) { // right chld
                current_cell->dR->up = current_cell->up;
                if (parent->dL == current_cell)
                    parent->dL = current_cell->dR;
                else
                    parent->dR = current_cell->dR;
                delete current_cell;
                return;
            }
            {                       // no chld
                if (parent->dL == current_cell)
                    parent->dL = NULL;
                else
                    parent->dR = NULL;
                delete current_cell;
                return;
            }
        }
        else { // if no parent
            if (!(nodeState % 15)) { // both chld
                cell* c = current_cell->dR; // not C28182 due to nodeState states that cell have children
                while (c->dL != NULL)
                    c = c->dL;
                current_cell->value = c->value;
                _size++;
                current_cell = c;
                erase();
                return;
            }
            if (!(nodeState % 3)) { // left chld
                root = current_cell->dL;
                delete current_cell;
                return;
            }
            if (!(nodeState % 5)) { // right chld
                root = current_cell->dR;
                delete current_cell;
                return;
            }
            {                       // no chld
                delete current_cell;
                return;
            }
        }

        /*
        if (current_cell->dL ^ current_cell->dR) { // if only one child cell
            cell* d = current_cell->dL + current_cell->dR;
            current_cell->value = d->value;
            current_cell->dL = d->dL;
            current_cell->dR = d->dR;
            delete d;
        }*/
    }

    void print(cell* root) {
        if (root->dL != NULL)
            print(root->dL);
        std::cout << root->value << std::endl;
        if (root->dR != NULL)
            print(root->dR);
    }

    void deleteCells(cell* root) {
        if (root->dL != NULL)
            deleteCells(root->dL);
        if (root->dR != NULL)
            deleteCells(root->dR);
        delete[] root;
    }
};

using namespace std;

int main() {
    set<int> a;
    a.insert(10);

    a.insert(5);
    a.insert(15);

    a.insert(3);
    a.insert(7);
    a.insert(13);
    a.insert(17);

    a.insert(2);
    a.insert(4);
    a.insert(6);
    a.insert(9);
    a.insert(12);
    a.insert(14);
    a.insert(16);
    a.insert(18);

    a.print();
    cout << a.size() << endl << endl;

    a.erase(10);
    a.print();
    cout << a.size() << endl;

    return 0;
}
