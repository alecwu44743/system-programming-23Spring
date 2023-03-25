CH1      START   4096     
         LDA     #5
         STA     ALPHA
         LDCH    #90
         STCH    C1
HERE     J       HERE
ALPHA    RESW    1
C1       RESB    1
         END     CH1