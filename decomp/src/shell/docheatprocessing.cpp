/* Shell_DoCheatProcessing__Fv (0x80078304) */
/* C++ (SHELL.CPP). Demo twin for the key part (THPS1 adds the cheat table); locals from its
   MAIN.SYM. Each newly pressed pad-1 button feeds its key into frug's rolling hash; when the hash
   hits a known cheat code the matching cheat is toggled. Returns whether a cheat fired. */
typedef unsigned char uchar;
typedef unsigned int uint;
struct SButton {
	uchar Pressed;
	uchar Triggered;
	int PressedTime;
	int ReleasedTime;
	int TriggeredTime;
};
struct SControl {
	SButton Triangle, Square, Circle, X;
	SButton LeftOne, LeftTwo, RightOne, RightTwo;
	SButton Left, Right, Up, Down;
	char pad[364 - 192];
};
extern SControl DAT_800c0a48[2];
uint DAT_800d1fec;
extern int DAT_800d1d24;
extern int DAT_800d1720;
extern int DAT_800d1710;
extern int DAT_800d1924;
extern int DAT_800d172c;
extern int DAT_800d1724;
extern int DAT_800d1708;
void frug(uint);

int Shell_DoCheatProcessing()
{
	int Result = 1;

	if (DAT_800c0a48[0].Up.Triggered)
		frug(0x01234567);
	else if (DAT_800c0a48[0].Right.Triggered)
		frug(0xab432901);
	else if (DAT_800c0a48[0].Down.Triggered)
		frug(0x776643d1);
	else if (DAT_800c0a48[0].Left.Triggered)
		frug(0x93fe1682);
	else if (DAT_800c0a48[0].Triangle.Triggered)
		frug(0x31415926);
	else if (DAT_800c0a48[0].Circle.Triggered)
		frug(0xdeadbeef);
	else if (DAT_800c0a48[0].X.Triggered)
		frug(0xb87610db);
	else if (DAT_800c0a48[0].Square.Triggered)
		frug(0x03185332);
	else
		return 0;
	switch (DAT_800d1fec) {
	case 0x63e4f9c8:
		DAT_800d172c ^= 1;
		break;
	case 0x1f71e119:
		DAT_800d1720 ^= 1;
		break;
	case 0x9c69b980:
		DAT_800d1724 ^= 1;
		break;
	case 0x7f361998:
		if (DAT_800d1924 == 10)
			DAT_800d1924 = 0;
		else
			DAT_800d1924 = 10;
		break;
	case 0xa7053a01:
		DAT_800d1708 ^= 1;
		break;
	case 0x259f7af5:
		if (DAT_800d1924 == 13)
			DAT_800d1924 = 0;
		else
			DAT_800d1924 = 13;
		break;
	case 0x021a16ed:
		DAT_800d1710 ^= 1;
		break;
	case 0x52265053:
		DAT_800d1d24 = 1;
		break;
	default:
		Result = 0;
		break;
	}
	return Result;
}
