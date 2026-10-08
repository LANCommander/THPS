/* Transform__FRC7CVectorRi (0x80027920) */
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>

typedef struct {
	int x, y, z;
} V;

typedef struct {
	int pad;
	int x, y, z;
	char rest[164 - 16];
} Cam;

extern Cam DAT_800c119c[];
extern int DAT_800d2048;

int Transform(const V *in, int *out) {
	V v;
	int z;

	v.x = (in->x >> 12) - DAT_800c119c[DAT_800d2048].x;
	v.y = (in->y >> 12) - DAT_800c119c[DAT_800d2048].y;
	v.z = (in->z >> 12) - DAT_800c119c[DAT_800d2048].z;
	gte_ldlv0(&v);
	gte_rtps();
	gte_stsxy(out);
	gte_stlvnl2(&z);
	return z;
}
