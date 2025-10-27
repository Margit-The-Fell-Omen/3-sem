#pragma once
#include <memory>

template <typename T> class Node
{
public:
  T value;
  Node *left;
  Node *right;

  explicit Node(const T &v) : value(v), left(nullptr), right(nullptr) {}

  friend std::ostream &operator<<(std::ostream &os, const Node<T> &node)
  {
    os << node.value;
    return os;
  }
};
