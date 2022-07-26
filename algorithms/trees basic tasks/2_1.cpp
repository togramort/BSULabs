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
  Node *deletion(Node *node, int find);
  Node *findmin(Node *node);
  Node *GetRoot() const {
    return root;
  }
};

void Tree::insert(int x) {
  if (root == nullptr) {
    root = new Node(x);
  } else {
    Node *temp = root;
    while (true) {
      if (temp->key < x) {
        if (temp->right == nullptr) {
          temp->right = new Node(x);
          break;
        } else {
          temp = temp->right;
        }
      } else if (temp->key > x) {
        if (temp->left == nullptr) {
          temp->left = new Node(x);
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

Node *Tree::findmin(Node *node) {
  if (node->left != nullptr) {
    return findmin(node->left);
  } else {
    return node;
  }
}

Node *Tree::deletion(Node *node, int find) {
  if (node == nullptr) {
    return node;
  }
  if (find < node->key) {
    node->left = deletion(node->left, find);
  } else if (find > node->key) {
    node->right = deletion(node->right, find);
  } else if (node->left != nullptr && node->right != nullptr) {
    node->key = findmin(node->right)->key;
    node->right = deletion(node->right, node->key);
  } else {
    if (node->left != nullptr) {
      if (node == root) {
        root = node->left;
      }
      node = node->left;
    } else if (node->right != nullptr) {
      if (node == root) {
        root = node->right;
      }
      node = node->right;
    } else {
      node = nullptr;
    }
  }
  return node;
}

void Tree::preOrder(Node *start) {
  if (start != nullptr) {
    std::cout << start->key << "\n";
    preOrder(start->left);
    preOrder(start->right);
  }
}

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int find;
  std::cin >> find;

  int x;
  Tree t{};
  while (!std::cin.eof()) {
    std::cin >> x;
    t.insert(x);
  }
  t.deletion(t.GetRoot(), find);
  t.preOrder(t.GetRoot());

  return 0;
}