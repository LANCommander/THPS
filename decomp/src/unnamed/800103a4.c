/* FUN_800103a4 (0x800103a4) */
/* Copies the saved preferences (career block DAT_800a6844) into the live game settings
   (DAT_800a4118): two words, the per-player controller settings and both name strings, with the
   first name zero-padded to 11 bytes. */
typedef struct { int a, b, c, d; } SPadPrefs;
typedef struct {
	int w0, w4;
	char pad8[0x110 - 8];
	int x110[2];
	int x118[2];
	SPadPrefs Pad[2];        /* 0x120 */
	char Str[0x184 - 0x140]; /* 0x140 */
	int x184, x188;
	int NameLen;             /* 0x18c */
	char Name[16];           /* 0x190 */
} SGame;
typedef struct {
	char pad0[0x830];
	int w830, w834;
	char pad838[0x940 - 0x838];
	int x940[2];
	int x948[2];
	SPadPrefs Pad[2];        /* 0x950 */
	char Str[0x9b4 - 0x970]; /* 0x970 */
	int x9b4, x9b8;
	int NameLen;             /* 0x9bc */
	char Name[16];           /* 0x9c0 */
} SCareer;
extern SGame DAT_800a4118;
extern SCareer DAT_800a6844;
int FUN_8008b900(char *, const char *, ...);
void FUN_800103a4(void)
{
	int i;
	DAT_800a4118.w0 = DAT_800a6844.w830;
	DAT_800a4118.w4 = DAT_800a6844.w834;
	DAT_800a4118.x184 = DAT_800a6844.x9b4;
	DAT_800a4118.x188 = DAT_800a6844.x9b8;
	for (i = 0; i < 2; i++) {
		DAT_800a4118.x110[i] = DAT_800a6844.x940[i];
		DAT_800a4118.x118[i] = DAT_800a6844.x948[i];
		DAT_800a4118.Pad[i].a = DAT_800a6844.Pad[i].a;
		DAT_800a4118.Pad[i].b = DAT_800a6844.Pad[i].b;
		DAT_800a4118.Pad[i].c = DAT_800a6844.Pad[i].c;
		DAT_800a4118.Pad[i].d = DAT_800a6844.Pad[i].d;
	}
	FUN_8008b900(DAT_800a4118.Name, DAT_800a6844.Name);
	DAT_800a4118.NameLen = DAT_800a6844.NameLen;
	{
		int j;
		for (j = DAT_800a4118.NameLen; j < 11; j++)
			DAT_800a4118.Name[j] = 0;
	}
	FUN_8008b900(DAT_800a4118.Str, DAT_800a6844.Str);
}
