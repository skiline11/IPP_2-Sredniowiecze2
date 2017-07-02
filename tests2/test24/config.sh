# ai1 writing invalid message, which is relayed to ai2 and everything ends in code 1
PLAYER1="MOCK"
PLAYER2="MOCK"
N=9
K=1
S=1
P1=1,1
P2=1,9
export AI1_ERROR_CODE=1
export AI2_ERROR_CODE=42
export GUI_ERROR_CODE=0
TIMEOUT=4
MINIMUM_DURATION=0
EXPECTED_GAME_ERROR_CODE=1
