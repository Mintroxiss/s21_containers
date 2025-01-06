#ifndef CPP2_S21_CONTAINERS_1_SET_H
#define CPP2_S21_CONTAINERS_1_SET_H

#include "AVL_tree.h"
#include "s21_vector.h"

namespace s21 {

template <typename Key>
class set : public BinaryTree<Key, Key> {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const Key &;
  using iterator = typename BinaryTree<Key, Key>::Iterator;
  using const_iterator = typename BinaryTree<Key, Key>::ConstIterator;
  using size_type = size_t;

  set() : BinaryTree<key_type, key_type>(){};
  set(std::initializer_list<value_type> const &items);
  set(const set &other) : BinaryTree<key_type, key_type>(other){};
  set(set &&other) noexcept
      : BinaryTree<key_type, key_type>(std::move(other)){};
  set &operator=(const set &other);
  set &operator=(set &&other) noexcept;
  ~set() = default;

  size_type count(const key_type &key);
  iterator lower_bound(const key_type &key);
  iterator upper_bound(const key_type &key);
  value_type extract(const key_type &key);

  // Объявление метода insert_many
  template <typename... Args>
  vector<std::pair<iterator, bool>> insert_many(Args &&...args);
};

}  // namespace s21

#include "../files/s21_set.cpp"

#endif  // CPP2_S21_CONTAINERS_1_SET_H