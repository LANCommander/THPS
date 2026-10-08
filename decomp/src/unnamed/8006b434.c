/* FUN_8006b434 (0x8006b434) flags=-fstrict-aliasing */
#include "names.h"
struct T {
	char pad[20];
	char *n;
	char q[96];
};

extern struct T DAT_800a5398[];
extern char DAT_800a5c68[];

int DAT_800d1e28;

extern int DAT_800d1114;

void Utils_CopyString(char *a, char *b);
void LaunchGame(void);

void FUN_8006b434(int a, int b) {
	char *n;

	DAT_800d1e28 = a;
	n = DAT_800a5398[a].n;
	DAT_800d1114 = b;
	Utils_CopyString(n, DAT_800a5c68);

	DAT_800a5c68[9] = 0;
	LaunchGame();
}
