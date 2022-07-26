#include <iostream>

struct Node {
  Node *left{};
  Node *right{};
  int key;
  explicit Node(int x) {
    key = x;
  }
};

class Tree {
 private:
  Node *root;

 public:
  void insert(int x);
  void preOrder(Node *start);
  Node *GetRoot() const {
    return root;
  }
};

void Tree::insert(int x) {
  if (root == nullptr) {
    root = new Node (x);
  } else {
    Node *temp = root;
    while (true) {
      if (temp->key < x) {
        if (temp->right == nullptr) {
          temp->right = new Node (x);
          break;
        } else {
          temp = temp->right;
        }
      } else if (temp->key > x) {
        if (temp->left == nullptr) {
          temp->left = new Node (x);
          break;
        } else {
          temp = temp->left;
        }
      } else {
        break;
      }
    }
  }
}

void Tree::preOrder(Node *start) {
  if (start != nullptr) {
    std::cout << start->key<< "\n";
    preOrder(start->left);
    preOrder(start->right);
  }
}

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int x;
    Tree t{};
    while (!/*std::*/std::cin.eof()) {
      std::cin >> x;
      t.insert(x);
    }
  t.preOrder(t.GetRoot());
  return 0;
  }