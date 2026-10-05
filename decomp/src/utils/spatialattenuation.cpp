/* Utils_CalculateSpatialAttenuation__FRC7CVectorii (0x800489e4) */
/* C++ (UTILS.CPP). Demo twin; locals from its MAIN.SYM. Volume for a sound at pos heard from the
   current camera: full inside near, silent past far, linear between; then panned left/right by
   the source's heading in camera space (quieter and flagged when it is behind). The sine table is
   a sized extern so its address is one `la` macro: reorg then fills the branch delay slot with the
   index shift, as retail does. */
extern "C" {
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
}
typedef unsigned int uint;
typedef unsigned short ushort;
struct CVector {
	int vx, vy, vz;
	CVector() {}
	CVector(int x, int y, int z) { vx = x; vy = y; vz = z; }
};
struct SMikeCam {
	int pad;
	CVector Pos;               /* 0x04 */
	char pad10[0x74 - 0x10];
	MATRIX Rot;                /* 0x74 */
	char pad94[164 - 0x94];
};
struct SSinCos {
	short s, c;
};
extern SMikeCam DAT_800c119c[];
extern SSinCos DAT_800c9670;
extern int DAT_800d2048;
int Utils_CrapDist(const CVector &, const CVector &);
extern "C" int FUN_800936d4(int, int);

int Utils_CalculateSpatialAttenuation(const CVector &pos, int near, int far)
{
	int vol;
	CVector cam_pos(DAT_800c119c[DAT_800d2048].Pos.vx << 12, DAT_800c119c[DAT_800d2048].Pos.vy << 12,
		DAT_800c119c[DAT_800d2048].Pos.vz << 12);
	int d = Utils_CrapDist(pos, cam_pos);
	CVector centre;
	short heading;
	uint behind;
	uint left;
	uint right;

	if (near >= d)
		return 0x0fff0fff;
	if (d >= far)
		return 0;
	vol = (((far - d) << 12) - (far - d)) / far;
	gte_SetRotMatrix(&DAT_800c119c[DAT_800d2048].Rot);
	centre.vx = (pos.vx >> 12) - DAT_800c119c[DAT_800d2048].Pos.vx;
	centre.vy = (pos.vy >> 12) - DAT_800c119c[DAT_800d2048].Pos.vy;
	centre.vz = (pos.vz >> 12) - DAT_800c119c[DAT_800d2048].Pos.vz;
	gte_ldlvl(&centre);
	gte_rtir();
	gte_stlvl(&centre);
	if (!(centre.vx | centre.vz))
		return vol | (vol << 16);
	heading = (1024 - FUN_800936d4(centre.vz, centre.vx)) & 4095;
	behind = 0;
	if (heading > 1024 && heading < 3072) {
		behind = 0x80000000;
		vol -= vol >> 4;
	}
	if (heading < 2048) {
		left = vol - ((vol * (&DAT_800c9670)[heading].s) >> 12);
		right = vol;
	} else {
		left = vol;
		right = left + ((vol * (&DAT_800c9670)[heading].s) >> 12);
	}
	return left | (right << 16) | behind;
}
