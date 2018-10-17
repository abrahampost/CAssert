#include <signal.h>

#include "../CAssert.h"

int int_tests() {
  int errors = 0;
  errors += assert_int_eq(1,1, "Happy int");
  errors += assert_int_eq(1,2, "Unhappy int");
  errors += assert_int_ineq(1,2, "Happy unequal int");
  errors += assert_int_ineq(1,1, "Unhappy unequal int");
  assert_int_eq(errors, 2, "Correct number of errors");
  return 0;
}

int string_tests() {
  int errors = 0;
  errors += assert_str_eq("Wow", "Wow", "Happy_str");
  errors += assert_str_eq("Wow", "Wowzers", "Unhappy_str");
  errors += assert_str_ineq("Wow", "Wowzers", "Happy unequal str");
  errors += assert_str_ineq("Wow", "Wow", "Unhappy unequal str");
  assert_int_eq(errors, 2, "Correct number of errors");
  return 0;
}

int segfault_test() {
  raise(SIGSEGV);
  return 0;
}

int main() {
  run_tests(int_tests, "Int Equality Tests");
  run_tests(segfault_test, "Segfault test (should fail)");
  run_tests(string_tests, "String Equality Tests");
}
