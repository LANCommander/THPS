/* FUN_8003159c (0x8003159c) */
/* C++ (PHYSICS.CPP). Called by HandleStickToRail when a trick is in progress (m35C): unless already
   scored (m364), plays the landing sound for anims 62..66 and scores the held trick (m368 & 0xff,
   0x4000/0x2000 states, the same test as the Limit block there) via Trick_Trick from the 44-byte
   trick table, counting it in m424, then sets 0x800 (the 0x4000 state always, the 0x2000 state only when the trick
   has frames; retail's `j L66` is the cross-jumped `m368 |= 0x800` tail).
   Score is declared at function scope and assigned in both arms: a pseudo set twice loses
   sched1's set-once priority boost, so its load stays above the m424 increment as retail has it.) */
typedef unsigned short ushort;
typedef unsigned char uchar;
struct STrick {
	int Flags;                /* 0x00 */
	int Anim;                 /* 0x04 */
	int w2;                   /* 0x08 */
	char *pName;              /* 0x0c */
	int Frames;               /* 0x10 */
	int w5;                   /* 0x14 */
	int MinFrame;             /* 0x18 */
	int Score;                /* 0x1c */
	int w8, w9, w10;
};
extern STrick DAT_800a7358[];
class CBruce {
public:
	char pad0[0x146];
	ushort mAnim;             /* 0x146 */
	char pad148[0x364 - 0x148];
	int m364;                 /* 0x364 */
	int m368;                 /* 0x368 */
	char pad36c[0x424 - 0x36c];
	int m424;                 /* 0x424 */
	void Trick_Trick(int, char *, int, int);
};
int SFX_PlayX(unsigned int, short, int);

extern "C" void FUN_8003159c(CBruce *pBruce)
{
	if (pBruce->m364)
		return;
	if ((ushort)(pBruce->mAnim - 62) < 5)
		SFX_PlayX(162, 0x2000, 0);
	int State = pBruce->m368;
	int Trick = State & 0xff;
	int Score;
	if (State & 0x4000) {
		Score = DAT_800a7358[Trick].Score;
		pBruce->m424++;
		pBruce->Trick_Trick(Trick, DAT_800a7358[Trick].pName, Score, 0);
		pBruce->m368 |= 0x800;
	} else if (State & 0x2000) {
		Score = DAT_800a7358[Trick].Score;
		pBruce->m424++;
		pBruce->Trick_Trick(Trick, DAT_800a7358[Trick].pName, Score, 0);
		if (DAT_800a7358[Trick].Frames)
			pBruce->m368 |= 0x800;
	}
}
