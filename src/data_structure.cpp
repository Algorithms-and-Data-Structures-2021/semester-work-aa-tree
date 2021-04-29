#include "data_structure.hpp";

// файл с определениями

namespace itis {

    //добавление
    void AATree::Add(int value) {
        auto node = new Node(value, nullptr, nullptr, nullptr, 1);

        //если дерево пустое
        if (root_ == nullptr) {
            root_ = node;

        }
        //дерево непустое
        else {
            Node *current = root_;
            bool isSet = false;
            while (!isSet) {
                //если значение больше или равно значению текущего, то идем в правую ветку
                if (value >= current->value) {
                    //если там пусто, то устанавливаем значение
                    if (current->right == nullptr) {
                        current->right = node;
                        node->parent = current;
                        Balance(current->right);
                        //установили, и цикл после этого прекратится
                        isSet = true;
                    }
                        //иначе текущий элемент меняется на правого ребенка
                    else {
                        current = current->right;
                    }
                }
                //если значение меньше значения текущего, то идем в левую ветку
                if (value < current->value) {
                    //если там пусто, то устанавливаем значение
                    if (current->left == nullptr) {
                        current->left = node;
                        node->parent = current;
                        Balance(current->left);
                        //установили, и цикл после этого прекратится
                        isSet = true;
                    }
                        //иначе текущий элемент меняется на левого ребенка
                    else {
                        current = current->left;
                    }
                }
            }
        }

    }

    // устранение левого горизонтального ребра. Делаем правое вращение, чтобы заменить поддерево,
    // содержащее левую горизонтальную связь, на поддерево, содержащее разрешенную правую горизонтальную связь
    // https://neerc.ifmo.ru/wiki/images/9/93/Skew.png
    Node *AATree::Skew(Node *parent) {
        if (parent->left != nullptr)
            if (parent->left->level == parent->level) {
                Node *child = parent->left;
                parent->left = child->right;
                if (child->right != nullptr) {
                    parent->left->parent = parent;
                }
                child->right = parent;
                child->parent = parent->parent;
                parent->parent = child;
                if (child->parent != nullptr) {
                    if (child->parent->left == parent) {
                        child->parent->left = child;
                    } else {
                        child->parent->right = child;
                    }
                }
                return child;
            }
        return parent;
    }


    //устранение двух последовательных правых горизонтальных ребер. Делаем левое вращение и увеличиваем уровень, чтобы заменить поддерево,
    //содержащее две или более последовательных правильных горизонтальных связи, на вершину, содержащую два поддерева с меньшим уровнем.
    //https://neerc.ifmo.ru/wiki/images/9/92/Split_rb.png
    Node *AATree::Split(Node *grandparent) {
        if (grandparent->right != nullptr && grandparent->right->right != nullptr)
            if (grandparent->level == grandparent->right->right->level) {
                Node *parent = grandparent->right;
                grandparent->right = parent->left;
                if (grandparent->right != nullptr) {
                    grandparent->right->parent = grandparent;
                }
                parent->left = grandparent;
                parent->parent = grandparent->parent;
                grandparent->parent = parent;
                if (parent->parent != nullptr) {
                    if (parent->parent->left == grandparent) {
                        parent->parent->left = parent;
                    } else {
                        parent->parent->right = parent;
                    }
                }
                parent->level++;
                return parent;
            }
        return grandparent;

    }


    //Балансировка дерева (вызываает split и skew)
    //Дерево таким способом "саморегулируется"
    void AATree::Balance(Node *temp) {
        while (temp->parent != nullptr) {
            temp = temp->parent;
            if (temp == root_) {
                temp = Skew(temp);
                temp = Split(temp);
                root_ = temp;
            } else {
                temp = Skew(temp);
                temp = Split(temp);
            }
        }
    }

    //Поиск выполняется похожим на добавление алгоритмом, мы "ходим" по дереву,
    //исходя из значения, которое ищем.
    //Если мы дойдем до конца дерева(листа) и так и не найдем элемент с нужным значением
    //метод вернет nullptr (т.е такого элемента в дереве нет)
    Node *AATree::Search(int value) {
        Node *current = root_;
        while (true) {
            if (value == current->value) {
                return current;
            } else if (value > current->value) {
                if (current->right == nullptr) {
                    return nullptr;
                } else {
                    current = current->right;
                }
            } else if (value < current->value) {
                if (current->left == nullptr) {
                    return nullptr;
                } else {
                    current = current->left;
                }
            }
        }
    }

