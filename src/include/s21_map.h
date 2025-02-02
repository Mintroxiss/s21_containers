#ifndef CPP2_S21_CONTAINERS_1_S21_MAP_H
#define CPP2_S21_CONTAINERS_1_S21_MAP_H

#include "AVL_tree.h"

namespace s21 {
template <typename Key, typename T>
class map : public BinaryTree<Key, T> {
 public:
  /* ___Внутриклассовые переопределения типов___ */

  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename BinaryTree<Key, T>::Iterator;
  using const_iterator = typename BinaryTree<Key, T>::ConstIterator;
  using size_type = size_t;

  /* ___Методы для взаимодействия с классом___ */

  map() : BinaryTree<key_type, mapped_type>(){};
  map(std::initializer_list<value_type> const &items);
  map(const map &other) : BinaryTree<key_type, mapped_type>(other){};
  map(map &&other) noexcept : BinaryTree<key_type, T>(std::move(other)){};
  ~map() = default;

  /* ___Методы для доступа к элементам класса___ */

  // Дает доступ к указанному элементу с проверкой границ
  mapped_type &at(const key_type &key);

  // Дает доступ или вставляет указанный элемент
  mapped_type &operator[](const key_type &key);

  /* ___Методы для изменения контейнера___ */

  // Вставляет элемент или присваивает текущему элементу, если ключ уже
  // существует
  std::pair<iterator, bool> insert_or_assign(const key_type &key,
                                             const mapped_type &obj);
};

}  // namespace s21

#include "../files/s21_map.cpp"

#endif  // CPP2_S21_CONTAINERS_1_S21_MAP_H
