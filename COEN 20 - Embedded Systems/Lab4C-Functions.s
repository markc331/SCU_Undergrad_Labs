	.syntax		unified
	.cpu		cortex-m4
	.text

	.global		FullWordAccess
	.thumb_func
FullWordAccess:
	.rept 		100
	LDR 		R1,[R0]
	.endr
	BX 			LR

	.global		HalfWordAccess
	.thumb_func
HalfWordAccess:
	.rept 		100
	LDRH		R1,[R0]
	.endr
	BX			LR

	.global		AddressDependency
	.thumb_func
AddressDependency:
	.rept 		100
	LDR			R1,[R0]
	LDR			R0,[R1]
	.endr
	BX			LR


	.global		NoAddressDependency
	.thumb_func
NoAddressDependency:
	.rept 		100
	LDR			R1,[R0]
	LDR 		R2,[R0]
	.endr
	BX 			LR

	.global		DataDependency
	.thumb_func
DataDependency:
	.rept			100
	VADD.F32		S1, S0, S0
	VADD.F32		S0, S1, S1
	.endr
	VMOV			S1, S0
	BX				LR

	.global		NoDataDependency
	.thumb_func
NoDataDependency:
	.rept 			100
	VADD.F32 		S1, S0, S0
	VADD.F32 		S2, S0, S0
	.endr
	VMOV			S1,S0
	BX				LR

	.global		VDIVOverlap
	.thumb_func
VDIVOverlap:
	VDIV.F32		S2, S1, S0
	.rept			14
	NOP
	.endr
	VMOV 			S3, S2
	BX 				LR


	.end
