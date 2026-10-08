# DecDCTvlcBuild3 (0x80022498) size=1364 -- hand-written assembly
	.set	noreorder
	.set	noat
	.text

	.globl	DecDCTvlcBuild3
DecDCTvlcBuild3:
	lui	$4,8064
	lui	$5,32778
	addiu	$5,$5,25208
	ori	$8,$0,214
$L4:
	lbu	$9,0($5)
	lbu	$10,1($5)
	sll	$9,$9,10
	sub	$11,$0,$10
	andi	$11,$11,1023
	or	$10,$9,$10
	sh	$10,0($4)
	or	$11,$9,$11
	sh	$11,2($4)
	addi	$5,$5,2
	addi	$4,$4,4
	bgez	$8,$L4
	addi	$8,$8,-2
	jr	$31
	sll	$0,$0,0
	.globl	DecDCTvlc3
DecDCTvlc3:
	addi	$29,$29,-4
	sw	$31,0($29)
	lui	$14,32778
	addiu	$14,$14,25424
	lw	$12,0($14)
	lui	$7,8064
	bne	$4,$0,$L47
	sll	$12,$12,1
	lui	$14,32778
	addiu	$14,$14,25428
	lw	$2,0($14)
	lw	$3,4($14)
	lw	$8,8($14)
	lw	$4,12($14)
	lw	$5,16($14)
	lw	$6,20($14)
	lw	$10,24($14)
	lw	$11,28($14)
	lw	$13,32($14)
	lw	$15,36($14)
	lw	$24,40($14)
	lw	$25,44($14)
	lw	$31,48($14)
	add	$12,$12,$5
	bne	$31,$0,$L84
	sll	$0,$0,0
	bgez	$0,$L301
	sll	$0,$0,0
$L47:
	add	$12,$12,$5
	lw	$8,0($4)
	lw	$11,4($4)
	lw	$2,8($4)
	lw	$3,12($4)
	lw	$6,16($4)
	or	$10,$0,$0
	or	$15,$0,$0
	or	$24,$0,$0
	or	$25,$0,$0
	sll	$1,$2,16
	srl	$2,$2,16
	or	$2,$2,$1
	sll	$1,$3,16
	srl	$3,$3,16
	or	$3,$3,$1
	sw	$8,0($5)
	addi	$5,$5,4
	addi	$4,$4,20
	andi	$8,$8,65535
	sll	$8,$8,2
	add	$13,$5,$8
	srl	$1,$11,16
	xori	$1,$1,3
	andi	$11,$11,63
	beq	$1,$0,$L237
	sll	$11,$11,10
	srl	$8,$2,22
	or	$8,$8,$11
	jal	FUN_80022624
	ori	$9,$0,10
	srl	$8,$8,22
	xori	$1,$8,511
	beq	$1,$0,$L308
	subu	$1,$5,$12
	bgez	$1,$L319
	or	$8,$8,$11
$L84:
	bgez	$0,$L99
	ori	$9,$0,12
	.globl	FUN_800225f0
FUN_800225f0:
$L86:
	bgez	$2,$L122
	sll	$1,$2,1
	bltz	$1,$L95
	sll	$1,$2,2
	ori	$8,$0,65024
	sh	$8,0($5)
	addi	$5,$5,2
	jr	$31
	sll	$8,$2,2
$L95:
	ori	$9,$0,3
	bgez	$1,$L99
	ori	$8,$0,1
	ori	$8,$0,1023
	.globl	FUN_80022624
FUN_80022624:
$L99:
	sh	$8,0($5)
	addi	$5,$5,2
	sllv	$2,$2,$9
	sub	$1,$0,$9
	srlv	$1,$3,$1
	or	$2,$2,$1
	add	$10,$10,$9
	addi	$1,$10,-32
	bltz	$1,$L86
	sllv	$3,$3,$9
	addi	$10,$10,-32
	sub	$1,$0,$10
	sll	$8,$6,16
	srl	$6,$6,16
	or	$6,$6,$8
	bne	$1,$0,$L117
	srlv	$1,$6,$1
	or	$1,$0,$0
