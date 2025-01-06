#include "../include/s21_list.h"

namespace s21 {
template <typename value_type>
list<value_type>::list() : head_(nullptr), tail_(nullptr), size_(0) {}

template <typename value_type>
list<value_type>::list(size_type n) : head_(nullptr), tail_(nullptr), size_(0) {
  for (size_type i = 0; i < n; ++i) push_back(value_type());
}

template <typename value_type>
list<value_type>::list(std::initializer_list<value_type> const &items)
    : head_(nullptr), tail_(nullptr), size_(0) {
  for (const auto &elem : items) push_back(elem);
}

template <typename value_type>
list<value_type>::list(const list &l)
    : head_(nullptr), tail_(nullptr), size_(0) {
  for (Node *node = l.head_; node; node = node->next) push_back(node->data);
}

template <typename value_type>
list<value_type>::list(list &&l) noexcept
    : head_(l.head_), tail_(l.tail_), size_(l.size_) {
  l.head_ = nullptr;
  l.tail_ = nullptr;
  l.size_ = 0;
}

template <typename value_type>
list<value_type>::~list() {
  Node *cur = head_;
  while (cur) {
    Node *temp = cur;
    cur = cur->next;
    delete temp;
  }
}

template <typename value_type>
list<value_type> &list<value_type>::operator=(list<value_type> &&l) noexcept {
  if (this == &l) return *this;
  clear();
  head_ = l.head_;
  tail_ = l.tail_;
  size_ = l.size_;
  l.head_ = nullptr;
  l.tail_ = nullptr;
  l.size_ = 0;
  return *this;
}

template <typename value_type>
const value_type &list<value_type>::front() const {
  if (!head_) throw std::out_of_range("list is empty");
  return head_->data;
}

template <typename value_type>
const value_type &list<value_type>::back() const {
  if (!tail_) throw std::out_of_range("list is empty");
  return tail_->data;
}

template <typename value_type>
typename list<value_type>::iterator list<value_type>::begin() {
  return iterator(head_);
}

template <typename value_type>
typename list<value_type>::iterator list<value_type>::end() {
  return iterator(nullptr);
}

template <typename value_type>
bool list<value_type>::empty() {
  return size_ == 0;
}

template <typename value_type>
size_t list<value_type>::size() {
  return size_;
}

template <typename value_type>
size_t list<value_type>::max_size() const {
  return std::numeric_limits<size_type>::max();
}

template <typename value_type>
typename list<value_type>::reference list<value_type>::at(iterator pos) {
  if (pos.get_cur() == nullptr) {
    throw std::out_of_range("Iterator points to nullptr");
  }

  return pos.get_cur()->data;
}

template <typename value_type>
void list<value_type>::clear() {
  Node *cur = tail_;
  while (cur) {
    Node *temp = cur;
    cur = cur->prev;
    delete temp;
    head_ = tail_ = nullptr;
    size_ = 0;
  }
}

template <typename value_type>
typename list<value_type>::iterator list<value_type>::insert(
    iterator pos, const_reference value) {
  Node *cur = pos.get_cur();
  if (cur == head_) {
    push_front(value);
    return iterator(head_);
  } else {
    Node *new_node = new Node(value);
    new_node->next = cur;
    new_node->prev = cur->prev;
    if (cur->prev) cur->prev->next = new_node;
    cur->prev = new_node;
    ++size_;
    return iterator(new_node);
  }
}

template <typename value_type>
void list<value_type>::erase(iterator pos) {
  if (pos.get_cur() == nullptr) return;
  Node *free_node_element = pos.get_cur();
  if (free_node_element->next) {
    free_node_element->next->prev = free_node_element->prev;
  } else {
    tail_ = free_node_element->prev;
  }
  if (free_node_element->prev) {
    free_node_element->prev->next = free_node_element->next;
  } else {
    head_ = free_node_element->next;
  }
  delete free_node_element;
  --size_;
}

template <typename value_type>
void list<value_type>::push_back(const_reference value) {
  Node *new_node = new Node(value);
  if (tail_) {
    tail_->next = new_node;
    new_node->prev = tail_;
    tail_ = new_node;
  } else {
    head_ = tail_ = new_node;
  }
  ++size_;
}

template <typename value_type>
void list<value_type>::pop_back() {
  if (!head_) return;
  Node *temp = tail_;
  if (tail_->prev) {
    tail_ = tail_->prev;
    tail_->next = nullptr;
  } else {
    head_ = tail_ = nullptr;
  }
  delete temp;
  --size_;
}

template <typename value_type>
void list<value_type>::push_front(const_reference value) {
  Node *new_node = new Node(value);
  if (head_) {
    head_->prev = new_node;
    new_node->next = head_;
    head_ = new_node;
  } else {
    head_ = tail_ = new_node;
  }
  ++size_;
}

template <typename value_type>
void list<value_type>::pop_front() {
  if (!tail_) return;
  Node *temp = head_;
  if (head_->next) {
    head_ = head_->next;
    head_->prev = nullptr;
  } else {
    head_ = tail_ = nullptr;
  }
  delete temp;
  --size_;
}

template <typename value_type>
void list<value_type>::swap(list &other) {
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
  std::swap(size_, other.size_);
}

template <typename value_type>
void list<value_type>::merge(list &other) {
  Node *first_1 = head_;
  Node *first_2 = other.head_;
  Node dummy;
  Node *last = &dummy;
  while (first_1 && first_2) {
    if (first_1->data < first_2->data) {
      last->next = first_1;
      first_1 = first_1->next;
    } else {
      last->next = first_2;
      first_2 = first_2->next;
    }
    last = last->next;
  }
  if (first_1) {
    last->next = first_1;
  } else {
    last->next = first_2;
  }
  head_ = dummy.next;
  while (last->next) {
    last = last->next;
  }
  tail_ = last;
  size_ += other.size_;
  other.head_ = other.tail_ = nullptr;
  other.size_ = 0;
}

template <typename value_type>
void list<value_type>::splice(const_iterator pos, list &other) {
  Node *cur = pos.get_cur();
  Node *other_head = other.head_;
  Node *other_tail = other.tail_;
  if (!other_head) return;
  if (!head_) {
    head_ = other_head;
    tail_ = other_tail;
  } else {
    if (cur == head_) {
      other_tail->next = head_;
      head_->prev = other_tail;
      head_ = other_head;
    } else {
      Node *prevnode = cur->prev;
      prevnode->next = other_head;
      other_head->prev = prevnode;
      other_tail->next = cur;
      cur->prev = other_tail;
    }
  }
  size_ += other.size_;
  other.head_ = nullptr;
  other.tail_ = nullptr;
  other.size_ = 0;
}

template <typename value_type>
void list<value_type>::reverse() {
  Node *cur = head_;
  Node *prev = nullptr;
  Node *next = nullptr;
  while (cur) {
    next = cur->next;
    cur->next = prev;
    cur->prev = next;
    prev = cur;
    cur = next;
  }
  std::swap(head_, tail_);
}

template <typename value_type>
void list<value_type>::unique() {
  if (!head_ || !head_->next) return;
  Node *cur = head_;
  while (cur && cur->next) {
    if (cur->data == cur->next->data) {
      Node *free_node_element = cur->next;
      cur->next = cur->next->next;

      if (cur->next) {
        cur->next->prev = cur;
      } else {
        tail_ = cur;
      }

      delete free_node_element;
      --size_;
    } else {
      cur = cur->next;
    }
  }
}

template <typename value_type>
void list<value_type>::sort() {
  if (size_ < 2) return;
  Node *cur = head_;
  while (cur) {
    Node *next = cur->next;
    while (next) {
      if (cur->data > next->data) std::swap(cur->data, next->data);
      next = next->next;
    }
    cur = cur->next;
  }
}

template <typename value_type>
void list<value_type>::remove(const_reference value) {
  Node *cur = head_;
  while (cur) {
    if (cur->data == value) {
      Node *free_node_element = cur;
      cur = cur->next;
      if (free_node_element->prev) {
        free_node_element->prev->next = free_node_element->next;
      } else {
        head_ = free_node_element->next;
      }
      if (free_node_element->next) {
        free_node_element->next->prev = free_node_element->prev;
      } else {
        tail_ = free_node_element->prev;
      }
      delete free_node_element;
      --size_;
    } else {
      cur = cur->next;
    }
  }
}

template <typename value_type>
template <typename... Args>
typename list<value_type>::iterator list<value_type>::insert_many(
    const_iterator pos, Args &&...args) {
  const size_type n = sizeof...(args);
  value_type arr[] = {std::forward<Args>(args)...};
  Node *cur_node = pos.get_cur();
  for (size_type i = 0; i < n; ++i) {
    iterator new_pos = insert(iterator(cur_node), arr[i]);
    cur_node = new_pos.get_cur()->next;
  }
  return iterator(cur_node);
}

template <typename value_type>
template <typename... Args>
void list<value_type>::insert_many_back(Args &&...args) {
  const size_type n = sizeof...(args);
  value_type arr[] = {std::forward<Args>(args)...};
  for (size_type i = 0; i < n; ++i) {
    push_back(arr[i]);
  }
}

template <typename value_type>
template <typename... Args>
void list<value_type>::insert_many_front(Args &&...args) {
  const size_type n = sizeof...(args);
  value_type arr[] = {std::forward<Args>(args)...};
  for (size_type i = n; i > 0; --i) {
    push_front(arr[i - 1]);
  }
}

}  // namespace s21