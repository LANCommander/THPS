/* FUN_80062de8 (0x80062de8) */
void Mem_Delete__FPv(int a);

void FUN_80062de8(int *p) {
	if (p[12] == 0) {
		p[12] = 1;
		Mem_Delete__FPv(p[5]);
	}
}
