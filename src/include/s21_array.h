#ifndef CPP2_S21_CONTAINERS_1_ARRAY_H
#define CPP2_S21_CONTAINERS_1_ARRAY_H

#include <exception>
#include <iostream>
#include <limits>

namespace s21 {
template <typename T, std::size_t N>
class array {
 public:
  /// типы
  using value_type = T;
  using size_type = std::size_t;
  using reference = T &;
  using const_reference = const T &;
  using const_iterator = const T *;
  using iterator = T *;

  /// конструкторы
  array();                                                // умолчанию
  array(std::initializer_list<value_type> const &items);  // инициализатор
  array(const array &a);        // копирование
  array(array &&a);             // перенос
  ~array() = default;           // деструктор
  array &operator=(array &&a);  // присваивания перемещения

  // доступ
  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  iterator data();

  // итератор
  iterator begin();
  iterator end();

  // вместимость
  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  // операции
  void fill(const_reference value);
  void swap(array &other);

 private:
  value_type elems[N] = {};  // массив
  size_type array_size = N;  // размер
};

}  // namespace s21

#include "../files/s21_array.cpp"

#endif  // CPP2_S21_CONTAINERS_1_ARRAY_H