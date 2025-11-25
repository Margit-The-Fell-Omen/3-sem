#pragma once
#include "BinLeaf.h"
#include "BinTreeException.h"
#include "InputException.h"
#include "Order.h"
#include <iostream>
#include <queue>
#include <stack>

template <typename T> class BinTree
{
private:
  Node<T> *root = nullptr;

  void clear(Node<T> *node)
  {
    if (node)
    {
      clear(node->left);
      clear(node->right);
      delete node;
    }
  }

  Node<T> *insertRec(Node<T> *node, const T &value)
  {
    if (!node)
      return new Node<T>(value);
    if (value < node->value)
      node->left = insertRec(node->left, value);
    else
      node->right = insertRec(node->right, value);
    return node;
  }

  Node<T> *findMin(Node<T> *node)
  {
    while (node && node->left)
      node = node->left;
    return node;
  }

  Node<T> *removeRec(Node<T> *node, const T &value)
  {
    if (!node)
      return nullptr;
    if (value < node->value)
    {
      node->left = removeRec(node->left, value);
    }
    else if (value > node->value)
    {
      node->right = removeRec(node->right, value);
    }
    else
    {
      if (!node->left && !node->right)
      {
        delete node;
        return nullptr;
      }
      else if (!node->left)
      {
        Node<T> *tmp = node->right;
        delete node;
        return tmp;
      }
      else if (!node->right)
      {
        Node<T> *tmp = node->left;
        delete node;
        return tmp;
      }
      else
      {
        Node<T> *succ = findMin(node->right);
        node->value = succ->value;
        node->right = removeRec(node->right, succ->value);
      }
    }
    return node;
  }

  Node<T> *findRec(Node<T> *node, const T &value)
  {
    if (!node)
      return nullptr;
    if (value == node->value)
      return node;
    return (value < node->value) ? findRec(node->left, value)
                                 : findRec(node->right, value);
  }

  void printInOrder(std::ostream &os, Node<T> *node) const
  {
    if (!node)
      return;
    printInOrder(os, node->left);
    os << node->value << " ";
    printInOrder(os, node->right);
  }

public:
  BinTree() = default;
  ~BinTree() { clear(root); }

  void insert(const T &value)
  {
    if (findRec(root, value) != nullptr)
    {
      throw BinTreeException(
          "Ошибка добавления: такой элемент уже существует в дереве.");
    }
    root = insertRec(root, value);
  }

  void remove(const T &value)
  {
    if (findRec(root, value) == nullptr)
    {
      throw BinTreeException("Ошибка удаления: элемент не найден в дереве.");
    }
    root = removeRec(root, value);
  }

  bool update(const T &oldValue, const T &newValue)
  {
    if (findRec(root, oldValue) == nullptr)
    {
      throw BinTreeException("Ошибка обновления: элемент не найден в дереве.");
    }

    if (oldValue == newValue)
      return false;

    if (findRec(root, newValue) != nullptr)
    {
      throw BinTreeException(
          "Ошибка обновления: новое значение уже существует в дереве.");
    }

    remove(oldValue);
    insert(newValue);
    return true;
  }
  Node<T> *getRoot() const { return root; }

  // --- InOrder Iterator ---
  class InOrderIterator
  {
    std::stack<Node<T> *> st;
    void pushLeft(Node<T> *node)
    {
      while (node)
      {
        st.push(node);
        node = node->left;
      }
    }

  public:
    InOrderIterator(Node<T> *root = nullptr) { pushLeft(root); }
    bool operator!=(const InOrderIterator &other) const
    {
      return st != other.st;
    }
    T &operator*() const { return st.top()->value; }
    InOrderIterator &operator++()
    {
      Node<T> *node = st.top();
      st.pop();
      if (node->right)
        pushLeft(node->right);
      return *this;
    }
  };

  // --- PreOrder Iterator ---
  class PreOrderIterator
  {
    std::stack<Node<T> *> st;

  public:
    PreOrderIterator(Node<T> *root = nullptr)
    {
      if (root)
        st.push(root);
    }
    bool operator!=(const PreOrderIterator &other) const
    {
      return st != other.st;
    }
    T &operator*() const { return st.top()->value; }
    PreOrderIterator &operator++()
    {
      Node<T> *node = st.top();
      st.pop();
      if (node->right)
        st.push(node->right);
      if (node->left)
        st.push(node->left);
      return *this;
    }
  };

  // --- PostOrder Iterator ---
  class PostOrderIterator
  {
    std::stack<Node<T> *> st1, st2;

  public:
    PostOrderIterator(Node<T> *root = nullptr)
    {
      if (root)
      {
        st1.push(root);
        while (!st1.empty())
        {
          Node<T> *node = st1.top();
          st1.pop();
          st2.push(node);
          if (node->left)
            st1.push(node->left);
          if (node->right)
            st1.push(node->right);
        }
      }
    }
    bool operator!=(const PostOrderIterator &other) const
    {
      return st2 != other.st2;
    }
    T &operator*() const { return st2.top()->value; }
    PostOrderIterator &operator++()
    {
      st2.pop();
      return *this;
    }
  };

  // --- LevelOrder Iterator ---
  class LevelOrderIterator
  {
    std::queue<Node<T> *> q;

  public:
    LevelOrderIterator(Node<T> *root = nullptr)
    {
      if (root)
        q.push(root);
    }
    bool operator!=(const LevelOrderIterator &other) const
    {
      return q != other.q;
    }
    T &operator*() const { return q.front()->value; }
    LevelOrderIterator &operator++()
    {
      Node<T> *node = q.front();
      q.pop();
      if (node->left)
        q.push(node->left);
      if (node->right)
        q.push(node->right);
      return *this;
    }
  };

  // --- Универсальный интерфейс ---
  template <Order O> auto begin() const
  {
    if constexpr (O == Order::InOrder)
    {
      return InOrderIterator(root);
    }
    else if constexpr (O == Order::PreOrder)
    {
      return PreOrderIterator(root);
    }
    else if constexpr (O == Order::PostOrder)
    {
      return PostOrderIterator(root);
    }
    else if constexpr (O == Order::LevelOrder)
    {
      return LevelOrderIterator(root);
    }
  }

  template <Order O> auto end() const -> decltype(begin<O>())
  {
    if constexpr (O == Order::InOrder)
    {
      return InOrderIterator(nullptr);
    }
    else if constexpr (O == Order::PreOrder)
    {
      return PreOrderIterator(nullptr);
    }
    else if constexpr (O == Order::PostOrder)
    {
      return PostOrderIterator(nullptr);
    }
    else if constexpr (O == Order::LevelOrder)
    {
      return LevelOrderIterator(nullptr);
    }
  }

  // --- Перегрузка вывода ---
  friend std::ostream &operator<<(std::ostream &os, const BinTree<T> &tree)
  {
    // Use the InOrder iterator by default for standard printing
    auto it = tree.template begin<Order::InOrder>();
    auto end_it = tree.template end<Order::InOrder>();

    // Add a check for an empty tree
    if (!(it != end_it))
    {
      return os;
    }

    // Loop through the elements
    while (it != end_it)
    {
      os << *it;
      ++it;
      // Add a space between elements, but not after the last one
      if (it != end_it)
      {
        os << " ";
      }
    }

    return os;
  }
  // --- Перегрузка ввода ---
  friend std::istream &operator>>(std::istream &is, BinTree<T> &tree)
  {
    T value;
    while (is >> value)
    {
      tree.insert(value);
    }
    return is;
  }
};
