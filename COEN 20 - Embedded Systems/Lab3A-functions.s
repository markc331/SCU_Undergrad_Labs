        .syntax		unified
        .cpu		cortex-m4
        .text

        .global Add //from the main function
        .thumb_func
Add:
        ADD     R0, R0, R1   //first R0 is destination , second is int8_t a and R1 is b, adds them
        BX      LR           // copies return address to PC

        .global Less
        .thumb_func
Less:
        SUB     R0, 1       //subtracts 1 from R0
        BX      LR


        .global Square2x
        .thumb_func
Square2x:
        PUSH    {LR}        //saves address
        ADD     R0, R0, R0  //adds R0 to R0
        BL      Square      //Squares that result
        POP     {PC}        //returns back to the program counter

        .global Last
        .thumb_func
Last:
        PUSH    {R4, LR}   //preserves R4
        MOV     R4, R0      //saves it in R4

        BL      SquareRoot   //does the squareroot of R0
        ADD     R0, R0, R4  //ads R0(sqrt x) adds R4

        POP     {R4, PC}     //restores R4 ad returns to PC

        .end
