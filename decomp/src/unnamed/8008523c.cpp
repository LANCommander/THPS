/* FUN_8008523c (0x8008523c) */
/* C++ (M3D.CPP, between M3d_BuildTransform and M3d_PreprocessWibblyTextures). Looks up a face's
   wibble offset: the high nibble of byte 3 picks a 64-entry row of a short table (0 = none), the
   low nibble phase-shifts the global counter DAT_800d21c4 into it. */
int DAT_800d21c4;
extern short DAT_800c7400[][64];
extern "C" int FUN_8008523c(unsigned char *p)
{
	int hi = p[3] >> 4;
	int lo = p[3] & 15;
	if (hi) {
		int i = (DAT_800d21c4 + lo * 4) & 63;
		short *row = DAT_800c7400[hi];
		return row[i];
	}
	return 0;
}
