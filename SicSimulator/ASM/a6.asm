PRO4     START   1000              PRO PROGRAM FOR SIC SOFTWARE
FOURTH   TD      INPUT
         JEQ     FOURTH
         RD      INPUT
WRITE    TD      OUTPUT
         JEQ     WRITE
         WD      OUTPUT
HERE     J       HERE
. 
. 
INPUT    BYTE    X'F3'
OUTPUT   BYTE    X'04'
         END     FOURTH