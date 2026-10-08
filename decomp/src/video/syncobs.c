/* Video_SyncObs__Fi (0x80069534) */
typedef struct CBody CBody;

typedef struct {
	char pad[0x1c];
	struct CBruce *other;
} CBruce;

extern CBruce *DAT_800d19a4;
extern CBody *DAT_800d1998, *DAT_800d19b0;

int DAT_800d1de4;

void Ob_ClearInputFlags__FP5CBody(CBody *);
void GetDataChunk__FP6CBrucei(CBruce *, int);
void Ob_QuickAI__FPP5CBody(CBody **);
void Ob_AI__FPP5CBody(CBody **);

void Video_SyncObs__Fi(int count) {
	CBruce *b = DAT_800d19a4;
	CBruce *o;
	int i;

	DAT_800d1de4 = 1;
	o = b->other;

	for (i = 0; i < count; i++) {
		Ob_ClearInputFlags__FP5CBody(DAT_800d1998);
		Ob_ClearInputFlags__FP5CBody(DAT_800d19b0);
		GetDataChunk__FP6CBrucei(b, -1);

		if (o)
			GetDataChunk__FP6CBrucei(o, -1);

		Ob_QuickAI__FPP5CBody(&DAT_800d19b0);
		Ob_AI__FPP5CBody(&DAT_800d1998);
	}

	DAT_800d1de4 = 0;
}
