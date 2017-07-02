#!/bin/bash

ps | grep -v " ps$" | grep -v " grep$" > "$OUTPUT_DIR/ps_before.txt"

if ! "$TEST_GAME_SCRIPT" "$GAME_SCRIPT" "$TEST_CASE" "$OUTPUT_DIR"; then
	echo "Run failed."
	exit 1
fi

sleep 3

ps | grep -v " ps$" | grep -v " grep$" > "$OUTPUT_DIR/ps_after.txt"

if grep -F -q -x -v -f "$OUTPUT_DIR/ps_before.txt" "$OUTPUT_DIR/ps_after.txt"; then
	echo "There were some background processes left after the run. Below is the list."
	grep -F -x -v -f "$OUTPUT_DIR/ps_before.txt" "$OUTPUT_DIR/ps_after.txt"
	exit 1
fi
