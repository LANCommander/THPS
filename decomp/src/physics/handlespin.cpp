/* HandleSpin__6CBruce (0x800323e0) flags=-fstructure-noalias */
/* C++ (PHYSICS.CPP). Demo twin (fuzzy), locals from its MAIN.SYM. Called from DoPhysics right
   after FRUVectorsFromRotMatrix. Spinning and leaning: THPS1 replaces the demo's rotate-speed
   loop with L2/R2 tap turns (mTapTurn counts queued 180s; each frame rotates the heading and
   tallies the angle, scoring a 180 every 2048 units). Otherwise it picks the turn rate and the
   maximum lean from the board's turning stat (on the ground) or the shoulder buttons (in the
   air), leans toward the analogue target or the d-pad direction, decays the lean when nothing
   is pressed, then (inline here; a separate CalcAnimLeanFrame in the demo) picks the lean anim
   frame, and finally sets the pitch from up/down.
   Levers: every MaxLeanAngle assignment is a positive constant (THPS1 writes 0x5a000 where the
   demo doubled it), so combine's nonzero_bits proves it non-negative and (Max >> 12) / 2 becomes
   retail's single `srl 13`; the d-pad anim-lean clamp only stores when in range
   (if (a - d >= -Max) a -= d;), giving the two arms' shared `slt; bne; sw` tail; the anim-range
   tests are switches (signed slti trees); DeltaAngle's per-stat rate is one ?: expression. */
struct CVector {
	int vx, vy, vz;
};

struct SButton {
	unsigned char Pressed;
	unsigned char Triggered;
	int PressedTime;
	int ReleasedTime;
	int TriggeredTime;
};

struct SControl {
	SButton Triangle; /* 0x00 */
	SButton Square;   /* 0x10 */
	SButton Circle;   /* 0x20 */
	SButton X;        /* 0x30 */
	SButton LeftOne;  /* 0x40 */
	SButton LeftTwo;  /* 0x50 */
	SButton RightOne; /* 0x60 */
	SButton RightTwo; /* 0x70 */
	SButton Left;     /* 0x80 */
	SButton Right;    /* 0x90 */
	SButton Up;       /* 0xa0 */
	SButton Down;     /* 0xb0 */
	char padc0[0x16c - 0xc0];
};

extern SControl Pad[];
extern int XFrames;
extern int TimeScale;

class CBruce {
  public:
	char pad0[0x6c];
	CVector mVel;  /* 0x6c */
	CVector mKick; /* 0x78 */
	char pad84[0x134 - 0x84];
	int mFlags; /* 0x134 */
	char pad138[0x144 - 0x138];
	short mFrame;         /* 0x144 */
	unsigned short mAnim; /* 0x146 */
	char pad148[0x150 - 0x148];
	int m150; /* 0x150 */
	char pad154[0x198 - 0x154];
	unsigned char *mpStatBonus; /* 0x198 */
	char pad19c[0x258 - 0x19c];
	int mFirstLeftRightPressed; /* 0x258 */
	char pad25c[0x284 - 0x25c];
	int mNoSpin;      /* 0x284 */
	int mNoSpinScore; /* 0x288 */
	char pad28c[0x318 - 0x28c];
	int mDoingSharpTurn; /* 0x318 */
	int mTurning;        /* 0x31c */
	char pad320[0x324 - 0x320];
	int mTapTurn;     /* 0x324 */
	int mTallyAngles; /* 0x328 */
	int mNum180Spins; /* 0x32c */
	char pad330[0x734 - 0x330];
	int mPhysicsState;  /* 0x734 */
	int m738;           /* 0x738 */
	int mManIsCrouched; /* 0x73c */
	char pad740[0x834 - 0x740];
	int mPitchAngle;    /* 0x834 */
	int mLeanAngle;     /* 0x838 */
	int mAnimLeanAngle; /* 0x83c */
	char pad840[0x86c - 0x840];
	SControl *mPad; /* 0x86c */
	char pad870[0x894 - 0x870];
	signed char mAX; /* 0x894 */
	signed char mAY; /* 0x895 */
	void RotateHeadingAndVelocity(int, int, int);
	void HandleSpin();
};

