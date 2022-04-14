    .syntax		unified
    .cpu		cortex-m4
    .text

    .global		GetNibble
    .thumb_func

//R0 = nibbles, R1 = which
GetNibble:
    LSR         R2, R1, 1       //stores which/2 in R2 to get byte index
    LDRB        R2, [R0, R2]    //shifts by byte index up
    AND         R1, R1, 1       //retains value of first bit
    CMP         R1, 1           //checks if off or even
    ITE         EQ              //IT block
    UBFXEQ      R0, R2, 4, 4    //if odd, get second nibble in the byte
    UBFXNE      R0, R2, 0, 4    //if even, get first nibble in the byte
    BX          LR


    .global		PutNibble
    .thumb_func

//R0 and R1 the same, R2 = value
PutNibble:
    PUSH        {R4, LR}
    LSR         R4, R1, 1   //stores which/2 in R4 for byte index
    LDRB        R3, [R0, R4] //moves R3 to byte
    AND         R1, R1, 1 //isolates first bit value
    CMP         R1, 1
    ITE         EQ
    BFIEQ       R3, R2, 4, 4 //if odd, then store value in R3 in second nibble
    BFINE       R3, R2, 0, 4 //if even, then store value in R3 in first nibble
    STRB        R3, [R0, R4]  //stores value of R2(now in R3) back into nibble
    POP         {R4, PC}
    BX          LR
