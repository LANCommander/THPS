/* FUN_8006dc78 (0x8006dc78) */
typedef struct P {
	char pad[0x1c];
	struct P *next;
	char pad2[0x924 - 0x20];
	char sub[8];
	unsigned short sel;
	char pad3[0xa88 - 0x92e];
	char a[0x4c];
	char b[1];
} P;

extern int DAT_800d1700;
extern int DAT_800d140c;
extern int DAT_800d173c;
extern P *DAT_800d19a4;

int DAT_800d1e5c, DAT_800d1e64;

void DisplayTapesSkate__Fv(void);
void FUN_8001e07c(char *);
void FUN_8001e100(char *, int);
void FUN_8006c610(int, int, int, int, int, int, int, int);
void FUN_8006ca78(P *, int, int);
void FUN_8006d0c8(P *, int, int);
void FUN_8006d39c(P *, int, int);
void FUN_8006d704(P *, int, int);
void FUN_8006d938(char *, P *, int, int);
void Panel_ReplayInstructions__Fv(void);
void TrickTips_Display__Fv(void);

void FUN_8006dc78(void) {
	P *s2;
	char *s3;

	if (DAT_800d1700) {
		s2 = DAT_800d19a4;
		Panel_ReplayInstructions__Fv();

		if (s2) {
			s3 = (char *)s2 + 0xa88;

			do {
				FUN_8001e07c(s3);
				FUN_8006d704(s2, 256, 90);
				DisplayTapesSkate__Fv();

				if (DAT_800d140c) {
					DAT_800d1e64 = 30;
					DAT_800d1e5c = 30;
					return;
				}

				switch (DAT_800d173c * 2 + s2->sel) {
					case 0:
					case 1:
						TrickTips_Display__Fv();
						FUN_8006d0c8(s2, 256, 224);
						FUN_8006d938(s2->sub, s2, 256, 205);
						FUN_8006ca78(s2, 25, 45);
						FUN_8006d39c(s2, 256, 48);
						FUN_8001e100(s3, 240);
						FUN_8001e100((char *)s2 + 0xad4, 240);
						break;
					case 2:
						FUN_8006d0c8(s2, 384, 224);
						FUN_8006d938(s2->sub, s2, 384, 205);
						FUN_8006ca78(s2, 358, 45);
						FUN_8001e100(s3, 240);
						FUN_8001e100((char *)s2 + 0xad4, 240);
						break;
					case 4:
						FUN_8006d938(s2->sub, s2, 256, 205);
						FUN_8006d0c8(s2, 256, 224);
						FUN_8006ca78(s2, 25, 145);
						FUN_8006d39c(s2, 452, 150);
						FUN_8001e100(s3, 240);
						FUN_8001e100((char *)s2 + 0xad4, 240);
						break;
					case 6:
						FUN_8006d0c8(s2, 128, 224);
						FUN_8006d938(s2->sub, s2, 128, 205);
						FUN_8006ca78(s2, 112, 150);
						FUN_8006d39c(s2, 55, 155);
						FUN_8001e100(s3, 240);
						FUN_8001e100((char *)s2 + 0xad4, 240);
						FUN_8006c610(256, 0, 256, 120, 30, 30, 30, 1);
						break;
					case 8:
						FUN_8006d0c8(s2, 256, 224);
						FUN_8006d938(s2->sub, s2, 256, 205);
						FUN_8006ca78(s2, 70, 175);
						FUN_8006d39c(s2, 133, 217);
						FUN_8001e100(s3, 240);
						FUN_8001e100((char *)s2 + 0xad4, 240);
						break;
					case 3:
						FUN_8006d0c8(s2, 128, 224);
						FUN_8006d938(s2->sub, s2, 128, 205);
						FUN_8006ca78(s2, 25, 45);
						FUN_8006d39c(s2, 256, 48);
						FUN_8001e100(s3, 240);
						FUN_8001e100((char *)s2 + 0xad4, 240);
						break;
					case 5:
						FUN_8006d938(s2->sub, s2, 256, 85);
						FUN_8006d0c8(s2, 256, 104);
						FUN_8006ca78(s2, 25, 45);
						FUN_8006d39c(s2, 452, 50);
						FUN_8001e100(s3, 118);
						FUN_8001e100((char *)s2 + 0xad4, 118);
						break;
					case 7:
						FUN_8006d0c8(s2, 384, 104);
						FUN_8006d938(s2->sub, s2, 384, 85);
						FUN_8006ca78(s2, 276, 45);
						FUN_8006d39c(s2, 457, 50);
						FUN_8006c610(0, 120, 257, 2, 30, 30, 30, 1);
						FUN_8006c610(0, 120, 257, 120, 20, 20, 20, 1);
						FUN_8006c610(256, 119, 512, 2, 30, 30, 30, 1);
						FUN_8001e100(s3, 122);
						FUN_8001e100((char *)s2 + 0xad4, 122);
						break;
					case 9:
						FUN_8006d0c8(s2, 256, 154);
						FUN_8006d938(s2->sub, s2, 256, 130);
						FUN_8006ca78(s2, 315, 43);
						FUN_8006d39c(s2, 371, 85);
						FUN_8001e100(s3, 152);
						FUN_8001e100((char *)s2 + 0xad4, 152);
						break;
				}

				s2 = s2->next;
				s3 = (char *)s2 + 0xa88;
			} while (s2);
		}
	}
}
