/* M3dZone_LineToItemNotSCached__FP9SLineInfoi (0x800827d4) */
/* C++ (M3DZONE.CPP). Demo twin (opcode-identical but for one lui); locals from its MAIN.SYM.
   Each zone is a box split into up to 20x20 cells; the line is clipped to the box and walked
   cell by cell with a DDA.
   Levers: the cell subtractions (x0 - xL etc.) are written inside the divisions; egcs's PRE
   hoists them to just after the last clip that changes their operands (the demo line table puts
   them on the z1 > zH test), which is what frees a register for zL. The single-cell case uses X/Z
   (not X0/Z0), raising X/Z's priority to s0/s1. The walk's bounds checks are part of the while
   condition (one source line in the demo). */
struct Item;
struct Vector {
	int vx, vy, vz;
};
struct SLineInfo {
	Vector StartCoords;
	Vector EndCoords;
};
struct SZone {
	int Active;
	int xL;
	int zL;
	int xH;
	int zH;
	int CellSize;
	int pad18;
	short NumX;
	short NumZ;
	Item *Cells[20][20];
};
extern SZone DAT_800c4e0c[2];
extern Item *DAT_800d19b0;
extern int DAT_800d20cc;
extern int DAT_800d20d0;
extern int DAT_800d20d4;
extern int DAT_800d20d8;
extern int DAT_800d20dc;
extern int DAT_800d20fc;
extern int DAT_800d2100;
void M3dColij_LineToItem(Item *, SLineInfo *);
int M3dColij_GetLineInfo(SLineInfo *);
extern "C" void FUN_80080328(Item *, SLineInfo *);
extern "C" int FUN_8008b62c(int, int, int);

