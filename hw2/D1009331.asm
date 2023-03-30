INPUT   BYTE    X'05'
NOWDATA RESW    1
NU   RESW    8


.read 05.dev
READCHAR LDA	 #0
READLOOP TD      INPUT             TEST INPUT DEVICE
         JEQ     READLOOP          LOOP UNTIL READY 
         RD      INPUT             READ CHARACTER 
         RSUB                      RETURN TO CALLER

.write data into 06.dev
WDBYTE   TD      OUTPUT
         JEQ     WDBYTE
         STA     NOWDATA
         LDCH    OUTD
         WD      OUTPUT
         RSUB
OUTPUT   BYTE    X'06'
OUTD     RESB    1

.char to integer
GETD     STL     RETGD             SAVE RETURN ADDRESS
GETDLOOP JSUB    READCHAR          READ CHARACTER 
         SUB     #48               SUBTRACT HEX 30 FROM ASCII CODE '0'
		 MUL     #10			   *10
		 STA     DIGIT10							
         JSUB    READCHAR          READ CHARACTER 
         SUB     #48               SUBTRACT HEX 30 FROM ASCII CODE '0'
         ADD     DIGIT10               
    LDL     RETGD             RETURN TO CALLER 
         RSUB
RETGD    RESW    1
DIGIT10  RESW    1

.
PLUSODD LDA ODDCNT
        ADD #1
        STA ODDCNT
        RSUB
ODDCNT RESW 1

.
PLUSEVEN LDA EVENCNT
        ADD #1
        STA EVENCNT
        RSUB
EVENCNT RESW 1


.count the amounts of odd and even in NU
OE_COUNT STL RETGD
        LDX #0
CLOOP   LDA NU,X
        AND #1
        COMP #0
        JEQ EVEN
        JSUB PLUSODD
        J MOVE1
EVEN    JSUB PLUSEVEN
MOVE1   TIXR X
        TIXR X
        TIX #24
        JLT CLOOP
        LDL RETGD
        RSUB

. NU[ODD] NU[EVEN] SUM
SUM_NU STL RETGD
    LDX #0
DOLOOP LDA NU, X
    ADD ODD_SUM
    STA ODD_SUM
    TIXR X
    TIXR X
    TIXR X
    LDA NU, X
    ADD EVEN_SUM
    STA EVEN_SUM
    TIXR X
    TIXR X
    TIX #24
    JLT DOLOOP
    LDL RETGD
    RSUB
ODD_SUM RESW 1
EVEN_SUM RESW 1



.main function END     END     MAINFUNC
MAINFUNC    LDA #0
            LDX #0
LOOP JSUB GETD
        STA NU,X
        JSUB READCHAR
        TIXR X
        TIXR X
        TIX #24
        JLT LOOP

        .PRACTICE 1
        LDA NU
        STCH OUTD
        JSUB WDBYTE

        .PRACTICE 2
        JSUB OE_COUNT
        LDA ODDCNT
        COMP EVENCNT
        JGT DOOR_ON
        LDA NOWDATA
        AND #254
        J OUT1
DOOR_ON LDA NOWDATA
    OR #1
OUT1  STCH OUTD
    JSUB WDBYTE

    .PRACTICE 3
    JSUB SUM_NU
    LDA ODD_SUM
    COMP EVEN_SUM
    JGT RINGRING
    LDA NOWDATA
    AND #247
    J OUT2
RINGRING LDA NOWDATA
    OR #8
OUT2  STCH OUTD
    JSUB WDBYTE

    .PRACTICE 4
    LDA NOWDATA
    AND #32
    COMP #32
    JEQ LIGHT
    LDA NOWDATA
    OR #32
    J OUT3
LIGHT LDA NOWDATA
    AND #223
OUT3  STCH OUTD
    JSUB WDBYTE
HERE    J HERE
    END     MAINFUNC