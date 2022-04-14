    .syntax		unified
    .cpu		cortex-m4
    .text

    .global		Integrate
    .thumb_func

Integrate:
    PUSH    {R4, LR}
    VPUSH   {S16-S31}
    BL      DeltaX //stores in S0
    VMOV    S16, S0 //dx in S16

    VMOV    S17, 1.0 //x
    VMOV    S18, 1.0 // r
    VMOV    S19, 1.0
    VMOV    S20, 2.0
    LDR     R4,=0 //n
    VSUB.F32    S21, S0, S0 //v
    VSUB.F32    S22, S0, S0 //a

L1:
    MOV     R0, R4  //preserves n in R0
    VMOV    S0, S18 //preserves r in S0
    VMOV    S1, S21 //preserves v in S1
    VMOV    S2, S22 //preserves a in S2
    BL      UpdateDisplay

    VMOV    S13,S1 //saves current v in S13

    VADD.F32    S5, S17, S16 // S5 = x + dx
    VDIV.F32    S6, S19, S5 // S6 = 1/(x + dx)
    VDIV.F32    S7, S19, S17 // S7 = 1/x
    VADD.F32    S8, S7, S6 // S8 = 1/x + 1/(x + dx)
    VDIV.F32    S18, S8, S20 //r = S8/2

    VADD.F32    S22, S22, S18  // add Ri to R for Area sum

    VMUL.F32    S9, S18, S18 //multiplies Ri to Ri Ri^2
    VADD.F32    S21, S21, S9  //adds it to volume sum

    ADD     R4, R4, 1 //increments n
    VADD.F32    S17, S17, S16 //x = x + dx

    VCMP.F32   S21, S13 //compares new v with old v
    VMRS     APSR_nzcv, FPSCR

    BNE     L1  //if(S21 != S13) go through L1 again
    VPOP    {S16-S31}
    POP     {R4, LR}
    BX      LR
