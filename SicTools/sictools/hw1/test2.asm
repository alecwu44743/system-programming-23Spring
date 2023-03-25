.計算5的三次方，將結果儲存到A
START  LDX    #0  
       LDA    #5 .Load 5
M5     MUL    #5  .乘上5       
       TIX    #2 .cc條件碼為 < ，因此再做一次乘積循環
       JLT    M5
       STA    A

       .計算-2 的平方，將結果儲存到C
       LDX    #0
       LDA    NegTwo
MN2    MUL    NegTwo
       TIX    #1 .cc條件碼為 = ，因此不做乘積循環
       JLT    MN2
       STA    B

       .計算B-A的絕對值，將結果儲存到C
       LDA    B
       SUB    A
MN1    MUL    NegOne  .乘上-1
       COMP   #0 .暫存器的值跟B本身比
       JLT    MN1 .如果CC結果為 < 0， 要再乘上-1
       STA	 C

       .將A-B結果儲存到D 
       LDA    A
       SUB    B
       STA    D
       
       .將A跟B交換
       .相等於
       .int temp = a;
       .int a = b;
       .int b = tmp;
       LDA    A
       STA    Tmp
       LDA    B
       STA    A
       LDA    Tmp
       STA    B

       .計算 B * B * B。將結果儲存到E
       LDX    #0
       LDA    B
LOOP   MUL    B
       TIX    #2 .再做一次循環
       JLT    LOOP
       STA    E

       .If A is odd then F = 15 else F = 30
       LDA    A
       AND    #1
       COMP   #0 .如果A & 1 結果為 1 ，則A為奇數。 反之，如果A & 1 結果為 0，則A為偶數
       JEQ    EVEN 
ODD    LDA    #15
       STA    F
       J      NEXT 
EVEN   LDA    #30
       STA    F
     
       .If B is odd then G = ‘ODD’ else G = ‘EVN’
NEXT   LDX    #0
       LDA    B
       AND    #1
       COMP   #0 
       JEQ    MVEEVN
MVEODD LDCH   STR1, X
       STCH   G, X
       TIX   #3
       JLT    MVEODD
       J      Cal
MVEEVN LDCH   STR2, X
       STCH   G, X
       TIX    #3
       JLT    MVEEVN
     
       .計算B/A，將結果儲存到H
Cal    LDA    B
       DIV    A
       STA    H

       .計算E%A，將結果儲存到J
       LDA    E
       DIV    A
       STA    Div .儲存E/A的值
       LDA    A
       MUL    Div
       STA    Tmp .儲存A * Div的值
       LDA    E
       SUB    Tmp 
END    STA    J

NegOne WORD   -1
NegTwo WORD   -2
STR1   BYTE   C'ODD'
STR2   BYTE   C'EVN'

A      RESW   1
B      RESW   1
C      RESW   1
D      RESW   1
E      RESW   1
H      RESW   1
J      RESW   1
G      RESB   3
F      RESW   1

Tmp    RESW  1
Div    RESW  1