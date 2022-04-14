    .syntax		unified
    .cpu		cortex-m4
    .text

    .global		Log2Phys
    .thumb_func

Log2Phys:
    PUSH {R4,R5,R6}
    //R0 : IBA, R1 : heads, R2 : sectors, R3: phy

    //cylinder
    MUL R4, R1, R2      // R4 <-- R1*R2
    UDIV R5,R0,R4       // R5 <-- R0/R4
    STRH R5, [R3]        // stores value of cylinder in struct which is the first two slots

    //head
    UDIV R4, R0, R2     //dividend = (iba/sectors)
    UDIV R5, R4, R1         //quotient (R4/R1) => (iba/sectors)/heads
    MLS R6, R1, R5, R4      //finds remainder of R4 and heads
    STRB R6, [R3,2]     // stores value of head in struct which the third, shift two spots down

    //sector
    UDIV R4, R0, R2     //divides iba and sectors
    MLS R5, R2, R4, R0      // finds remainder of IBA and sectors
    ADD R6, R5, 1       //adds 1
    STRB R6, [R3,3]        //stores value of sector in struct which is 4th, shift 3 spots

    POP {R4, R5, R6}
    BX LR
