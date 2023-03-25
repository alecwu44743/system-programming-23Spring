CH1      START   4096     
         LDS     INCR
         LDA     ALPHA
         ADDR    S,A
         SUB     #1
         STA     BETA
         LDA     GAMMA
         ADDR    S,A
         SUB     #1
         STA     DELTA
HERE     J       HERE
ALPHA    RESW    1
BETA     RESW    1
GAMMA    RESW    1
DELTA    RESW    1
INCR     RESW    1
         END     CH1