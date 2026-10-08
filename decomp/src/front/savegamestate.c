/* Front_SaveGameState__Fv (0x8001cbf0) */
typedef struct {
	int x, y, z;
} CVector;

typedef struct {
	int checksum;
	char name[9];
	char level[53];
	char x42;
	char pad[33];
	int x64;
	char pad2[8];
	char x70[1];
} SSaveGame;

extern char *DAT_800d1f84;
extern int DAT_800d19e4;
extern char *DAT_800d19a4;
extern SSaveGame DAT_800a5bdc;

char *Trig_GetPosition__FR7CVectori(CVector *, int);
void FUN_800171e0(char *);
unsigned Front_CalculateGameChecksum__FR9SSaveGame(SSaveGame *);

void Front_SaveGameState(void) {
	CVector v;
	char *s = DAT_800d1f84, *d = DAT_800a5bdc.name;

	while (*s)
		*d++ = *s++;

	*d = 0;
	s = Trig_GetPosition__FR7CVectori(&v, DAT_800d19e4) + 6;
	d = DAT_800a5bdc.level;

	while (*s)
		*d++ = *s++;

	*d = 0;

	if (DAT_800d19a4) {
		DAT_800a5bdc.x64 = *(short *)(DAT_800d19a4 + 0xe6);
		DAT_800a5bdc.x42 = 0;
	}

	FUN_800171e0(DAT_800a5bdc.x70);

	DAT_800a5bdc.checksum = Front_CalculateGameChecksum__FR9SSaveGame(&DAT_800a5bdc);
}
