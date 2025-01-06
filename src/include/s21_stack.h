#ifndef CPP2_S21_CONTAINERS_1_STACK_H
#define CPP2_S21_CONTAINERS_1_STACK_H

#include "s21_vector.h"

namespace s21 {

template <class T, class Container = s21::vector<T>>
class stack {
 public:
  using value_type = typename Container::value_type;
  using size_type = typename Container::size_type;
  using reference = typename Container::reference;
  using const_reference = typename Container::const_reference;

  stack();
  stack(std::initializer_list<value_type> const &items);
  stack(const stack &stc);
  stack(stack &&stc);
  ~stack();
  stack &operator=(stack &&stc);

  // доступ
  const_reference top();

  // вместимость
  bool empty();
  size_type size();

  // модификаторы
  void push(const_reference value);
  void pop();
  void swap(stack &other);

  template <typename... Args>
  void insert_many_back(Args &&...args);

 private:
  Container container_;
};

}  // namespace s21

#include "../files/s21_stack.cpp"

#endif  // CPP2_S21_CONTAINERS_1_STACK_H