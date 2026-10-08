/* FUN_8004f578 (0x8004f578) */
extern short **OffsetList;

int FUN_8004f578(unsigned short *p) {
	unsigned a;

	if (p[-1] == 11) {
		a = p[1];

		if (*OffsetList[a] == 10)
			return a;

		return p[2];
	}

	return p[1];
}
