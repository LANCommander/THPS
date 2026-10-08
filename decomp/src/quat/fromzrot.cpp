/* QFromZRot__Fs (0x800775a8) */
/* C++ (QUAT.CPP). Exact demo twin: quaternion for a rotation about one axis. Locals from MAIN.SYM. */
#pragma interface

class CClass {
  public:
	virtual ~CClass() {}
};

class CQuat : public CClass {
  public:
	int x, y, z, w;
	CQuat() {}
	CQuat(int a, int b, int c, int d) {
		x = a;
		y = b;
		z = c;
		w = d;
	}
};

struct SSinCos {
	short s, c;
};

extern SSinCos rcossin_tbl[1]; /* declared <= 8 bytes: one la, as retail */

CQuat QFromZRot(short angle) {
	int cos2 = (rcossin_tbl + ((angle >> 1) & 4095))->c;
	int sin2 = (rcossin_tbl + ((angle >> 1) & 4095))->s;

	return CQuat(0, 0, sin2, cos2);
}
