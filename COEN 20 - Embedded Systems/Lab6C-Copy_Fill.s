    .syntax		unified
    .cpu		cortex-m4
    .text

    .global		FillCell
    .thumb_func

FillCell:
    LDR    R2, =0       //rows
rowLoop1:
    LDR    R3, =0       //columns
    CMP    R2,60
    BEQ    doneRow1     //if(row==60), then go to doneRow1
colmnLoop1:
    CMP    R3, 60
    BEQ    doneColmn1   //if(column == 60), go to doneColmn1
    STR    R1, [R0, R3, LSL 2]  //stores pixel in dst[R3]
    ADD    R3, R3, 1 //next loop
    B      colmnLoop1
doneColmn1:
    ADD    R2, R2, 1 //next loop
    ADD    R0, R0, 960 //next row
    B      rowLoop1
doneRow1:
    BX     LR



    .global		CopyCell
    .thumb_func

CopyCell:
    PUSH        {R4}
    LDR         R2, = 0 //rows

rowLoop2:
    LDR         R3, =0 //columns
    CMP         R2, 60
    BEQ         doneRow2 //if(row==60), then go to doneRow2

colmnLoop2:
    CMP         R3, 60
    BEQ         doneColmn2 //if(column == 60), go to doneColmn1
    LDR         R4,[R1, R3, LSL 2]
    STR         R4,[R0, R3, LSL2] //prev two lines stores src[R3]->R4->dst[R3]
    ADD         R3, R3, 1 //next loop
    B           colmnLoop2

doneColmn2:
    ADD         R2, R2, 1 //next loop
    ADD         R0, R0, 960 //next row for dst
    ADD         R1, R1, 960 //next row for src
    B           rowLoop2

doneRow2:
    POP         {R4}
    BX          LR

.end
