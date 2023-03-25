.23456789012345678901234567890
A1       START   1000                 
         LDA     FIVE              
         STA     ALPHA             
         LDCH    CHARZ              
         STCH    C1  
HERE     J       HERE		 
FIVE     WORD    5
ALPHA    RESW    1
CHARZ    BYTE    C'EOF'
C1       RESW    1
         END     A1