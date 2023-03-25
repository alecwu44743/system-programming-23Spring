CH1      START   4096     
         LDS     #3
         LDT     #300
         LDX     #0
ADDLP    LDA     ALPHA,X
         ADD     BETA,X
         STA     GAMMA,X
         ADDR    S,X
         COMPR   X,T
         JLT     ADDLP
HERE     J       HERE
.
ALPHA    RESW    100
BETA     RESW    100
GAMMA    RESW    100
.
         END     CH1