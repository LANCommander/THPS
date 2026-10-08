/* __12VerticalMenuiiiPPciPiT6i (0x800642e8) */
/* C++ (SHELLUTILS.CPP). Demo twin (0.998 by opcode); locals from its MAIN.SYM. Builds a vertical
   menu: measures each item, centres the block between top and bottom, places each item (custom
   x/y if given) with a highlight bar sprite, draws it, then selects the initial item. */
#pragma interface

class CClass {
  public:
	virtual ~CClass();
};

class CItem {
  public:
	virtual ~CItem();
	void *operator new(unsigned int) throw();
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
};

struct VerticalMenuItem {
	Sprite *pBar;  /* 0 */
	char text[32]; /* 4 */
	int x;         /* 36 */
	int y;         /* 40 */
	int w;         /* 44 */
	int h;         /* 48 */
	int yoff;      /* 52 */
	int disabled;  /* 56 */
	int barx;      /* 60 */
};

class VerticalMenu : public CClass {
  public:
	int item_spacing;          /* 0x004 */
	int font_scale;            /* 0x008 */
	int font_scale_big;        /* 0x00c */
	int num_items;             /* 0x010 */
	int old_selected;          /* 0x014 */
	int selected;              /* 0x018 */
	VerticalMenuItem list[12]; /* 0x01c */
	int tick;                  /* 0x31c */
	Sprite *mTri1;             /* 0x320 */
	Sprite *mTri2;
	Sprite *mEraseTri1;
	Sprite *mEraseTri2;
	VerticalMenu(int top, int bottom, int spacing, char **items, int num, int *xlist, int *ylist,
	             int selection);
	void select(int);
};

int Mess_GetFontScale();
int Mess_TextHeight(const char *);
void Mess_SetRGB(unsigned char, unsigned char, unsigned char, int);

extern "C" {
	void FUN_8008e904(char *, char *);
	int FUN_8001da44(char *);
	int FUN_8001dc9c(char *);
	int FUN_8008c468(int);
	int FUN_8001e114(int, int, char *, int, int, int, int);
}

VerticalMenu::VerticalMenu(int top, int bottom, int spacing, char **items, int num, int *xlist,
                           int *ylist, int selection) {
	int tot_h = 0;
	int y;

	item_spacing = spacing;
	num_items = num;
	font_scale = Mess_GetFontScale();
	font_scale_big = font_scale * 320 / 256;

	{
		int i;

		for (i = 0; i < num_items; i++) {
			FUN_8008e904(list[i].text, items[i]);

			list[i].w = FUN_8001da44(items[i]);
			list[i].h = Mess_TextHeight(items[i]);
			list[i].x = xlist ? xlist[i] : 320;
			list[i].yoff = FUN_8001dc9c(list[i].text);
			list[i].disabled = 0;
			tot_h += item_spacing + list[i].h;
		}
	}

	y = (top + bottom - tot_h) / 2;

	{
		int i;

		for (i = 0; i < num_items; i++) {
			list[i].y = y + (list[i].h >> 1);
			y += item_spacing + list[i].h;

			if (ylist)
				list[i].y = ylist[i];
			else
				list[i].y = list[i].y;

			if (xlist[i] && xlist[i] != 320)
				list[i].barx = list[i].x - 230;
			else
				list[i].barx = 45;

			list[i].pBar = new Sprite(
			    list[i].barx, list[i].y - (list[i].h >> 1) * font_scale_big / font_scale - 1, 550,
			    list[i].h * font_scale_big / font_scale + 4, 1, 32, 128);
			FUN_8008c468(0);

			if (list[i].disabled)
				Mess_SetRGB(64, 64, 64, 0);
			else
				Mess_SetRGB(122, 122, 122, 0);

			FUN_8001e114(list[i].x, list[i].y - (list[i].h >> 1) + list[i].yoff, list[i].text, 0, 0,
			             256, 0);
		}
	}

	mTri1 = 0;
	mTri2 = 0;
	mEraseTri1 = 0;
	mEraseTri2 = 0;
	selected = selection;
	select(selection);
}
