#include <iostream>

#include "data_structure.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    /*
   *                8
   *        3               10
   *    1     6         x      14
   * x   x  4   7     x   x  13   x
   *
   * x - это nullptr
   */

    itis::AATree tree;


    tree.Add(8);
    tree.Add(3);
    tree.Add(10);
    tree.Add(1);
    tree.Add(6);
    tree.Add(4);
    tree.Add(7);
    tree.Add(14);
    tree.Add(13);
    cout << "_________________________________" << endl;
    tree.Print(tree.root_);
    cout << "----------------------------------" << endl;
    tree.Delete(8);
    tree.Delete(3);
    tree.Delete(10);
    tree.Delete(1);
    tree.Delete(6);
    tree.Delete(4);
    tree.Delete(7);
    tree.Delete(14);
    tree.Delete(13);

    tree.Print(tree.root_);
    cout << "----------------------------------" << endl;

    tree.Add(8);
    tree.Add(8);
    tree.Add(8);
    tree.Add(8);
    tree.Add(8);
    tree.Add(10);
    tree.Add(9);
    tree.Add(8);
    tree.Add(8);
    tree.Add(8);
    tree.Add(11);
    tree.Add(7);
    tree.Add(7);
    tree.Add(7);
    tree.Add(7);

    cout << "_________________________________" << endl;
    tree.Print(tree.root_);
    cout << "----------------------------------" << endl;
    tree.Delete(8);
    tree.Delete(8);
    tree.Delete(8);
    tree.Delete(8);
    tree.Delete(8);
    tree.Delete(8);
    tree.Print(tree.root_);
    cout << "----------------------------------" << endl;
    return 0;
}