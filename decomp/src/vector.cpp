class CVector {
public:
    int x, y, z;
    CVector& operator+=(const CVector& v);
};
CVector& CVector::operator+=(const CVector& v)
{
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}
