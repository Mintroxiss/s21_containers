#include <gtest/gtest.h>

#include "../include/s21_vector.h"

TEST(constructor_test, test1) {
  s21::vector<int> a;
  ASSERT_EQ(a.data(), nullptr);
  ASSERT_EQ(a.size(), 0);
  ASSERT_EQ(a.capacity(), 0);
}

TEST(constructor_test, test2) {
  s21::vector<int> a(3);
  for (std::size_t i = 0; i < a.size(); i++) {
    ASSERT_EQ(0, a[i]);
  }
  ASSERT_EQ(a.size(), 3);
  ASSERT_EQ(a.capacity(), 3);
}

TEST(constructor_test, test3) {
  s21::vector<double> a(5);
  for (std::size_t i = 0; i < a.size(); i++) {
    ASSERT_EQ(0, a[i]);
  }
  ASSERT_EQ(a.size(), 5);
  ASSERT_EQ(a.capacity(), 5);
}

TEST(constructor_test, test4) {
  s21::vector<int> a = {1, 2, 3};
  ASSERT_EQ(a.size(), 3);
  ASSERT_EQ(a.capacity(), 3);
  ASSERT_EQ(a[0], 1);
  ASSERT_EQ(a[1], 2);
  ASSERT_EQ(a[2], 3);
}

TEST(constructor_test, test5) {
  s21::vector<char> a = {'a', 'b', 'c', 'd'};
  ASSERT_EQ(a.size(), 4);
  ASSERT_EQ(a.capacity(), 4);
  ASSERT_EQ(a[0], 'a');
  ASSERT_EQ(a[1], 'b');
  ASSERT_EQ(a[2], 'c');
  ASSERT_EQ(a[3], 'd');
}

TEST(constructor_test, test6) {
  s21::vector<int> a = {123, 658678, 999};
  s21::vector<int> b(a);
  ASSERT_EQ(b.size(), a.size());
  ASSERT_EQ(b.capacity(), a.capacity());
  ASSERT_EQ(b[0], a[0]);
  ASSERT_EQ(b[1], a[1]);
  ASSERT_EQ(b[2], a[2]);
}

TEST(constructor_test, test7) {
  s21::vector<int> a = {234, 2398, 19192, 1};
  s21::vector<int> b(std::move(a));
  ASSERT_EQ(a.data(), nullptr);
  ASSERT_EQ(b.size(), 4);
  ASSERT_EQ(a.size(), 0);
  ASSERT_EQ(b.capacity(), 4);
  ASSERT_EQ(a.capacity(), 0);
  ASSERT_EQ(b[0], 234);
  ASSERT_EQ(b[1], 2398);
  ASSERT_EQ(b[2], 19192);
  ASSERT_EQ(b[3], 1);
}

TEST(constructor_test, test8) {
  s21::vector<double> a = {0.6, 0.34, 0.89};
  s21::vector<double> b = std::move(a);
  ASSERT_EQ(a.data(), nullptr);
  ASSERT_EQ(b.size(), 3);
  ASSERT_EQ(a.size(), 0);
  ASSERT_EQ(b.capacity(), 3);
  ASSERT_EQ(a.capacity(), 0);
  ASSERT_EQ(b[0], 0.6);
  ASSERT_EQ(b[1], 0.34);
  ASSERT_EQ(b[2], 0.89);
}

TEST(access_test, test1) {
  s21::vector<double> a = {0.6, 0.34, 0.89};
  ASSERT_EQ(a.at(0), 0.6);
  ASSERT_EQ(a.at(1), 0.34);
  ASSERT_EQ(a.at(2), 0.89);
  ASSERT_THROW(a.at(-1), std::out_of_range);
  ASSERT_THROW(a.at(3), std::out_of_range);
}

TEST(access_test, test2) {
  s21::vector<int> a = {99, 2, 3, 4, 5};
  ASSERT_EQ(a.front(), 99);
  ASSERT_EQ(a.back(), 5);
}

TEST(iterator_test, test1) {
  s21::vector<int> a = {99, 2, 3, 4, 5};
  int i = 0;
  for (s21::vector<int>::iterator iter = a.begin(); iter < a.end(); iter++) {
    ASSERT_EQ(*iter, a[i]);
    i++;
  }
}

TEST(capacity_test, test1) {
  s21::vector<char> a;
  s21::vector<int> b = {1, 2, 3};
  ASSERT_TRUE(a.empty());
  ASSERT_FALSE(b.empty());
}

