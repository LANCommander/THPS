/* FUN_80023fb0 (0x80023fb0) */
int DAT_800d1680;

int FUN_80023fb0(int a) {
	int t = (a * DAT_800d1680) / 128;

	if (t > 16383)
		t = 16383;

	return t;
}
