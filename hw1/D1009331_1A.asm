.a=5^3
START   LDA #5 
    MUL #5 
    MUL #5
    STA A

.b=(-2)^2
    LDA negTwo
    MUL negTwo
    STA B

.c=|b-a|
    LDA B
    SUB A
toPos MUL negOne .multiply by -1
    COMP #0 .compare to 0
    JLT toPos .if negative, multiply by -1
    STA C

.d=a-b
    LDA  A
    SUB B
    STA D

.swap a,b
TEMP RESW 1
    LDA A
    STA TEMP
    LDA B
    STA A
    LDA TEMP
    STA B

.e=b*b*b Must use loop
    LDA B 
    STA TEMP
    LDX #0 .counter
LOOP LDA TEMP
    MUL B
    STA TEMP .store in TEMP
    TIX #2 .increment counter
    JLT LOOP .if counter < 3, loop
    STA E

.If A is odd then F = 15 else F = 30
    LDA A
    AND #1 
    COMP #0 .compare to 0
    JEQ EVEN .if A is even, jump to EVEN
    LDA #15
EVEN LDA #30
    STA F

.If B is odd then G load "ODD" string else G = "EVN"
    LDA B
    AND #1 .AND with 1, if odd, last bit will be 1 else 0
    COMP #0 .compare to 0
    LDX #0 .counter for string
    JEQ EVFUNC .if even, jump to EVFUNC
ODDFUNC LDCH ODD, X .load odd string
    STCH G,X .store in G, X is counter
    TIX #3 .increment counter, 3 because 3 chars in string
    JLT ODDFUNC .if counter < 3, loop
EVFUNC LDCH EVN, X .load even string
    STCH G,X .store in G, X is counter
    TIX #3 .increment counter, 3 because 3 chars in string
    JLT EVFUNC .if counter < 3, loop


.h=b/a
    LDA B
    DIV A
    STA H

.j=e%a
    LDA E
    DIV A
    STA Quotient
    LDA Quotient 
    MUL A
    STA T
    LDA E
    SUB T
    STA J

negOne WORD -1
negTwo WORD -2

ODD BYTE C'ODD' 
EVN BYTE C'EVN'

A   RESW 1
B   RESW 1
C   RESW 1
D   RESW 1
E   RESW 1
F   RESW 1
G   RESB 3
H   RESW 1
J   RESW 1
Quotient RESW 1
T RESW 1