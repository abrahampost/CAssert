#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void report_success(char* test_name) {
	fprintf(stderr, "SUCCESS: %s\n", test_name);
}

void report_error(char* test_name) {
	fprintf(stderr, "FAIL: %s\n", test_name);
}

int assert_int_eq(int one, int two, char* test_name) {
	if (one == two) {
		report_success(test_name);
		return 0;
	} else {
		report_error(test_name);
		return 1;
	}
}

int assert_int_ineq(int one, int two, char* test_name) {
	if (one != two) {
		report_success(test_name);
		return 0;
	} else {
		report_error(test_name);
		return 1;
	}
}

int assert_str_eq(char* one, char* two, char* test_name) {
	if (strcmp(one, two) == 0) {
		report_success(test_name);
		return 0;
	} else {
		report_error(test_name);
		return 1;
	}
}

int assert_str_ineq(char* one, char* two, char* test_name) {
	if (strcmp(one, two) != 0) {
		report_success(test_name);
		return 0;
	} else {
		report_error(test_name);
		return 1;
	}
}

int run_tests(int(*func)(), char* test_name) {
	int pid = fork();
	if (pid == 0) {
		(*func)();
		exit(0);
	} else if (pid < 0) {
		fprintf(stderr, "Error: unable to create testing process\n");
		return 1;
	} else {
		int status;
		wait(&status);
		if (status == 0) {
			fprintf(stderr, "Successfully completed: %s.\n\n\n", test_name);
			return 0;
		} else {
			fprintf(stderr, "Error: unable to complete %s.\n\n\n", test_name);
			return 1;
		}
	}
	//should never hit this
	return 0;
}

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
