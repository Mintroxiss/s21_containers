#ifndef CPP2_S21_CONTAINERS_1_VECTOR_H
#define CPP2_S21_CONTAINERS_1_VECTOR_H

#include <exception>
#include <iostream>
#include <limits>

namespace s21 {
template <typename T>
class vector {
 public:
  // типы
  using value_type = T;
  using size_type = std::size_t;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;

  // конструкторы
  vector();
  vector(size_type n);
  vector(std::initializer_list<value_type> const &items);
  vector(const vector &val);
  vector(vector &&val);
  ~vector();
  vector &operator=(const vector &other);
  vector &operator=(vector &&other) noexcept;

  // доступ
  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  iterator data();

  // итератор
  iterator begin();
  iterator end();

  // Вместимость
  bool empty() const;
  size_type size() const;
  size_type max_size() const;
  void reserve(size_type size);
  size_type capacity() const;
  void shrink_to_fit();

  // модификаторы

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void resize(size_type new_size);
  void swap(vector &other);

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);
  template <typename... Args>
  void insert_many_back(Args &&...args);

 private:
  value_type *elems;
  size_type a_size;
  size_type c_size;
};
}  // namespace s21

#include "../files/s21_vector.cpp"

#endif  // CPP2_S21_CONTAINERS_1_VECTOR_H