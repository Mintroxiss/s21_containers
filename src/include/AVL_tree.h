#ifndef CPP2_S21_CONTAINERS_1_AVL_TREE_H
#define CPP2_S21_CONTAINERS_1_AVL_TREE_H

#include <iostream>
#include <limits>

#include "s21_vector.h"

namespace s21 {
template <typename Key, typename T>
struct Node {
  Key key;
  T value;
  Node *left;
  Node *right;
  Node *parent;
  int height;
  Node(Key key, T value)
      : key(key),
        value(value),
        left(nullptr),
        right(nullptr),
        parent(nullptr),
        height(1) {}
};

template <typename Key, typename T>
class BinaryTree {
 public:
  class Iterator;
  class ConstIterator;

  using key_type = Key;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  using iterator = Iterator;
  using const_iterator = ConstIterator;

 protected:
  Node<key_type, value_type> *root_;

  // Балансирует дерево
  Node<key_type, value_type> *Balance(Node<key_type, value_type> *node);

 public:
  BinaryTree();
  BinaryTree(
      std::initializer_list<std::pair<key_type, value_type>> const &items);
  BinaryTree(const key_type &key, const value_type &value);
  BinaryTree(const BinaryTree &other);
  BinaryTree(BinaryTree &&other) noexcept;
  ~BinaryTree();
  BinaryTree &operator=(BinaryTree &&other);

  std::pair<iterator, bool> insert(const value_type &value);
  std::pair<iterator, bool> insert(
      const std::pair<key_type, value_type> &value);
  iterator find(const key_type &key);
  iterator find(Node<key_type, value_type> *node, const key_type &key);

  // Проверяет, содержится ли элемент с заданным ключом в бинарном дереве
  bool contains(const key_type &key);

  // Проверяет контейнер на пустоту
  bool empty() const;

  // Возвращает кол-во узлов в дереве
  size_type size() const;

  // Возвращает максимально возможное количество элементов
  size_type max_size() const;

  // Cтирает элемент в позиции
  void erase(iterator pos);

  // Cтирает элемент в позиции
  bool erase(const key_type &key);

  // Меняет местами содержимое
  void swap(BinaryTree &other);

  // Объединяет два дерева
  void merge(BinaryTree &other);

  // Очищает содержимое
  void clear();

  // Возвращает итератор к началу
  iterator begin();

  // Возвращает итератор к концу
  iterator end();

  // Вычисление max высоты бинарного дерева
  int Height();

  // Вычисляет разницу высот левого и правого поддерева
  int BalanceFactor();

  // Реализует правое вращение узлов в дереве
  Node<key_type, value_type> *RightRotate();

  // Реализует левое вращение узлов в дереве
  Node<key_type, value_type> *LeftRotate();

  // // Балансирует дерево
  Node<key_type, value_type> *Balance();

  // Проверяет, является ли дерево сбалансированным
  bool IsBalanced();

  // Вставляет новые элементы в контейнер
  template <typename... Args>
  vector<std::pair<iterator, bool>> insert_many(Args &&...args);

  class Iterator {
   private:
    Node<key_type, value_type> *iter_node;
    Node<key_type, value_type> *iter_past_node;

   public:
    friend class BinaryTree;

    Iterator() {}
    Iterator(Node<key_type, value_type> *node,
             Node<key_type, value_type> *past_node = nullptr)
        : iter_node(node), iter_past_node(past_node) {}

    iterator operator++(int);
    iterator &operator++();
    bool operator==(const iterator &other) const;
    bool operator!=(const iterator &other) const;
    const_reference operator*();
    reference second();
  };

  class ConstIterator {
   private:
    const Node<key_type, value_type> *iter_node;
    const Node<key_type, value_type> *iter_past_node;

   public:
    friend class BinaryTree;
    ConstIterator(const Node<key_type, value_type> *node,
                  const Node<key_type, value_type> *past_node = nullptr)
        : iter_node(node), iter_past_node(past_node) {}

    const_iterator operator++(int) const;
    const_iterator &operator++() const;
    bool operator==(const const_iterator &other) const;
    bool operator!=(const const_iterator &other) const;
    reference operator*();
  };

 private:
  // Вставляет новый узел в дерево
  Node<key_type, value_type> *insert(Node<key_type, value_type> *node,
                                     const key_type &key,
                                     const value_type &value, bool &inserted);

  // Удаляет узел из дерева
  Node<key_type, value_type> *remove(Node<key_type, value_type> *node,
                                     const key_type &key);

  // Удаляет дерево
  void clear(Node<key_type, value_type> *node);

  // Объединяет два дерева
  void merge(Node<key_type, value_type> *&into,
             Node<key_type, value_type> *&from, BinaryTree &other);

  // Возвращает кол-во узлов в дереве
  size_type size(Node<key_type, value_type> *node) const;

  // Вычисление высоту бинарного дерева
  int Height(Node<key_type, value_type> *node);

  // Вычисляет разницу высот левого и правого поддерева
  int BalanceFactor(Node<key_type, value_type> *node);

  // Реализует правое вращение узлов в дереве
  Node<key_type, value_type> *RightRotate(Node<key_type, value_type> *node);

  // Реализует левое вращение узлов в дереве
  Node<key_type, value_type> *LeftRotate(Node<key_type, value_type> *node);

  // Обновляет значение высоты в узлах
  int UpdateHeight(Node<key_type, value_type> *node);

  // Проверяет, сбалансировано ли поддерево
  bool IsBalanced(Node<key_type, value_type> *node);

  // Возвращает узел с минимальным ключом
  Node<key_type, value_type> *GetMin(Node<key_type, value_type> *node);

  // Копирует дерево в текущее
  Node<key_type, value_type> *copy(Node<key_type, value_type> *other_node);

  // Возвращает ключ корневого узла
  key_type GetRootKey();

  // Возвращает ключ корневого узла левого поддерева
  key_type GetLeftChildKey();

  // Возвращает ключ корневого узла правого поддерева
  key_type GetRightChildKey();
};
}  // namespace s21

#include "../files/AVL_tree.cpp"

#endif  // CPP2_S21_CONTAINERS_1_AVL_TREE_H
