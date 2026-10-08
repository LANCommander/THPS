/* Utils_GetGroundHeight__FRC7CVectorii (0x800481e8) */
typedef struct {
	int x, y, z;
} V;

typedef struct {
	V start, end;
	char pad[0x68 - 24];
	int hit;
	char pad6c[4];
	int y;
	char pad74[6];
	short ny;
	char pad7c[0x88 - 0x7c];
	char flag;
	char pad2[0xa8 - 0x89];
} SLineInfo;

void M3dColij_InitLineInfo__FP9SLineInfo(SLineInfo *li);
int FUN_800827d4(SLineInfo *li, int n);

int Utils_GetGroundHeight(V *p, int up, int down) {
	SLineInfo li;

	li.start.x = p->x;
	li.start.y = p->y - (up << 12);
	li.start.z = p->z;
	li.end.x = p->x;
	li.end.y = p->y + (down << 12);
	li.end.z = p->z;
	M3dColij_InitLineInfo__FP9SLineInfo(&li);

	li.flag = 0;
	FUN_800827d4(&li, 1);

	if (li.hit && li.ny < -3071)
		return li.y;

	return -1;
}
