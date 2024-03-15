#include <fstream>
#include <iostream>
using namespace std;

// typedef int termeszetes;

// keresofa
template <typename T>
class Binary
{
  struct Node
  {
    T data;
    Node *left;
    Node *right;
    Node(T data, Node *left, Node *right)
        : data(data), left(left), right(right) {}
  } * root;

public:
  class NoKey
  {
  };
  class KeyExists
  {
  };
  // lituya bay mega tsunami  konstruktorok
  Binary();
  ~Binary();

  void preorder() const;

  bool search(T) const; // megnezi hogy benne van/e
  void insert(T);       //
  void remove(T);

private:
  Node *insert(Node *, T);
};

// Node::Node(int data)
// {
//     left = NULL;
//     right = NULL;
//     this->data = data;
// }

Binary::Binary() : root(NULL)
{
}

template <typename T>
Binary::Node *Binary::insert(Binary::Node *root, T key)
{
  if (!root)
    return new Node(key, NULL, NULL);

  if (key < root->data)
  {
    root->left = insert(root->left, key);
  }
  if (key > root->data)
  {
    root->right = insert(root->right, key);
  }

  else
    throw KeyExists();

  return root;

  // if (!root) {
  //     root = new Node();
  //     root->data = key;
  //     root->left = root->right;
  // }
}

template <typename T>
void Binary::insert(T key)
{
  root = insert(root, key);
}
template <typename T>
void Binary::remove(T key)
{
}
template <typename T>
bool Binary::search(T key) const
{
  return true;
}

void Binary::preorder() const
{
  if (root)
  {
    cout << root->data << " ";
    inorder(root->left);
    inorder(root->right);
  }
}

Binary::~Binary() {}

int main()
{
  Binary b;
  if (b.search(6))
    cout << "talalt";
  else
    cout << "nem talalt.";

  try
  {
    b.insert(3);
    b.insert(8);
    b.insert(6);
    b.insert(7);

    b.remove(6);
  }
  catch (Binary::NoKey)
  {
    cout << "nem talalhato a torolni kivant elem!" << endl;
  }
  catch (Binary::KeyExists)
  {
    cout << "az elem mar benne van a keresofaban" << endl;
  }

  cout << "inoreder: ";
  b.inorder();
  cout << endl;

  cout << "postorder: ";
  b.postorder();
  cout << endl;

  cout << "preorder: ";
  b.preorder();
  cout << endl;

  return 0;
}
