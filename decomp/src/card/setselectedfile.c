/* Card_SetSelectedFile__FPc (0x80014218) */
extern char DAT_800a5848[];
extern char DAT_800a5864[];

void Card_SetSelectedFile__FPc(char *p) {
	DAT_800a5848[22] = p[17];
	DAT_800a5848[23] = p[18];
	DAT_800a5864[22] = p[17];
	DAT_800a5864[23] = p[18];
}
