/* __ml__FRC5CQuatT0 (0x8007722c) */
/* C++ (QUAT.CPP). Exact demo twin (the demo reaches the vtables through gp): copy b, multiply in
   place by a with the inline operator*=, return by value. Locals (tempw..tempx, inline q) from MAIN.SYM. */
#pragma interface

class CClass {
  public:
	virtual ~CClass() {}
};

class CQuat : public CClass {
  public:
	int x, y, z, w;
	CQuat() {}
	CQuat &operator*=(const CQuat &q) {
		int tempw = (w * q.w - x * q.x - y * q.y - z * q.z) >> 12;
		int tempx = (w * q.x + x * q.w + y * q.z - z * q.y) >> 12;
		int tempy = (w * q.y + y * q.w + z * q.x - x * q.z) >> 12;
		int tempz = (w * q.z + z * q.w + x * q.y - y * q.x) >> 12;

		x = tempx;
		y = tempy;
		z = tempz;
		w = tempw;
		return *this;
	}
};

CQuat operator*(const CQuat &a, const CQuat &b) {
	CQuat q = b;

	q *= a;
	return q;
}