TEST(capacity_test, test2) {
  s21::vector<char> a = {'h', 'y'};
  ASSERT_EQ(a.size(), 2);
}

TEST(capacity_test, test3) {
  s21::vector<double> a;
  ASSERT_EQ(a.max_size(), std::numeric_limits<std::size_t>::max());
}

TEST(capacity_test, test4) {
  s21::vector<int> a = {1, 2};
  ASSERT_EQ(a.capacity(), 2);
}

TEST(capacity_test, test5) {
  s21::vector<int> a(5);
  a.reserve(8);
  ASSERT_EQ(a.size(), 5);
  ASSERT_EQ(a.capacity(), 8);
}

TEST(capacity_test, test6) {
  s21::vector<int> a(5);
  a.reserve(5);
  ASSERT_EQ(a.size(), 5);
  ASSERT_EQ(a.capacity(), 5);
}

TEST(capacity_test, test7) {
  s21::vector<int> a(5);
  a.reserve(4);
  ASSERT_EQ(a.size(), 5);
  ASSERT_EQ(a.capacity(), 5);
}

TEST(capacity_test, test8) {
  s21::vector<int> a(5);
  a.shrink_to_fit();
  ASSERT_EQ(a.size(), 5);
  ASSERT_EQ(a.capacity(), 5);
}

TEST(capacity_test, test9) {
  s21::vector<int> a(5);
  a.reserve(10);
  ASSERT_EQ(a.size(), 5);
  ASSERT_EQ(a.capacity(), 10);
  a.shrink_to_fit();
  ASSERT_EQ(a.size(), 5);
  ASSERT_EQ(a.capacity(), 5);
}

TEST(modifiers_test, test1) {
  s21::vector<char> a = {'h', 'y'};
  a.clear();
  ASSERT_EQ(a.size(), 0);
  ASSERT_EQ(a.capacity(), 2);
}

TEST(modifiers_test, test2) {
  s21::vector<char> a = {'x', 'y'};
  a.push_back('z');
  ASSERT_EQ(a.size(), 3);
  ASSERT_EQ(a.capacity(), 4);
  ASSERT_EQ(a[2], 'z');
}

TEST(modifiers_test, test3) {
  s21::vector<int> a;
  a.push_back(99);
  a.push_back(88);
  a.push_back(77);
  a.push_back(66);
  ASSERT_EQ(a.size(), 4);
  ASSERT_EQ(a.capacity(), 4);
  ASSERT_EQ(a[0], 99);
  ASSERT_EQ(a[1], 88);
  ASSERT_EQ(a[2], 77);
  ASSERT_EQ(a[3], 66);
}

TEST(modifiers_test, test4) {
  s21::vector<int> a;
  a.push_back(32);
  a.push_back(76);
  a.pop_back();
  ASSERT_EQ(a.size(), 1);
  ASSERT_EQ(a.capacity(), 2);
}

TEST(modifiers_test, test5) {
  s21::vector<int> a;
  a.pop_back();
  ASSERT_EQ(a.size(), 0);
  ASSERT_EQ(a.capacity(), 0);
}

TEST(modifiers_test, test6) {
  s21::vector<int> a = {1, 2, 3, 4}, b = {6, 7}, c(a), d(b);
  a.swap(b);

  for (size_t i = 0; i < b.size(); i++) {
    ASSERT_EQ(b[i], c[i]);
  }

  for (size_t i = 0; i < a.size(); i++) {
    ASSERT_EQ(a[i], d[i]);
  }
}

TEST(modifiers_test, test7) {
  s21::vector<int> a = {1, 2, 3, 4}, b, c(a);
  a.swap(b);

  for (size_t i = 0; i < b.size(); i++) {
    ASSERT_EQ(b[i], c[i]);
  }

  ASSERT_EQ(a.size(), 0);
  ASSERT_EQ(a.capacity(), 0);
}

TEST(modifiers_test, test8) {
  s21::vector<int> a = {1, 2, 3, 4};
  auto it = a.begin() + 2;
  a.insert(it, 777);

  ASSERT_EQ(a[2], 777);

  ASSERT_EQ(a.size(), 5);
  ASSERT_EQ(a.capacity(), 8);
}

TEST(modifiers_test, test9) {
  s21::vector<int> a = {1, 2, 3, 4};
  auto it = a.begin() + 2;
  a.erase(it);

  ASSERT_EQ(a[0], 1);
  ASSERT_EQ(a[1], 2);
  ASSERT_EQ(a[2], 4);

  ASSERT_EQ(a.size(), 3);
  ASSERT_EQ(a.capacity(), 4);
}

