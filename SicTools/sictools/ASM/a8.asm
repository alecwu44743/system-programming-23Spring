PRO5P2   START   1000              PRO PROGRAM FOR SIC SOFTWARE
FIFTH    LDA     ZERO
         JSUB    READ
WRITE    TD      OUTPUT
         JEQ     WRITE
         WD      OUTPUT
HERE     J       HERE
.
READ     TD      INPUT
         JEQ     READ
         RD      INPUT
         RSUB
. 
. 
ZERO     WORD    0
INPUT    BYTE    X'F3'
OUTPUT   BYTE    X'04'
         END     FIFTH