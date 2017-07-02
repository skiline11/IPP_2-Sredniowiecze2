# ai vs ai, test with -s 3 if game takes 14-20 seconds (6 END_TURNs with 3 seconds in-between)
PLAYER1="MOCK"
PLAYER2="MOCK"
N=9
K=3
S=3
P1=1,1
P2=1,9
TIMEOUT=20
MINIMUM_DURATION=14
EXPECTED_GAME_ERROR_CODE=0
export GUI_ERROR_CODE=0
export AI1_ERROR_CODE=1
export AI2_ERROR_CODE=1
