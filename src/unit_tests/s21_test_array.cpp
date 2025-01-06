#include <gtest/gtest.h>

#include "../include/s21_array.h"

TEST(constructor_test_array, test1) {
  s21::array<int, 5> a;
  ASSERT_EQ(a.size(), 5);
}

TEST(constructor_test_array, test2) {
  s21::array<char, 3> a = {'a', 'b', 'c'};
  ASSERT_EQ(a.size(), 3);
  ASSERT_EQ(a[0], 'a');
  ASSERT_EQ(a[1], 'b');
  ASSERT_EQ(a[2], 'c');
}

TEST(constructor_test_array, test3) {
  s21::array<int, 3> a = {4, 5, 6};
  s21::array<int, 3> b(a);
  ASSERT_EQ(b.size(), 3);
  ASSERT_EQ(a[0], b[0]);
  ASSERT_EQ(a[1], b[1]);
  ASSERT_EQ(a[2], b[2]);
}

TEST(constructor_test_array, test4) {
  s21::array<int, 3> a = {3, 2, 1};
  s21::array<int, 3> b(std::move(a));
  ASSERT_EQ(b.size(), 3);
  ASSERT_EQ(3, b[0]);
  ASSERT_EQ(2, b[1]);
  ASSERT_EQ(1, b[2]);
}

TEST(constructor_test_array, test5) {
  s21::array<int, 3> a = {3, 2, 1};
  s21::array<int, 3> b = std::move(a);
  ASSERT_EQ(b.size(), 3);
  ASSERT_EQ(3, b[0]);
  ASSERT_EQ(2, b[1]);
  ASSERT_EQ(1, b[2]);
}

TEST(access_test_array, test1) {
  s21::array<double, 3> a = {0.6, 0.34, 0.89};
  ASSERT_EQ(a.at(0), 0.6);
  ASSERT_EQ(a.at(1), 0.34);
  ASSERT_EQ(a.at(2), 0.89);
  ASSERT_THROW(a.at(-1), std::out_of_range);
  ASSERT_THROW(a.at(5), std::out_of_range);
}

TEST(access_test_array, test2) {
  s21::array<double, 3> a = {0.9, 0.8, 0.7};
  ASSERT_EQ(a.front(), a[0]);
  ASSERT_EQ(a.front(), *a.data());
  ASSERT_EQ(a.back(), a[2]);
}

TEST(iterator_test_array, test1) {
  s21::array<double, 5> a = {0.9, 0.8, 0.7, 0.6, 0.5};
  int i = 0;
  for (s21::array<double, 5>::iterator iter = a.begin(); iter < a.end();
       iter++) {
    ASSERT_EQ(*iter, a[i]);
    i++;
  }
}

TEST(iterator_test_array, test2) {
  s21::array<double, 0> a;
  ASSERT_EQ(a.begin(), a.end());
}

TEST(capacity_test_array, test1) {
  s21::array<double, 5> a;
  ASSERT_FALSE(a.empty());
}

TEST(capacity_test_array, test2) {
  s21::array<double, 0> a;
  ASSERT_TRUE(a.empty());
}

TEST(capacity_test_array, test3) {
  s21::array<double, 10> a;
  ASSERT_EQ(a.max_size(), 10);
}

TEST(modifiers_test_array, test1) {
  s21::array<int, 4> a = {1, 2, 3, 4};
  s21::array<int, 4> b = {9, 8, 7, 6};

  a.swap(b);
  ASSERT_EQ(a[0], 9);
  ASSERT_EQ(a[1], 8);
  ASSERT_EQ(a[2], 7);
  ASSERT_EQ(a[3], 6);
  ASSERT_EQ(b[0], 1);
  ASSERT_EQ(b[1], 2);
  ASSERT_EQ(b[2], 3);
  ASSERT_EQ(b[3], 4);
}

TEST(modifiers_test_array, test2) {
  s21::array<std::string, 4> a;

  a.fill("s21");
  ASSERT_EQ(a[0], "s21");
  ASSERT_EQ(a[1], "s21");
  ASSERT_EQ(a[2], "s21");
  ASSERT_EQ(a[3], "s21");
}

// Test default constructor
TEST(ArrayTest, DefaultConstructor) {
  s21::array<int, 5> arr;
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(arr[i], 0);
  }
}

// Test initializer list constructor
TEST(ArrayTest, InitializerListConstructor) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  EXPECT_EQ(arr[0], 1);
  EXPECT_EQ(arr[1], 2);
  EXPECT_EQ(arr[2], 3);
  EXPECT_EQ(arr[3], 4);
  EXPECT_EQ(arr[4], 5);
}

