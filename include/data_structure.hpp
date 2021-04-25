#pragma once
#include <node.hpp>
#include <iostream>
using namespace std;

// Заголовочный файл с объявлением структуры данных

namespace itis {

    // Tip 1: объявите здесь необходимые структуры, функции, константы и прочее

    // Пример: объявление константы времени компиляции в заголовочном файле
    inline constexpr auto kStringConstant = "Hello, stranger!";

    // Пример: объявление структуры с полями и методами
    struct AATree {
    public:
        Node* root_{nullptr};

        void Add(int value);

        Node* Search(int value);

        void Delete(int value);
        void Delete(Node *current);

        void IncreaseLevel(Node* current);

        void Print(Node* current);
        void Print1(Node* current);
        void Balance(Node* temp);
        Node* Split(Node* temp);
        Node* Skew(Node* temp);
        void Swap(Node* one, Node* two);
    };

}  // namespace itis