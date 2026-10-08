/* FUN_80062de8 (0x80062de8) */
void FUN_8004d5d0(int a);

void FUN_80062de8(int *p) {
	if (p[12] == 0) {
		p[12] = 1;
		FUN_8004d5d0(p[5]);
	}
}
