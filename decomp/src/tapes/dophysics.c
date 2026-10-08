/* DoPhysics__5CTape (0x8007333c) */
typedef struct {
	int x, y, z;
} V;

extern short DAT_800c9670[] __attribute__((section(".data")));
void __apl__8CSVectorRC8CSVector(char *, char *);
void Mask__8CSVector(char *);

void DoPhysics__5CTape(char *t) {
	__apl__8CSVectorRC8CSVector(t + 0x10, t + 0x88);
	Mask__8CSVector(t + 0x10);

	*(V *)(t + 4) = *(V *)(t + 0x180);
	*(int *)(t + 8) += (*(unsigned short *)(t + 0x190) *
	                    DAT_800c9670[(*(unsigned short *)(t + 0x18c) & 0xfff) * 2] / 4096)
	                   << 12;
	*(unsigned short *)(t + 0x18c) += *(unsigned short *)(t + 0x192);
}
