.23456789012345678901234567890
CH1B	START	 0
	LDA	 FIVE
	STA	 ALPHA
	LDCH	 CHARZ
	STCH	 C1
	LDA	 NEG1
HERE	J      	 HERE
FIVE	WORD	 5
CHARZ	BYTE	 C'Z'
NEG1	WORD     -1
ALPHA	RESW	 1
ALPHA2	RESW	 2
C1	RESB	 1
C2	RESB	 2
CA	BYTE	 X'41'
CB	BYTE	 X'41C1'
CC	BYTE	 C'41'
CD	BYTE	 C'41C1'
CE	BYTE	 C'AB'
CF	BYTE	 C'ab'
CG	BYTE	 C'012'
	END	 CH1B