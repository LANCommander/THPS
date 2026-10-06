/* GetStats__6CBrucei (0x80041ce0) */
/* C++ (MECH.CPP). Demo twin; locals from its MAIN.SYM. Fills player Skater's four stat bytes: in a
   career game, from the best board the skater's tape count has unlocked; otherwise all 3. */
typedef unsigned char uchar;
struct SBoard {
	uchar Req;                 /* tapes needed */
	char p1[3];
	uchar Stat0;               /* 4 */
	char p5[3];
	uchar Stat1;               /* 8 */
	char p9[3];
	uchar Stat2;               /* 12 */
	char p13[3];
	uchar Stat3;               /* 16 */
	char p17[32 - 17];
};
struct SSkater {
	char pad0[92];
	SBoard Boards[7];          /* 92 */
	char pad[340 - 92 - 7 * 32];
};
struct SSkaterCareer {
	char pad0[8];
	uchar NumTapes;            /* 8 */
	char pad9[14 - 9];
};
struct SStats {
	uchar s[5];
};
extern SSkater DAT_800a44fc[];
extern SSkaterCareer DAT_800a6844[];
extern SStats DAT_800a8240[];
extern int DAT_800d1780;
struct CBruce {
	char pad0[0x2e8];
	int mSkaterIndex;          /* 0x2e8 */
	void GetStats(int Skater);
};

void CBruce::GetStats(int Skater)
{
	if (DAT_800d1780 == 1) {
		int highest_board = 0;
		while (highest_board < 7) {
			if (DAT_800a6844[mSkaterIndex].NumTapes < DAT_800a44fc[mSkaterIndex].Boards[highest_board + 1].Req)
				break;
			highest_board++;
		}
		DAT_800a8240[Skater].s[0] = DAT_800a44fc[mSkaterIndex].Boards[highest_board].Stat0;
		DAT_800a8240[Skater].s[1] = DAT_800a44fc[mSkaterIndex].Boards[highest_board].Stat1;
		DAT_800a8240[Skater].s[2] = DAT_800a44fc[mSkaterIndex].Boards[highest_board].Stat2;
		DAT_800a8240[Skater].s[3] = DAT_800a44fc[mSkaterIndex].Boards[highest_board].Stat3;
	} else {
		DAT_800a8240[Skater].s[0] = 3;
		DAT_800a8240[Skater].s[1] = 3;
		DAT_800a8240[Skater].s[2] = 3;
		DAT_800a8240[Skater].s[3] = 3;
	}
}
