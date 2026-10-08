/* Utils_KillEverythingInBox__FRC7CVectorT0 (0x800483e8) */
typedef struct {
	int x, y, z;
} V;

extern void *DAT_800d1998, *DAT_800d19b0, *DAT_800d1618, *DAT_800d19b4;

int FUN_80048278(V *a, V *b, void *list, int f);

int Utils_KillEverythingInBox(V *a, V *b) {
	int n = 0;

	n += FUN_80048278(a, b, DAT_800d1998, 1);
	n += FUN_80048278(a, b, DAT_800d19b0, 1);
	n += FUN_80048278(a, b, DAT_800d1618, 1);
	n += FUN_80048278(a, b, DAT_800d19b4, 0);
	return n;
}
