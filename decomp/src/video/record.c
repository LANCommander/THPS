/* Video_Record__FP6CBruce (0x8006a118) */
typedef struct CBruce CBruce;

extern int DAT_800d1784;

void Video_Stop__FP6CBruce(CBruce *);
void PutDataChunk__FP6CBruce(CBruce *);

void Video_Record__FP6CBruce(CBruce *b) {
	if (DAT_800d1784 == 1)
		Video_Stop__FP6CBruce(b);
	else
		PutDataChunk__FP6CBruce(b);
}