TEST(modifiers_test, ReserveIncreaseCapacity) {
  s21::vector<int> vec = {1, 2, 3};

  // Проверяем начальную емкость
  size_t initial_capacity = vec.capacity();
  EXPECT_EQ(initial_capacity, 3);

  // Вызываем reserve для увеличения емкости
  vec.reserve(10);

  // Проверяем, что емкость увеличилась
  EXPECT_GE(vec.capacity(), 10);
  EXPECT_EQ(vec.size(), 3);

  // Проверяем, что элементы остались на своих местах
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
}

TEST(modifiers_test, ReserveNoChange) {
  s21::vector<int> vec = {1, 2, 3};

  // Проверяем начальную емкость
  size_t initial_capacity = vec.capacity();
  EXPECT_EQ(initial_capacity, 3);

  // Вызываем reserve с размером меньшим, чем текущая емкость
  vec.reserve(2);

  // Проверяем, что емкость не изменилась
  EXPECT_EQ(vec.capacity(), initial_capacity);
  EXPECT_EQ(vec.size(), 3);

  // Проверяем, что элементы остались на своих местах
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
}

// Тестирование insert_many в середину вектора
TEST(VectorBonusFunctionsTest, InsertManyMiddle) {
  s21::vector<int> s21_vec = {1, 2, 6, 7};
  std::vector<int> std_vec = {1, 2, 6, 7};

  s21_vec.insert_many(s21_vec.begin() + 2, 3, 4, 5);
  std_vec.insert(std_vec.begin() + 2, {3, 4, 5});

  EXPECT_EQ(s21_vec.size(), std_vec.size());
  for (size_t i = 0; i < s21_vec.size(); ++i) {
    EXPECT_EQ(s21_vec[i], std_vec[i]);
  }
}

// Тестирование insert_many_back с большим количеством элементов
TEST(VectorBonusFunctionsTest, InsertManyBack) {
  s21::vector<int> s21_vec = {1, 2, 3};
  std::vector<int> std_vec = {1, 2, 3};

  s21_vec.insert_many_back(4, 5, 6, 7, 8, 9, 10);
  std_vec.insert(std_vec.end(), {4, 5, 6, 7, 8, 9, 10});

  EXPECT_EQ(s21_vec.size(), std_vec.size());
  for (size_t i = 0; i < s21_vec.size(); ++i) {
    EXPECT_EQ(s21_vec[i], std_vec[i]);
  }
}

// Тестирование insert_many с перемещением большого количества элементов
TEST(VectorBonusFunctionsTest, InsertManyWithMove) {
  s21::vector<int> s21_vec;
  std::vector<int> std_vec;

  for (int i = 0; i < 1000; ++i) {
    s21_vec.push_back(i);
    std_vec.push_back(i);
  }

  s21_vec.insert_many(s21_vec.begin() + 500, -1, -2, -3);
  std_vec.insert(std_vec.begin() + 500, {-1, -2, -3});

  EXPECT_EQ(s21_vec.size(), std_vec.size());
  for (size_t i = 0; i < s21_vec.size(); ++i) {
    EXPECT_EQ(s21_vec[i], std_vec[i]);
  }
}

// Тестирование insert_many_back с перемещением большого количества элементов
TEST(VectorBonusFunctionsTest, InsertManyBackWithMove) {
  s21::vector<int> s21_vec;
  std::vector<int> std_vec;

  for (int i = 0; i < 1000; ++i) {
    s21_vec.push_back(i);
    std_vec.push_back(i);
  }

  s21_vec.insert_many_back(-1, -2, -3);
  std_vec.insert(std_vec.end(), {-1, -2, -3});

  EXPECT_EQ(s21_vec.size(), std_vec.size());
  for (size_t i = 0; i < s21_vec.size(); ++i) {
    EXPECT_EQ(s21_vec[i], std_vec[i]);
  }
}

// Тестирование insert_many в пустой вектор
TEST(VectorBonusFunctionsTest, InsertManyEmptyVector) {
  s21::vector<int> s21_vec;
  std::vector<int> std_vec;

  s21_vec.insert_many(s21_vec.begin(), 1, 2, 3);
  std_vec.insert(std_vec.begin(), {1, 2, 3});

  EXPECT_EQ(s21_vec.size(), std_vec.size());
  for (size_t i = 0; i < s21_vec.size(); ++i) {
    EXPECT_EQ(s21_vec[i], std_vec[i]);
  }
}
