/* getFile__10PREManagerPcPi (0x800663d8) */
#include "names.h"
typedef struct {
	int pad;
	char *pre[16];
	char names[16][16];
} PREManager;

char *PREManager_parsePRE(PREManager *, char *, char *, int *);

char *PREManager_getFile(PREManager *m, char *name, int *size) {
	char *r = 0;
	int i;

	for (i = 0; i < 16; i++)
		if (m->pre[i])
			r = PREManager_parsePRE(m, m->pre[i], name, size);

	return r;
}
