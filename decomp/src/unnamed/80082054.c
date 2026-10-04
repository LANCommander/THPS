/* FUN_80082054 (0x80082054) */
extern short DAT_800c7400[];
extern short DAT_800c9670;
extern int DAT_800d2174;
void M3dInit_SetResolution__FUiUi(unsigned int, unsigned int);
void M3dInit_SetFoggingParams__FiiUi(int, int, unsigned int);
void FUN_80082054(void)
{
	int i, j;
	short *out;
	M3dInit_SetResolution__FUiUi(512, 240);
	M3dInit_SetFoggingParams__FiiUi(10, 6000, 2048);
	for (i = 0, out = DAT_800c7400; i < 16; i++)
		for (j = 0; j < 4096; j += 64)
			*out++ = ((&DAT_800c9670)[j * 2] * i) >> 4;
	DAT_800d2174 = 0x80000000;
}