// Test copy constructor
TEST(ArrayTest, CopyConstructor) {
  s21::array<int, 5> arr1 = {1, 2, 3, 4, 5};
  s21::array<int, 5> arr2 = arr1;
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(arr2[i], arr1[i]);
  }
}

// Test move constructor
TEST(ArrayTest, MoveConstructor) {
  s21::array<int, 5> arr1 = {1, 2, 3, 4, 5};
  s21::array<int, 5> arr2 = std::move(arr1);
  EXPECT_EQ(arr2[0], 1);
  EXPECT_EQ(arr2[1], 2);
  EXPECT_EQ(arr2[2], 3);
  EXPECT_EQ(arr2[3], 4);
  EXPECT_EQ(arr2[4], 5);
}

// Test move assignment operator
TEST(ArrayTest, MoveAssignmentOperator) {
  s21::array<int, 5> arr1 = {1, 2, 3, 4, 5};
  s21::array<int, 5> arr2;
  arr2 = std::move(arr1);
  EXPECT_EQ(arr2[0], 1);
  EXPECT_EQ(arr2[1], 2);
  EXPECT_EQ(arr2[2], 3);
  EXPECT_EQ(arr2[3], 4);
  EXPECT_EQ(arr2[4], 5);
}

// Test at() method
TEST(ArrayTest, AtMethod) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  EXPECT_EQ(arr.at(0), 1);
  EXPECT_EQ(arr.at(1), 2);
  EXPECT_EQ(arr.at(2), 3);
  EXPECT_EQ(arr.at(3), 4);
  EXPECT_EQ(arr.at(4), 5);
  EXPECT_THROW(arr.at(5), std::out_of_range);
}

// Test operator[] method
TEST(ArrayTest, OperatorSquareBrackets) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  EXPECT_EQ(arr[0], 1);
  EXPECT_EQ(arr[1], 2);
  EXPECT_EQ(arr[2], 3);
  EXPECT_EQ(arr[3], 4);
  EXPECT_EQ(arr[4], 5);
}

// Test front() method
TEST(ArrayTest, FrontMethod) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  EXPECT_EQ(arr.front(), 1);
}

// Test back() method
TEST(ArrayTest, BackMethod) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  EXPECT_EQ(arr.back(), 5);
}

// Test data() method
TEST(ArrayTest, DataMethod) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  int* data = arr.data();
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(data[i], arr[i]);
  }
}

// Test iterators with non-const array
TEST(ArrayTest, IteratorWithNonConstArray) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  auto it = arr.begin();
  for (int i = 0; i < 5; ++i, ++it) {
    EXPECT_EQ(*it, i + 1);
  }
}

// Test end() method
TEST(ArrayTest, EndMethod) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  auto it = arr.end();
  --it;
  EXPECT_EQ(*it, 5);
}

// Test empty() method
TEST(ArrayTest, EmptyMethod) {
  s21::array<int, 5> arr;
  EXPECT_FALSE(arr.empty());
}

// Test size() method
TEST(ArrayTest, SizeMethod) {
  s21::array<int, 5> arr;
  EXPECT_EQ(arr.size(), 5);
}

// Test max_size() method
TEST(ArrayTest, MaxSizeMethod) {
  s21::array<int, 5> arr;
  EXPECT_EQ(arr.max_size(), 5);
}

// Test swap() method
TEST(ArrayTest, SwapMethod) {
  s21::array<int, 5> arr1 = {1, 2, 3, 4, 5};
  s21::array<int, 5> arr2 = {6, 7, 8, 9, 10};
  arr1.swap(arr2);
  EXPECT_EQ(arr1[0], 6);
  EXPECT_EQ(arr1[1], 7);
  EXPECT_EQ(arr1[2], 8);
  EXPECT_EQ(arr1[3], 9);
  EXPECT_EQ(arr1[4], 10);
  EXPECT_EQ(arr2[0], 1);
  EXPECT_EQ(arr2[1], 2);
  EXPECT_EQ(arr2[2], 3);
  EXPECT_EQ(arr2[3], 4);
  EXPECT_EQ(arr2[4], 5);
}

// Test fill() method
TEST(ArrayTest, FillMethod) {
  s21::array<int, 5> arr;
  arr.fill(42);
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(arr[i], 42);
  }
}

// Test iterators
TEST(ArrayTest, Iterators) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  int i = 0;
  for (auto it = arr.begin(); it != arr.end(); ++it, ++i) {
    EXPECT_EQ(*it, arr[i]);
  }
}

