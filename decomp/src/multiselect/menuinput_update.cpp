/* update__9MenuInput (0x80063f58) */
/* MenuInput: a small queue of d-pad presses for the front-end menus. update() samples the
   Left/Right/Up/Down "Pressed" flags of one controller (or of both when mPad >= 2), queues one
   press (1..4) per push and waits for every direction to be released before queueing again. */
#pragma interface
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
	SButton AnalogueLeft, AnalogueRight, Start, Select;
	SButton Crouch, Jump, SmartBomb, SelectWeapon;
	int rest[11];
};

class CItem {
public:
	virtual ~CItem();
};
class MenuInput : public CItem {
public:
	int mCount;          /* 4 */
	int mHeld;           /* 8 */
	int mQueue[64];      /* 0xc */
	int mTail;           /* 0x10c */
	int mHead;           /* 0x110 */
	int mLast;           /* 0x114 */
	uint mPad;           /* 0x118 */
	MenuInput(int);
	~MenuInput();
	void update();
	int getPress();
	void reset();
};

extern SControl DAT_800c0a48[];

void MenuInput::update()
{
	if (!mHeld) {
		mLast = 0;
		if (mPad < 2) {
			if (DAT_800c0a48[mPad].Left.Pressed) mLast = 1;
			if (DAT_800c0a48[mPad].Right.Pressed) mLast = 2;
			if (DAT_800c0a48[mPad].Up.Pressed) mLast = 3;
			if (DAT_800c0a48[mPad].Down.Pressed) mLast = 4;
		} else {
			if (DAT_800c0a48[0].Left.Pressed || DAT_800c0a48[1].Left.Pressed) mLast = 1;
			if (DAT_800c0a48[0].Right.Pressed || DAT_800c0a48[1].Right.Pressed) mLast = 2;
			if (DAT_800c0a48[0].Up.Pressed || DAT_800c0a48[1].Up.Pressed) mLast = 3;
			if (DAT_800c0a48[0].Down.Pressed || DAT_800c0a48[1].Down.Pressed) mLast = 4;
		}
		if (mLast && mCount < 8) {
			mQueue[mHead++] = mLast;
			if (mHead >= 8) mHead = 0;
			mHeld = 1;
			mCount++;
		}
	} else {
		if (mPad < 2) {
			if (!DAT_800c0a48[mPad].Left.Pressed && !DAT_800c0a48[mPad].Right.Pressed &&
			    !DAT_800c0a48[mPad].Up.Pressed && !DAT_800c0a48[mPad].Down.Pressed)
				mHeld = 0;
		} else {
			if (!DAT_800c0a48[0].Left.Pressed && !DAT_800c0a48[0].Right.Pressed &&
			    !DAT_800c0a48[0].Up.Pressed && !DAT_800c0a48[0].Down.Pressed &&
			    !DAT_800c0a48[1].Left.Pressed && !DAT_800c0a48[1].Right.Pressed &&
			    !DAT_800c0a48[1].Up.Pressed && !DAT_800c0a48[1].Down.Pressed)
				mHeld = 0;
		}
	}
}
