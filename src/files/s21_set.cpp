#include "../include/s21_set.h"

namespace s21 {

// Конструктор со списком инициализации
template <typename key_type>
set<key_type>::set(const std::initializer_list<value_type> &items) {
  for (const value_type &item : items) {
    this->insert(item);
  }
}

// Оператор присваивания (копирования)
template <typename key_type>
set<key_type> &set<key_type>::operator=(const set &other) {
  if (this != &other) {
    BinaryTree<key_type, key_type>::operator=(other);
  }
  return *this;
}

// Оператор присваивания (перемещения)
template <typename key_type>
set<key_type> &set<key_type>::operator=(set &&other) noexcept {
  if (this != &other) {
    BinaryTree<key_type, key_type>::operator=(std::move(other));
  }
  return *this;
}

// Специальные методы для set
template <typename key_type>
typename set<key_type>::size_type set<key_type>::count(const key_type &key) {
  return BinaryTree<key_type, key_type>::contains(key) ? 1 : 0;
}

template <typename Key>
typename set<Key>::iterator set<Key>::lower_bound(const key_type &key) {
  Node<key_type, value_type> *current = this->root_;
  Node<key_type, value_type> *result = nullptr;

  while (current != nullptr) {
    if (current->key >= key) {
      result = current;
      current = current->left;
    } else {
      current = current->right;
    }
  }

  return result == nullptr ? this->end() : iterator(result);
}

template <typename Key>
typename set<Key>::iterator set<Key>::upper_bound(const key_type &key) {
  Node<key_type, value_type> *current = this->root_;
  Node<key_type, value_type> *result = nullptr;

  while (current != nullptr) {
    if (current->key > key) {
      result = current;
      current = current->left;
    } else {
      current = current->right;
    }
  }

  return result == nullptr ? this->end() : iterator(result);
}

template <typename key_type>
typename set<key_type>::value_type set<key_type>::extract(const key_type &key) {
  auto it = this->find(key);
  if (it != this->end()) {
    value_type val = *it;
    this->erase(it);
    return val;
  }
  throw std::out_of_range("Key not found");
}

// Реализация метода insert_many
template <typename Key>
template <typename... Args>
vector<std::pair<typename set<Key>::iterator, bool>> set<Key>::insert_many(
    Args &&...args) {
  vector<std::pair<iterator, bool>> results;
  (..., results.push_back(this->insert(std::forward<Args>(args))));
  return results;
}

}  // namespace s21