#include "list.h"

int main(int argc, char **argv) {
    int pos = 0;
    LinkedList<int> l1, l2;

    for (int i = 0; i < 10; i++) {
        pos = l1.insert_after(pos, i);
    }

    l2 = l1;
    LinkedList<int> l3 = l1;

    for (int i = 0; i < 5; i++) {
        l3.erase_after(5);
    }

    l1.remove(7);
    l1.insert_after(3, 15);
    l1.insert_after(3, 15);
    l1.insert_after(3, 15);
    l1.remove(15);

    cout << l1 << endl;
    cout << l2 << endl;
    cout << l3 << endl;

    cout << l1.empty() << endl;
    l1.clear();
    cout << l1 << endl;
    cout << l1.empty() << endl;

    return (0);
}
