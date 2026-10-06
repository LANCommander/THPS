/* Front_SetSJISName__FPc (0x800116b4) */
/* C++ (RFRONT.CPP). Demo twin; locals from its MAIN.SYM. Converts the 10-character high-score name
   entry buffer to Shift-JIS for the memory card title: trailing blanks are trimmed, embedded holes
   become spaces, A-Z map to full-width letters (0x82, c+31) and spaces to 0x81 0x40. */
extern char DAT_800a42d0[];

void Front_SetSJISName(char *SJISName)
{
	int i;
	for (i = 9; i > 0; i--) {
		if (DAT_800a42d0[i] != ' ' && DAT_800a42d0[i])
			break;
		DAT_800a42d0[i] = 0;
	}
	for (; i >= 0; i--) {
		if (!DAT_800a42d0[i])
			DAT_800a42d0[i] = ' ';
	}
	for (i = 0; i < 10; i++) {
		if (!DAT_800a42d0[i]) {
			*SJISName = 0;
			return;
		}
		if ((unsigned char)(DAT_800a42d0[i] - 'A') < 26) {
			*SJISName++ = 130;
			*SJISName++ = DAT_800a42d0[i] + 31;
		} else if (DAT_800a42d0[i] == ' ') {
			*SJISName++ = 129;
			*SJISName++ = 64;
		}
	}
}
