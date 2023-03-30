INPUT   BYTE    X'05'
CURR	RESW	1
NU 	RESW 	8

.read character function
READCHAR LDA	#0
READLOOP TD     INPUT             TEST INPUT DEVICE
        JEQ     READLOOP          LOOP UNTIL READY 
        RD      INPUT             READ CHARACTER 
        RSUB                      RETURN TO CALLER 

.get two-digits number function
GETD    STL     RETGD   .save return address
GETDLOOP JSUB   READCHAR.read character
        SUB     #48     .subtract hex 0 from ascii code '0'   
	MUL     #10	.multiply 10	for two-digit
	STA     DIGIT10							
        JSUB    READCHAR.read character
        SUB     #48	.subtract hex 0 from ascii code '0'
        ADD     DIGIT10           
	LDL     RETGD	.set L to return address
        RSUB
RETGD   RESW    1
DIGIT10 RESW    1		 

.Write into the 06.DEV
WDBYTE  TD      OUTPUT
        JEQ     WDBYTE
	STA	CURR
        LDCH    OUTD
        WD      OUTPUT
        RSUB
OUTPUT  BYTE    X'06'
OUTD    RESB    1

.if is odd ,the amounts of odd plus 1
ISODD	LDA	ODDSUM
	ADD	#1
	STA	ODDSUM
	RSUB
ODDSUM	RESW	1
.if is even , the amounts of even plus 1
ISEVN	LDA	EVNSUM
	ADD	#1
	STA	EVNSUM
	RSUB
EVNSUM	RESW	1

.check the odd and even, count their amounts
ODDORDEVN STL   RETGD .save return address
	LDX	#0
CLOOP	LDA	NU,X
	AND	#1 
	COMP	#0
	JEQ	TOEVN
	JSUB	ISODD
	J	NEXT1
TOEVN	JSUB	ISEVN
NEXT1	TIXR	X .X+1
	TIXR	X .X+1
	TIX	#24 .X+1 and compare to 24
	JLT	CLOOP
	LDL	RETGD
	RSUB

.array sum function
SUMARRAY STL	RETGD
	LDX	#0
SUMLOOP	LDA	NU,X
	ADD	ODDARRAY
	STA	ODDARRAY
	TIXR	X	 .X+1 
	TIXR	X	 .X+1
	TIXR	X	 .X+1
	LDA	NU,X
	ADD	EVNARRAY
	STA	EVNARRAY
	TIXR	X	 .X+1
	TIXR	X	 .X+1
	TIX	#24	 .X+1 and compare to 24
	JLT	SUMLOOP
	LDL	RETGD
	RSUB
ODDARRAY RESW	1
EVNARRAY RESW	1

TMP	RESW	1
.main function
MAIN	LDA	#0
	LDX	#0
LOOP	JSUB    GETD 	 .get two-digits number
	STA	NU,X
	JSUB    READCHAR .get a space
	TIXR	X	 .X+1
	TIXR	X	 .X+1
	TIX	#24	 .X+1 and compare to 24
	JLT	LOOP

	.first step	
	LDA	NU
	STCH	OUTD
	JSUB	WDBYTE

	.second step
	JSUB	ODDORDEVN
	LDA	ODDSUM
	COMP	EVNSUM
	JGT	OPENDOOR
	LDA	CURR
	AND	#254  .AND 11111110
	J	NEXT2
OPENDOOR LDA	CURR
	OR	#1
NEXT2	STCH	OUTD
	JSUB	WDBYTE

	.third step
	JSUB	SUMARRAY
	LDA	ODDARRAY
	COMP	EVNARRAY
	JGT	ALARM
	LDA	CURR
	AND	#247 .AND 11110111
	J	NEXT3
ALARM	LDA	CURR
	OR	#8
NEXT3	STCH	OUTD
	JSUB	WDBYTE

	.fourth step
	LDA	CURR
	AND	#32 .AND 00100000
	COMP	#32 .compare to 00100000
	JEQ	CLOSE
	LDA	CURR 
	OR	#32 .OR 00100000
	J	NEXT4
CLOSE	LDA	CURR
	AND	#223 .AND 11011111
NEXT4	STCH	OUTD
	JSUB	WDBYTE
HERE	J       HERE .loop forever
        END     MAIN
