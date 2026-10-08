/* FUN_8006e7c0 (0x8006e7c0) */
void TrickMessageRefresh__10CPanelData(int *p);

void FUN_8006e7c0(int *p) {
	if (p[226]) {
		p[83] = 1;
		p[84] = 0;
		TrickMessageRefresh__10CPanelData(p);
	} else
		p[83] = 0;
}
