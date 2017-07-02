#!/bin/bash

# Environment variables:
# GUI_MOCK_OUTPUT can be set to output file
# GUI_EXPECTED_INPUT must be set to expected input file
# OUTPUT_DIR must be set to output directory
# GUI_ERROR_CODE must be set to a number

if ! [ -f "$GUI_EXPECTED_INPUT" ]; then
	echo "Missing env GUI_EXPECTED_INPUT with a readable file." >&2
	exit 1
fi

if ! [ -d "$OUTPUT_DIR" ]; then
	echo "Missing env OUTPUT_DIR with a writable directory." >&2
	exit 1
fi

if ! [[ "$GUI_ERROR_CODE" =~ ^[0-9]+$ ]]; then
	echo "Missing env GUI_ERROR_CODE with a number." >&2
	exit 1
fi

echo "$@" > "$OUTPUT_DIR/gui.args"

if [[ "$GUI_MOCK_OUTPUT" != "" ]]; then
	cat $GUI_MOCK_OUTPUT &
	OUTPUT_PID=$!
fi

TURN=0

EXPECTED_LINES=`cat $GUI_EXPECTED_INPUT | wc -l`

head -n $EXPECTED_LINES > "$OUTPUT_DIR/gui.in"

# self-kill if output not read in 1 second
sleep 0.2 && kill $$ 2> /dev/null &

if [[ "$GUI_MOCK_OUTPUT" != "" ]]; then
	wait $OUTPUT_PID
fi

exit $GUI_ERROR_CODE
