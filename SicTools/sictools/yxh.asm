.D1051401 HW2
MAIN     START    0

.Test file ready
INDEV    TD    INPUT
    JEQ    INDEV

.Read file byte then convert ascii char to number, store in DATA
.If read a char is space(ascii = 32), then skip
    LDX    #0
RLOOP    RD    INPUT
    COMP    #32
    JEQ    RLOOP
    SUB    #48
    MUL    #10
    STA    TMP
    RD    INPUT
    SUB    #48
    ADD    TMP
    STCH    DATA, X
    TIX    #8
    JLT    RLOOP

.Set first byte, and write to 06.dev
SFB    LDX    #0
    LDCH    DATA, X
    STCH    CTRLSW
    JSUB    OUTDEV

.Compare odd count and even count, if odd count bigger then evencount, then open door, otherwise close door
    LDX    #0
CMPOE    LDCH    DATA, X
    JSUB    ISODD
    ADD    ODDCNT
    STA    ODDCNT
    TIX    #8
    JLT    CMPOE
    LDA    #8
    SUB    ODDCNT
    COMP    ODDCNT
    LDCH    CTRLSW
    JLT    OPEN
    AND    #254
    STCH    CTRLSW
    J    WDSND
OPEN    OR    #1
    STCH    CTRLSW
    J    WDSND
WDSND    JSUB    OUTDEV

.Sum of index of 0, 2, 4, 6, compare with 1, 3, 5, 7. If 0, 2, 4, 6 bigger then 1, 3, 5, 7, ring.
    LDX    #0
SUMLOOP    LDCH    DATA, X
    ADD    ODDSUM
    STA    ODDSUM
    TIX    #8
    LDCH    DATA, X
    ADD    EVNSUM
    STA    EVNSUM
    TIX    #8
    JLT    SUMLOOP
    LDA    ODDSUM
    COMP    EVNSUM
    LDCH    CTRLSW
    JGT    RING
    AND    #247
    J    WDTRD
RING    OR    #8
    J    WDTRD

WDTRD    STCH    CTRLSW
    JSUB    OUTDEV

.Switch the light inverse
STLI    LDCH    CTRLSW
    AND    #32
    COMP    #0
    LDCH    CTRLSW
    JEQ    OPENLT
    AND    #223
    J    WDFTH
OPENLT    OR    #32
    J    WDFTH
WDFTH    STCH    CTRLSW
    JSUB    OUTDEV
    J    ENDMAIN


ISODD    AND    #1
    RSUB

ODD    LDA    ODDCNT
    ADD    #1
    STA    ODDCNT
    RSUB


.Write CTRLSW to 06.dev
OUTDEV    TD    OUTPUT
    JEQ    OUTDEV
    LDCH    CTRLSW
    WD    OUTPUT
    RSUB

INPUT    BYTE    X'05'
OUTPUT    BYTE    X'06'
TMP    RESW    1
DATA    RESB    8
CTRLSW    RESB    1
ODDCNT    WORD    0
ODDSUM    WORD    0
EVNSUM    WORD    0
    
ENDMAIN    END    MAIN