$L117:
	sllv	$3,$6,$10
	lw	$6,0($4)
	or	$2,$2,$1
	bgez	$0,$L86
	addi	$4,$4,4
	.globl	FUN_80022680
FUN_80022680:
$L122:
	bgez	$1,$L142
	sll	$1,$2,2
	bgez	$1,$L131
	sll	$1,$2,3
	ori	$9,$0,4
	bgez	$1,$L99
	ori	$8,$0,1025
	bgez	$0,$L99
	ori	$8,$0,2047
$L131:
	ori	$9,$0,5
	bltz	$1,$L138
	sll	$1,$2,4
	bgez	$1,$L99
	ori	$8,$0,2
	bgez	$0,$L99
	ori	$8,$0,1022
$L138:
	bgez	$1,$L99
	ori	$8,$0,2049
	bgez	$0,$L99
	ori	$8,$0,3071
$L142:
	bgez	$1,$L158
	sll	$1,$2,3
	srl	$1,$1,30
	beq	$1,$0,$L152
	srl	$1,$2,25
	andi	$1,$1,14
	add	$1,$1,$7
	lh	$8,412($1)
	bgez	$0,$L99
	ori	$9,$0,6
$L152:
	srl	$1,$2,22
	andi	$1,$1,30
	add	$1,$1,$7
	lh	$8,384($1)
	bgez	$0,$L99
	ori	$9,$0,9
$L158:
	mtc2	$2,$30
	srl	$1,$2,26
	addi	$1,$1,-1
	beq	$1,$0,$L190
	mfc2	$9,$31
	bltz	$1,$L174
	sllv	$1,$2,$9
	srl	$1,$1,27
	andi	$1,$1,14
	addi	$8,$9,-3
	sll	$8,$8,4
	add	$1,$1,$8
	add	$1,$1,$7
	lh	$8,0($1)
	bgez	$0,$L99
	addi	$9,$9,4
$L174:
	addi	$8,$9,-6
	blez	$8,$L184
	sll	$8,$8,6
	srl	$1,$1,25
	andi	$1,$1,62
	add	$1,$1,$8
	add	$1,$1,$7
	lh	$8,0($1)
	bgez	$0,$L99
	addi	$9,$9,6
$L184:
	srl	$1,$1,26
	andi	$1,$1,30
	add	$1,$1,$7
	lh	$8,32($1)
	bgez	$0,$L99
	addi	$9,$0,11
$L190:
	srl	$8,$2,10
	andi	$8,$8,65535
	bgez	$0,$L99
	addi	$9,$0,22
	.globl	FUN_800227a0
FUN_800227a0:
	bltz	$8,$L209
	sll	$1,$8,1
	bgez	$1,$L204
	sll	$1,$1,1
	ori	$9,$0,6
	srl	$8,$1,30
	bltz	$1,$L233
	add	$25,$25,$8
	bgez	$0,$L233
	addi	$25,$25,-3
$L204:
	ori	$9,$0,5
	bltz	$1,$L233
	addi	$25,$25,1
	bgez	$0,$L233
	addi	$25,$25,-2
$L209:
	mtc2	$8,$30
	bltz	$1,$L221
	sll	$14,$1,1
	bgez	$14,$L233
	ori	$9,$0,5
	ori	$9,$0,8
	sll	$1,$8,3
	srl	$8,$1,29
	bltz	$1,$L233
	add	$25,$25,$8
	bgez	$0,$L233
	addi	$25,$25,-7
$L221:
	mfc2	$9,$31
	addi	$14,$0,-2
	sllv	$1,$1,$9
	sub	$9,$14,$9
	bltz	$1,$L229
	srlv	$8,$1,$9
	srlv	$1,$14,$9
	sub	$8,$8,$1
