CH1      START   4096     
         LDA     ZERO
         STA     INDEX     
ADDLP    LDX     INDEX
         LDA     ALPHA,X
         ADD     BETA,X
         STA     GAMMA,X
         LDA     INDEX
         ADD     THREE
         STA     INDEX
         COMP    K300
         JLT     ADDLP
HERE     J       HERE
.
INDEX    RESW    1
.
ALPHA    RESW    100
BETA     RESW    100
GAMMA    RESW    100
.
ZERO     WORD    0
K300     WORD    300
THREE    WORD    3
         END     CH1