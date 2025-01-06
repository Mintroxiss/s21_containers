#include <gtest/gtest.h>

#include "../include/s21_stack.h"

TEST(StackTest, DefaultConstructor) {
  s21::stack<int> s;
  EXPECT_TRUE(s.empty());
}

TEST(StackTest, InitializerListConstructor) {
  s21::stack<int> s = {1, 2, 3};
  EXPECT_FALSE(s.empty());
  EXPECT_EQ(s.top(), 3);
}

TEST(StackTest, CopyConstructor) {
  s21::stack<int> original = {1, 2, 3};
  s21::stack<int> copied(original);

  EXPECT_FALSE(copied.empty());
  EXPECT_EQ(copied.top(), 3);
}

TEST(StackTest, MoveConstructor) {
  s21::stack<int> original = {1, 2, 3};
  s21::stack<int> moved(std::move(original));

  EXPECT_FALSE(moved.empty());
  EXPECT_EQ(moved.top(), 3);

  EXPECT_TRUE(original.empty());
}

TEST(StackTest, Destructor) {
  s21::stack<int> *dynamicStack = new s21::stack<int>({1, 2, 3});
  delete dynamicStack;

  // Тест пройдёт, если деструктор не вызовет исключение
}

TEST(StackTest, MoveAssignmentOperator) {
  s21::stack<int> original = {1, 2, 3};
  s21::stack<int> target;

  target = std::move(original);

  EXPECT_FALSE(target.empty());
  EXPECT_EQ(target.top(), 3);
  EXPECT_TRUE(original.empty());
}

TEST(StackTest, TopMethod) {
  s21::stack<int> s = {1, 2, 3};
  EXPECT_EQ(s.top(), 3);
}

TEST(StackTest, EmptyMethod) {
  s21::stack<int> s1;
  EXPECT_TRUE(s1.empty());

  s21::stack<int> s2 = {1, 2, 3};
  EXPECT_FALSE(s2.empty());
}

TEST(StackTest, SizeMethod) {
  s21::stack<int> s;
  EXPECT_EQ(s.size(), 0);

  s.push(1);
  EXPECT_EQ(s.size(), 1);

  s.push(2);
  EXPECT_EQ(s.size(), 2);

  s.pop();
  EXPECT_EQ(s.size(), 1);
}

TEST(StackTest, PushMethod) {
  s21::stack<int> s;
  s.push(1);
  EXPECT_EQ(s.top(), 1);

  s.push(2);
  EXPECT_EQ(s.top(), 2);
}

TEST(StackTest, PopMethod) {
  s21::stack<int> s = {1, 2, 3};
  s.pop();
  EXPECT_EQ(s.top(), 2);

  s.pop();
  EXPECT_EQ(s.top(), 1);
}

TEST(StackTest, SwapMethod) {
  s21::stack<int> s1 = {1, 2, 3};
  s21::stack<int> s2 = {4, 5, 6};

  s1.swap(s2);

  EXPECT_EQ(s1.top(), 6);
  EXPECT_EQ(s2.top(), 3);
}

TEST(StackTest, InsertManyBack) {
  s21::stack<int> my_stack;

  my_stack.push(1);
  my_stack.push(2);
  my_stack.push(3);

  my_stack.insert_many_back(4, 5, 6);

  for (int i = 6; i > 0; i--) {
    EXPECT_EQ(my_stack.top(), i);
    my_stack.pop();
  }
}

TEST(StackOperations, PushOperation) {
  s21::stack<int> stack;
  stack.push(1);
  stack.push(2);
  stack.push(3);

  EXPECT_EQ(stack.size(), 3);
  EXPECT_EQ(stack.top(), 3);
}

// Тестирование конструктора с инициализатором
TEST(StackOperations, InitializerListConstructorOperation) {
  s21::stack<int> stack = {1, 2, 3};

  EXPECT_EQ(stack.size(), 3);
  EXPECT_EQ(stack.top(), 3);
}

// Тестирование конструктора копирования
TEST(StackOperations, CopyConstructorOperation) {
  s21::stack<int> stack1 = {1, 2, 3};
  s21::stack<int> stack2(stack1);

  EXPECT_EQ(stack2.size(), 3);
  EXPECT_EQ(stack2.top(), 3);

  stack2.pop();
  EXPECT_EQ(stack2.top(), 2);
  EXPECT_EQ(stack1.top(), 3);  // убедиться, что stack1 не изменился
}

// Тестирование конструктора перемещения
TEST(StackOperations, MoveConstructorOperation) {
  s21::stack<int> stack1 = {1, 2, 3};
  s21::stack<int> stack2(std::move(stack1));

  EXPECT_EQ(stack2.size(), 3);
  EXPECT_EQ(stack2.top(), 3);
  EXPECT_EQ(stack1.size(), 0);  // убедиться, что stack1 теперь пуст
}

// Тестирование оператора присваивания перемещением
TEST(StackOperations, MoveAssignmentOperation) {
  s21::stack<int> stack1 = {1, 2, 3};
  s21::stack<int> stack2;
  stack2 = std::move(stack1);

  EXPECT_EQ(stack2.size(), 3);
  EXPECT_EQ(stack2.top(), 3);
  EXPECT_EQ(stack1.size(), 0);  // убедиться, что stack1 теперь пуст
}

// Тестирование метода pop
TEST(StackOperations, PopOperation) {
  s21::stack<int> stack = {1, 2, 3};
  stack.pop();

  EXPECT_EQ(stack.size(), 2);
  EXPECT_EQ(stack.top(), 2);

  stack.pop();
  EXPECT_EQ(stack.size(), 1);
  EXPECT_EQ(stack.top(), 1);

  stack.pop();
  EXPECT_TRUE(stack.empty());
}

// Тестирование метода swap
TEST(StackOperations, SwapOperation) {
  s21::stack<int> stack1 = {1, 2, 3};
  s21::stack<int> stack2 = {4, 5};

  stack1.swap(stack2);

  EXPECT_EQ(stack1.size(), 2);
  EXPECT_EQ(stack1.top(), 5);

  EXPECT_EQ(stack2.size(), 3);
  EXPECT_EQ(stack2.top(), 3);
}

// Тестирование метода insert_many_back
TEST(StackOperations, InsertManyBackOperation) {
  s21::stack<int> stack;
  stack.insert_many_back(1, 2, 3, 4, 5);

  EXPECT_EQ(stack.size(), 5);
  EXPECT_EQ(stack.top(), 5);
}

// Тестирование метода push после insert_many_back
TEST(StackOperations, PushAfterInsertManyBackOperation) {
  s21::stack<int> stack;
  stack.insert_many_back(1, 2, 3, 4, 5);
  stack.push(6);

  EXPECT_EQ(stack.size(), 6);
  EXPECT_EQ(stack.top(), 6);
}

// Тестирование метода pop после insert_many_back
TEST(StackOperations, PopAfterInsertManyBackOperation) {
  s21::stack<int> stack;
  stack.insert_many_back(1, 2, 3, 4, 5);
  stack.pop();

  EXPECT_EQ(stack.size(), 4);
  EXPECT_EQ(stack.top(), 4);
}
