/* FUN_80063290 (0x80063290) */
extern int DAT_800d1a90;
extern int DAT_800d1a8c;

int Get256SlotNumber__FUs(unsigned short a);
void FUN_80061c98(int a, int b);

void FUN_80063290(char *p) {
	int n = Get256SlotNumber__FUs(*(unsigned short *)(p + 40));

	FUN_80061c98(DAT_800d1a8c, DAT_800d1a90 + n);
}
