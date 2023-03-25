PRO5P1   START   1000              PRO PROGRAM FOR SIC SOFTWARE
FIFTH    LDA     ZERO
         JSUB    READ
WRITE    TD      OUTPUT
         JEQ     WRITE
         WD      OUTPUT
HERE     J       HERE
.
ZERO     WORD    0
OUTPUT   BYTE    X'04'
.
.
READ     TD      INPUT
         JEQ     READ
         RD      INPUT
         RSUB
. 
INPUT    BYTE    X'F3'
         END     FIFTH