int M3dZone_LineToItemNotSCached(SLineInfo *pInfo, int CheckEnviroObs)
{
	int x0, x1, z0, z1;
	int xL, xH, zL, zH;
	int X0, X1, Z0, Z1;
	int r0, s0;
	int X, Z;
	int dX, dZ;
	int w, h, l, d;
	int qh, qw;

	DAT_800d2100 = 0;
	DAT_800d20fc = -1;
	if (DAT_800d20dc)
		DAT_800d2100 = 0x400000;
	if (DAT_800d20d4)
		DAT_800d2100 ^= 0x400000;
	if (!DAT_800d20d0)
		DAT_800d2100 ^= 0x200000;
	if (DAT_800d20cc)
		DAT_800d20fc = 0xffefffff;
	if (DAT_800d20d8)
		DAT_800d20fc ^= 0x20000;
	if (CheckEnviroObs)
		M3dColij_LineToItem(DAT_800d19b0, pInfo);
	{
		int EnvIndex;
		for (EnvIndex = 0; EnvIndex < 2; EnvIndex++) {
			if (!DAT_800c4e0c[EnvIndex].Active)
				continue;
			x0 = pInfo->StartCoords.vx;
			x1 = pInfo->EndCoords.vx;
			z0 = pInfo->StartCoords.vz;
			z1 = pInfo->EndCoords.vz;
			xL = DAT_800c4e0c[EnvIndex].xL;
			xH = DAT_800c4e0c[EnvIndex].xH;
			zL = DAT_800c4e0c[EnvIndex].zL;
			zH = DAT_800c4e0c[EnvIndex].zH;
			l = DAT_800c4e0c[EnvIndex].CellSize;
			if ((x0 < xL && x1 < xL) || (x0 > xH && x1 > xH) || (z0 < zL && z1 < zL) || (z0 > zH && z1 > zH))
				continue;
			if (x0 == x1 && z0 == z1) {
				X = (x0 - xL) / l;
				Z = (z0 - zL) / l;
				if (X == DAT_800c4e0c[EnvIndex].NumX)
					X--;
				if (Z == DAT_800c4e0c[EnvIndex].NumZ)
					Z--;
				FUN_80080328(DAT_800c4e0c[EnvIndex].Cells[X][Z], pInfo);
				continue;
			}
			if (x0 < xL) {
				z0 = z0 < z1 ? z0 + FUN_8008b62c(xL - x0, z1 - z0, x1 - x0) : z1 + FUN_8008b62c(x1 - xL, z0 - z1, x1 - x0); x0 = xL;
			}
			if (x1 < xL) {
				z1 = z1 < z0 ? z1 + FUN_8008b62c(xL - x1, z0 - z1, x0 - x1) : z0 + FUN_8008b62c(x0 - xL, z1 - z0, x0 - x1); x1 = xL;
			}
			if (x0 > xH) {
				z0 = z1 < z0 ? z1 + FUN_8008b62c(xH - x1, z0 - z1, x0 - x1) : z0 + FUN_8008b62c(x0 - xH, z1 - z0, x0 - x1); x0 = xH;
			}
			if (x1 > xH) {
				z1 = z0 < z1 ? z0 + FUN_8008b62c(xH - x0, z1 - z0, x1 - x0) : z1 + FUN_8008b62c(x1 - xH, z0 - z1, x1 - x0); x1 = xH;
			}

			if (z0 < zL) {
				x0 = x0 < x1 ? x0 + FUN_8008b62c(zL - z0, x1 - x0, z1 - z0) : x1 + FUN_8008b62c(z1 - zL, x0 - x1, z1 - z0); z0 = zL;
			}
			if (z1 < zL) {
				x1 = x1 < x0 ? x1 + FUN_8008b62c(zL - z1, x0 - x1, z0 - z1) : x0 + FUN_8008b62c(z0 - zL, x1 - x0, z0 - z1); z1 = zL;
			}
			if (z0 > zH) {
				x0 = x1 < x0 ? x1 + FUN_8008b62c(zH - z1, x0 - x1, z0 - z1) : x0 + FUN_8008b62c(z0 - zH, x1 - x0, z0 - z1); z0 = zH;
			}
			if (z1 > zH) {
				x1 = x0 < x1 ? x0 + FUN_8008b62c(zH - z0, x1 - x0, z1 - z0) : x1 + FUN_8008b62c(z1 - zH, x0 - x1, z1 - z0); z1 = zH;
			}

			w = x1 - x0;
			if (w < 0) { dX = -1; w = -w; }
			else dX = 1;
			h = z1 - z0;
			if (h < 0) { dZ = -1; h = -h; }
			else dZ = 1;

			X0 = (x0 - xL) / l;
			X1 = (x1 - xL) / l;
			Z0 = (z0 - zL) / l;
			Z1 = (z1 - zL) / l;
			r0 = (x0 - xL) % l;
			s0 = (z0 - zL) % l;

			if (X0 == DAT_800c4e0c[EnvIndex].NumX) { X0--; r0 += l; }
			if (Z0 == DAT_800c4e0c[EnvIndex].NumZ) { Z0--; s0 += l; }
			if (X1 == DAT_800c4e0c[EnvIndex].NumX) X1--;
			if (Z1 == DAT_800c4e0c[EnvIndex].NumZ) Z1--;

			qw = FUN_8008b62c(w, s0, l);
			qh = FUN_8008b62c(h, r0, l);
			X = X0; Z = Z0;
			d = (x0 < x1 ? qh - h : -qh) + (z0 < z1 ? w - qw : qw);

			while ((X != X1 || Z != Z1) && X >= 0 && X < DAT_800c4e0c[EnvIndex].NumX && Z >= 0 && Z < DAT_800c4e0c[EnvIndex].NumZ) {
				FUN_80080328(DAT_800c4e0c[EnvIndex].Cells[X][Z], pInfo);
				if (d >= 0) { d -= h; X += dX; }
				else { d += w; Z += dZ; }
			}
			if (X >= 0 && X < DAT_800c4e0c[EnvIndex].NumX && Z >= 0 && Z < DAT_800c4e0c[EnvIndex].NumZ)
				FUN_80080328(DAT_800c4e0c[EnvIndex].Cells[X][Z], pInfo);
		}
	}
	return M3dColij_GetLineInfo(pInfo);
}
