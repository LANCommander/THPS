typedef struct { int x, y, z; } CVector;
CVector *op(CVector *p1, const CVector *p2)
{
    p1->x -= p2->x; p1->y -= p2->y; p1->z -= p2->z; return p1;
}
