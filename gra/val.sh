#!/bin/bash
valgrind --leak-check=full ./middle_ages < tests/test$1.in > tests/my_result_test$1.out> /dev/null
