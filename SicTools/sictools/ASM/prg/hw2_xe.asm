HW2      START   1000
FIRST    JSUB    RINT
         STA     NUM1
         JSUB    RINT
         STA     NUM2
ODDEVEN  LDA     NUM1
         AND     #1
         COMP    #1
         JEQ     ODD
         LDT     #2
         J       INITL
ODD      LDT     #3                 T: addi
INITL    STT     ADDI               for(i=num1;i<=num2;i+=addi)
         LDS     #0                 S: sum = 0
         LDA     NUM1
         STA     ADDN               A: addn(i)
LOOP     COMP    NUM2
         JGT     EXIT
         ADDR    A,S                (S)sum  += (A)addn;
         ADDR    T,A                (A)addn += (T)addi; 
         J       LOOP
.
EXIT     STA     ADDN
         STS     SUM
         J       EXIT
.
RINT     TD      INDEV
         JEQ     RINT
         LDA     #0
         RD      INDEV
         RSUB
.  
INDEV    BYTE    X'F3'
.
NUM1     RESW    1
NUM2     RESW    1
ADDN     RESW    1
SUM      RESW    1
ADDI     RESW    1
.
         END     HW2