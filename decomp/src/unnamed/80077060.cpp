/* FUN_80077060 (0x80077060) size=196 */
/* C++ (COMPETITION). The static teardown (_GLOBAL_.D, 0x80077060) and construction (_GLOBAL_.I,
   0x800770dc) of the global object at 0x800c0fdc; one source covers both. X derives from CClass
   (vtable 0x800a3444) and holds five polymorphic 8-byte elements at +40 (vtable 0x800a3454). Its
   destructor is the implicit one, which never re-stores X's own vptr; only the inlined
   ~CClass store (0x800a3464) remains. The out-of-line copy is FUN_80077130. */
#pragma interface
class CClass {
public:
	virtual ~CClass() {}
};
class E : public CClass {
public:
	int a;
};
class X : public CClass {
public:
	char pad[36];
	E e[5];
	char pad2[200 - 80];
	int f200;
	int f204;
	int f208;
	X()
	{
		f200 = 0;
		f204 = 0;
		f208 = 0;
	}
};
X DAT_800c0fdc;
