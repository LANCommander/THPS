/* GetStats__6CBrucei (0x80041ce0) */
/* C++ (MECH.CPP). Demo twin; locals from its MAIN.SYM. Fills player Skater's four stat bytes: in a
   career game, from the best board the skater's tape count has unlocked; otherwise all 3. */
typedef unsigned char uchar;

struct SBoard {
	char *File;
	char *Name;
	uchar Req; /* tapes needed */
	int Stats[4];
	int pad;
};

struct SSkater {
	char pad0[0x54];
	SBoard Boards[8];
	char pad[340 - 0x54 - 8 * 32];
};

struct SSkaterCareer {
	char pad0[8];
	uchar NumTapes; /* 8 */
	char pad9[14 - 9];
};

struct SStats {
	uchar s[5];
};

extern SSkater DAT_800a44fc[];
extern SSkaterCareer GCareer[];
extern SStats DAT_800a8240[];
extern int GNumberOfPlayers;

struct CBruce {
	char pad0[0x2e8];
	int mSkaterIndex; /* 0x2e8 */
	void GetStats(int Skater);
};

void CBruce::GetStats(int Skater) {
	if (GNumberOfPlayers == 1) {
		int highest_board = 0;

		while (highest_board < 7) {
			if (GCareer[mSkaterIndex].NumTapes <
			    DAT_800a44fc[mSkaterIndex].Boards[highest_board + 1].Req)
				break;

			highest_board++;
		}

		DAT_800a8240[Skater].s[0] = DAT_800a44fc[mSkaterIndex].Boards[highest_board].Stats[0];
		DAT_800a8240[Skater].s[1] = DAT_800a44fc[mSkaterIndex].Boards[highest_board].Stats[1];
		DAT_800a8240[Skater].s[2] = DAT_800a44fc[mSkaterIndex].Boards[highest_board].Stats[2];
		DAT_800a8240[Skater].s[3] = DAT_800a44fc[mSkaterIndex].Boards[highest_board].Stats[3];
	} else {
		DAT_800a8240[Skater].s[0] = 3;
		DAT_800a8240[Skater].s[1] = 3;
		DAT_800a8240[Skater].s[2] = 3;
		DAT_800a8240[Skater].s[3] = 3;
	}
}
