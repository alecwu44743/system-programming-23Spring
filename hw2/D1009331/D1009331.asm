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


.count the amounts of odd and even in NU
OE_COUNT STL RETGD .save return address
        LDX #0 .X=0
CLOOP   LDA NU,X .load data, X=0
        AND #1 .AND 0000 0001
        COMP #0 .compare with 0
        JEQ PLUSEVEN .if 0, PLUSEVEN
        J PLUSODD
PLUSODD LDA ODDCNT .load odd count
        ADD #1 .add 1
        STA ODDCNT .store odd count
        J GOMOVE .go to move
PLUSEVEN LDA EVENCNT .load even count
        ADD #1 .add 1
        STA EVENCNT .store even count
        J GOMOVE .go to move
GOMOVE   TIXR X .X=X+1
        TIXR X .X=X+1
        TIX #24 .X=24
        JLT CLOOP .if X<24, CLOOP
        LDL RETGD .return to caller
        LDA ODDCNT .load odd count
        COMP EVENCNT .compare with even count
        JGT DOOR_ON .if odd>even, door on
        LDA NOWDATA .load data
        AND #254    .AND 1111 1110
        J OUT1 .go to output
DOOR_ON LDA NOWDATA .load data
        OR #1 .OR 0000 0001
OUT1  STCH OUTD .store data
        JSUB WDBYTE .write data
        J TOGO3 .go to practice 3
EVENCNT RESW 1
ODDCNT RESW 1


. NU[ODD] NU[EVEN] SUM
SUM_NU STL RETGD .save return address
    LDX #0 .X=0
DOLOOP LDA NU, X .load data, X=0
    ADD ODD_SUM .add odd sum
    STA ODD_SUM .store odd sum
    TIXR X .X=X+1
    TIXR X .X=X+1
    TIXR X .X=X+1
    LDA NU, X .load data, X=3
    ADD EVEN_SUM .add even sum
    STA EVEN_SUM .store even sum
    TIXR X .X=X+1
    TIXR X .X=X+1
    TIX #24 .X=24
    JLT DOLOOP .if X<24, DOLOOP
    LDL RETGD .return to caller
    LDA ODD_SUM .load odd sum
    COMP EVEN_SUM .compare with even sum
    JGT RINGRING .if odd>even, ring ring
    LDA NOWDATA .load data
    AND #247 .AND 1111 0111
    J OUT2 .go to output
RINGRING LDA NOWDATA .load data
    OR #8 .OR 0000 1000
OUT2  STCH OUTD .store data
    JSUB WDBYTE .write data
    J TOGO4 .go to practice 4
ODD_SUM RESW 1 .odd sum
EVEN_SUM RESW 1 .even sum

.light on or off
LIGHT_ON_OFF LDA NOWDATA .load data
    AND #32 .AND 0010 0000
    COMP #32 .compare with 32
    JEQ LIGHT .if 32, light 
    LDA NOWDATA .load data
    OR #32 .OR 0010 0000
    J OUT3 .go to output
LIGHT LDA NOWDATA .load data
    AND #223 .AND 1101 1111
OUT3  STCH OUTD .store data
    JSUB WDBYTE .write data
    J HERE .go to here


.main function END     END     MAINFUNC
MAINFUNC    LDA #0 .A=0
            LDX #0 .X=0
LOOP JSUB GETD .get data
        STA NU,X .store data
        JSUB READCHAR .read character
        TIXR X .X=X+1
        TIXR X .X=X+1
        TIX #24 .X=24
        JLT LOOP .if X<24, LOOP

        .PRACTICE 1 
        LDA NU .load data
        STCH OUTD .store data
        JSUB WDBYTE .write data

        .PRACTICE 2 
        JSUB OE_COUNT .count the amounts of odd and even in NU

    .PRACTICE 3
TOGO3    JSUB SUM_NU .NU[ODD] NU[EVEN] SUM

    .PRACTICE 4
TOGO4    JSUB LIGHT_ON_OFF .NU[ODD] NU[EVEN] LIGHT
HERE    J HERE
    END     MAINFUNC .end main function