/* OrientUsing__8CQuadBitRC7CVectorRC7SVECTORiii (0x800284d8) */
struct CVector {
	int x, y, z;
	int Length() const;
};
struct SVECTOR { short vx, vy, vz, pad; };
CVector operator+(const CVector &, const CVector &);
CVector operator-(const CVector &, const CVector &);
CVector operator*(const CVector &, const int &);
CVector operator/(const CVector &, const int &);
struct CQuadBit {
	char pad0[0x18];
	CVector mA;
	char pad1[0x48 - 0x24];
	CVector mB;
	CVector mC;
	CVector mD;
	void OrientUsing(const CVector &Position, const SVECTOR &Normal, int dx, int dy, int Angle);
};
void CQuadBit::OrientUsing(const CVector &Position, const SVECTOR &Normal, int dx, int dy, int Angle)
{
	CVector b1;
	CVector b2;
	int l1;
	int l2;
	b1.x = 0;
	b1.y = -Normal.vz;
	b1.z = Normal.vy;
	b2.x = Normal.vy * Normal.vy + Normal.vz * Normal.vz;
	b2.y = -Normal.vx * Normal.vy;
	b2.z = -Normal.vz * Normal.vx;
	l1 = b1.Length();
	l2 = b2.Length();
	b1 = (b1 * dx) / l1;
	b2 = (b2 * dy) / l2;
	mA = Position - b1 - b2;
	mB = Position + b1 - b2;
	mC = Position - b1 + b2;
	mD = Position + b1 + b2;
}
