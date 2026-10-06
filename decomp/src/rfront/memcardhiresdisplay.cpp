/* Front_MemCardHiResDisplay__Fv (0x8001206c) */
/* C++ (RFRONT.CPP), from the demo twin + its MAIN.SYM locals (i, XMid, block `load`, block `up`).
   Hi-res memory-card screen: the save/load progress screen, the background state machine, then
   one case per card state (case 20 = the save-file VerticalMenu with scroll arrows).
   Levers: the arrow text is `if (up && down) ... else sprintf(.., up ? a : b)` with `down` a
   separate block local (keeps up in a1 and XMid in s1); FUN_8008c468 returns int; the
   VerticalMenu ?: count is `n < 6 ? n : 5`; sizeof(VerticalMenu) = 820. */
typedef struct{char pad0[0xc];char*f0c;char*f10;char pad1[0x104-0x14];char*f104;char*f108;char*f10c;char pad2[0x128-0x110];char*f128;char*f12c;char*f130;char*f134;char pad3[0x180-0x138];char*f180;char pad4[0x1c8-0x184];char*f1c8;char*f1cc;char*f1d0;char*f1d4;char pad5[0x1f8-0x1d8];char*f1f8;char*f1fc;char*f200;char pad6[0x244-0x204];char*f244;}S;
class CItem {
public:
	virtual ~CItem();
	void *operator new(unsigned int) throw();
};
class VerticalMenu : public CItem {
public:
	char pad[816];
	virtual void draw();
	VerticalMenu(int, int, int, char **, int, int *, int *, int);
	void erase();
	int getSelected();
	void setString(int, char *);
};
extern "C" {
extern S DAT_800a5d5c;
extern char* DAT_800a5edc[];
extern char* DAT_800a43bc[];
extern char DAT_8009d11c[];
extern char DAT_8009d130[];
extern char DAT_8009d144[];
extern char DAT_800d2474[];
extern int DAT_800d16e4;
}
VerticalMenu* DAT_800d1104;
int DAT_800d1108,DAT_800d110c,DAT_800d1110,DAT_800d111c,DAT_800d1120,DAT_800d1128,DAT_800d1144;
extern "C" {
void FUN_80011214(void);
void FUN_80011570(void);
void FUN_8001d250(int);
void FUN_80061ea0(void);
void FUN_8006b240(void);
void FUN_8006b26c(void);
void FUN_8008b900(char*,char*,char*);
int FUN_8008c468(int);
}
void Front_DirtyRectText(int,int,const char*);
void Front_PrintCentredPrompt(const char*);
void Front_PrintGoBackSelect();
void Front_RestoreBackground();
void Mess_SetScale(int);
void RGBRed();
void Front_MemCardHiResDisplay()
{
	int i;
	int XMid;
	Mess_SetScale(200);
	XMid = DAT_800d1128 >> 1;
	if (DAT_800d111c == 21 && DAT_800d1144 == 2) {
		{
			char *load;
			for (i = 0; i < 2; i++) {
				FUN_8006b240();
				FUN_80061ea0();
				if (DAT_800d1104) DAT_800d1104->erase();
				FUN_8006b26c();
			}
			load = DAT_8009d130;
			FUN_8008c468(0);
			for (i = 0; i < 4; i++) {
				FUN_8006b240();
				FUN_80061ea0();
				FUN_80011214();
				Front_DirtyRectText(XMid, 240, load);
				RGBRed();
				FUN_8006b26c();
			}
		}
		DAT_800d1120 = 24;
		return;
	}
	if (DAT_800d1120 != 26) Front_RestoreBackground();
	{
		int w = DAT_800d1120;
		int v = w;
		if (v != DAT_800d111c) {
			if (v == 15) goto set;
			if (v == 24) {
				DAT_800d1120 = 25;
				return;
			}
			if (v == 25) {
				DAT_800d1120 = 26;
				return;
			}
			if (w != 26) {
				DAT_800d1120 = 24;
				return;
			}
			FUN_80011570();
		set:
			DAT_800d1120 = DAT_800d111c;
		}
	}
	Mess_SetScale(200);
	FUN_8001d250(0);
	switch (DAT_800d111c) {
	case 15:
	case 16:
		FUN_80011214();
		Front_DirtyRectText(XMid, 180, DAT_800a5d5c.f200);
		RGBRed();
		Front_DirtyRectText(XMid, 280, DAT_800a5d5c.f1f8);
		Front_DirtyRectText(XMid, 332, DAT_800a5d5c.f1fc);
		break;
	case 17:
		RGBRed();
		Front_DirtyRectText(XMid, 180, DAT_800a5d5c.f1c8);
		Front_DirtyRectText(XMid, 232, DAT_800a5d5c.f1cc);
		Front_DirtyRectText(XMid, 284, DAT_800a5d5c.f1d0);
		Front_DirtyRectText(XMid, 336, DAT_800a5d5c.f1d4);
		break;
	case 18:
		RGBRed();
		Front_DirtyRectText(XMid, 174, DAT_800a5d5c.f104);
		Front_DirtyRectText(XMid, 226, DAT_800a5d5c.f108);
		Front_DirtyRectText(XMid, 278, DAT_800a5d5c.f10c);
		break;
	case 19:
		RGBRed();
		if (DAT_800d1144 == 2) Front_DirtyRectText(XMid, 220, DAT_800a5d5c.f10);
		else Front_DirtyRectText(XMid, 220, DAT_800a5d5c.f0c);
		if (DAT_800d1128 == 512) Front_PrintCentredPrompt(DAT_800a5d5c.f180);
		break;
	case 20:
		if (!DAT_800d1104) {
			DAT_800d1104 = new VerticalMenu(100, 398, 15, DAT_800a43bc, DAT_800d1108 < 6 ? DAT_800d1108 : 5, 0, 0, 0);
			FUN_8008b900(DAT_800d2474, DAT_800a5d5c.f128, DAT_800a5d5c.f134);
			Front_DirtyRectText(XMid, 380, DAT_800d2474);
		}
		for (i = 0; i < 5; i++) {
			if (i != DAT_800d1104->getSelected() || DAT_800d1110)
				DAT_800d1104->setString(i, DAT_800a43bc[DAT_800d110c + i]);
		}
		if (DAT_800d1108 > 5 && ((DAT_800d16e4 / 20) & 3)) {
			FUN_80011214();
			{
				int up = DAT_800d110c > 0;
				int down = DAT_800d110c < DAT_800d1108 - 5;
				if (up && down) FUN_8008b900(DAT_800d2474, DAT_800a5d5c.f128, DAT_800a5d5c.f134);
				else FUN_8008b900(DAT_800d2474, DAT_800a5d5c.f128, up ? DAT_800a5d5c.f12c : DAT_800a5d5c.f130);
			}
			Front_DirtyRectText(XMid, 380, DAT_800d2474);
		}
		DAT_800d1104->draw();
		if (DAT_800d1128 == 512) Front_PrintGoBackSelect();
		break;
	case 21:
		FUN_80011214();
		Front_DirtyRectText(XMid, 220, DAT_8009d11c);
		RGBRed();
		Front_DirtyRectText(XMid, 280, DAT_800a5d5c.f1f8);
		Front_DirtyRectText(XMid, 332, DAT_800a5d5c.f1fc);
		break;
	case 22:
		RGBRed();
		Front_DirtyRectText(XMid, 220, DAT_800a5d5c.f244);
		if (DAT_800d1128 == 512) Front_PrintCentredPrompt(DAT_800a5d5c.f180);
		break;
	case 23:
		RGBRed();
		Front_DirtyRectText(XMid, 220, DAT_8009d144);
		if (DAT_800d1128 == 512) Front_PrintCentredPrompt(DAT_800a5edc[0]);
		break;
	case 27:
		break;
	}
}
