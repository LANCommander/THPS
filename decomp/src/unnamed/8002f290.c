/* FUN_8002f290 (0x8002f290) */
/* Scales a score by the per-slot mode word at +0x428: 100%, 75%, 1/2, 1/4, otherwise 1/10. */
typedef struct {
	char pad[0x428];
	int Mode[8];
} S;

int FUN_8002f290(S *p, int i, int v) {
	switch (p->Mode[i]) {
		case 0:
		case 1:
			break;
		case 2:
			v = v * 75 / 100;
			break;
		case 3:
			v /= 2;
			break;
		case 4:
			v /= 4;
			break;
		default:
			v /= 10;
			break;
	}

	return v;
}
