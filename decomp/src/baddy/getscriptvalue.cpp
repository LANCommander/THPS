/* GetScriptValue__6CBaddy (0x80040c68) */
/* C++ (BADDY.CPP). Demo twin; locals from its MAIN.SYM. Reads the next script word: a literal value,
   or (0x2000 set, 0x8000 clear) a variable number resolved through the virtual GetVariable. */
#pragma interface

typedef unsigned short ushort;

class CItem {
  public:
	char pad0[0x48];
	virtual ~CItem();
	virtual void Virtual2();
	virtual void AI();
	virtual void Virtual4();
	virtual void Virtual5();
	virtual void Virtual6();
	virtual void Virtual7();
	virtual void Virtual8();
	virtual void SetVariable(ushort);
	virtual int GetVariable(ushort);
};

class CBaddy : public CItem {
  public:
	char pad4c[0x1b0 - 0x4c];
	ushort *mpScript; /* 0x1b0 */
	int GetScriptValue();
};

int CBaddy::GetScriptValue() {
	ushort value = *mpScript++;

	if (!(value & 0x8000)) {
		if (value & 0x2000)
			value = GetVariable(value);
	}

	return value;
}
