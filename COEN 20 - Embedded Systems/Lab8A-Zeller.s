    .syntax		unified
    .cpu		cortex-m4
    .text

    .global		Zeller1
    .thumb_func

//R0 = k, R1 = m, R2 = D , R3 = C
Zeller1:
        PUSH    {R4, R5, R6, R7, R8}
        LDR     R4, =13
        LDR     R5, =5
        LDR     R6, =4
        LDR     R7, =2

        MUL     R7, R3, R7 //R7 = 2*C
        UDIV    R8, R3, R6 //R8 = C/4
        UDIV    R6, R2, R6 //R6 = D/4
        MUL     R4, R1, R4 //R4 = 13*m
        SUB     R4, R4, 1 //R4 = 13*m - 1
        UDIV    R4, R4, R5 // R4 = (13*m-1)/5
        ADD     R0, R0, R4 // R0 = k + R4
        ADD     R0, R0, R2 //R0 = k + R4 + R2
        ADD     R0, R0, R6 //R0 = k + R4 + R2 + R6
        ADD     R0, R0, R8 //R0 = k + R4 + R2 + R6 + R8
        SUB     R0, R0, R7 //R0 = k + R4 + R2 + R6 + R8 - R7

        LDR     R8, =7
        SDIV    R2, R0, R8   // R2 = R0/7
        MLS     R3, R8, R2, R0 //R3 = R0 = R8*R2 = remainder
        IT      LT
        ADDLT   R3, R3, R8 //if remainder = 0, add 7
        MOV     R0, R3 //stores remainder to R0
        POP     {R4, R5, R6, R7, R8}
        BX      LR

    .global		Zeller2
    .thumb_func

//R0 = k, R1 = m, R2 = D , R3 = C
Zeller2:
PUSH	{R4}
		ADD		R0, R0, R2			// R0 = k + D
		ADD		R0, R0, R2, LSR 2	// R0 = k + D+ D / 4
		ADD		R0, R0, R3, LSR 2	// R0 = k + D+ D / 4+ C / 4
		SUB		R0, R0, R3, LSL 1	// R0 = k + D+ D / 4 + C / 4 - 2*C
		LDR		R3, =13
		MUL		R2, R1, R3			// 13 * m
		SUB		R2, R2, 1			// 13 * m - 1
		LDR		R3, =858993459		// 2^32 / 5
		SMULL	R2, R3, R2, R3		// R3 = R3 * (2^32)/5 = quotient
		ADD		R0, R0, R3			//R0 = k + D+ D / 4 + C / 4 - 2*C + R3

		LDR		R3, =613566757		// 2^32 / 7
		SMULL	R2, R3, R0, R3		// R3 = R0 * (2^32)/7 = quotient
		LDR		R4, =7
		MUL		R3, R3, R4			// R3 = R3 * R4
		SUB		R3, R0, R3			// R3 = R0 - R3
		CMP		R3, 0
		IT		LT
		ADDLT	R3, R3, 7			// if R3 < 0, add 7
		MOV		R0, R3
		POP		{R4}
		BX 		LR

    .global		Zeller3
    .thumb_func

//R0 = k, R1 = m, R2 = D, R3 = C
Zeller3:
PUSH	{R4}
    ADD		R0, R0, R2			// R0 = k + R2
    ADD		R0, R0, R2, LSR 2	//R0 = k + R2 + D / 4
    ADD		R0, R0, R3, LSR 2	// R0 = k + R2 + D / 4 + C / 4
    SUB		R0, R0, R3, LSL 1	// R0 = k + R2 + D/4 + C/4 - C * 2
    ADD		R4, R1, R1, LSL 3	// R4 = m(8 + 1) = 9m
    ADD		R2, R4, R1, LSL 2	// R2 = m(4) + 9m = 13m
    SUB		R2, R2, 1			// R2 = 13 * m - 1
    LDR		R4, =5
    UDIV	R2, R2, R4			// R2 = (13 * m - 1) / 5
    ADD		R0, R0, R2			// R0 + R2

    LDR		R4, =7
    SDIV	R2, R0, R4			// R2 = R0 / 7
    LSL		R4, R2, 3			// R4 = 8*(R0/7)
    SUB		R2, R4, R2			//R4 - R2 = 7*R4
    SUB		R2, R0, R2			//R2 = R0 - R2
    CMP		R2, 0
    IT		LT
    ADDLT	R2, R2, 7			// if R2 < 0, R2= R2 + 7
    MOV		R0, R2
    POP		{R4}
    BX 		LR
