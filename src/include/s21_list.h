#ifndef CPP2_S21_CONTAINERS_1_S21_LIST_H
#define CPP2_S21_CONTAINERS_1_S21_LIST_H

#include <iostream>
#include <limits>

namespace s21 {
template <typename T>
class list {
 public:
  /* ___Внутриклассовые переопределения типов___ */
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;

 private:
  struct Node {
    value_type data;
    Node *prev;
    Node *next;
    Node() : data(value_type()), prev(nullptr), next(nullptr) {}
    explicit Node(const_reference data)
        : data(data), prev(nullptr), next(nullptr) {}
  };

  Node *head_;
  Node *tail_;
  size_type size_;

 public:
  /* ___Методы для взаимодействия с классом___ */

  list();
  explicit list(size_type n);
  explicit list(std::initializer_list<value_type> const &items);
  list(const list &l);
  list(list &&l) noexcept;
  ~list();
  list &operator=(list &&l) noexcept;

  template <typename value_type>
  class ListIterator {
   private:
    Node *cur;

   public:
    explicit ListIterator(Node *cur) : cur(cur) {}
    ListIterator() { cur = nullptr; }
    virtual const T &operator*() const { return cur->data; }
    virtual T &operator*() { return cur->data; }

    ListIterator &operator++() {
      if (cur) {
        cur = cur->next;
      }
      return *this;
    }

    ListIterator operator++(int) {
      ListIterator tmp = *this;
      ++(*this);
      return tmp;
    }

    ListIterator &operator--() {
      if (cur) {
        cur = cur->prev;
      }
      return *this;
    }

    ListIterator operator--(int) {
      ListIterator tmp = *this;
      --(*this);
      return tmp;
    }

    bool operator==(const ListIterator &other) const {
      return cur == other.cur;
    }

    bool operator!=(const ListIterator &other) const { return *this != other; }

    Node *get_cur() { return this->cur; }
  };

  template <typename value_type>
  class ListConstIterator : public ListIterator<T> {
   public:
    explicit ListConstIterator(ListIterator<T> other)
        : ListIterator<T>(other) {}
    const T &operator*() const override { return ListIterator<T>::operator*(); }
  };

  using iterator = ListIterator<value_type>;
  using const_iterator = ListConstIterator<value_type>;

  /* ___Методы для доступа к элементам класса___ */

  // Доступ к 1-ому элементу
  const_reference front() const;

  // Доступ к последнему элементу
  const_reference back() const;

  /* ___Методы для итерирования по элементам класса___ */

  // Возвращает итератор к началу
  iterator begin();

  // Возвращает итератор к концу
  iterator end();

  /* ___Методы для доступа к информации о наполнении контейнера___ */

  // Проверяет, пуст ли контейнер
  bool empty();

  // Возвращает количество элементов
  size_type size();

  // Возвращает максимально возможное количество элементов
  size_type max_size() const;

  // Дает доступ к элементу списка по итератору
  reference at(iterator pos);

  /* ___Методы для изменения контейнера___ */

  // Очищает содержимое
  void clear();

  // Вставляет элемент в конкретную позицию и возвращает итератор, указывающий
  // на новый элемент
  iterator insert(iterator pos, const_reference value);

  // Cтирает элемент в позиции
  void erase(iterator pos);

  // Добавляет элемент в конец
  void push_back(const_reference value);

  // Удаляет последний элемент
  void pop_back();

  // Добавляет элемент в начало
  void push_front(const_reference value);

  // Удаляет первый элемент
  void pop_front();

  // Меняет местами содержимое
  void swap(list &other);

  // Объединяет два отсортированных списка
  void merge(list &other);

  // Переносит элементы из другого списка, начиная с pos
  void splice(const_iterator pos, list &other);

  // Изменяет порядок элементов
  void reverse();

  // Удаляет последовательные дублирующиеся элементы
  void unique();

  // Сортирует элементы
  void sort();

  // Удаляет элемент
  void remove(const_reference value);

  /* ___Дополнительно___ */

  // Вставляет новые элементы в контейнер непосредственно перед pos
  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);

  // Добавляет новые элементы в конец контейнера
  template <typename... Args>
  void insert_many_back(Args &&...args);

  // Добавляет новые элементы в начало контейнераы
  template <typename... Args>
  void insert_many_front(Args &&...args);
};
}  // namespace s21

#include "../files/s21_list.cpp"

#endif  // CPP2_S21_CONTAINERS_1_S21_LIST_H
