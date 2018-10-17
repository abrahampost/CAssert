#define CAssert_H
#ifndef CAssert_H
#endif

//assertion methods
int assert_int_eq(int, int, char*);
int assert_int_ineq(int, int, char*);
int assert_str_eq(char*, char*, char*);
int assert_str_ineq(char*, char*, char*);

//test runner methods
int run_tests(int(*f)(), char*);

//color definitions for printed output
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"
