WORK2    START   4096               WORK2 PROGRAM
FIRST    LDA     AA
         ADD     BB
         STA     CC
. ACC = 12 + (3) = 15; CC = 15
         SUB     BB
         STA     DD
. ACC = 15 - (3) = 12; DD = 12
         MUL     BB
         STA     FF
. ACC = 12 * (3) = 36; EE = 36
         DIV     BB
         STA     FF
. ACC = 36 / (3) = 12 ; FF = 12
HERE     J       HERE
AA       WORD    12
BB       WORD    3
CC       RESW    1
DD       RESW    1
EE       RESW    1
FF       RESW    1
         END     FIRST