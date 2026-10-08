/* Bit_CalculateSparkVelocity__FR7CVectori (0x80029550) */
typedef struct {
	int x, y, z;
} V;

typedef struct {
	short x, y, z;
} SV;

SV DAT_800d18a4;
short DAT_800d18ac, DAT_800d18ae, DAT_800d18b0;

int Redbook_Rnd__Fi(int);
void Utils_GetVecFromMagDir__FR7CVectoriRC8CSVector(V *, int, SV *);

void Bit_CalculateSparkVelocity(V *out, int mag) {
	SV d = DAT_800d18a4;

	if (DAT_800d18ac)
		d.x += Redbook_Rnd__Fi(DAT_800d18ac) - (DAT_800d18ac >> 1);

	if (DAT_800d18ae)
		d.y += Redbook_Rnd__Fi(DAT_800d18ae) - (DAT_800d18ae >> 1);

	if (DAT_800d18b0)
		d.z += Redbook_Rnd__Fi(DAT_800d18b0) - (DAT_800d18b0 >> 1);

	Utils_GetVecFromMagDir__FR7CVectoriRC8CSVector(out, mag, &d);
}
