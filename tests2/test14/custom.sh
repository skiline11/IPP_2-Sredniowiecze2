#!/bin/bash

for ((i = 1; i <= 8; ++i)); do
	echo "Run $i ---"

	mkdir "$OUTPUT_DIR/$i"

	if "$TEST_GAME_SCRIPT" "$GAME_SCRIPT" "$TEST_CASE" "$OUTPUT_DIR/$i"; then
		head -n 2 "$OUTPUT_DIR/$i/gui.in" >> "$OUTPUT_DIR/inits.in"
		echo "Run $i succeeded."
	else
		echo "Run $i failed (error code)."
		exit 1
	fi
done

UNIQ_INITS=`cat "$OUTPUT_DIR/inits.in" | sort | uniq -u | wc -l`

# 0.3% change of fail for uniform distribution
if (( $UNIQ_INITS < 6 )); then
	echo "Got only $UNIQ_INITS unique INITs out of 16 possible in 8 games - the randomness is very bad."
	exit 1
else
	echo "Randomness is okay - got $UNIQ_INITS unique INITs out of 16 possible in 8 games."
fi
