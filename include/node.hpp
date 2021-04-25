#pragma once

namespace itis {

    struct Node {
    public:
        // хранимое значение
        int value;

        // указатели на родителя
        Node *parent;

        // указатели на левого и правого потомка
        Node *left;
        Node *right;

        // уровень
        int level;


        Node(int value, Node *parent, Node *left, Node *right, int level) : value(value), parent(parent), left(left),
                                                                            right(right), level(level) {}


    };
}
