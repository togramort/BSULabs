#include <iostream>
#include <vector>
#include <algorithm>

struct Node {
  Node *left{};
  Node *right{};
  int key;
  explicit Node(int x) {
    key = x;
  }
  int hL = -1, hR = -1, hD = -1;
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

std::vector<std::pair<int, int>> v;
int heightTree(Node *start) {
  if (start == nullptr) {
    return 0;
  }
  if (start->left) {
    heightTree(start->left);
    start->hL = std::max(start->left->hL, start->left->hR) + 1;
  }
  if (start->right) {
    heightTree(start->right);
    start->hR = std::max(start->right->hL, start->right->hR) + 1;
  }

  start->hD = std::abs(start->hL - start->hR);
  v.emplace_back(std::make_pair(start->hD, start->key));

  return 0;
}

int main() {
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  int x;
  Tree t{};
  while (!std::cin.eof()) {
    std::cin >> x;
    t.insert(x);
  }

  heightTree(t.GetRoot());
  std::sort(v.begin(), v.end());
  std::vector<int> vertexWithMaxH;

  int maxDeltaH = v[v.size() - 1].first;
  for (int i = v.size() - 1; i > -1; --i) {
    if (v[i].first == maxDeltaH) {
      vertexWithMaxH.emplace_back(v[i].second);
    }
  }

  if (vertexWithMaxH.size() % 2 != 0) {
    t.deletion(t.GetRoot(), vertexWithMaxH[vertexWithMaxH.size() / 2]);
  } else {
    t.preOrder(t.GetRoot());
    return 0;
  }

  t.preOrder(t.GetRoot());
  return 0;
}