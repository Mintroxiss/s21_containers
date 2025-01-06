#include "list_tests.cpp"
#include "map_tests.cpp"
#include "queue_tests.cpp"
#include "s21_test_array.cpp"
#include "s21_test_multiset.cpp"
#include "s21_test_set.cpp"
#include "s21_test_stack.cpp"
#include "s21_test_vector.cpp"
#include "tree_tests.cpp"

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
