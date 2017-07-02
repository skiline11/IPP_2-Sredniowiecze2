# invalid -ai1 and -ai2
PLAYER1="REAL"
PLAYER2="REAL"
OVERRIDE_ARGS="-k 1 -a1 `dirname ${BASH_SOURCE[0]}`/garbage.sh -ai2 /i/will/be/really/surprised/if/this/file/exists"
export GUI_ERROR_CODE=0
MINIMUM_DURATION=0
TIMEOUT=4
EXPECTED_GAME_ERROR_CODE=1
NO_GUI_ARGS_CHECK=1
NO_DIFF_CHECK=1
