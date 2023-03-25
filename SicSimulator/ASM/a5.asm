PRO3     START   1000              PRO PROGRAM FOR SIC SOFTWARE
THIRD    LDA     ZERO
         LDX     ZERO
DO       STX     TEMP
         ADD     TEMP
         TIX     FOUR
         JLT     DO
         STA     ANS
HERE     J       HERE
. 
. 
ZERO     WORD    0
ONE      WORD    1
FOUR     WORD    4
TEMP     WORD    0
ANS      WORD    0
         END     THIRD