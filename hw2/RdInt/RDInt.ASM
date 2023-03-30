.2345678901234567890123456789012345678901234567890
TINT    START   0
. 
. Variables
DIGIT10  RESW    1		 
RETGD    RESW    1	
INPUT    BYTE    X'05'			   device 05 (05.DEV)
.	  
. READCHAR reads a char from 05.dev
. return:  Accumulator A
. 
READCHAR LDA	 #0
READLOOP TD      INPUT             TEST INPUT DEVICE
         JEQ     READLOOP          LOOP UNTIL READY 
         RD      INPUT             READ CHARACTER 
         RSUB                      RETURN TO CALLER 
.
. 
. THIS SUBROUTINE READS TWO CHARACTERs FROM THE INPUT AND COVERTS 
. IT FROM ASCII CODE TO integer VALUE. Assume: decimal system
. RETURNED IN REGISTER A
. 
GETD     STL     RETGD             SAVE RETURN ADDRESS
GETDLOOP JSUB    READCHAR          READ CHARACTER 
         SUB     #48               SUBTRACT HEX 30 FROM ASCII CODE '0'
		 MUL     #10			   *10
		 STA     DIGIT10							
         JSUB    READCHAR          READ CHARACTER 
         SUB     #48               SUBTRACT HEX 30 FROM ASCII CODE '0'
         ADD     DIGIT10               
RETURN   LDL     RETGD             RETURN TO CALLER 
         RSUB
. Read 2 characters from INPUT (05.DEV), calculate its integer value
MAIN	 JSUB    GETD			   A 2-digit number 
		 JSUB    READCHAR		   A space
		 JSUB    GETD			   A 2-digit number 
		 JSUB    READCHAR		   A space
		 JSUB    GETD			   A 2-digit number 
		 JSUB    READCHAR		   A space
		 JSUB    GETD			   A 2-digit number 
		 JSUB    READCHAR		   A space
HERE	 J       HERE
         END     MAIN
