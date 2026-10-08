/* FUN_8005c8dc (0x8005c8dc) */
struct T {
	char pad[128];
	int f;
};

extern struct T DAT_800be478[];
extern char DAT_800bec34[];

int DAT_800d1cac;

void FUN_8005c8bc(void);
void FUN_80065594(char *a, struct T *b, int c);

void FUN_8005c8dc(int a) {
	DAT_800d1cac = a;
	FUN_8005c8bc();
	FUN_80065594(DAT_800bec34, &DAT_800be478[a], DAT_800be478[a].f);
}
