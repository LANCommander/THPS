/* erase__12VerticalMenu (0x80064f9c) */
struct Sprite {
	int vf;
	int m_w, m_h, m_packed, m_bpp;
	void *m_image;
	void draw(int, int, int, int, int, int);
};
struct VerticalMenuItem {
	Sprite *erase_sprite;
	char string[32];
	int x, y, w, h, baseline, grayed, erase_sprite_x;
};
struct VerticalMenu {
	int vf;
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
	void erase();
};
void VerticalMenu::erase()
{
	int tri_off;
	tri_off = ((list[selected].w >> 1) * font_scale_big) / font_scale + 30;
	if (tick < 61) {
		if (mEraseTri1)
			mEraseTri1->draw(list[selected].x - tri_off - 22, list[selected].y - 34, 0, -1, -1, -1);
		if (mEraseTri2)
			mEraseTri2->draw(list[selected].x + tri_off - 22, list[selected].y - 34, 0, -1, -1, -1);
	}
	for (int i = 0; i < num_items; i++) {
		list[i].erase_sprite->draw(list[i].erase_sprite_x, list[i].y - ((list[i].h >> 1) * font_scale_big) / font_scale - 1, 0, -1, -1, -1);
	}
}
