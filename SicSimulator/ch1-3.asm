CH1      START   4096     
         LDA     ALPHA
         ADD     INCR
         STA     BETA
         LDA     GAMMA
         ADD     INCR
         SUB     ONE
         STA     DELTA
HERE     J       HERE
ONE      WORD    1
ALPHA    RESW    1
BETA     RESW    1
GAMMA    RESW    1
DELTA    RESW    1
INCR     RESW    1
         END     CH1