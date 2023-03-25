WORK2    START   0x1000             
         LDA	 #-1
         LDF     ZERO
         LDF     Z1
.
         LDF     #0.25
         FIX
         LDA     #4
         FLOAT
.        LDX     #99999
HERE     J       HERE
ZERO     FLOT    0.0
Z1       FLOT    0.25
Z2       FLOT    -0.25
.
         END     WORK2