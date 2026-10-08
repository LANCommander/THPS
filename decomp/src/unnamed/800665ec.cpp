/* FUN_800665ec (0x800665ec) */
/* C++ (IMAGE.CPP). Sibling of the demo's MakeTransparentClut2 (same locals): reads the 256-entry
   CLUT at (x, y) back from VRAM, turns every colour into an opaque grey of 55% of r+g+b, and
   uploads it again. */
struct RECT {
	short x, y, w, h;
};

extern "C" void *Mem_NewX__FUiii(unsigned int, int, int);
extern "C" void FUN_8004d5d0(void *);
extern "C" int FUN_8008c774(RECT *, void *);
extern "C" int FUN_8008c714(RECT *, void *);

extern "C" void FUN_800665ec(int x, int y) {
	unsigned short *buf = (unsigned short *)Mem_NewX__FUiii(512, 1, 1);
	RECT temp;
	unsigned short *buf2;
	temp.x = x;
	temp.y = y;
	temp.w = 256;
	temp.h = 1;

	FUN_8008c774(&temp, buf);

	buf2 = buf;

	for (int i = 0; i < 256; i++) {
		unsigned int r = (*buf2 >> 10) & 31;
		unsigned int g = (*buf2 >> 5) & 31;
		unsigned int b = *buf2 & 31;
		unsigned int grey = (r + g + b) * 550 / 3000;

		*buf2 = ((grey << 10) + (grey << 5) + grey) | 0x8000;
		buf2++;
	}

	FUN_8008c714(&temp, buf);
	FUN_8004d5d0(buf);
}
