#include "../include/AVL_tree.h"

namespace s21 {

template <typename key_type, typename value_type>
Node<key_type, value_type> *BinaryTree<key_type, value_type>::Balance(
    Node<key_type, value_type> *node) {
  if (node == nullptr) return node;
  node->left = Balance(node->left);
  node->right = Balance(node->right);
  int bf = BalanceFactor(node);
  if (bf < -1) {
    if (BalanceFactor(node->right) <= 0) {
      return LeftRotate(node);
    } else {
      node->right = RightRotate(node->right);
      return LeftRotate(node);
    }
  } else if (bf > 1) {
    if (BalanceFactor(node->left) >= 0) {
      return RightRotate(node);
    } else {
      node->left = LeftRotate(node->left);
      return RightRotate(node);
    }
  }
  return node;
}

template <typename key_type, typename value_type>
BinaryTree<key_type, value_type>::BinaryTree() : root_(nullptr) {}

template <typename key_type, typename value_type>
BinaryTree<key_type, value_type>::BinaryTree(
    std::initializer_list<std::pair<key_type, value_type>> const &items) {
  root_ = nullptr;
  for (const auto &item : items) insert(item);
}

template <typename key_type, typename value_type>
BinaryTree<key_type, value_type>::BinaryTree(const key_type &key,
                                             const value_type &value) {
  root_ = nullptr;
  bool inserted;
  root_ = insert(root_, key, value, inserted);
}

template <typename key_type, typename value_type>
BinaryTree<key_type, value_type>::BinaryTree(const BinaryTree &other) {
  if (other.root_) {
    root_ = copy(other.root_);
  } else {
    root_ = nullptr;
  }
}

template <typename key_type, typename value_type>
BinaryTree<key_type, value_type>::BinaryTree(BinaryTree &&other) noexcept {
  if (&other != this) {
    root_ = other.root_;
    other.root_ = nullptr;
  }
}

template <typename key_type, typename value_type>
BinaryTree<key_type, value_type>::~BinaryTree() {
  clear();
}

template <typename key_type, typename value_type>
BinaryTree<key_type, value_type> &BinaryTree<key_type, value_type>::operator=(
    BinaryTree &&other) {
  if (&other != this) {
    clear(root_);
    root_ = other.root_;
    other.root_ = nullptr;
  }
  return *this;
}

template <typename key_type, typename value_type>
std::pair<typename BinaryTree<key_type, value_type>::iterator, bool>
BinaryTree<key_type, value_type>::insert(const value_type &value) {
  bool inserted = false;
  root_ = insert(root_, value, value, inserted);
  return {find(value), inserted};
}

template <typename key_type, typename value_type>
std::pair<typename BinaryTree<key_type, value_type>::iterator, bool>
BinaryTree<key_type, value_type>::insert(
    const std::pair<key_type, value_type> &value) {
  bool inserted = false;
  root_ = insert(root_, value.first, value.second, inserted);
  return {find(value.first), inserted};
}

template <typename key_type, typename value_type>
typename BinaryTree<key_type, value_type>::iterator
BinaryTree<key_type, value_type>::find(const key_type &key) {
  return find(root_, key);
}

template <typename key_type, typename value_type>
typename BinaryTree<key_type, value_type>::iterator
BinaryTree<key_type, value_type>::find(Node<key_type, value_type> *node,
                                       const key_type &key) {
  if (node == nullptr) return Iterator(nullptr);
  if (key < node->key) {
    return find(node->left, key);
  } else if (key > node->key) {
    return find(node->right, key);
  } else {
    return iterator(node);
  }
}

template <typename key_type, typename value_type>
bool BinaryTree<key_type, value_type>::contains(const key_type &key) {
  iterator iter = find(key);
  return iter != iterator(nullptr);
}

template <typename key_type, typename value_type>
bool BinaryTree<key_type, value_type>::empty() const {
  return root_ == nullptr;
}

template <typename key_type, typename value_type>
typename BinaryTree<key_type, value_type>::size_type
BinaryTree<key_type, value_type>::size() const {
  return size(root_);
}

template <typename key_type, typename value_type>
typename BinaryTree<key_type, value_type>::size_type
BinaryTree<key_type, value_type>::max_size() const {
  return std::numeric_limits<size_type>::max();
}

template <typename key_type, typename value_type>
void BinaryTree<key_type, value_type>::erase(iterator pos) {
  if (pos != end()) root_ = remove(root_, pos.iter_node->key);
}

template <typename key_type, typename value_type>
bool BinaryTree<key_type, value_type>::erase(const key_type &key) {
  if (contains(key)) {
    root_ = remove(root_, key);
    return true;
  }
  return false;
}

template <typename key_type, typename value_type>
void BinaryTree<key_type, value_type>::swap(BinaryTree &other) {
  std::swap(root_, other.root_);
}

template <typename key_type, typename value_type>
void BinaryTree<key_type, value_type>::merge(BinaryTree &other) {
  merge(this->root_, other.root_, other);
}

template <typename key_type, typename value_type>
void BinaryTree<key_type, value_type>::clear() {
  clear(root_);
  root_ = nullptr;
}

template <typename key_type, typename value_type>
typename BinaryTree<key_type, value_type>::iterator
BinaryTree<key_type, value_type>::begin() {
  Node<key_type, value_type> *minNode = GetMin(root_);
  if (minNode == nullptr) {
    return this->end();
  }
  return iterator(minNode);
}

template <typename key_type, typename value_type>
typename BinaryTree<key_type, value_type>::iterator
BinaryTree<key_type, value_type>::end() {
  return iterator(nullptr);
}

template <typename key_type, typename value_type>
int BinaryTree<key_type, value_type>::Height() {
  return Height(root_);
}

template <typename key_type, typename value_type>
int BinaryTree<key_type, value_type>::BalanceFactor() {
  return BalanceFactor(root_);
}

template <typename key_type, typename value_type>
Node<key_type, value_type> *BinaryTree<key_type, value_type>::RightRotate() {
  return RightRotate(root_);
}

template <typename key_type, typename value_type>
Node<key_type, value_type> *BinaryTree<key_type, value_type>::LeftRotate() {
  return LeftRotate(root_);
}

template <typename key_type, typename value_type>
Node<key_type, value_type> *BinaryTree<key_type, value_type>::Balance() {
  return Balance(root_);
}

template <typename key_type, typename value_type>
bool BinaryTree<key_type, value_type>::IsBalanced() {
  return IsBalanced(root_);
}

template <typename key_type, typename value_type>
template <class... Args>
vector<std::pair<typename BinaryTree<key_type, value_type>::iterator, bool>>
BinaryTree<key_type, value_type>::insert_many(Args &&...args) {
  vector<std::pair<typename BinaryTree<key_type, value_type>::iterator, bool>>
      res;
  (..., res.push_back(insert(std::forward<Args>(args))));

  return res;
}

template <typename key_type, typename value_type>
typename BinaryTree<key_type, value_type>::iterator
BinaryTree<key_type, value_type>::iterator::operator++(int) {
  iterator temp = *this;
  ++(*this);
  return temp;
}

template <typename key_type, typename value_type>
typename BinaryTree<key_type, value_type>::iterator &
BinaryTree<key_type, value_type>::iterator::operator++() {
  if (iter_node == nullptr) return *this;
  if (iter_node->right != nullptr) {
    iter_node = iter_node->right;
    while (iter_node->left != nullptr) iter_node = iter_node->left;
  } else {
    Node<key_type, value_type> *parent = iter_node->parent;
    while (parent != nullptr && iter_node == parent->right) {
      iter_node = parent;
      parent = parent->parent;
    }
    iter_node = parent;
  }
  return *this;
}

template <typename key_type, typename value_type>
bool BinaryTree<key_type, value_type>::iterator::operator==(
    const iterator &other) const {
  return iter_node == other.iter_node && iter_past_node == other.iter_past_node;
}

template <typename key_type, typename value_type>
bool BinaryTree<key_type, value_type>::iterator::operator!=(
    const iterator &other) const {
  return !(*this == other);
}

template <typename key_type, typename value_type>
const value_type &BinaryTree<key_type, value_type>::iterator::operator*() {
  static value_type dummy;
  return (iter_node != nullptr) ? iter_node->value : dummy;
}

template <typename key_type, typename value_type>
value_type &BinaryTree<key_type, value_type>::iterator::second() {
  static value_type dummy;
  return (iter_node != nullptr) ? iter_node->value : dummy;
}

template <typename key_type, typename value_type>
Node<key_type, value_type> *BinaryTree<key_type, value_type>::insert(
    Node<key_type, value_type> *node, const key_type &key,
    const value_type &value, bool &inserted) {
  if (node == nullptr) {
    inserted = true;
    return new Node<key_type, value_type>(key, value);
  }
  if (key < node->key) {
    node->left = insert(node->left, key, value, inserted);
  } else if (key > node->key) {
    node->right = insert(node->right, key, value, inserted);
  } else {
    inserted = false;
  }
  return Balance(node);
}

template <typename key_type, typename value_type>
Node<key_type, value_type> *BinaryTree<key_type, value_type>::remove(
    Node<key_type, value_type> *node, const key_type &key) {
  if (node == nullptr) return node;
  if (key < node->key) {
    node->left = remove(node->left, key);
  } else if (key > node->key) {
    node->right = remove(node->right, key);
  } else {
    if (node->left == nullptr && node->right == nullptr) {
      delete node;
      return nullptr;
    } else if (node->left == nullptr) {
      Node<key_type, value_type> *temp = node->right;
      delete node;
      return temp;
    } else if (node->right == nullptr) {
      Node<key_type, value_type> *temp = node->left;
      delete node;
      return temp;
    } else {
      Node<key_type, value_type> *temp = GetMin(node->right);
      node->key = temp->key;
      node->value = temp->value;
      node->right = remove(node->right, temp->key);
    }
  }
  UpdateHeight(node);
  return Balance(node);
}

template <typename key_type, typename value_type>
void BinaryTree<key_type, value_type>::clear(Node<key_type, value_type> *node) {
  if (node) {
    clear(node->left);
    clear(node->right);
    delete node;
  }
}

template <typename key_type, typename value_type>
void BinaryTree<key_type, value_type>::merge(Node<key_type, value_type> *&into,
                                             Node<key_type, value_type> *&from,
                                             BinaryTree &other) {
  if (from == nullptr) {
    return;
  }
  if (!this->contains(from->key)) {
    bool inserted = false;
    into = insert(into, from->key, from->value, inserted);
    if (inserted) {
      Node<key_type, value_type> *left_from = from->left;
      Node<key_type, value_type> *right_from = from->right;
      merge(into, left_from, other);
      merge(into, right_from, other);
      if (other.contains(from->key)) {
        other.erase(from->key);
      }
    }
  } else {
    merge(into, from->left, other);
    merge(into, from->right, other);
  }
}

template <typename key_type, typename value_type>
typename BinaryTree<key_type, value_type>::size_type
BinaryTree<key_type, value_type>::size(Node<key_type, value_type> *node) const {
  if (node == nullptr) {
    return 0;
  } else {
    return size(node->left) + size(node->right) + 1;
  }
}

template <typename key_type, typename value_type>
int BinaryTree<key_type, value_type>::Height(Node<key_type, value_type> *node) {
  if (node == nullptr) return 0;
  return 1 + std::max(Height(node->left), Height(node->right));
}

template <typename key_type, typename value_type>
int BinaryTree<key_type, value_type>::BalanceFactor(
    Node<key_type, value_type> *node) {
  if (node == nullptr) return 0;
  return Height(node->left) - Height(node->right);
}

template <typename key_type, typename value_type>
Node<key_type, value_type> *BinaryTree<key_type, value_type>::RightRotate(
    Node<key_type, value_type> *node) {
  if (node == nullptr || node->left == nullptr) {
    return node;
  }
  Node<key_type, value_type> *left = node->left;
  Node<key_type, value_type> *left_right = left->right;

  left->right = node;
  node->left = left_right;

  return left;
}

template <typename key_type, typename value_type>
Node<key_type, value_type> *BinaryTree<key_type, value_type>::LeftRotate(
    Node<key_type, value_type> *node) {
  if (node == nullptr || node->right == nullptr) return node;
  Node<key_type, value_type> *right = node->right;
  Node<key_type, value_type> *right_left = right->left;
  right->left = node;
  node->right = right_left;
  return right;
}

template <typename key_type, typename value_type>
int BinaryTree<key_type, value_type>::UpdateHeight(
    Node<key_type, value_type> *node) {
  if (node == nullptr) return 0;
  int left_height = UpdateHeight(node->left);
  int right_height = UpdateHeight(node->right);
  node->height = 1 + std::max(left_height, right_height);
  return node->height;
}

template <typename key_type, typename value_type>
bool BinaryTree<key_type, value_type>::IsBalanced(
    Node<key_type, value_type> *node) {
  if (node == nullptr) return true;
  int left_height = Height(node->left);
  int right_height = Height(node->right);
  return abs(left_height - right_height) <= 1 && IsBalanced(node->left) &&
         IsBalanced(node->right);
}

template <typename key_type, typename value_type>
Node<key_type, value_type> *BinaryTree<key_type, value_type>::GetMin(
    Node<key_type, value_type> *node) {
  while (node && node->left) node = node->left;
  return node;
}

template <typename key_type, typename value_type>
Node<key_type, value_type> *BinaryTree<key_type, value_type>::copy(
    Node<key_type, value_type> *other_node) {
  if (other_node == nullptr) return nullptr;
  Node<key_type, value_type> *new_node =
      new Node<key_type, value_type>(other_node->key, other_node->value);
  new_node->left = copy(other_node->left);
  new_node->right = copy(other_node->right);
  return new_node;
}

template <typename key_type, typename value_type>
typename BinaryTree<key_type, value_type>::key_type
BinaryTree<key_type, value_type>::GetRootKey() {
  return root_->key;
}

template <typename key_type, typename value_type>
typename BinaryTree<key_type, value_type>::key_type
BinaryTree<key_type, value_type>::GetLeftChildKey() {
  return root_->left->key;
}

template <typename key_type, typename value_type>
typename BinaryTree<key_type, value_type>::key_type
BinaryTree<key_type, value_type>::GetRightChildKey() {
  return root_->right->key;
}

}  // namespace s21