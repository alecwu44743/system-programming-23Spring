.23456789012345678901234567890
CH1B     START   4096
         LDA     FIVE
         STA     ALPHA
         LDCH    CHARZ
         STCH    C1
ALPHA    RESW    1
C1       RESB    1
FIVE     WORD    5
CHARZ    BYTE    C'Z'     
         END     CH1B