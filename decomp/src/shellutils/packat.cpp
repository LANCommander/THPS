/* FUN_800627ec (0x800627ec) flags=-fstructure-noalias */
/* C++ (SHELLUTILS.CPP). SlicedImage method between pack and unpack that THPS1 added (the demo has
   nothing at SHELLUTILS.CPP lines 688-831): loads the slices to a fixed VRAM position (x, y) instead
   of Pack_Pack-allocated space, column by column, then frees the source buffer
   (FUN_80062de8 = removeFromMemory). is_packed stays 0, so unpack won't release the VRAM.
   Codegen notes: sx/sy are function-scope copies assigned in every block (a variable set in
   several blocks becomes CSE's canonical register, so the copies survive: retail's s4/t0);
   curx is declared before remx and remy at its assignment, which fixes the spill-slot order. */
extern "C" {
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
}
typedef unsigned short ushort;
typedef unsigned int uint;

class SlicedImage {
public:
	int **vf;
	int width;
	int height;
	int slice_width;
	int slice_height;
	char *slicedBuffer;
	RECT *sliceTab;
	int num_slices_x;
	int num_slices_y;
	int bpp;
	ushort clut;
	int is_packed;
	int m_removed_from_memory;
	void packAt(int x, int y);
	void removeFromMemory();
};

void *Mem_New(uint, int, int);
extern int DAT_800d1a6c;

void SlicedImage::packAt(int x, int y)
{
	int j;
	int k;
	ushort *data_col;
	ushort *data;
	RECT r;
	int curx;
	int remx;
	int numy;
	int numx;
	int cury;
	int sx;
	int sy;

	is_packed = 0;
	sliceTab = (RECT *)Mem_New(num_slices_y * num_slices_x * sizeof(RECT), 1, 1);
	data_col = (ushort *)slicedBuffer;
	numx = width / slice_width;
	numy = height / slice_height;
	remx = width - numx * slice_width;
	int remy = height - numy * slice_height;
	curx = x;
	DAT_800d1a6c = 1;

	for (j = 0; j < numx; j++)
	{
		data = data_col;
		cury = y;
		for (k = 0; k < numy; k++)
		{
			sx = curx;
			sy = cury;
			cury = sy + slice_height;
			r.x = sx;
			r.y = sy;
			r.w = slice_width;
			r.h = slice_height;
			sliceTab[k * num_slices_x + j].x = sx;
			sliceTab[k * num_slices_x + j].y = sy;
			sliceTab[k * num_slices_x + j].w = slice_width;
			sliceTab[k * num_slices_x + j].h = slice_height;
			LoadImage(&r, (u_long *)data);
			data += slice_width * slice_height;
		}
		if (remy > 0)
		{
			sx = curx;
			sy = cury;
			r.h = remy;
			r.y = sy;
			r.x = sx;
			r.w = slice_width;
			sliceTab[numy * num_slices_x + j].x = sx;
			sliceTab[numy * num_slices_x + j].y = sy;
			sliceTab[numy * num_slices_x + j].w = slice_width;
			sliceTab[numy * num_slices_x + j].h = remy;
			LoadImage(&r, (u_long *)data);
		}
		curx += slice_width;
		data_col += slice_width * height;
	}

	if (remx > 0)
	{
		data = data_col;
		cury = y;
		for (k = 0; k < numy; k++)
		{
			sx = curx;
			sy = cury;
			cury = sy + slice_height;
			r.x = sx;
			r.y = sy;
			r.w = remx;
			r.h = slice_height;
			sliceTab[k * num_slices_x + numx].x = sx;
			sliceTab[k * num_slices_x + numx].y = sy;
			sliceTab[k * num_slices_x + numx].w = remx;
			sliceTab[k * num_slices_x + numx].h = slice_height;
			LoadImage(&r, (u_long *)data);
			data += remx * slice_height;
		}
		if (remy > 0)
		{
			sx = curx;
			sy = cury;
			r.w = remx;
			r.y = sy;
			r.x = sx;
			r.h = remy;
			sliceTab[numy * num_slices_x + numx].x = sx;
			sliceTab[numy * num_slices_x + numx].y = sy;
			sliceTab[numy * num_slices_x + numx].w = remx;
			sliceTab[numy * num_slices_x + numx].h = remy;
			LoadImage(&r, (u_long *)data);
		}
	}
	DAT_800d1a6c = 0;
	DrawSync(0);
	removeFromMemory();
}
