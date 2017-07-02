#!/bin/bash
if [ "$1" == "-v" ]
then
	for test in tests/*.in
	do
		first_part=${test%.*}
		first_part=${first_part#*/}
		echo "Test : " $first_part
		valgrind --leak-check=full ./middle_ages < tests/$first_part.in > /dev/null
	done
else
	for test in tests/*.in
	do
		first_part=${test%.*}
		first_part=${first_part#*/}
		./middle_ages < tests/$first_part.in > tests/my_result_$first_part.out 2> tests/my_result_$first_part.err
		if [ "$(diff tests/$first_part.out tests/my_result_$first_part.out)" != "" ]
			then echo "Your standard output on test: $first_part is uncorrect"
		else
			echo "Correct output on test: $first_part"
		fi
		if [ "$(diff tests/$first_part.err tests/my_result_$first_part.err)" != "" ]
			then echo "Your diagnostic error output on test: $first_part is uncorrect"
		else
			echo "Correct diagnostic error output on test: $first_part"
		fi
	done
fi
