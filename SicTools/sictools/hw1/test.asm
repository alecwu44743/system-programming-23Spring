  .A = 5 ^ 3
START    LDA    FIVE
    MUL    FIVE
    MUL    FIVE
    STA    A

    .B = (-2) ^ 2
    LDA    NTWO
    MUL    NTWO
    STA    B

    .C = |B - A|
    LDA    B
    SUB    A
NEG    MUL    NONE
    COMP    ZERO
    JLT    NEG     .如果C < 0，則到 NEG 再乘一次 -1
    STA    C

    .D = A - B
    LDA    A
    SUB    B
    STA    D

    .Swap A, B
    LDA    B
    STA    TEMP     .將 B 值存到 TEMP
    LDA    A
    STA    B     .將 A 值存到 B
    LDA    TEMP
    STA    A     .將 TEMP 的值存到 A

    .E = B * B * B
    LDA    B
    STA    TEMP     .用 TEMP 來計算 B 值的三次方
    LDX    ZERO
loop    LDA    TEMP
    MUL    B
    STA    TEMP
    TIX    TWO     .迴圈跑兩次即可得出 TEMP * TEMP * TEMP
    JLT    loop     .若 <= 2 則繼續 loop
    STA    E    .將結果存到 E

    .If A is odd then F = 15 else F = 30
    LDA     A
    AND    ONE    .A & 1 如果為 1，則 A 為奇數，為 0 則為偶數
    COMP    ONE
    LDA     FIFTEEN
    JEQ    ELSE    .若為 1 ，則不用乘二
    MUL    TWO
ELSE    STA    F

    .If B is odd then G = ‘ODD’ else G = ‘EVN’
    LDA    B
    AND    ONE    .若 B & 1 如果為 0，則 B 為偶數，為 0 則為奇數
    COMP    ZERO
    LDX    ZERO
    JEQ    CPYEVN    .若為偶數則跳至CPYEVN
CPYODD    LDCH    STR1, X
    STCH    G, X
    TIX    THREE
    JLT    CPYODD
    J    EXIT    .迴圈結束則跳至EXIT
    
CPYEVN    LDCH    STR2, X
    STCH    G, X
    TIX    THREE
    JLT    CPYEVN
    J    EXIT    .迴圈結束則跳至EXIT

    .H = B / A
EXIT    LDA    B
    DIV    A
    STA    H

    .利用被除數 - (商 * 除數) = 餘數
    .J = E mod A
    LDA    E
    DIV    A
    STA    TEMP
    LDA    TEMP
    MUL    A
    STA    TEMP
    LDA    E
    SUB    TEMP
    STA    J


NTWO    WORD    -2
NONE    WORD    -1
ZERO    WORD    0
ONE    WORD    1
TWO    WORD    2
THREE    WORD    3
FIVE    WORD    5
FIFTEEN WORD    15
STR1    BYTE    C'ODD'
STR2    BYTE    C'EVN'


A    RESW    1
B    RESW    1
C    RESW    1
D    RESW    1
E    RESW    1
F    RESW    1
G    RESB    3
H    RESW    1
J    RESW    1
TEMP    RESW    1
MOD    RESW    1