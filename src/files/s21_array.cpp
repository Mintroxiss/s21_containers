#include "../include/s21_array.h"

namespace s21 {
// конструкторы
template <typename T, std::size_t N>
array<T, N>::array() : array_size(N) {}

template <typename T, std::size_t N>  // инициализатор
array<T, N>::array(std::initializer_list<value_type> const &items) {
  std::copy(items.begin(), items.end(), elems);
}

template <typename T, std::size_t N>
array<T, N>::array(const array &a) {
  std::copy(a.elems, a.elems + N, elems);
}

template <typename T, std::size_t N>
array<T, N>::array(array &&a) {
  std::move(a.elems, a.elems + N, elems);
}

template <typename T, std::size_t N>
array<T, N> &array<T, N>::operator=(array &&a) {
  std::move(a.elems, a.elems + N, elems);
  return *this;
}

// доступ

// access specified element with bounds checking
template <typename T, std ::size_t N>
typename array<T, N>::reference array<T, N>::at(size_type pos) {
  if (pos >= N) {
    throw std::out_of_range("Index is out of range");
  }
  return elems[pos];
}

// access specified element
template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::operator[](size_type pos) {
  return elems[pos];
}

// access the first element
template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::front() {
  return elems[0];
}

// access the last element
template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::back() {
  return elems[N - 1];
}

// direct access to the underlying contiguous storage
template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::data() {
  return elems;
}

// итераторы

// returns an iterator to the beginning
template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::begin() {
  return elems;
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::end() {
  return elems + array_size;
}

// вместимость

// checks whether the container is empty
template <typename T, std::size_t N>
bool array<T, N>::empty() const {
  return !array_size;
}

// returns the number of elements
template <typename T, std::size_t N>
typename array<T, N>::size_type array<T, N>::size() const {
  return array_size;
}

template <typename T, std::size_t N>
typename array<T, N>::size_type array<T, N>::max_size() const {
  return array_size;
}

// операции

// fill the container with specified value
template <typename T, std::size_t N>
void array<T, N>::fill(const_reference value) {
  std::fill(begin(), end(), value);
}

// swaps the contents
template <typename T, std::size_t N>
void array<T, N>::swap(array &other) {
  std::swap_ranges(begin(), end(), other.begin());
}
}  // namespace s21