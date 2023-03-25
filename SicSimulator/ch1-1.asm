CH1      START   4096     
         LDA     FIVE
         STA     ALPHA
         LDCH    CHARZ
         STCH    C1
HERE     J       HERE
ALPHA    RESW    1
FIVE     WORD    5
CHARZ    BYTE    C'Z' 
C1       RESB    1
         END     CH1