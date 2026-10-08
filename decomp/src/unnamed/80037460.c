/* DoHandPlantPhysics__6CBruce (0x80037460) */
typedef struct {
	int f0, f4, f8, fc;
	char p10[0x70 - 0x10];
	int f70;
	char p74[0x134 - 0x74];
	int f134;
	char p138[0x144 - 0x138];
	short f144;
	unsigned short f146;
	char f148, f149, f14a, f14b, f14c, f14d, f14e;
	unsigned char f14f;
	char p150[0x248 - 0x150];
	int f248, f24c;
	char p250[0x2f0 - 0x250];
	int f2f0, f2f4;
	char p2f8[0x364 - 0x2f8];
	int f364;
	char p368[0x70c - 0x368];
	int f70c;
	char p710[0x740 - 0x710];
	int f740;
	char p744[0x78c - 0x744];
	short f78c, p78e, f790, f792, p794, f796, f798, p79a, f79c;
	char p79e[0x7d8 - 0x79e];
	int f7d8, f7dc, f7e0, f7e4, f7e8, f7ec, f7f0, f7f4, f7f8;
	char p7fc[0x86c - 0x7fc];
	unsigned char *f86c;
} O;

extern void Bail__6CBrucei13ELimitBailVel(O *, int);
extern void FUN_8002f438(O *, int);
extern void Debug_RunAnim__6CBruceii(O *, int, int);
extern void StateTransition__6CBruce13EPhysicsStatei(O *, int, int, int);
extern void Trick_Land__6CBruce(O *);
extern short PingPong__Fiii(int, int, int);

void DoHandPlantPhysics__6CBruce(O *o) {
	int a, b;
	unsigned short t1, t2, t3, t4, t5, t6;
	int s;

	o->f70c = 5;

	if (o->f146 != 0x22 && o->f146 != 0x3f) {
		Bail__6CBrucei13ELimitBailVel(o, 0);
		return;
	}

	if (o->f146 < 0x3e) {
		s = o->f144;

		if (s >= 20)
			if (s < 25) {
				a = o->f248;

				if (a >= 0) {
					if (*o->f86c != 0) {
						o->f144 = PingPong__Fiii(20, 22, 15);
						FUN_8002f438(o, 20);

						o->f248 = o->f248 + 1;

						if (o->f248 >= 21) {
							Bail__6CBrucei13ELimitBailVel(o, 0);
							Debug_RunAnim__6CBruceii(o, 0x38, 0x1602);

							o->f24c = 9;
							return;
						}
					} else
						o->f248 = -a;
				}
			}
	}

	if (o->f14f != 0 || (o->f146 < 0x3e && o->f144 >= 31)) {
		b = o->f248;
		o->f740 = 0;
		o->f70 = (40 - b * 3) << 12;
		StateTransition__6CBruce13EPhysicsStatei(o, 0, 0x1614, b);

		o->f364 = 1;
		Trick_Land__6CBruce(o);

		o->f4 = o->f4 + o->f7f0 * 30;
		o->f8 = o->f8 + o->f7f4 * 30;
		o->fc = o->fc + o->f7f8 * 30;

		if (!(o->f146 < 0x3e)) {
			o->f2f0 = 0;
			o->f2f4 = 0;
			o->f134 = o->f134 ^ 2;
			o->f790 = -o->f7d8;
			o->f7d8 = o->f790;
			o->f796 = -o->f7dc;
			o->f7dc = o->f796;
			o->f79c = -o->f7e0;
			o->f7e0 = o->f79c;
			o->f78c = -o->f7e4;
			o->f7e4 = o->f78c;
			o->f792 = -o->f7e8;
			o->f7e8 = o->f792;
			o->f798 = -o->f7ec;
			o->f7ec = o->f798;
			Debug_RunAnim__6CBruceii(o, 0, 0x162b);
		}
	}
}
