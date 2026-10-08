/* Pack_KillSlot__FP6TSPack (0x800495f4) */
int DAT_800d1a68;

void Mem_Delete__FPv(void);

void Pack_KillSlot__FP6TSPack(void) {
	Mem_Delete__FPv();

	DAT_800d1a68 = DAT_800d1a68 - 1;
}
