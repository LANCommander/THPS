/* Trig_ResetCPCollisionFlags__Fi (0x80044994) */
typedef struct CP {
	int pad0;
	unsigned char coll, exec;
	char pad6[14];
	struct CP *next;
} CP;

CP *DAT_800d19f8;

void Trig_ResetCPCollisionFlags(int m) {
	CP *p;

	for (p = DAT_800d19f8; p; p = p->next)
		p->coll &= ~m;
}
