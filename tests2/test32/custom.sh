#!/bin/bash

cat "`dirname ${BASH_SOURCE[0]}`/ai.in" | "$REAL_AI_PROGRAM" > "$OUTPUT_DIR/ai.out"
ERROR_CODE=$?

if ! diff "`dirname ${BASH_SOURCE[0]}`/ai.out" "$OUTPUT_DIR/ai.out" > /dev/null; then
	echo "Wyjście AI studenta posiada inne wiadomości niż END_TURN lub posiada ich złą ilość"
	exit 1
elif [[ $ERROR_CODE != 2 ]]; then
	echo "AI kończy się niepoprawnym kodem błędu ($ERROR_CODE zamiast 2)."
fi
