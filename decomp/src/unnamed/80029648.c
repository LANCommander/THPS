/* Bit_SetSparkSize__FUi (0x80029648) */
int DAT_800d18b4;

void Bit_SetSparkSize__FUi(int a) {
	DAT_800d18b4 = (a << 16) | a;
}
