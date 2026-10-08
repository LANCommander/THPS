/* FUN_80059758 (0x80059758) */
int DAT_800d1c80;
short DAT_800d1c94;
short DAT_800d1c98;

void FUN_80059618(int a);
void FUN_8004d5d0(int a);
void Pack_Unpack__Fss(short a, short b);

void FUN_80059758(void) {
	FUN_80059618(-1);
	FUN_8004d5d0(DAT_800d1c80);
	Pack_Unpack__Fss(DAT_800d1c94, DAT_800d1c98);
}
