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

            while (true) {
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
                    else {
                        buf = buf->left;
                    }
                }
                else {
                    if (buf->right == nullptr) {
                        buf->right = new Node<T>{ newData };
                        buf->right->parent = buf;
                        count++;
                        break;
                    }
                    else {
                        buf = buf->right;
                    }
                }
            }
        }
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
};

int main() {
    MyList<int> mylist;
    const int array[20] = { 9, 2, 5, 13, 7, 10, 18, 4, 16, 11, 6, 3, 19, 14, 12, 17, 8, 1, 15, 20 };
    mylist.pushArray(array, 20);
    mylist.show();
    cout << endl;
    return 0;
}