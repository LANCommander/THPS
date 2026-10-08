/* __6CSuper (0x80043d04) */
/* C++: constructor of a CBody-derived class (vtable 0x800a0574). */
#pragma interface

typedef unsigned char uchar;
typedef unsigned short ushort;

class CItem {
  public:
	ushort mFlags;
	char pad2[0x48 - 2];
	CItem();
	virtual ~CItem();
};

class CBody : public CItem {
  public:
	char pad4c[0x134 - 0x4c];
	CBody();
	virtual ~CBody();
};

class CObj : public CBody {
  public:
	int m134;
	char pad138[0x14e - 0x138];
	uchar m14e;
	uchar m14f;
	int m150;
	CObj();
	virtual ~CObj();
};

CObj::CObj() {
	m134 = 0;
	m150 = 0x10000;
	m14e = 1;
	m14f = 1;
	mFlags |= 2;
}
