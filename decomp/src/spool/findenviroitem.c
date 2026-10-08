/* Spool_FindEnviroItem__FUi (0x8006ee88) */
typedef struct {
	char name[10];
	unsigned char f0a, f0b;
	unsigned *models;
	unsigned *f10;
	char *f14;
	char pad[0x28];
} SRegion;

extern SRegion DAT_800bf7a8[];

typedef struct SEnviro {
	char pad[0x16];
	unsigned short model;
	char pad2[3];
	unsigned char region;
	struct SEnviro *next;
} SEnviro;

SEnviro *DAT_800d1eec;

SEnviro *Spool_FindEnviroItem__FUi(unsigned id) {
	SEnviro *e = DAT_800d1eec;
	int cur = -1;
	unsigned *tbl;

	while (e) {
		if (e->region != cur) {
			cur = e->region;
			tbl = DAT_800bf7a8[cur].models;
		}

		if (tbl[e->model] == id)
			return e;

		e = e->next;
	}

	return 0;
}
