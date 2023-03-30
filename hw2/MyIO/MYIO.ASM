.2345678901234567890123456789012345678901234567890
TIO      START   0
         LDX     #0
         LDS     #56				56 char			
LOOP     JSUB    RDWR
         TIXR    S
         JLT     LOOP
. AAA		 
         LDA	 #65
         STCH	 OUTD
         JSUB	 WDBYTE
         LDA	 #65
         STCH	 OUTD
         JSUB	 WDBYTE
         LDA	 #65
         STCH	 OUTD
         JSUB	 WDBYTE
.		 
		 JSUB	 RDBYTE
.
HERE     J       HERE
.
.
RDWR     STL     RETADR1
.
. Read one byte as Char into IND ; device: F1.DEV       
         JSUB    RDBYTE
         LDA     IND
         STA     OUTD
. Write one byte Char (at OUTD); device: F2.DEV          
         JSUB    WDBYTE
.
         LDL     RETADR1
         RSUB
RETADR1  RESW    1
.
.
.       Subroutine to read one byte from INPUT
.
RDBYTE   TD      INPUT
         JEQ     RDBYTE
         RD      INPUT
         STCH    IND
         RSUB
INPUT    BYTE    X'F1'
IND      RESB    1
.
.
.
WDBYTE   TD      OUTPUT
         JEQ     WDBYTE
         LDCH    OUTD
         WD      OUTPUT
         RSUB
OUTPUT   BYTE    X'F2'
OUTD     RESB    1
         END     TIO