#include "../include/s21_vector.h"

namespace s21 {

/* Конструкторы */

template <typename T>
vector<T>::vector() : elems(nullptr), a_size(0), c_size(0) {}

template <typename T>
vector<T>::vector(size_type n)
    : elems(new value_type[n]), a_size(n), c_size(n) {
  for (std::size_t i = 0; i < a_size; ++i) {
    elems[i] = T();
  }
}

template <typename T>
vector<T>::vector(std::initializer_list<value_type> const &items)
    : elems(new value_type[items.size()]),
      a_size(items.size()),
      c_size(items.size()) {
  std::copy(items.begin(), items.end(), elems);
}

template <typename T>
vector<T>::vector(const vector &val)
    : elems(new value_type[val.c_size]),
      a_size(val.a_size),
      c_size(val.c_size) {
  std::copy(val.elems, val.elems + val.a_size, elems);
}

template <typename T>
vector<T>::vector(vector &&val)
    : elems(val.elems), a_size(val.a_size), c_size(val.c_size) {
  val.elems = nullptr;
  val.a_size = 0;
  val.c_size = 0;
}

template <typename T>
vector<T>::~vector() {
  delete[] elems;
  a_size = 0;
  c_size = 0;
  elems = nullptr;
}

template <typename T>
vector<T> &vector<T>::operator=(const vector &val) {
  if (this != &val) {
    delete[] elems;
    a_size = val.a_size;
    c_size = val.c_size;
    elems = new value_type[c_size];
    std::copy(val.elems, val.elems + a_size, elems);
  }
  return *this;
}

template <typename T>
vector<T> &vector<T>::operator=(vector &&val) noexcept {
  if (this != &val) {
    delete[] elems;
    elems = val.elems;
    a_size = val.a_size;
    c_size = val.c_size;

    val.elems = nullptr;
    val.a_size = 0;
    val.c_size = 0;
  }
  return *this;
}

/* Доступ */

// access specified element with bounds checking
template <typename T>
typename vector<T>::reference vector<T>::at(size_type pos) {
  if (/*pos < 0 ||*/ pos >= a_size) {
    throw std::out_of_range("Index is out of range");
  }
  return *(elems + pos);
}

// access specified element
template <typename T>
typename vector<T>::reference vector<T>::operator[](size_type pos) {
  return *(elems + pos);
}

// access the first element
template <typename T>
typename vector<T>::const_reference vector<T>::front() {
  return elems[0];
}

// access the last element
template <typename T>
typename vector<T>::const_reference vector<T>::back() {
  return elems[a_size - 1];
}

// direct access to the underlying contiguous storage
template <typename T>
typename vector<T>::iterator vector<T>::data() {
  return elems;
}

/* Итератор */

// returns an iterator to the beginning
template <typename T>
typename vector<T>::iterator vector<T>::begin() {
  return elems;
}

// returns an iterator to the end
template <typename T>
typename vector<T>::iterator vector<T>::end() {
  return elems + a_size;
}

/* Capacity */

// checks whether the container is empty
template <typename T>
bool vector<T>::empty() const {
  return !a_size;
}

// returns the number of elements
template <typename T>
typename vector<T>::size_type vector<T>::size() const {
  return a_size;
}

// returns the maximum possible number of elements
template <typename T>
typename vector<T>::size_type vector<T>::max_size() const {
  return std::numeric_limits<size_type>::max();
}

// reserves storage
template <typename T>
void vector<T>::reserve(size_type size) {
  if (size > max_size()) {
    throw std::length_error("Capacity cannot be greater than maximum size");
  }
  if (size > c_size) {
    value_type *new_elems = new value_type[size];
    for (std::size_t i = 0; i < a_size; i++) {
      new_elems[i] = elems[i];
    }

    delete[] elems;
    elems = new_elems;
    c_size = size;
  }
}

// returns the number of elements that can be held in currently allocated
// storage
template <typename T>
typename vector<T>::size_type vector<T>::capacity() const {
  return c_size;
}

// reduces memory usage by freeing unused memory
template <typename T>
void vector<T>::shrink_to_fit() {
  if (c_size > a_size) {
    value_type *new_elems = new value_type[a_size];
    for (std::size_t i = 0; i < a_size; i++) {
      new_elems[i] = elems[i];
    }
    delete[] elems;
    elems = new_elems;
    c_size = a_size;
  }
}

/* Модификаторы */

// clears the contents
template <typename T>
void vector<T>::clear() {
  delete[] elems;
  elems = new value_type[c_size];
  a_size = 0;
}

// inserts elements
template <typename T>
typename vector<T>::iterator vector<T>::insert(iterator pos,
                                               const_reference value) {
  size_type index = pos - begin();

  if (a_size >= c_size) {
    reserve(c_size == 0 ? 1 : c_size * 2);
  }

  iterator new_pos = begin() + index;
  for (iterator it = end(); it != new_pos; --it) {
    *it = *(it - 1);
  }

  *new_pos = value;
  ++a_size;
  return new_pos;
}

// erases elements
template <typename T>
void vector<T>::erase(iterator pos) {
  size_type index = pos - begin();
  iterator new_pos = begin() + index;
  for (iterator it = new_pos; it != end() - 1; ++it) {
    *it = *(it + 1);
  }
  --a_size;
}

// adds an element to the end
template <typename T>
void vector<T>::push_back(const_reference value) {
  if (a_size >= c_size) {
    reserve(c_size == 0 ? 1 : c_size * 2);
  }
  elems[a_size] = value;
  a_size++;
}

// removes the last element
template <typename T>
void vector<T>::pop_back() {
  if (a_size > 0) {
    --a_size;
    elems[a_size]
        .~T();  // Вызов деструктора для уничтожения последнего элемента
  }
}

// changes the number of elements stored
template <typename T>
void vector<T>::resize(size_type new_size) {
  if (new_size > c_size) {
    reserve(new_size);
  }
  if (new_size > a_size) {
    for (size_type i = a_size; i < new_size; ++i) {
      elems[i] = T();
    }
  } else {
    // Если новый размер меньше текущего, вызываем деструктор для "удаляемых"
    // элементов
    for (size_type i = new_size; i < a_size; ++i) {
      elems[i].~T();
    }
  }
  a_size = new_size;
}

template <typename T>
void vector<T>::swap(vector &other) {
  std::swap(elems, other.elems);
  std::swap(a_size, other.a_size);
  std::swap(c_size, other.c_size);
}

/* Бонус */

//вставить ПАК элементов перед индексом
template <typename T>
template <typename... Args>
typename vector<T>::iterator vector<T>::insert_many(const_iterator pos,
                                                    Args &&...args) {
  size_type index = pos - begin();
  size_type num_new_elements = sizeof...(args);

  if (a_size + num_new_elements > c_size) {
    reserve(a_size + num_new_elements);
  }

  iterator new_pos = begin() + index;
  vector<value_type> temp = {args...};

  for (size_type i = 0; i < temp.size(); ++i) {
    new_pos = insert(new_pos, temp[i]);
    ++new_pos;
  }

  return new_pos;
}

// Вставка элементов в конец
template <typename T>
template <typename... Args>
void vector<T>::insert_many_back(Args &&...args) {
  size_type num_new_elements = sizeof...(args);

  // Проверка и резервирование емкости
  if (a_size + num_new_elements > c_size) {
    reserve(a_size + num_new_elements);
  }

  // Вставка элементов в конец
  (insert(end(), std::forward<Args>(args)), ...);
}

}  // namespace s21