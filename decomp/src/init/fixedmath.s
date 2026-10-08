# D_80071fa4 (0x80071fa4) size=448 -- hand-written assembly: memory-layout table + 64-bit fixed-point helpers
	.set	noreorder
	.set	noat
	.text

# Memory-layout table: name[8], then six words per region (referenced from 0x800171f4).
	.globl	D_80071fa4
D_80071fa4:
	.word	0x6d6d6f63	# "comm"
	.word	0x00006e6f	# "on"
	.word	0x00000800
	.word	0x00000800
	.word	0x00071800
	.word	0x0000a800
	.word	0x00003000
	.word	0x00000000
	.word	0xffffffff
	.word	0x74616b73	# "skat"
	.word	0x00745f65	# "e_t"
	.word	0x0005b000
	.word	0x0000a800
	.word	0x00003000
	.word	0x00032000
	.word	0x00001800
	.word	0xffffffff
	.word	0x63736b73	# "sksc"
	.word	0x745f6c68	# "hl_t"
	.word	0x00000000
	.word	0x0005b000
	.word	0x0000a800
	.word	0x00003000
	.word	0x00047800
	.word	0x00007000
	.word	0x0007c800
	.word	0xffffffff
	.word	0x61766b73	# "skva"
	.word	0x745f736e	# "ns_t"
	.word	0x00000000
	.word	0x0005b000
	.word	0x0000a800
	.word	0x00003000
	.word	0x00000000
	.word	0x0005f800
	.word	0xffffffff
	.word	0x00000000

# 64-bit fixed-point multiply helpers

	.globl	Mips_DotProd2Sign
Mips_DotProd2Sign:
	mult	$4,$5
	mflo	$2
	mfhi	$3
	addu	$8,$0,$0
	sll	$0,$0,0
	mult	$6,$7
	mflo	$10
	mfhi	$11
	addu	$2,$2,$10
	sltu	$7,$2,$10
	addu	$3,$3,$7
	addu	$3,$3,$11
	or	$2,$2,$3
	beq	$2,$0,$L20
	ori	$8,$8,1
	bgez	$3,$L18
	sll	$0,$0,0
	subu	$8,$0,$8
$L18:
	jr	$31
	addu	$2,$8,$0
$L20:
	jr	$31
	sll	$0,$0,0
	.globl	Mips_FixMul__Fii
Mips_FixMul__Fii:
	mult	$4,$5
	mflo	$2
	mfhi	$3
	srl	$2,$2,12
	sll	$3,$3,20
	jr	$31
	or	$2,$2,$3
	.globl	Mips_DotProd2
Mips_DotProd2:
	mult	$4,$5
	mflo	$2
	mfhi	$3
	sll	$0,$0,0
	sll	$0,$0,0
	mult	$6,$7
	mflo	$10
	mfhi	$11
	addu	$2,$2,$10
	sltu	$7,$2,$10
	addu	$3,$3,$7
	addu	$3,$3,$11
	srl	$2,$2,12
	sll	$3,$3,20
	jr	$31
	or	$2,$2,$3
	.globl	Mips_CVecDotProd__FP7CVectorT0
Mips_CVecDotProd__FP7CVectorT0:
	lw	$8,0($4)
	lw	$9,0($5)
	sll	$0,$0,0
	mult	$8,$9
	lw	$8,4($4)
	lw	$9,4($5)
	mflo	$2
	mfhi	$3
	sll	$0,$0,0
	sll	$0,$0,0
	mult	$8,$9
	lw	$8,8($4)
	lw	$9,8($5)
	mflo	$10
	mfhi	$11
	addu	$2,$2,$10
	sltu	$7,$2,$10
	mult	$8,$9
	addu	$3,$3,$7
	addu	$3,$3,$11
	mflo	$10
	mfhi	$11
	addu	$2,$2,$10
	sltu	$7,$2,$10
	addu	$3,$3,$7
	addu	$3,$3,$11
	srl	$2,$2,12
	sll	$3,$3,20
	jr	$31
	or	$2,$2,$3
