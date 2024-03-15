// Domokos Ábel
// 411

#include <iostream>
using namespace std;

/////////////////////////////////////////////
// Node:
/////////////////////////////////////////////

template <class T>
class Queue;

template <class T>
class Node {
  T* elem;
  Node* next;

 public:
  Node(T e);
  ~Node();
  ostream& print(ostream& s);
  friend class Queue<T>;
};

template <class T>
Node<T>::Node(T e) {
  elem = new T(e);
  next = NULL;
}

template <class T>
Node<T>::~Node() {
  delete elem;
}

template <class T>
ostream& Node<T>::print(ostream& s) {
  return s << *elem;
}

template <class T>
ostream& operator<<(ostream& s, Node<T>& o) {
  return o.print(s);
}

/////////////////////////////////////////////
// Queue:
/////////////////////////////////////////////

template <class T>
class Queue {
  Node<T>* top;
  Node<T>* endq;
  int n;

 public:
  Queue();
  ~Queue();

  void add(T e);
  void remove();
  bool isempty();
  ostream& print(ostream& s);

  class iterator;

  iterator begin() { return iterator(top); }

  iterator end() { return iterator(NULL); }
};

template <class T>
Queue<T>::Queue() {
  n = 0;
  top = NULL;
  endq = NULL;
}

template <class T>
Queue<T>::~Queue() {
  Node<T>* a = top;
  while (top != NULL) {
    top = top->next;
    delete a;
    a = top;
  }
}

template <class T>
void Queue<T>::add(T e) {
  Node<T>* a = new Node<T>(e);
  if (endq == NULL) {
    endq = a;
    top = a;
  } else {
    endq->next = a;
    endq = a;
  }
  n++;
}

template <class T>
void Queue<T>::remove() {
  if (n == 0) return;
  Node<T>* a = top;
  top = top->next;
  delete a;
  n--;
}

template <class T>
ostream& Queue<T>::print(ostream& s) {
  if (n == 0) return s << "[]";
  Node<T>* a = top;
  s << "[";
  while (a->next != NULL) {
    s << *a << ", ";
    a = a->next;
  }
  s << *a << "]";
  return s;
}

template <class T>
ostream& operator<<(ostream& s, Queue<T>& o) {
  return o.print(s);
}

template <class T>
bool Queue<T>::isempty() {
  return (n > 0) ? false : true;
}

template <class T>
class Queue<T>::iterator {
  Node<T>* current;

 public:
  iterator(Node<T>* p) { current = p; }

  ~iterator() {}

  // iterator& operator =(const iterator& other) {
  //	current = other.current;
  //	return *this;
  // }

  iterator& operator=(const iterator& other);

  bool operator==(const iterator& other) { return (current == other.current); }

  bool operator!=(const iterator& other) { return (current != other.current); }

  iterator& operator++() {
    if (current != NULL) {
      current = current->next;
    }
    return *this;
  }

  iterator operator++(int) {
    iterator tmp(*this);
    ++(*this);
    return tmp;
  }

  T operator*() { return (*current->elem); }
};

// typename: (http://pages.cs.wisc.edu/~driscoll/typename.html)
template <class T>
typename Queue<T>::iterator& Queue<T>::iterator::operator=(
    const iterator& other) {
  current = other.current;
  return *this;
}

/////////////////////////////////////////////
// main:
/////////////////////////////////////////////

int main() {
  Node<int> a(1);
  cout << a << endl;
  Queue<int> b;
  b.add(1);
  b.add(2);
  b.add(3);
  cout << b << endl;
  b.remove();
  cout << b << endl;

  cout << "[";
  for (Queue<int>::iterator i = b.begin(); i != b.end(); i++) {
    cout << *i << ", ";
  }
  cout << "]";
  return 0;
}