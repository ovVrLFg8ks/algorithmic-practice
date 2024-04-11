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

    void insert(T value) {
        if (!_size) {
            root->value = value;
            _size++;
            return;
        }
        current_cell = root;
        while (true) {
            if (current_cell->value < value) {
                if (current_cell->dL != NULL)
                    current_cell = current_cell->dL;
                else {
                    cell* t = new cell{ current_cell, value, NULL, NULL };
                    current_cell->dL = t;
                    _size++;
                    return;
                }
            }
            else if (current_cell->value > value) {
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

    void erase(T value) {
        if (!contains(value))
            return;
        if (current_cell->dL ^ current_cell->dR) {
            cell* d = current_cell->dL + current_cell->dR;
        }
    }

    int size() {
        return size;
    }

    void print() {
        print(root);
    }

    bool contains(T value) {
        current_cell = root;
        if (!_size)
            return false;
        while (true) {
            if (current_cell->value < value) {
                if (current_cell->dL != NULL)
                    current_cell = current_cell->dL;
                else
                    return false;
            }
            else if (current_cell->value > value) {
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
    a.insert(4);
    a.insert(6);
    a.insert(2);

    cout << a.contains(3) << endl;
    cout << a.contains(4) << endl << endl;
    a.print();

    return 0;
}