int InterpolateFrame(int, int);

extern "C" {
	int Mips_CVecDotProd__FP7CVectorT0(CVector *, CVector *);
	int FUN_8008b5dc(int);
	void Debug_RunAnim__6CBruceii(CBruce *, int, int);
	void Debug_RunAnim2__6CBruceiiii(CBruce *, int, int, int, int);
	void Debug_RunAnim3__6CBruceiiiii(CBruce *, int, int, int, int, int);
}

void CBruce::HandleSpin() {
	int DeltaAngle;
	int MaxLeanAngle;
	int LeftPressed;
	int RightPressed;

	if (mPhysicsState == 1 || mPhysicsState == 2) {
		if (!mNoSpin) {
			if (mPad->LeftTwo.Triggered) {
				mPad->LeftTwo.Triggered = 0;

				if (mTapTurn > 0)
					mTapTurn = 0;

				mTapTurn--;
			}

			if (mPad->RightTwo.Triggered) {
				mPad->RightTwo.Triggered = 0;

				if (mTapTurn < 0)
					mTapTurn = 0;

				mTapTurn++;
			}
		}

		if (mTapTurn > 0) {
			RotateHeadingAndVelocity((TimeScale * 150) >> 8, 0, 0);

			mTallyAngles += (TimeScale * 150) >> 8;

			if (mTallyAngles >= 2048) {
				mTallyAngles -= 2048;
				mTapTurn--;

				if (!mNoSpinScore)
					mNum180Spins++;
			}
		}

		if (mTapTurn < 0) {
			RotateHeadingAndVelocity(-((TimeScale * 150) >> 8), 0, 0);

			mTallyAngles -= (TimeScale * 150) >> 8;

			if (mTallyAngles <= -2048) {
				mTallyAngles += 2048;
				mTapTurn++;

				if (!mNoSpinScore)
					mNum180Spins++;
			}
		}
	} else
		mTapTurn = 0;

	if (mTapTurn) {
		mLeanAngle = 0;
		return;
	}

	mTurning = 0;

	if (mPhysicsState == 0) {
		DeltaAngle = (TimeScale * (mpStatBonus[4] == 1   ? 10240
		                              : mpStatBonus[4] == 3 ? 15872
		                                                    : 30720)) >>
		             8;
		MaxLeanAngle = 0x2d000;
		LeftPressed = mPad->Left.Pressed;
		RightPressed = mPad->Right.Pressed;
		mFirstLeftRightPressed = 0;

		if (mAY >= 31 || mPad->Down.Pressed) {
			mDoingSharpTurn = 1;

			{
				int Speed = (FUN_8008b5dc(Mips_CVecDotProd__FP7CVectorT0(&mVel, &mVel)) << 6) >> 12;

				DeltaAngle *= 2;
				MaxLeanAngle = 0x5a000;
				mKick.vx -= mVel.vx / Speed;
				mKick.vy -= mVel.vy / Speed;
				mKick.vz -= mVel.vz / Speed;
			}
		}
	} else {
		if (Pad[0].LeftOne.Pressed || Pad[0].RightOne.Pressed)
			DeltaAngle = (TimeScale * 0x64000) >> 8;
		else
			DeltaAngle = (TimeScale * 0xa000) >> 8;

		MaxLeanAngle = 0xa0000;
		LeftPressed = mPad->Left.Pressed || mPad->LeftOne.Pressed;
		RightPressed = mPad->Right.Pressed || mPad->RightOne.Pressed;

		if (LeftPressed || RightPressed) {
			if (mFirstLeftRightPressed > 0 && XFrames - mFirstLeftRightPressed < 8) {
				LeftPressed = 0;
				RightPressed = 0;
			}
		} else
			mFirstLeftRightPressed = XFrames;

		LeftPressed |= mPad->LeftOne.Pressed;
		RightPressed |= mPad->RightOne.Pressed;

		if (mNoSpin)
			LeftPressed = RightPressed = 0;

		if (!LeftPressed && !RightPressed && !mAX)
			mLeanAngle = 0;

		mDoingSharpTurn = 0;
	}

	if (mAX && !LeftPressed && !RightPressed) {
		int TargetAngle = mAX * MaxLeanAngle / 128;

		if (TargetAngle < -MaxLeanAngle)
			TargetAngle = -MaxLeanAngle;

		if (TargetAngle > MaxLeanAngle)
			TargetAngle = MaxLeanAngle;

		if (mLeanAngle < TargetAngle) {
			int Diff = (TargetAngle - mLeanAngle) >> 12;

			mTurning = 1;
			mLeanAngle += DeltaAngle + DeltaAngle * Diff / ((MaxLeanAngle >> 12) / 2);

			if (mLeanAngle > TargetAngle)
				mLeanAngle = TargetAngle;

			mAnimLeanAngle += DeltaAngle;

			if (mAnimLeanAngle > TargetAngle)
				mAnimLeanAngle = TargetAngle;
		}

		if (mLeanAngle > TargetAngle) {
			int Diff = (mLeanAngle - TargetAngle) >> 12;

			mTurning = 1;
			mLeanAngle -= DeltaAngle + DeltaAngle * Diff / ((MaxLeanAngle >> 12) / 2);

			if (mLeanAngle < TargetAngle)
				mLeanAngle = TargetAngle;

			mAnimLeanAngle -= DeltaAngle;

			if (mAnimLeanAngle < TargetAngle)
				mAnimLeanAngle = TargetAngle;
		}
	} else if (LeftPressed) {
		mTurning = 1;
		mLeanAngle -= DeltaAngle;

		if (mLeanAngle < -MaxLeanAngle)
			mLeanAngle = -MaxLeanAngle;

		if (mAnimLeanAngle - DeltaAngle >= -MaxLeanAngle)
			mAnimLeanAngle -= DeltaAngle;
	} else if (RightPressed) {
		mTurning = 1;
		mLeanAngle += DeltaAngle;

		if (mLeanAngle > MaxLeanAngle)
			mLeanAngle = MaxLeanAngle;

		if (mAnimLeanAngle + DeltaAngle <= MaxLeanAngle)
			mAnimLeanAngle += DeltaAngle;
	} else {
		int Step;

		if (mDoingSharpTurn)
			mLeanAngle -= mLeanAngle >> 1;
		else
			mLeanAngle -= mLeanAngle >> 2;

		if (((mLeanAngle + 2048) >> 12) == 0)
			mLeanAngle = 0;

		Step = mAnimLeanAngle >> 4;

		if (Step < 0)
			if (Step > -1024)
				Step = -1024;

		if (Step > 0 && Step < 1024)
			Step = 1024;

		mAnimLeanAngle -= Step;

		if (((mAnimLeanAngle + 2048) >> 12) == 0)
			mAnimLeanAngle = 0;
	}

	mAnimLeanAngle = mLeanAngle;

	if (mAnimLeanAngle) {
		if (!mManIsCrouched) {
			switch (mAnim) {
				case 0:
				case 6:
				case 7:
				case 8:
				case 9:
				case 10:
					if (mFlags & 2) {
						if (mAnimLeanAngle < 0) {
							int Frame = -(mAnimLeanAngle * 22) / MaxLeanAngle;

							if (Frame > 22)
								Frame = 22;

							m150 = 0x10000;

							if (mAnim != 7)
								mFrame = 0;

							mFrame = InterpolateFrame(mFrame, Frame);
							Debug_RunAnim2__6CBruceiiii(this, 7, mFrame, mFrame, 2881);
						} else {
							int Frame = mAnimLeanAngle * 22 / MaxLeanAngle;

							if (Frame > 22)
								Frame = 22;

							m150 = 0x10000;

							if (mAnim != 6)
								mFrame = 0;

							if (mFrame < Frame)
								mFrame++;

							mFrame = InterpolateFrame(mFrame, Frame);
							Debug_RunAnim2__6CBruceiiii(this, 6, mFrame, mFrame, 2892);
						}
					} else {
						if (mAnimLeanAngle < 0) {
							int Frame = -(mAnimLeanAngle * 22) / MaxLeanAngle;

							if (Frame > 22)
								Frame = 22;

							m150 = 0x10000;

							if (mAnim != 6)
								mFrame = 0;

							mFrame = InterpolateFrame(mFrame, Frame);
							Debug_RunAnim2__6CBruceiiii(this, 6, mFrame, mFrame, 2906);
						} else {
							int Frame = mAnimLeanAngle * 22 / MaxLeanAngle;

							if (Frame > 22)
								Frame = 22;

							m150 = 0x10000;

							if (mAnim != 7)
								mFrame = 0;

							mFrame = InterpolateFrame(mFrame, Frame);
							Debug_RunAnim2__6CBruceiiii(this, 7, mFrame, mFrame, 2916);
						}
					}
			}
		}
	}

	if (mAnimLeanAngle) {
		if (mManIsCrouched) {
			switch (mAnim) {
				case 0:
				case 6:
				case 7:
				case 8:
				case 9:
				case 10:
					if (mFlags & 2) {
						if (mAnimLeanAngle < 0) {
							int Frame = -(mAnimLeanAngle * 12) / MaxLeanAngle;

							if (Frame > 12)
								Frame = 12;

							m150 = 0x10000;

							if (mAnim == 7) {
								mAnim = 10;
								mFrame = Frame;
							}

							if (mAnim != 10)
								mFrame = 0;

							mFrame = InterpolateFrame(mFrame, Frame);
							Debug_RunAnim2__6CBruceiiii(this, 10, mFrame, mFrame, 2953);
						} else {
							int Frame = mAnimLeanAngle * 15 / MaxLeanAngle;

							if (Frame > 15)
								Frame = 15;

							m150 = 0x10000;

							if (mAnim == 6) {
								mAnim = 9;
								mFrame = Frame;
							}

							if (mAnim != 9)
								mFrame = 0;

							mFrame = InterpolateFrame(mFrame, Frame);
							Debug_RunAnim2__6CBruceiiii(this, 9, mFrame, mFrame, 2968);
						}
					} else {
						if (mAnimLeanAngle < 0) {
							int Frame = -(mAnimLeanAngle * 15) / MaxLeanAngle;

							if (Frame > 15)
								Frame = 15;

							m150 = 0x10000;

							if (mAnim == 6) {
								mAnim = 9;
								mFrame = Frame;
							}

							if (mAnim != 9)
								mFrame = 0;

							mFrame = InterpolateFrame(mFrame, Frame);
							Debug_RunAnim2__6CBruceiiii(this, 9, mFrame, mFrame, 2988);
						} else {
							int Frame = mAnimLeanAngle * 12 / MaxLeanAngle;

							if (Frame > 12)
								Frame = 12;

							m150 = 0x10000;

							if (mAnim == 7) {
								mAnim = 10;
								mFrame = Frame;
							}

							if (mAnim != 10)
								mFrame = 0;

							mFrame = InterpolateFrame(mFrame, Frame);
							Debug_RunAnim2__6CBruceiiii(this, 10, mFrame, mFrame, 3003);
						}
					}
			}
		}
	}

	if (!mAnimLeanAngle) {
		switch (mAnim) {
			case 6:
			case 7:
				m150 = 0x10000;
				Debug_RunAnim__6CBruceii(this, 0, 3017);
				break;
			case 9:
			case 10:
				m150 = 0x10000;
				Debug_RunAnim3__6CBruceiiiii(this, 8, 19, 26, 19, 3024);
				break;
		}
	}

	mPitchAngle = 0;

	if (mPhysicsState == 1 && !mPad->Square.Pressed && !mPad->Circle.Pressed) {
		if (mPad->Up.Pressed || mAY < -40)
			mPitchAngle = -((TimeScale * 20) >> 8);

		if (mPad->Down.Pressed || mAY > 40)
			mPitchAngle = (TimeScale * 20) >> 8;
	}
}
