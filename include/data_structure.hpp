#pragma once
#include <node.hpp>
#include <iostream>
using namespace std;

// Заголовочный файл с объявлением структуры данных

namespace itis {

    struct AATree {
    public:
        Node* root_{nullptr};

        void Add(int value);

        Node* Search(int value);

        void Delete(int value);
        void Delete(Node *current);

        void IncreaseLevel(Node* current);

        void Print(Node* current);
        void Balance(Node* temp);
        Node* Split(Node* temp);
        Node* Skew(Node* temp);
        void Swap(Node* one, Node* two);
    };

}  // namespace itis