$L229:
	sub	$9,$0,$9
	add	$9,$9,$9
	addi	$9,$9,1
	add	$25,$25,$8
$L233:
	sll	$8,$25,2
	andi	$8,$8,1023
	j	FUN_80022624
	or	$8,$8,$11
	.globl	FUN_8002284c
FUN_8002284c:
$L237:
	mtc2	$2,$30
	bltz	$2,$L248
	sll	$1,$2,1
	bgez	$1,$L259
	ori	$9,$0,2
	sll	$1,$1,1
	ori	$9,$0,3
	bltz	$1,$L259
	addi	$15,$15,1
	bgez	$0,$L259
	addi	$15,$15,-2
$L248:
	mfc2	$9,$31
	addi	$14,$0,-1
	sllv	$1,$1,$9
	sub	$9,$14,$9
	bltz	$1,$L256
	srlv	$8,$1,$9
	srlv	$1,$14,$9
	sub	$8,$8,$1
$L256:
	sub	$9,$0,$9
	add	$9,$9,$9
	add	$15,$15,$8
$L259:
	sll	$8,$15,2
	andi	$8,$8,1023
	jal	FUN_80022624
	or	$8,$8,$11
	mtc2	$8,$30
	bltz	$8,$L274
	sll	$1,$8,1
	bgez	$1,$L286
	ori	$9,$0,4
	sll	$1,$1,1
	ori	$9,$0,5
	bltz	$1,$L286
	addi	$24,$24,1
	bgez	$0,$L286
	addi	$24,$24,-2
$L274:
	mfc2	$9,$31
	addi	$14,$0,-1
	sllv	$1,$1,$9
	sub	$9,$14,$9
	bltz	$1,$L282
	srlv	$8,$1,$9
	srlv	$1,$14,$9
	sub	$8,$8,$1
$L282:
	sub	$9,$0,$9
	add	$9,$9,$9
	addi	$9,$9,2
	add	$24,$24,$8
$L286:
	sll	$8,$24,2
	andi	$8,$8,1023
	jal	FUN_80022624
	or	$8,$8,$11
	jal	FUN_800227a0
	sll	$0,$0,0
	jal	FUN_800227a0
	sll	$0,$0,0
	jal	FUN_800227a0
	sll	$0,$0,0
	jal	FUN_800227a0
	sll	$0,$0,0
	subu	$1,$5,$12
	bgez	$1,$L321
	srl	$8,$8,22
	.globl	FUN_8002294c
FUN_8002294c:
$L301:
	xori	$8,$8,1023
	sll	$2,$2,2
	srl	$1,$3,30
	or	$2,$2,$1
	sll	$3,$3,2
	bne	$8,$0,$L237
	addi	$10,$10,2
	.globl	FUN_80022968
FUN_80022968:
$L308:
	ori	$8,$0,65024
	lw	$31,0($29)
	addi	$29,$29,4
$L311:
	subu	$1,$5,$13
	bgez	$1,$L317
	sll	$0,$0,0
	sh	$8,0($5)
	bgez	$0,$L311
	addi	$5,$5,2
$L317:
	jr	$31
	or	$2,$0,$0
	.globl	FUN_80022994
FUN_80022994:
$L319:
	bgez	$0,$L322
	or	$1,$0,$31
$L321:
	or	$1,$0,$0
$L322:
	lw	$31,0($29)
	addi	$29,$29,4
	lui	$14,32778
	addiu	$14,$14,25428
	sw	$2,0($14)
	sw	$3,4($14)
	sw	$8,8($14)
	sw	$4,12($14)
	sw	$5,16($14)
	sw	$6,20($14)
	sw	$10,24($14)
	sw	$11,28($14)
	sw	$13,32($14)
	sw	$15,36($14)
	sw	$24,40($14)
	sw	$25,44($14)
	sw	$1,48($14)
	jr	$31
	ori	$2,$0,1
