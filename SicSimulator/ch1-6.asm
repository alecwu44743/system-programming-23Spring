CH1      START   4096     
         LDT     #11
         LDX     #0
MOVCH    LDCH    STR1,X
         STCH    STR2,X
         TIXR    T
         JLT     MOVCH
HERE     J       HERE
STR1     BYTE    C'TEST STRING'
STR2     RESB    11
.
         END     CH1