/* Card_CheckStatus__Fii (0x80015278) */
#include "names.h"
int DAT_800d1394, DAT_800d1384, DAT_800d1390, DAT_800d1380, DAT_800d13bc;

extern int DAT_800d10f4;

int FUN_8008e914(int);
int _card_event(void);
void _clear_event(void);
int FUN_8008f0cc(int);
void _clear_event_x(void);
void FUN_8008ea68(int);
void _card_event_x(void);

int Card_CheckStatus(int a, int b) {
	int s0 = a * 16 + b;
	int ev;

	switch (DAT_800d1394) {
		case 0:
			FUN_8008e914(s0);

			DAT_800d1394 = 1;
			DAT_800d13bc = 0;
			DAT_800d1380 = 0;
			break;
		case 1:
			ev = _card_event();

			if (ev == 0)
				break;

			switch (ev) {
				case 1:
					DAT_800d1390 = 1;

					if (DAT_800d1384 == 1)
						DAT_800d1394 = 4;
					else
						DAT_800d1394 = 2;

					break;
				case 2:
					DAT_800d1390 = -3;
					DAT_800d1394 = 4;
					DAT_800d1384 = 0;
					break;
				case 3:
					DAT_800d1390 = -1;
					DAT_800d1394 = 4;
					DAT_800d1384 = 0;
					break;
				case 4:
					DAT_800d10f4 = 0;
					DAT_800d1390 = 2;
					_clear_event_x();
					FUN_8008ea68(s0);
					_card_event_x();

					DAT_800d1394 = 2;
					DAT_800d1384 = 0;
					break;
				default:
					DAT_800d1390 = -3;
					DAT_800d1394 = 4;
					DAT_800d1384 = 0;
					break;
			}

			break;
		case 2:
			_clear_event();
			FUN_8008f0cc(s0);

			DAT_800d1394 = 3;
			DAT_800d13bc = 0;
			break;
		case 3:
			ev = _card_event();

			if (ev == 0)
				break;

			DAT_800d1394 = 4;

			switch (ev) {
				case 1:
					DAT_800d1384 = 1;
					break;
				case 2:
					DAT_800d1390 = -3;
					DAT_800d1384 = 0;
					break;
				case 3:
					DAT_800d1390 = -1;
					DAT_800d1384 = 0;
					break;
				case 4:
					DAT_800d1390 = -2;
					DAT_800d1384 = 0;
					break;
				default:
					DAT_800d1390 = -3;
					DAT_800d1384 = 0;
					break;
			}

			break;
		case 4:
			DAT_800d1380 = DAT_800d1390;
			DAT_800d1394 = 0;
			break;
	}

	return DAT_800d1380;
}
