# run with closing gui in the middle of the game, with mock ai that makes subprocesses
# some processes will have to be killed, so expected error code is 1
PLAYER1="MOCK"
PLAYER2="MOCK"
N=9
K=1000
S=1
P1=1,1
P2=1,9
export AI1_ERROR_CODE=1
export AI2_ERROR_CODE=1
export GUI_ERROR_CODE=1
TIMEOUT=5
MINIMUM_DURATION=1
EXPECTED_GAME_ERROR_CODE=1
NO_DIFF_CHECK=1
