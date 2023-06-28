#include <iostream>

using namespace std;

template <typename T>
struct Node {
    T data;
    Node* left = nullptr;
    Node* right = nullptr;
    Node* parent = nullptr;
};

template <typename T>
class MyList {
    Node<T>* root = nullptr;
    int count = 0;
    void twoPar(Node<T>* buf) {
        Node<T>* smallest = buf->right;
        while (smallest->left != nullptr) {
            smallest = smallest->left;
        }

        buf->data = smallest->data;

        if (smallest->parent->left == smallest) {
            smallest->parent->left = smallest->right;
            if (smallest->right != nullptr) {
                smallest->right->parent = smallest->parent;
            }
        }
        else {
            smallest->parent->right = smallest->right;
            if (smallest->right != nullptr) {
                smallest->right->parent = smallest->parent;
            }
        }

        delete smallest;
    }
    void onePar(Node<T>* buf, T data) {
        Node<T>* bufChild = (buf->left != nullptr) ? buf->left : buf->right;

        if (buf->parent != nullptr) {
            if (buf == buf->parent->left) {
                buf->parent->left = bufChild;
            }
            else {
                buf->parent->right = bufChild;
            }

            if (bufChild != nullptr) {
                bufChild->parent = buf->parent;
            }
        }
        else {
            root = bufChild;
            if (bufChild != nullptr) {
                bufChild->parent = nullptr;
            }
        }

        delete buf;
    }
    void withoutPar(Node<T>* buf) {
        if (buf->parent != nullptr) {
            if (buf == buf->parent->left) {
                buf->parent->left = nullptr;
            }
            else {
                buf->parent->right = nullptr;
            }
        }
        else {
            root = nullptr;
        }

        delete buf;
    }
    Node<T>* delData(Node<T>* buf, T data) {
        if (buf == nullptr) {
            return nullptr;
        }

        if (data == buf->data) {
            return buf;
        }

        if (data < buf->data) {
            return delData(buf->left, data);
        }
        else {
            return delData(buf->right, data);
        }
    }
    void showAll(Node<T>* bufRoot) {
        if (bufRoot != nullptr) {
            cout << bufRoot->data << " ";
            showAll(bufRoot->left);
            showAll(bufRoot->right);
        }
    }
    void destroyTree(Node<T>* node) {
        if (node != nullptr) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }
public:
    MyList() {}
    ~MyList() {
        destroyTree(root);
    }
    void push(T newData) {
        if (count == 0) {
            root = new Node<T>{ newData };
            count++;
        }
        else {
            Node<T>* buf = root;
            Node<T>* parent = nullptr;
            while (true) {
                parent = buf;
                if (buf->data == newData) {
                    buf->data = newData;
                    break;
                }
                else if (newData < buf->data) {
                    if (buf->left == nullptr) {
                        buf->left = new Node<T>{ newData };
                        buf->left->parent = buf;
                        count++;
                        break;
                    }
                    buf = buf->left;
                }
                else {
                    if (buf->right == nullptr) {
                        buf->right = new Node<T>{ newData };
                        buf->right->parent = buf;
                        count++;
                        break;
                    }
                    buf = buf->right;
                }
            }

            // проверка баланса 
            while (parent != nullptr) {
                int balanceFactor = getHeight(parent->left) - getHeight(parent->right);
                if (balanceFactor > 1) {
                    if (newData < parent->left->data) {
                        parent = rightRotate(parent);
                    }
                    else {
                        parent->left = leftRotate(parent->left);
                        parent = rightRotate(parent);
                    }
                }
                else if (balanceFactor < -1) {
                    if (newData > parent->right->data) {
                        parent = leftRotate(parent);
                    }
                    else {
                        parent->right = rightRotate(parent->right);
                        parent = leftRotate(parent);
                    }
                }
                parent = parent->parent;
            }
        }
    }
    int getHeight(Node<T>* node) {
        if (node == nullptr) {
            return 0;
        }
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);
        return 1 + max(leftHeight, rightHeight);
    }
    void show() {
        showAll(root);
    }
    void delData(T data) {
        Node<T>* buf = delData(root, data);

        if (buf != nullptr) {
            Node<T>* bufLeft = buf->left;
            Node<T>* bufRight = buf->right;

            if (bufLeft == nullptr && bufRight == nullptr) {
                withoutPar(buf);
            }
            else if (bufLeft != nullptr && bufRight != nullptr) {
                twoPar(buf);
            }
            else {
                onePar(buf, data);
            }
        }
    }
    void pushArray(const T* arr, int size) {
        for (int i = 0; i < size; i++) {
            push(arr[i]);
        }
    }
    Node<T>* leftRotate(Node<T>* node) {
        Node<T>* newRoot = node->right;
        node->right = newRoot->left;
        if (newRoot->left != nullptr) {
            newRoot->left->parent = node;
        }
        newRoot->parent = node->parent;
        if (node->parent != nullptr) {
            if (node == node->parent->left) {
                node->parent->left = newRoot;
            }
            else {
                node->parent->right = newRoot;
            }
        }
        newRoot->left = node;
        node->parent = newRoot;
        return newRoot;
    }
    Node<T>* rightRotate(Node<T>* node) {
        Node<T>* newRoot = node->left;
        node->left = newRoot->right;
        if (newRoot->right != nullptr) {
            newRoot->right->parent = node;
        }
        newRoot->parent = node->parent;
        if (node->parent != nullptr) {
            if (node == node->parent->right) {
                node->parent->right = newRoot;
            }
            else {
                node->parent->left = newRoot;
            }
        }
        newRoot->right = node;
        node->parent = newRoot;
        return newRoot;
    }

};

int main() {
    MyList<int> mylist;
    const int array[20] = { 9, 2, 5, 13, 7, 10, 18, 4, 16, 11, 6, 3, 19, 14, 12, 17, 8, 1, 15, 20 };
    mylist.pushArray(array, 20);
    mylist.show();
    cout << endl;
    return 0;
}