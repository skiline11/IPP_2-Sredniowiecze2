#!/bin/bash

PROCESSES_BEFORE=`ps | wc -l`

if ! "$TEST_GAME_SCRIPT" "$GAME_SCRIPT" "$TEST_CASE" "$OUTPUT_DIR"; then
	echo "Run failed."
	exit 1
fi

sleep 3

PROCESSES_AFTER=`ps | wc -l`

if [[ $PROCESSES_BEFORE != $PROCESSES_AFTER ]]; then
	echo "There were $PROCESSES_BEFORE in the current shell before and there are $PROCESSES_AFTER now."
	echo "Fixing this for mocks is quite complicated though (recursive kill), so it's not required."
fi
