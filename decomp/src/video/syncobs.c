/* Video_SyncObs__Fi (0x80069534) */
#include "names.h"
typedef struct CBody CBody;

typedef struct {
	char pad[0x1c];
	struct CBruce *other;
} CBruce;

extern CBruce *DAT_800d19a4;
extern CBody *DAT_800d1998, *DAT_800d19b0;

int DAT_800d1de4;

void Ob_ClearInputFlags(CBody *);
void GetDataChunk(CBruce *, int);
void Ob_QuickAI(CBody **);
void Ob_AI(CBody **);

void Video_SyncObs(int count) {
	CBruce *b = DAT_800d19a4;
	CBruce *o;
	int i;

	DAT_800d1de4 = 1;
	o = b->other;

	for (i = 0; i < count; i++) {
		Ob_ClearInputFlags(DAT_800d1998);
		Ob_ClearInputFlags(DAT_800d19b0);
		GetDataChunk(b, -1);

		if (o)
			GetDataChunk(o, -1);

		Ob_QuickAI(&DAT_800d19b0);
		Ob_AI(&DAT_800d1998);
	}

	DAT_800d1de4 = 0;
}
