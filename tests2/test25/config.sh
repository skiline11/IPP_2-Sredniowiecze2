# human vs ai, ai crashes, expected code 1
PLAYER1="HUMAN"
PLAYER2="REAL"
OVERRIDE_ARGS="-n 9 -k 2 -s 0 -p1 1,1 -p2 1,9 -ai2 `dirname ${BASH_SOURCE[0]}`/crash_ai.sh"
export GUI_ERROR_CODE=0
TIMEOUT=4
MINIMUM_DURATION=0
EXPECTED_GAME_ERROR_CODE=1
