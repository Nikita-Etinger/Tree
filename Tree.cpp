
#include <iostream>

using namespace std;

template <typename T>
struct Node {
    T data;
    Node* left = nullptr;
    Node* right = nullptr;


};
template <typename T>
class MyList {
    Node <T>* root = nullptr;
    int count = 0;
public:
    MyList() {}
    void push(T  newData) {
        if (count == 0) {
            root = new Node<T>{ newData };
            count++;
        }
        else {
            Node<T>* buf = root;

            while (1) {
                if (buf->data == newData) {
                    buf->data = newData;
                    break;
                }
                if (newData < buf->data) {
                    if (buf->left == nullptr) {
                        buf->left = new Node<T>{ newData };
                        count++;
                        break;
                    }
                    else {
                        buf = buf->left;
                        continue;
                    }
                }
                else {
                    if (newData > buf->data) {
                        if (buf->right == nullptr) {
                            buf->right = new Node<T>{ newData };
                            count++;
                            break;
                        }
                        else {
                            buf = buf->right;
                            continue;
                        }
                    }

                }
            }
        }
    }
    void show() {
        showAll(root);
    }

    void showAll(Node <T>* bufRoot) {
        cout << bufRoot->data << " ";
        if (bufRoot->left != nullptr) {
            showAll(bufRoot->left);
        }
        if (bufRoot->right != nullptr) {
            showAll(bufRoot->right);
        }
    }
    /*
    1. нет потомков
    2. один потомок
    3. оба потомка






    */
    void twoPar(Node<T>* buf) {




    }
    void onePar(Node<T>* buf, T data) {
        Node<T>* bufLeft = buf->left;
        Node<T>* bufRight = buf->right;
        if (bufLeft != nullptr) {
            buf->left = bufLeft->left->left;

        }



    }

    void withoutPar(Node<T>* buf, T data) {
        buf->left == nullptr;
        buf->right == nullptr;


    }

    void delData(T data) {
        Node<T>buf *= delData(root);

        if (buf != nullptr) {
            Node<T>* bufLeft = buf->left;
            Node<T>* bufRight = buf->right;
            if (bufLeft == nullptr && bufRight == nullptr) {
                withoutPar(buf);
            }
            else if (bufLeft != nullptr && bufRight != nullptr) {
                onePar(buf);
            }
            else twoPar(buf);

        }
    }



    Node<T>buf delData(Node<T>* buf) {
        if (data == buf->data) return buf;
        if (data < buf->data) {
            buf = buf->left;
            return delData(buf);
        }
        if (data > buf->data) {
            buf = buf->right;
            continue delData(buf);
        }
        return nullptr;
    }



};
int main()
{
    MyList<int> mylist;
    mylist.push(10);
    mylist.push(9);
    mylist.push(15);
    mylist.push(7);
    mylist.push(6);
    mylist.push(8);
    mylist.push(20);
    mylist.push(31);
    mylist.show();
    std::cout << "Hello World!\n";
}

