/* PreProcessAnimPacket__FPUiT0 (0x8006ff48) */
typedef struct {
	char pad[4];
	unsigned char f4;
	char pad5;
	unsigned short flags;
	char pad8;
	unsigned char f9, fa, fb;
} STex;

typedef struct {
	int a;
	STex *t;
} SAnimFrame;

typedef struct SAnimNode {
	unsigned *data;
	struct SAnimNode *next;
} SAnimNode;

SAnimNode *DAT_800d1efc;

unsigned *Spool_SkipPackets__FPUi(unsigned *);
void *Mem_NewX__FUiii(int, int, int);

void PreProcessAnimPacket__FPUiT0(unsigned *packet, unsigned *data) {
	STex **tbl = (STex **)(Spool_SkipPackets__FPUi(packet) + 1);
	SAnimNode *node = Mem_NewX__FUiii(8, 0, 1);
	unsigned n, i;

	node->next = DAT_800d1efc;
	node->data = data;
	DAT_800d1efc = node;
	n = *data++;

	for (i = 0; i < n; i++) {
		unsigned m, j;
		SAnimFrame *f;

		data += 2;
		m = *data++;
		f = (SAnimFrame *)data;

		for (j = 0; j < m; j++) {
			f[j].t = tbl[(int)f[j].t];
			f[j].t->flags |= 0x20;
			f[j].t->f4++;
			f[j].t->f9++;
			f[j].t->fa++;
			f[j].t->fb++;
			data += 2;
		}
	}
}
