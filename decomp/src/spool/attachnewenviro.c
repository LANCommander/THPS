/* AttachNewEnviro__Fi (0x8006f7a4) */
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
	char pad[0x1c];
	struct SEnviro *next;
} SEnviro;

SEnviro *DAT_800d1eec;
int DAT_800d1ee0;
int DAT_800d1ee4[2];

int Spool_GetEnvIndex__Fi(int);

void AttachNewEnviro__Fi(int region) {
	if (!DAT_800d1eec) {
		DAT_800d1eec = (SEnviro *)(DAT_800bf7a8[region].f14 + 12);
	} else {
		SEnviro *head = (SEnviro *)(DAT_800bf7a8[region].f14 + 12);
		SEnviro *p = head;

		while (p->next)
			p = p->next;

		p->next = DAT_800d1eec;
		DAT_800d1eec = head;
	}

	DAT_800d1ee4[Spool_GetEnvIndex__Fi(region)] = DAT_800d1ee0;
}