    //Удаление использвует поиск
    //сначала находим нужную вершину
    //потом рассматриваем четыре варианта удаления
    void AATree::Delete(int value) {
        Node *current = Search(value);
        //первый случай: удаляем листик (ничего сложного)
        if (current->left == nullptr && current->right == nullptr) {
            if (root_ != current) {
                Node *parent = current->parent;
                if (parent->left == current) {
                    parent->left = nullptr;
                } else {
                    parent->right = nullptr;
                }
            } else {
                root_ = nullptr;
            }
            delete current;
        }
            //второй случай: слева - ничего, справа что-то есть
            //удаляем элемент, а всю его правую ветку поднимаем на один уровень
        else if (current->left == nullptr && current->right != nullptr) {
            if (root_ != current) {
                Node *parent = current->parent;
                if (parent->left == current) {
                    parent->left = current->right;
                } else {
                    parent->right = current->right;
                }

                current->right->parent = parent;
                IncreaseLevel(current->parent->left);
                IncreaseLevel(current->parent->right);
                Balance(current->parent);
            } else {
                root_ = current->right;
                current->right->parent = nullptr;
            }
            delete current;
        }
            //третий случай: справа - ничего, слева что-то есть
            //удаляем элемент, а всю его левую ветку поднимаем на один уровень
        else if (current->left != nullptr && current->right == nullptr) {
            if (root_ != current) {
                Node *parent = current->parent;
                if (parent->left == current) {
                    parent->left = current->left;
                } else {
                    parent->right = current->left;
                }
                current->left->parent = parent;
                IncreaseLevel(current->parent->left);
                IncreaseLevel(current->parent->right);
                Balance(current->parent);
            } else {
                root_ = current->left;
                current->right->parent = nullptr;
            }
            delete current;
        }
            //четвертый случай: и слева, и справа что-то есть
            //сначала у правого потомка находим его самого левого потомка
            //потом меняем его и удаляемный элемент местами
            //далее мы вызывем перегруженный метод удаления, но уже без поиска элемента(тк мы знаем, где он находится)
            //а там лишь два варианта (либо он листик, либо у него есть правый ребенок) с этими ситуациями мы уже умеем справляться
        else {
            Node *node = current->right;
            while (node->left != nullptr) {
                node = node->left;
            }
            Swap(node, current);
            Delete(current);
        }
    }

    //тот самый перегруженный метод удаления :D
    void AATree::Delete(Node *current) {
        if (current->left == nullptr && current->right == nullptr) {
            Node *parent = current->parent;
            if (parent->left == current) {
                parent->left = nullptr;
            } else {
                parent->right = nullptr;
            }
            delete current;
        } else if (current->left == nullptr && current->right != nullptr) {
            if (root_ != current) {
                Node *parent = current->parent;
                if (parent->left == current) {
                    parent->left = current->right;
                } else {
                    parent->right = current->right;
                }

                current->right->parent = parent;
                IncreaseLevel(current->parent->left);
                IncreaseLevel(current->parent->right);
                Balance(current->parent);
            } else {
                root_ = current->right;
                current->right->parent = nullptr;
            }
            delete current;
        }
    }

    //метод для смены местами элементов (мы его используем в четвертом варианте удаления)
    void AATree::Swap(Node *one, Node *two) {
        int value = one->value;
        one->value = two->value;
        two->value = value;
    }

    //метод повышения уровня элемента
    void AATree::IncreaseLevel(Node *current) {
        if (current != nullptr) {
            IncreaseLevel(current->left);
            IncreaseLevel(current->right);
            current->level++;
            Balance(current);
        }
    }

    //метод вывода дерева в виде списка элементов со значениями их параметров
    void AATree::Print(Node *current) {
        cout << "Level ";
        cout << current->level;
        cout << " | Value = ";
        cout << current->value;
        cout << " | Left ";
        if (current->left != nullptr) {
            int left = current->left->value;
            cout << left;
        }
        cout << " | Right ";
        if (current->right != nullptr) {
            int right = current->right->value;
            cout << right;
        }
        cout << " | Parent ";
        if (current->parent != nullptr) {
            int parent = current->parent->value;
            cout << parent;
        }
        cout << endl;
        if (current->left != nullptr)Print(current->left);
        if (current->right != nullptr)Print(current->right);
    }

}  // namespace itis