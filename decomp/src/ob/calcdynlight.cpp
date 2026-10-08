/* CalculateDynamicLighting__6CBrucePUiP4Item (0x800425c0) */
typedef unsigned int uint;

typedef struct {
	char pad[0x24];
	uint *ctab;
	char pad2[0x40 - 0x28];
} E;

extern E DAT_800bf7a8[] __attribute__((section(".data")));

struct Item {
	char pad[0x1b];
	unsigned char type;
};

class CBase {
  public:
	char pad[0x48];
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
};

class CBruce : public CBase {
  public:
	char pad4c[0x87c - 0x4c];
	int mLight;
	void CalculateDynamicLighting(uint *p_face, Item *p_item);
};

void CBruce::CalculateDynamicLighting(uint *p_face, Item *p_item) {
	unsigned short f = *(unsigned short *)p_face;

	if (f & 0x800) {
		uint *pColourTable = DAT_800bf7a8[p_item->type].ctab;
		int vertices = 4;

		mLight = 0;

		if (f & 0x10)
			vertices = 3;

		{
			int i;

			for (i = 0; i < vertices; i++) {
				uint rgb = pColourTable[((unsigned char *)p_face)[8 + i]] & 0xffffff;

				mLight = mLight + (rgb & 255) + ((rgb >> 8) & 255) + (rgb >> 16);
			}
		}

		mLight = mLight / (vertices * 3);
	} else {
		uint rgb = p_face[2] & 0xffffff;

		mLight = (int)((rgb & 255) + ((rgb >> 8) & 255) + (rgb >> 16)) / 3;
	}

	mLight = mLight * 3;
	v4();
}
