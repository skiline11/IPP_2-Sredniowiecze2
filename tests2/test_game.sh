#!/bin/bash

function error_usage {
	echo "Usage: bash test_game.sh game input_dir output_dir" >&2
	echo "game must be a an executable." >&2
	echo "input_dir must be a readable directory." >&2
	echo "output_dir must be a writable directory." >&2
	exit 1
}

if [[ $# != 3 || ! -x "$1" || ! -d "$2" || ! -d "$3" ]]; then
	error_usage
fi

GAME=`realpath $1`
INPUT_DIR=`realpath $2`

export OUTPUT_DIR=`realpath $3`

export GUI_EXPECTED_INPUT="$INPUT_DIR/gui.in"

source "$INPUT_DIR/config.sh"

cd "`dirname ${BASH_SOURCE[0]}`"

if [[ "$PLAYER1" == "MOCK" ]]; then
	AI1="-ai1 ./ai1_mock.sh"
	export AI1_MOCK_OUTPUT="$INPUT_DIR/ai1.out"
	export AI1_EXPECTED_INPUT="$INPUT_DIR/ai1.in"
elif [[ "$PLAYER1" == "REAL" ]]; then
	AI1="-ai1 $REAL_AI_PROGRAM"
fi

if [[ "$PLAYER2" == "MOCK" ]]; then
	AI2="-ai2 ./ai2_mock.sh"
	export AI2_MOCK_OUTPUT="$INPUT_DIR/ai2.out"
	export AI2_EXPECTED_INPUT="$INPUT_DIR/ai2.in"
elif [[ "$PLAYER2" == "REAL" ]]; then
	AI2="-ai2 $REAL_AI_PROGRAM"
fi

if [[ -f "$INPUT_DIR/gui.out" ]]; then
	export GUI_MOCK_OUTPUT="$INPUT_DIR/gui.out"
fi

if [[ "$N" != "" ]]; then
	N="-n $N"
fi

if [[ "$K" != "" ]]; then
	K="-k $K"
fi

if [[ "$S" != "" ]]; then
	S="-s $S"
fi

if [[ "$P1" != "" ]]; then
	P1="-p1 $P1"
fi

if [[ "$P2" != "" ]]; then
	P2="-p2 $P2"
fi

START=$SECONDS
if [[ "$OVERRIDE_ARGS" != "" ]]; then
	time timeout $TIMEOUT "$GAME" $OVERRIDE_ARGS
else
	time timeout $TIMEOUT "$GAME" $N $K $S $P1 $P2 $AI1 $AI2
fi
GAME_ERROR_CODE=$?
TIME_ELAPSED=$((SECONDS-START))

OK=1

if [[ $GAME_ERROR_CODE != $EXPECTED_GAME_ERROR_CODE ]]; then
	echo "Wrong code returned by the game ($GAME_ERROR_CODE) or timeout."
	OK=0
fi

# sorting the first two lines of GUI input, since their ordering can be arbitrary
if [[ -f "$OUTPUT_DIR/gui.in" ]]; then
	TMP_GUI_INPUT="`mktemp -u`"
	head -n 2 "$OUTPUT_DIR/gui.in" | sort > $TMP_GUI_INPUT
	tail -n +3 "$OUTPUT_DIR/gui.in" >> $TMP_GUI_INPUT
fi

if [[ "$NO_GUI_ARGS_CHECK" != "1" ]] && ! diff -B "$OUTPUT_DIR/gui.args" "$INPUT_DIR/gui.args" > /dev/null; then
	echo "GUI got incorrect arguments."
	OK=0
fi

if [[ "$NO_DIFF_CHECK" != "1" ]] && ! diff "$GUI_EXPECTED_INPUT" "$TMP_GUI_INPUT" > /dev/null; then
	echo "GUI input is incorrect."
	OK=0
fi

if [[ ("$AI1_MOCK_OUTPUT" != "" && "`cat $OUTPUT_DIR/ai1.args`" != "") ||
	("$AI2_MOCK_OUTPUT" != "" && "`cat $OUTPUT_DIR/ai2.args`" != "") ]]; then
	echo "Supplied some arguments to AIs."
	OK=0
fi

if [[ "$NO_DIFF_CHECK" != "1" && "$AI1_MOCK_OUTPUT" != "" ]] &&
	! diff "$AI1_EXPECTED_INPUT" "$OUTPUT_DIR/ai1.in" > /dev/null; then
	echo "AI1 input is incorrect."
	OK=0
fi

if [[ "$NO_DIFF_CHECK" != "1" && "$AI2_MOCK_OUTPUT" != "" ]] &&
	! diff "$AI2_EXPECTED_INPUT" "$OUTPUT_DIR/ai2.in" > /dev/null; then
	echo "AI2 input is incorrect."
	OK=0
fi

if ((TIME_ELAPSED < MINIMUM_DURATION)); then
	echo "Executing the script took less time than required."
	OK=0
fi

if [[ $OK != 1 ]]; then
	exit 1
else
	echo "Everything correct."
fi
