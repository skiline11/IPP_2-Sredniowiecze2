#!/bin/bash

if [[ $# == 0 ]]; then
	export GAME_SCRIPT="`dirname ${BASH_SOURCE[0]}`/../wzorcowka2/game.sh"
else
	export GAME_SCRIPT="`realpath $1`/game.sh"
fi

SUCCESS=0
FAIL=0

cd "`dirname ${BASH_SOURCE[0]}`"

export TEST_GAME_SCRIPT="$PWD/test_game.sh"
export REAL_AI_PROGRAM="`dirname $GAME_SCRIPT`/middle_ages"

for TEST_CASE in test*; do
	if [[ -d "$TEST_CASE" ]]; then
		export TEST_CASE="$TEST_CASE"

		echo "---"

		export OUTPUT_DIR="`dirname $GAME_SCRIPT`/`basename $TEST_CASE`-result"
		if [[ -f "$OUTPUT_DIR" || -d "$OUTPUT_DIR" ]]; then
			echo "Output directory \"$OUTPUT_DIR\" already exists."
			exit 1
		fi
		mkdir "$OUTPUT_DIR"

		if [[ -x "$TEST_CASE/custom.sh" ]]; then
			echo "Running custom test `basename $TEST_CASE`"

			"$TEST_CASE/custom.sh"
		else
			echo "Running default test `basename $TEST_CASE`"

			"$TEST_GAME_SCRIPT" "$GAME_SCRIPT" "$TEST_CASE" "$OUTPUT_DIR"
		fi

		if [[ $? == 0 ]]; then
			echo OK
			SUCCESS=$((SUCCESS+1))
		else
			echo FAIL
			FAIL=$((FAIL+1))
		fi
	fi
done

echo "---"
echo "$SUCCESS/$((SUCCESS+FAIL)) tests succeeded."

if [[ $FAIL == 0 ]]; then
	echo "EVERYTHING OKAY - 20/20"
elif (( FAIL > 20)); then
	echo "THERE WERE $FAIL ERRORS - 0/20"
else
	echo "THERE WERE $FAIL ERRORS - $((20-FAIL))/20"
fi
