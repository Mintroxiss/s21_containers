#ifndef CPP2_S21_CONTAINERS_1_S21_QUEUE_H
#define CPP2_S21_CONTAINERS_1_S21_QUEUE_H

#include <iostream>

#include "s21_list.h"

namespace s21 {
template <typename T, typename Container = s21::list<T>>
class queue {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

 private:
  Container container_;

 public:
  /* ___Методы для взаимодействия с классом___ */

  queue();
  queue(std::initializer_list<value_type> const &items);
  queue(const queue &q);
  queue(queue &&q);
  ~queue();
  queue &operator=(queue &&q);

  /* ___Методы для доступа к элементам класса___ */

  // Доступ к первому элементу
  const_reference front();

  // Доступ к последнему элементу
  const_reference back();

  /* ___Методы для доступа к информации о наполнении контейнера___ */

  // Проверяет контейнер на пустоту
  bool empty();

  // Возвращает количество элементов
  size_type size();

  /* ___Методы для изменения контейнера___ */

  // Добавляет элемент в конец
  void push(const_reference value);

  // Возвращает последний элемент
  void pop();

  // Меняет элементы в очередях местами
  void swap(queue &other);

  /* ___Дополнительно___ */

  // Добавляет новые элементы в конец контейнера
  template <typename... Args>
  void insert_many_back(Args &&...args);
};
}  // namespace s21

#include "../files/s21_queue.cpp"

#endif  // CPP2_S21_CONTAINERS_1_S21_QUEUE_H
