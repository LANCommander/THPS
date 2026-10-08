/* strNext__Fv (0x80023e88) */
int DAT_800d1654, DAT_800d1660, DAT_800d1630;

int FUN_800911fc(int *, int **);

int strNext(void) {
	int addr;
	int *hdr;

	if (FUN_800911fc(&addr, &hdr))
		return 0;

	DAT_800d1654 = hdr[2];

	if (DAT_800d1654 >= DAT_800d1660)
		DAT_800d1630 = 1;

	return addr;
}
