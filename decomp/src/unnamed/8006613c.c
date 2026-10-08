/* FUN_8006613c (0x8006613c) */
typedef struct {
	unsigned char b;
	char pad[15];
} E;

typedef struct {
	char *vt;
	int a[16];
	E e[16];
} X;

extern char DAT_800a2120[];
extern unsigned char DAT_800d1dbc[];

X *FUN_8006613c(X *p) {
	int i;

	p->vt = DAT_800a2120;

	for (i = 0; i < 16; i++) {
		p->a[i] = 0;
		p->e[i].b = DAT_800d1dbc[0];
	}

	return p;
}
