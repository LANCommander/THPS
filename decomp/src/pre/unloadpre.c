/* unloadPRE__10PREManagerPc (0x80066338) */
/* PREManager::unloadPRE (PRE.CPP), as C: frees the archive loaded under pre_name and clears its slot. */
typedef struct {
	int pad;
	char *pre[16];
	char names[16][16];
} PREManager;

extern char DAT_800d1dbc[];

int FUN_8008f6fc(char *, char *);
void Mem_Delete__FPv(void *);

void unloadPRE__10PREManagerPc(PREManager *m, char *name) {
	int i;

	for (i = 0; i < 16; i++) {
		char *n = m->names[i];

		if (!FUN_8008f6fc(n, name)) {
			n[0] = DAT_800d1dbc[0];

			if (m->pre[i])
				Mem_Delete__FPv(m->pre[i]);

			m->pre[i] = 0;
			return;
		}
	}
}
