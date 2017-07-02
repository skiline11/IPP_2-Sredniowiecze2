#!/bin/bash

if ! [ -f "$AI1_MOCK_OUTPUT" ]; then
	echo "Missing env AI1_MOCK_OUTPUT with a readable file." >&2
	exit 1
fi

if ! [ -f "$AI1_EXPECTED_INPUT" ]; then
	echo "Missing env AI1_EXPECTED_INPUT with a readable file." >&2
	exit 1
fi

if ! [ -d "$OUTPUT_DIR" ]; then
	echo "Missing env OUTPUT_DIR with a writable directory." >&2
	exit 1
fi

if ! [[ "$AI1_ERROR_CODE" =~ ^[0-9]+$ ]]; then
	echo "Missing env AI1_ERROR_CODE with a number." >&2
	exit 1
fi

echo "$@" > "$OUTPUT_DIR/ai1.args"

cat $AI1_MOCK_OUTPUT &

EXPECTED_LINES=`cat $AI1_EXPECTED_INPUT | wc -l`
head -n $EXPECTED_LINES > "$OUTPUT_DIR/ai1.in"

wait

exit $AI1_ERROR_CODE