// Test modifying through iterators
TEST(ArrayTest, ModifyThroughIterators) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  for (auto it = arr.begin(); it != arr.end(); ++it) {
    *it *= 2;
  }
  EXPECT_EQ(arr[0], 2);
  EXPECT_EQ(arr[1], 4);
  EXPECT_EQ(arr[2], 6);
  EXPECT_EQ(arr[3], 8);
  EXPECT_EQ(arr[4], 10);
}

// Test default constructor with char type
TEST(CharArrayTest, DefaultConstructor) {
  s21::array<char, 5> arr;
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(arr[i], '\0');
  }
}

// Test initializer list constructor with char type
TEST(CharArrayTest, InitializerListConstructor) {
  s21::array<char, 5> arr = {'a', 'b', 'c', 'd', 'e'};
  EXPECT_EQ(arr[0], 'a');
  EXPECT_EQ(arr[1], 'b');
  EXPECT_EQ(arr[2], 'c');
  EXPECT_EQ(arr[3], 'd');
  EXPECT_EQ(arr[4], 'e');
}

// Test copy constructor with char type
TEST(CharArrayTest, CopyConstructor) {
  s21::array<char, 5> arr1 = {'a', 'b', 'c', 'd', 'e'};
  s21::array<char, 5> arr2 = arr1;
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(arr2[i], arr1[i]);
  }
}

// Test move constructor with char type
TEST(CharArrayTest, MoveConstructor) {
  s21::array<char, 5> arr1 = {'a', 'b', 'c', 'd', 'e'};
  s21::array<char, 5> arr2 = std::move(arr1);
  EXPECT_EQ(arr2[0], 'a');
  EXPECT_EQ(arr2[1], 'b');
  EXPECT_EQ(arr2[2], 'c');
  EXPECT_EQ(arr2[3], 'd');
  EXPECT_EQ(arr2[4], 'e');
}

// Test move assignment operator with char type
TEST(CharArrayTest, MoveAssignmentOperator) {
  s21::array<char, 5> arr1 = {'a', 'b', 'c', 'd', 'e'};
  s21::array<char, 5> arr2;
  arr2 = std::move(arr1);
  EXPECT_EQ(arr2[0], 'a');
  EXPECT_EQ(arr2[1], 'b');
  EXPECT_EQ(arr2[2], 'c');
  EXPECT_EQ(arr2[3], 'd');
  EXPECT_EQ(arr2[4], 'e');
}

// Test at() method with char type
TEST(CharArrayTest, AtMethod) {
  s21::array<char, 5> arr = {'a', 'b', 'c', 'd', 'e'};
  EXPECT_EQ(arr.at(0), 'a');
  EXPECT_EQ(arr.at(1), 'b');
  EXPECT_EQ(arr.at(2), 'c');
  EXPECT_EQ(arr.at(3), 'd');
  EXPECT_EQ(arr.at(4), 'e');
  EXPECT_THROW(arr.at(5), std::out_of_range);
}

// Test operator[] method with char type
TEST(CharArrayTest, OperatorSquareBrackets) {
  s21::array<char, 5> arr = {'a', 'b', 'c', 'd', 'e'};
  EXPECT_EQ(arr[0], 'a');
  EXPECT_EQ(arr[1], 'b');
  EXPECT_EQ(arr[2], 'c');
  EXPECT_EQ(arr[3], 'd');
  EXPECT_EQ(arr[4], 'e');
}

// Test front() method with char type
TEST(CharArrayTest, FrontMethod) {
  s21::array<char, 5> arr = {'a', 'b', 'c', 'd', 'e'};
  EXPECT_EQ(arr.front(), 'a');
}

// Test back() method with char type
TEST(CharArrayTest, BackMethod) {
  s21::array<char, 5> arr = {'a', 'b', 'c', 'd', 'e'};
  EXPECT_EQ(arr.back(), 'e');
}

// Test data() method with char type
TEST(CharArrayTest, DataMethod) {
  s21::array<char, 5> arr = {'a', 'b', 'c', 'd', 'e'};
  char* data = arr.data();
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(data[i], arr[i]);
  }
}

// Test iterators with char type
TEST(CharArrayTest, Iterators) {
  s21::array<char, 5> arr = {'a', 'b', 'c', 'd', 'e'};
  int i = 0;
  for (auto it = arr.begin(); it != arr.end(); ++it, ++i) {
    EXPECT_EQ(*it, arr[i]);
  }
}

// Test modifying through iterators with char type
TEST(CharArrayTest, ModifyThroughIterators) {
  s21::array<char, 5> arr = {'a', 'b', 'c', 'd', 'e'};
  for (auto it = arr.begin(); it != arr.end(); ++it) {
    *it = 'z';
  }
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(arr[i], 'z');
  }
}
