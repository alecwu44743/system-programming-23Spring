HW1SIC   START   1200
FIRST    LDA     AA
         ADD     BB
         STA     CC
         SUB     DD
         STA     EE
         MUL     AA
         STA     FF
.
         LDA     EE
         DIV     AA
         STA     GG
         MUL     THREE
         STA     HH
         LDA     ZERO
         STA     II 
         LDA     FF
         COMP    HH
         JGT     IF
.
IF       LDA     GG
         DIV     SIX 
         STA     II
HERE     J       HERE
. 
. 
AA       WORD    2
BB       WORD    7
CC       RESW    1
DD       WORD    3
EE       RESW    1
FF       RESW    1
GG       RESW    1
HH       RESW    1
II       RESW    1
THREE    WORD    3
SIX      WORD    6
ZERO     WORD    0
         END     FIRST