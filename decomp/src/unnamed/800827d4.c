/* FUN_800827d4 (0x800827d4) */
typedef struct {
	int x0, y0, z0, x1, y1, z1;
} SLine;

typedef struct {
	int active;
	int minx, minz, maxx, maxz;
	int cell;
	int pad;
	short nx, nz;
	int cells[20][20];
} SGrid;

extern SGrid DAT_800c4e0c[2];
extern int DAT_800d2100, DAT_800d20fc, DAT_800d20dc, DAT_800d20d4, DAT_800d20d0, DAT_800d20cc,
    DAT_800d20d8;
extern int DAT_800d19b0;

int FUN_8008b62c(int, int, int);
void FUN_80080328(int, SLine *);
void M3dColij_LineToItem__FP4ItemP9SLineInfo(int, SLine *);
void M3dColij_GetLineInfo__FP9SLineInfo(SLine *);

void FUN_800827d4(SLine *line, int items) {
	int z0, x1, x0, z1;
	int minx, minz, maxx, maxz, cell;
	int cx, cz, ex, ez, rx, rz, dx, dz, sx, sz, err, a, b;
	int ox0, oz0, ox1, oz1, x, z, t, e;
	int i;

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

	if (items)
		M3dColij_LineToItem__FP4ItemP9SLineInfo(DAT_800d19b0, line);

	for (i = 0; i < 2; i++) {
		if (!DAT_800c4e0c[i].active)
			continue;

		x0 = line->x0;
		x1 = line->x1;
		z0 = line->z0;
		z1 = line->z1;
		minx = DAT_800c4e0c[i].minx;
		maxx = DAT_800c4e0c[i].maxx;
		minz = DAT_800c4e0c[i].minz;
		maxz = DAT_800c4e0c[i].maxz;
		cell = DAT_800c4e0c[i].cell;

		if (x0 < minx && x1 < minx)
			continue;

		if (maxx < x0 && maxx < x1)
			continue;

		if (z0 < minz && z1 < minz)
			continue;

		if (maxz < z0 && maxz < z1)
			continue;

		if (x0 == x1 && z0 == z1) {
			cx = (x0 - minx) / cell;
			cz = (z0 - minz) / cell;

			if (cx == DAT_800c4e0c[i].nx)
				cx--;

			if (cz == DAT_800c4e0c[i].nz)
				cz--;

			FUN_80080328(DAT_800c4e0c[i].cells[cx][cz], line);
			continue;
		}

		if (x0 < minx) {
			z0 = (z0 < z1) ? z0 + FUN_8008b62c(minx - x0, z1 - z0, x1 - x0)
			               : z1 + FUN_8008b62c(x1 - minx, z0 - z1, x1 - x0);
			x0 = minx;
		}

		if (x1 < minx) {
			z1 = (z1 < z0) ? z1 + FUN_8008b62c(minx - x1, z0 - z1, x0 - x1)
			               : z0 + FUN_8008b62c(x0 - minx, z1 - z0, x0 - x1);
			x1 = minx;
		}

		if (maxx < x0) {
			z0 = (z1 < z0) ? z1 + FUN_8008b62c(maxx - x1, z0 - z1, x0 - x1)
			               : z0 + FUN_8008b62c(x0 - maxx, z1 - z0, x0 - x1);
			x0 = maxx;
		}

		if (maxx < x1) {
			z1 = (z0 < z1) ? z0 + FUN_8008b62c(maxx - x0, z1 - z0, x1 - x0)
			               : z1 + FUN_8008b62c(x1 - maxx, z0 - z1, x1 - x0);
			x1 = maxx;
		}

		if (z0 < minz) {
			x0 = (x0 < x1) ? x0 + FUN_8008b62c(minz - z0, x1 - x0, z1 - z0)
			               : x1 + FUN_8008b62c(z1 - minz, x0 - x1, z1 - z0);
			z0 = minz;
		}

		if (z1 < minz) {
			x1 = (x1 < x0) ? x1 + FUN_8008b62c(minz - z1, x0 - x1, z0 - z1)
			               : x0 + FUN_8008b62c(z0 - minz, x1 - x0, z0 - z1);
			z1 = minz;
		}

		if (maxz < z0) {
			x0 = (x1 < x0) ? x1 + FUN_8008b62c(maxz - z1, x0 - x1, z0 - z1)
			               : x0 + FUN_8008b62c(z0 - maxz, x1 - x0, z0 - z1);
			z0 = maxz;
		}

		if (maxz < z1) {
			x1 = (x0 < x1) ? x0 + FUN_8008b62c(maxz - z0, x1 - x0, z1 - z0)
			               : x1 + FUN_8008b62c(z1 - maxz, x0 - x1, z1 - z0);
			z1 = maxz;
		}

		dx = x1 - x0;
		ox1 = x1 - minx;
		oz1 = z1 - minz;

		if (dx < 0) {
			sx = -1;
			dx = -dx;
		} else
			sx = 1;

		dz = z1 - z0;

		if (dz < 0) {
			sz = -1;
			dz = -dz;
		} else
			sz = 1;

		ex = ox1 / cell;
		cx = (x0 - minx) / cell;
		rx = (x0 - minx) % cell;
		cz = (z0 - minz) / cell;
		rz = (z0 - minz) % cell;
		ez = oz1 / cell;

		if (cx == DAT_800c4e0c[i].nx) {
			cx--;
			rx += cell;
		}

		if (cz == DAT_800c4e0c[i].nz) {
			cz--;
			rz += cell;
		}

		if (ex == DAT_800c4e0c[i].nx)
			ex--;

		if (ez == DAT_800c4e0c[i].nz)
			ez--;

		a = FUN_8008b62c(dx, rz, cell);
		b = FUN_8008b62c(dz, rx, cell);

		if (x0 < x1)
			e = b - dz;
		else
			e = -b;

		err = (z0 < z1) ? e + (dx - a) : e + a;
		x = cx;
		z = cz;

		while ((x != ex || z != ez) && x >= 0 && x < DAT_800c4e0c[i].nx && z >= 0 &&
		       z < DAT_800c4e0c[i].nz) {
			FUN_80080328(DAT_800c4e0c[i].cells[x][z], line);

			if (err >= 0) {
				err -= dz;
				x += sx;
			} else {
				err += dx;
				z += sz;
			}
		}

		if (x >= 0 && x < DAT_800c4e0c[i].nx && z >= 0 && z < DAT_800c4e0c[i].nz)
			FUN_80080328(DAT_800c4e0c[i].cells[x][z], line);
	}

	M3dColij_GetLineInfo__FP9SLineInfo(line);
}
