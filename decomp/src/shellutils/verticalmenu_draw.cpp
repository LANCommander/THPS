/* draw__12VerticalMenu (0x80064990) */
/* C++ (SHELLUTILS.CPP). Fuzzy demo twin (0.98); locals and layouts from its MAIN.SYM. Draws a
   vertical text menu: erases the old selection triangles (ticks 63/64), redraws every item (the
   selected one large and orange, greyed ones dark), rebuilds the triangles' erase sprites at
   tick 61 (the selected item's width is re-measured at tick 63), and draws the selection triangles while the tick counts down. */
#pragma interface
typedef unsigned int uint;
class CItem {
public:
	virtual ~CItem();
	void *operator new(uint) throw();
};
class SlicedImage;
class Sprite : public CItem {
public:
	int m_w;
	int m_h;
	int m_packed;
	int m_bpp;
	SlicedImage *m_image;
	Sprite(int, int, int, int, int, int, int);
	~Sprite();
	void draw(int, int, int, int, int, int);
};
struct VerticalMenuItem {
	Sprite *erase_sprite;
	char string[32];
	int x;
	int y;
	int w;
	int h;
	int baseline;
	int grayed;
	int erase_sprite_x;
};
class VerticalMenu {
public:
	void *vptr;
	int item_spacing;
	int font_scale;
	int font_scale_big;
	int num_items;
	int old_selected;
	int selected;
	VerticalMenuItem list[12];
	int tick;
	Sprite *mTri1;
	Sprite *mTri2;
	Sprite *mEraseTri1;
	Sprite *mEraseTri2;
	int mDontDeleteSprites;
	void draw();
};
void Mess_SetFontScale(uint);
void Mess_SetRGB(unsigned char, unsigned char, unsigned char, int);
extern "C" {
void FUN_8001d250(int);
int FUN_8001da44(char *);
void FUN_8001e114(int, int, char *, int, int, int, int);
}

void VerticalMenu::draw()
{
	int tri_off;
	int y;

	FUN_8001d250(0);
	Mess_SetFontScale(font_scale);
	if ((uint)(tick - 63) < 2) {
		tri_off = (list[old_selected].w >> 1) * font_scale_big / font_scale + 30;
		if (mEraseTri1)
			mEraseTri1->draw(list[old_selected].x - tri_off - 22, list[old_selected].y - 34, 0, -1, -1, -1);
		if (mEraseTri2)
			mEraseTri2->draw(list[old_selected].x + tri_off - 22, list[old_selected].y - 34, 0, -1, -1, -1);
		if (tick == 63)
			list[selected].w = FUN_8001da44(list[selected].string);
	}
	{
		int i;
		for (i = 0; i < num_items; i++) {
			list[i].erase_sprite->draw(list[i].erase_sprite_x, list[i].y - (list[i].h >> 1) * font_scale_big / font_scale - 1, 0, -1, -1, -1);
			if (i == selected) {
				Mess_SetRGB(182, 132, 36, 0);
				Mess_SetFontScale(font_scale_big);
				y = list[i].y - ((list[i].h >> 1) - list[i].baseline) * font_scale_big / font_scale;
			} else {
				if (list[i].grayed)
					Mess_SetRGB(64, 64, 64, 0);
				else
					Mess_SetRGB(122, 122, 122, 0);
				y = list[i].y - (list[i].h >> 1) + list[i].baseline;
			}
			FUN_8001e114(list[i].x, y, list[i].string, 0, 0, 256, 0);
			Mess_SetFontScale(font_scale);
		}
	}
	tri_off = (list[selected].w >> 1) * font_scale_big / font_scale + 30;
	if (tick == 61) {
		if (mEraseTri1)
			delete mEraseTri1;
		mEraseTri1 = new Sprite(list[selected].x - ((list[selected].w >> 1) * font_scale_big / font_scale + 30) - 22, list[selected].y - 34, 44, 68, 1, 0, 0);
		if (mEraseTri2)
			delete mEraseTri2;
		mEraseTri2 = new Sprite(list[selected].x + ((list[selected].w >> 1) * font_scale_big / font_scale + 30) - 22, list[selected].y - 34, 44, 68, 1, 0, 0);
	}
	if ((uint)(tick - 16) < 45) {
		if (mTri1)
			mTri1->draw(list[selected].x - tri_off - 22, list[selected].y - 34, 0, -1, -1, -1);
		if (mTri2)
			mTri2->draw(list[selected].x + tri_off - 22, list[selected].y - 34, 0, -1, -1, -1);
	} else if ((uint)(tick - 14) < 2) {
		mEraseTri1->draw(list[selected].x - tri_off - 22, list[selected].y - 34, 0, -1, -1, -1);
		mEraseTri2->draw(list[selected].x + tri_off - 22, list[selected].y - 34, 0, -1, -1, -1);
	}
	if (--tick <= 0)
		tick = 60;
}
