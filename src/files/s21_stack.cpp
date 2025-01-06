#include "../include/s21_stack.h"

namespace s21 {

/* Конструкторы */

template <class T, class Container>
stack<T, Container>::stack() : container_() {}

template <class T, class Container>
stack<T, Container>::stack(std::initializer_list<value_type> const &items)
    : container_(items) {}

template <class T, class Container>
stack<T, Container>::stack(const stack &stc) : container_(stc.container_) {}

template <class T, class Container>
stack<T, Container>::stack(stack &&stc)
    : container_(std::move(stc.container_)) {}

template <class T, class Container>
stack<T, Container>::~stack() {}

template <class T, class Container>
stack<T, Container> &stack<T, Container>::operator=(stack &&stc) {
  this->container_ = std::move(stc.container_);
  return *this;
}

/* Доступ */

template <class T, class Container>
typename stack<T, Container>::const_reference stack<T, Container>::top() {
  return container_.back();
}

/* Вместимость */

template <class T, class Container>
bool stack<T, Container>::empty() {
  return container_.empty();
}

template <class T, class Container>
typename stack<T, Container>::size_type stack<T, Container>::size() {
  return container_.size();
}

/* Модификаторы */

template <class T, class Container>
void stack<T, Container>::push(const_reference value) {
  container_.push_back(value);
}

template <class T, class Container>
void stack<T, Container>::pop() {
  container_.pop_back();
}

template <class T, class Container>
void stack<T, Container>::swap(stack &other) {
  container_.swap(other.container_);
}

template <typename T, typename Container>
template <typename... Args>
void stack<T, Container>::insert_many_back(Args &&...args) {
  container_.insert_many_back(std::forward<Args>(args)...);
}

}  // namespace s21