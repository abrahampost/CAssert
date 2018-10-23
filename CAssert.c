#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "CAssert.h"

void report_success(char* test_name) {
	fprintf(stderr, "%sSUCCESS:%s %s\n", ANSI_COLOR_GREEN, ANSI_COLOR_RESET, test_name);
}

void report_error(char* test_name) {
	fprintf(stderr, "%sFAIL:%s %s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET, test_name);
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
		int result = (*func)();
		exit(result);
	} else if (pid < 0) {
		fprintf(stderr, "\nError: unable to create testing process\n\n\n");
		return 1;
	} else {
		int status;
		wait(&status);
		if (status == 0) {
			fprintf(stderr, "\n%sPassed Test%s: %s%s%s.\n\n\n", ANSI_COLOR_GREEN, ANSI_COLOR_RESET, ANSI_COLOR_YELLOW, test_name, ANSI_COLOR_RESET);
			return 0;
		} else {
			fprintf(stderr, "\n%sFailed Test%s: %s%s%s.\n\n\n", ANSI_COLOR_RED, ANSI_COLOR_RESET, ANSI_COLOR_YELLOW, test_name, ANSI_COLOR_RESET);
			return 1;
		}
	}
	//should never hit this
	return 0;
}
