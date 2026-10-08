/* FUN_800316cc (0x800316cc) */
/* PHYSICS: copies a trick-table entry's flag bits (top 12 bits of its first word) into the
   skater; called twice from HandleTricksNew__6CBruce with &DAT_800a7358[i]. */
struct STrick {
	unsigned Word0; /* trick flags in the top 12 bits */
};

class CBruce {
  public:
	char pad0[0x1ec];
	int m1EC; /* 0x1ec */
	char pad1f0[0x284 - 0x1f0];
	int m284; /* 0x284 */
	int m288; /* 0x288 */
	char pad28c[0x2f0 - 0x28c];
	int m2F0; /* 0x2f0 */
	int m2F4; /* 0x2f4 */
	char pad2f8[0x324 - 0x2f8];
	int m324; /* 0x324 */
	char pad328[0x368 - 0x328];
	unsigned m368; /* 0x368 */
	void SetTrickFlags(STrick *pTrick);
};

void CBruce::SetTrickFlags(STrick *pTrick) {
	unsigned Flags = pTrick->Word0 & 0xfff00000;

	m284 = (Flags & 0x100000) != 0;
	m288 = (Flags & 0x200000) != 0;
	m1EC = (Flags & 0x4000000) != 0;

	if (m284)
		m324 = 0;

	if (Flags & 0x800000) {
		m368 = (m368 & 0xffffff) | 0x80000000;
		m368 &= ~0x4000;
		m368 |= 0x2000;
	}

	m2F0 = (Flags & 0x1000000) != 0;
	m2F4 = (Flags & 0x400000) != 0;
}
