#include "data_structure.hpp"

// файл с определениями

namespace itis {

    // здесь должны быть определения методов вашей структуры
    void AATree::Add(int value){
        auto node = new Node(value, nullptr, nullptr, nullptr, 1);

        if(root_ == nullptr){
            root_ = node;

        }
        else{
            Node* current = root_;
            bool isSet = false;
            while(!isSet) {
                if (value >= current->value){
                    if(current->right == nullptr){
                        current->right = node;
                        node->parent=current;
                        Balance(current->right);
                        isSet = true;
                    }
                    else{
                        current = current->right;
                    }
                }
                if (value < current->value){
                    if(current->left == nullptr){
                        current->left = node;
                        node->parent=current;
                        Balance(current->left);
                        isSet = true;

                    }
                    else{
                        current = current->left;
                    }
                }
            }
        }

    }

    Node* AATree::Skew(Node *parent)
    {
        if (parent->left != nullptr)
            if (parent->left->level == parent->level)
            {
                Node *child = parent->left;
                parent->left = child->right;
                if(child->right != nullptr) {
                    parent->left->parent = parent;
                }
                child->right = parent;
                child->parent = parent->parent;
                parent->parent = child;
                if(child->parent != nullptr) {
                    if(child->parent->left == parent) {
                        child->parent->left = child;
                    }
                    else{
                        child->parent->right = child;
                    }
                }
                return child;
            }
        return parent;
    }


    Node* AATree::Split(Node *grandparent)
    {
        if(grandparent->right!=nullptr && grandparent->right->right!=nullptr)
            if(grandparent->level == grandparent->right->right->level)
            {
                Node *parent = grandparent->right;
                grandparent->right = parent->left;
                if(grandparent->right != nullptr) {
                    grandparent->right->parent = grandparent;
                }
                parent->left = grandparent;
                parent->parent = grandparent->parent;
                grandparent->parent = parent;
                if(parent->parent != nullptr) {
                    if(parent->parent->left == grandparent) {
                        parent->parent->left = parent;
                    }
                    else{
                        parent->parent->right = parent;
                    }
                }
                parent->level++;
                return parent;
            }
        return grandparent;

    }

    void AATree::Balance(Node* temp)
    {
        while(temp->parent != nullptr)
        {
            temp = temp->parent;
            if(temp == root_)
            {
                temp = Skew(temp);
                temp = Split(temp);
                root_ = temp;
            }
            else
            {
                temp = Skew(temp);
                temp = Split(temp);
            }
        }
    }


    Node* AATree::Search(int value) {
        Node* current = root_;
        while(true) {
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

    void AATree::Delete(int value){
        Node* current = Search(value);
        if(current->left == nullptr && current->right == nullptr) {
            if (root_ != current) {
                Node *parent = current->parent;
                if (parent->left == current) {
                    parent->left = nullptr;
                } else {
                    parent->right = nullptr;
                }
            }
            else{
                root_ = nullptr;
            }
            delete current;
        }
        else if(current->left == nullptr && current->right != nullptr){
            if(root_ != current) {
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
            }
            else{
                root_ = current->right;
                current->right->parent = nullptr;
            }
            delete current;
        }
        else if(current->left != nullptr && current->right == nullptr){
            if(root_ != current) {
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
            }
            else{
                root_ = current->left;
                current->right->parent = nullptr;
            }
            delete current;
        }
        else{
            Node* node = current->right;
            while(node->left != nullptr){
                node = node->left;
            }
            Swap(node, current);
            Delete(current);
        }
    }

    void AATree::Delete(Node* current){
        if(current->left == nullptr && current->right == nullptr){
            Node* parent = current->parent;
            if(parent->left == current){
                parent->left = nullptr;
            }
            else{
                parent->right = nullptr;
            }
            delete current;
        }
        else if(current->left == nullptr && current->right != nullptr){
            if(root_ != current) {
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
            }
            else{
                root_ = current->right;
                current->right->parent = nullptr;
            }
            delete current;
        }
    }


    void AATree::Swap(Node *one, Node *two){
        int value = one->value;
        one->value = two->value;
        two->value = value;
        /* Node twoCopy = *two;
        Node* parent = two->parent;

        two->level = one->level;
        if(one->parent == two){
            one->parent = parent;
            if(parent->left == two){
                parent->left = one;
            }
            else{
                parent->right = one;
            }
          two->parent = one;
          two->left = one->left;
          two->right = one->right;
          if(two->right != nullptr) {
            two->right->parent = two;
          }

          one->level = twoCopy.level;
          one->parent = twoCopy.parent;
          if(one->parent->left == two){
            one->parent->left = one;
          }
          else{
            one->parent->right = one;
          }
          one->left = twoCopy.left;
          one->left->parent = one;
          one->right = two;
        }
        else {
          two->parent = one->parent;
          two->parent->left = two;
          two->left = one->left;
          two->right = one->right;
          if(two->right != nullptr) {
            two->right->parent = two;
          }

          one->level = twoCopy.level;
          one->parent = twoCopy.parent;
          if(root_ != two) {
              if (one->parent->left == two) {
                  one->parent->left = one;
              } else {
                  one->parent->right = one;
              }
          }
          else{
              root_ = one;
          }
          one->left = twoCopy.left;
          one->left->parent = one;
          one->right = twoCopy.right;
          one->right->parent = one;
        }

         */
    }

    void AATree::IncreaseLevel(Node *current) {
        if(current!= nullptr) {
            IncreaseLevel(current->left);
            IncreaseLevel(current->right);
            current->level++;
            Balance(current);
        }
    }

    void AATree::Print(Node* current) {
        cout << "Level ";
        cout << current->level;
        cout << " | Value = ";
        cout << current->value;
        cout << " | Left ";
        if (current->left != NULL) {
            int left = current->left->value;
            cout << left;
        }
        cout << " | Right ";
        if (current->right !=NULL){
            int right = current->right->value;
            cout << right;
        }
        cout << " | Parent ";
        if (current->parent != NULL){
            int parent = current->parent->value;
            cout << parent;
        }
        cout << endl;
        if(current->left != nullptr)Print(current->left);
        if(current->right != nullptr)Print(current->right);
    }

    void AATree::Print1(Node* current) {
        if (current != nullptr) {
            cout << "Level ";
            cout << current->level;
            cout << " | Value = ";
            cout << current->value;
            cout << " | Left ";
            if (current->left != NULL) {
                int left = current->left->value;
                cout << left;
            }
            cout << " | Right ";
            if (current->right != NULL) {
                int right = current->right->value;
                cout << right;
            }
            cout << endl;
        }
    }

}  // namespace itis