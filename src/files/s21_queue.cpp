#include "../include/s21_queue.h"

namespace s21 {
template <typename value_type, typename Container>
queue<value_type, Container>::queue() : container_() {}

template <typename value_type, typename Container>
queue<value_type, Container>::queue(
    std::initializer_list<value_type> const &items)
    : container_(items) {}

template <typename value_type, typename Container>
queue<value_type, Container>::queue(const queue &q)
    : container_(q.container_) {}

template <typename value_type, typename Container>
queue<value_type, Container>::queue(queue &&q)
    : container_(std::move(q.container_)) {}

template <typename value_type, typename Container>
queue<value_type, Container>::~queue() {}

template <typename value_type, typename Container>
queue<value_type, Container> &queue<value_type, Container>::operator=(
    queue &&q) {
  if (this != &q) this->container_ = std::move(q.container_);
  return *this;
}

template <typename value_type, typename Container>
typename queue<value_type, Container>::const_reference
queue<value_type, Container>::front() {
  return container_.front();
}

template <typename value_type, typename Container>
typename queue<value_type, Container>::const_reference
queue<value_type, Container>::back() {
  return container_.back();
}

template <typename value_type, typename Container>
bool queue<value_type, Container>::empty() {
  return container_.empty();
}

template <typename value_type, typename Container>
typename queue<value_type, Container>::size_type
queue<value_type, Container>::size() {
  return container_.size();
}

template <typename value_type, typename Container>
void queue<value_type, Container>::push(const_reference value) {
  return container_.push_back(value);
}

template <typename value_type, typename Container>
void queue<value_type, Container>::pop() {
  return container_.pop_front();
}

template <typename value_type, typename Container>
void queue<value_type, Container>::swap(queue &other) {
  container_.swap(other.container_);
}

template <typename value_type, typename Container>
template <typename... Args>
void queue<value_type, Container>::insert_many_back(Args &&...args) {
  container_.insert_many_back(std::forward<Args>(args)...);
}

}  // namespace s21
