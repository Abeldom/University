// Domokos Ábel
// 411

#include <iostream>
using namespace std;

template <typename T>
struct Node {
    T data;
    Node<T>* next;

    Node(T);
};

template <typename T>
class Stack {
    Node<T>* head;
    int maxsize;
    int size;

public:
    Stack(int);
    ~Stack();
    void push(T);
    void pop();
    T& operator[](int);
    void print();
    void operator()(T f(T));
};

template <typename T>
Node<T>::Node(T data)
{
    this->data = data;
}

template <typename T>
Stack<T>::Stack(int length)
{
    maxsize = length;
    size = 0;
    head = NULL;
}

template <typename T>
Stack<T>::~Stack()
{
    delete head;
}

template <typename T>
void Stack<T>::push(T data)
{
    if (size < maxsize) {
        Node<T>* tmp = new Node<T>(data);
        tmp->next = head;
        head = tmp;
        size++;
    } else {
        throw "Full Stack";
    }
}

template <typename T>
void Stack<T>::pop()
{
    if (size == 0) {
        throw "Pop: Empty.";
    }
    Node<T>* tmp = head;
    head = head->next;
    delete tmp;
    size--;
}

template <typename T>
void Stack<T>::print()
{
    Node<T>* tmp = head;
    while (tmp != NULL) {
        cout << tmp->data << " ";
        tmp = tmp->next;
    }
    cout << endl;
}

template <typename T>
void Stack<T>::operator()(T fg(T))
{
    Node<T>* tmp = head;
    while (tmp) {
        tmp->data = fg(tmp->data);
        tmp = tmp->next;
    }
}

template <typename T>
T& Stack<T>::operator[](int it)
{
    Node<T>* tmp = head;
    for (int i = 0; i < it && tmp != NULL; i++) {
        tmp = tmp->next;
    }
    if (tmp == NULL) {
        throw "Index out of range";
    }
    return tmp->data;
}

int fg(int data)
{
    return data + 1;
}
