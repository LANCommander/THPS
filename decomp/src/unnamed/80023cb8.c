/* FUN_80023cb8 (0x80023cb8) */
int DAT_800d222c;
int DAT_800d1668;
unsigned char DAT_800d167c;

extern int DAT_800d1698;
extern int DAT_800d169c;
extern int DAT_800d16a0;

void FUN_80023d3c(void);
void FUN_8009028c(int a);
void FUN_8009035c(void (*f)(void));
void FUN_800911cc(int a, int b);
void FUN_800907cc(int a, int b, int c, int d, int e);
void strKickCD__Fv(void);
void FUN_8008f3a0(int a, int b);

void FUN_80023cb8(void) {
	FUN_8009028c(0);
	FUN_8009035c(FUN_80023d3c);
	FUN_800911cc(DAT_800d222c, DAT_800d1668);
	FUN_800907cc(DAT_800d167c, 0, -1, 0, 0);

	DAT_800d1698 = 0;
	DAT_800d169c = 1;
	DAT_800d16a0 = 0;
	strKickCD__Fv();
	FUN_8008f3a0(12, 0);
}
