PRO      START   1000              PRO PROGRAM FOR SIC SOFTWARE
FIRST    LDA     ONE
         ADD     TWO
         ADD     THREE
         STA     SUM
.
         COMP    FOUR
         JGT     THIS
         JEQ     THAT
         JLT     THAT
.
THIS     SUB     FOUR
.
THAT     STA     SUM
HERE     J       HERE
. 
. 
ONE      WORD    1
TWO      WORD    2
THREE    WORD    3
FOUR     WORD    4
SUM      WORD    0
         END     FIRST