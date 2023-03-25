CH1      START   4096     
         LDX     ZERO
MOVCH    LDCH    STR1,X
         STCH    STR2,X
         TIX     ELEVEN
         JLT     MOVCH
HERE     J       HERE
STR1     BYTE    C'TEST STRING'
STR2     RESB    11
.
ZERO     WORD    0
ELEVEN   WORD    11
         END     CH1