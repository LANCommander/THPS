/* ExecuteCommandList__FPUsii (0x80046374) flags=-fstructure-noalias */
/* C++ (TRIG.CPP). Fuzzy demo twin (0.52); locals from its MAIN.SYM. Runs a trigger node's command
   script: restart names and points, spooling, kill/visibility boxes, backgrounds, fog and sky
   colours, gaps, sounds, pulses and signals to linked nodes, and the camera settings. */
#pragma interface

typedef unsigned short ushort;
typedef unsigned char uchar;
typedef unsigned int uint;

struct CVector {
	int vx, vy, vz;
	CVector() {}
	int Length() const;
};

CVector operator-(const CVector &, const CVector &);

struct CSVector {
	short vx, vy, vz;
	CSVector() {}
};

struct SGapTrick {
	short Type;
	short Score;
	char *Name;
};

struct SCommandPoint {
	ushort *pCommands;
	uchar Collision;
	uchar Executed;
	uchar NumPulsesSet;
	uchar PulsesReceived;
	ushort NumPulses;
	ushort NodeIndex;
	uint Checksum;
	SCommandPoint *pNextSimilar;
	SCommandPoint *pNext;
};

class CCamera {
  public:
	char pad0[0x420];
	class CBody *mTripod; /* 0x420 */
	char pad424[0x458 - 0x424];
	class CBody *mFocus; /* 0x458 */
	char pad45c[0x4b0 - 0x45c];
	short mPitchDamper;      /* 0x4b0 */
	short mTripodPosYDamper; /* 0x4b2 */
	void SetPitchDamper(short v) {
		mPitchDamper = v;
	}
	void SetTripodPosYDamper(short v) {
		mTripodPosYDamper = v;
	}
	char pad4b4[0x584 - 0x4b4];
	int mCameraMode; /* 0x584 */
	void ResetOrientation();
	void SetZoom(ushort, ushort);
	void SetCamAngle(short, ushort);
	void SetCamXZDistance(ushort, ushort);
	void SetCamYDistance(short, ushort);
	void SetCamXOffset(short, ushort);
	void SetCamYOffset(short, ushort);
	void SetCamZOffset(short, ushort);
	void SetCollisionRayLR(int);
	void SetCollisionRayBack(int);
	void SetCollisionAngLR(short);
	void SetCollisionAngBack(short);
	void SetComplexMode(ushort);
};

class CPanelData {
  public:
	void OutOfBounds();
};

class CBruce {
  public:
	char pad0[4];
	CVector mPos;     /* 0x04 */
	CSVector mAngles; /* 0x10 */
	char pad16[0x6c - 0x16];
	CVector mVel; /* 0x6c */
	CVector mAcc; /* 0x78 */
	char pad84[0xf0 - 0x84];
	CVector mOldPos; /* 0xf0 */
	char padfc[0x1bc - 0xfc];
	CVector mSafePos; /* 0x1bc */
	char pad1c8[0x1d8 - 0x1c8];
	CCamera *mpCamera; /* 0x1d8 */
	CVector m1DC;      /* 0x1dc */
	char pad1e8[0x28c - 0x1e8];
	int mGapChecksum[10];       /* 0x28c */
	int mGapType[10];           /* 0x2b4 */
	int mGaps;                  /* 0x2dc */
	SGapTrick *mpGrindGapTrick; /* 0x2e0 */
	char pad2e4[0x358 - 0x2e4];
	int mInBail;      /* 0x358 */
	int mDoingATrick; /* 0x35c */
	char pad360[0x6e0 - 0x360];
	int mStickToRail; /* 0x6e0 */
	char pad6e4[0x744 - 0x6e4];
	int mJumpPending;  /* 0x744 */
	int mJumpStrength; /* 0x748 */
	char pad74c[0x884 - 0x74c];
	int mIgnoreBruceInputTimer;       /* 0x884 */
	int mIgnoreBruceInputFreezeTimer; /* 0x888 */
	char pad88c[0x8a4 - 0x88c];
	int m8A4; /* 0x8a4 */
	int m8A8; /* 0x8a8 */
	void SetM8A4(int a, int b) {
		m8A4 = a;
		m8A8 = b;
	}
	char pad8ac[0x924 - 0x8ac];
	CPanelData mPanelData; /* 0x924 */
	void Trick(int, char *, int, int);
	void Bail();
	void ResetTrickBuffers();
	void RunAnim(int, int, int, int);
};

class CItem {
  public:
	char padItem[0x4c];
	static void *operator new(uint) throw();
};

class CBackground : public CItem {
  public:
	char pad4c[312 - 0x4c];
	CBackground(uint, const CSVector &);
};

int DAT_800d19d8;
int DAT_800d19dc;
int DAT_800d19e4;
short **DAT_800d19e8;
int DAT_800d19ec;
char *DAT_800d19f0;
char DAT_800d1a14;

extern char *DAT_800a8788[];
extern char *DAT_800a87d8[];
extern SGapTrick DAT_800a8258[];
extern int DAT_800bf318[];
extern int DAT_800d16a4;
extern int DAT_800d17ac;
extern int DAT_800d1780;
extern int DAT_800d1f14;
extern uint DAT_800d2174;
extern uint DAT_800d1a3c;
extern CBruce *DAT_800d199c;
extern CBruce *DAT_800d19a4;
extern int DAT_800d19c0;
extern ushort DAT_800d214c;
extern ushort DAT_800d214e;
extern CCamera *DAT_800d2044;
extern int DAT_800d1764;

SCommandPoint *GetCommandPoint(int);
char *SkipString(char *);
ushort *SkipCommand(ushort *);
void Trig_RemoveDualBuffer();
void Trig_AllocateDualBuffer(uint);
void Trig_SetRestart(char *);
void Mess_DeleteAll();
void Front_SaveGameState();
int Spool_PSX(char *, int, int);
void Spool_Sync();
void Spool_ClearPSX(char *);
void SFX_SpoolInMIDI(const char *);
char Spool_FindRegion(char *);
int Utils_KillEverythingInBox(const CVector &, const CVector &);
void Utils_SetVisibilityInBox(const CVector &, const CVector &, bool, bool);
void Backgrnd_On(ushort);
void Backgrnd_Off(ushort);
void Db_UpdateSky();
int SFX_PlayX(uint, short, int);
void SFX_Stop(uint);
void SFX_MIDIChannelMute(ushort);
void SFX_MIDIFadeIn(int);
void SFX_MIDIFadeOut(int);
void SFX_SetReverbType(uchar);
void Game_Over();
ushort *Trig_GetLinksPointer(int);
CSVector *Trig_GetPosition(CVector &, int);
int Utils_CompareStrings(const char *, const char *, uint);
void FudgeAngles(CBruce *);
void Front_Restart();
void Trig_SendPulse(ushort *);
void SendSuspendOrActivate(ushort *, int);
void SendSignalToLinks(ushort *);
void SendVisibleFromNode(int, int);
void SendKillFromNode(int, int);
void Redbook_XAAllow(bool);
void M3dInit_SetFoggingParams(int, int, uint);

void ExecuteCommandList(ushort *pCommands, int Node, int WaitForSpooling) {
	int NewFoggingParameters = 0;
	int ZHither;
	int ZDpqMin;
	uint Range;
	SCommandPoint *pCommandPoint = GetCommandPoint(Node);

	while (*pCommands != 0xffff) {
		ushort Command = *pCommands++;

		switch (Command) {
			case 0x02:
				DAT_800d19d8 = 0;

				while (*(char *)pCommands) {
					DAT_800a8788[DAT_800d19d8++] = (char *)pCommands;
					pCommands = (ushort *)SkipString((char *)pCommands);
				}

				pCommands++;
				break;

			case 0x97:
				Trig_RemoveDualBuffer();
				Trig_AllocateDualBuffer(*pCommands++ * 1000);
				break;

			case 0x8c:
			case 0xb0: {
				int OldRestart = DAT_800d19e4;

				if (DAT_800d16a4 == 7)
					Trig_SetRestart(DAT_800a87d8[DAT_800d17ac]);
				else
					Trig_SetRestart((char *)pCommands);

				pCommands = (ushort *)SkipString((char *)pCommands);

				if (OldRestart != 0xffff && DAT_800d19e4 != OldRestart) {
					if (Command != 0xb0)
						Mess_DeleteAll();

					Front_SaveGameState();
				}

				break;
			}

			case 0xb2:
				if (DAT_800d1780 == 2) {
					if (DAT_800d16a4 == 7)
						Trig_SetRestart(DAT_800a87d8[DAT_800d17ac]);
					else
						Trig_SetRestart((char *)pCommands);
				}

				pCommands = (ushort *)SkipString((char *)pCommands);
				break;

			case 0x7e:
				Spool_PSX((char *)pCommands, 0, 0);

				if (WaitForSpooling)
					Spool_Sync();

				pCommands = (ushort *)SkipString((char *)pCommands);
				break;

			case 0x7f:
				Spool_ClearPSX((char *)pCommands);

				pCommands = (ushort *)SkipString((char *)pCommands);
				break;

			case 0x80:
				Spool_PSX((char *)pCommands, 1, 0);

				if (WaitForSpooling)
					Spool_Sync();

				pCommands = (ushort *)SkipString((char *)pCommands);
				break;

			case 0x81:
				Spool_Sync();
				break;

			case 0x9f:
				SFX_SpoolInMIDI((char *)pCommands);

				pCommands = (ushort *)SkipString((char *)pCommands);
				break;

			case 0x8e:
				DAT_800d19f0 = (char *)pCommands;
				pCommands = (ushort *)SkipString((char *)pCommands);
				DAT_800d1a14 = Spool_FindRegion(DAT_800d19f0);
				break;

			case 0x85: {
				CVector min, max;

				while (*pCommands != 0xff) {
					int *p_pos = (int *)(((int)pCommands + 3) & ~3);

					min.vx = *p_pos++ << 12;
					min.vy = *p_pos++ << 12;
					min.vz = *p_pos++ << 12;
					max.vx = *p_pos++ << 12;
					max.vy = *p_pos++ << 12;
					max.vz = *p_pos++ << 12;
					Utils_KillEverythingInBox(min, max);

					pCommands = (ushort *)p_pos;
				}

				pCommands++;
				break;
			}

			case 0x8a:
				pCommands++;
				break;

			case 0x8d: {
				ushort on = *pCommands++;
				ushort in = *pCommands++;
				CVector min, max;

				while (*pCommands != 0xff) {
					int *p_pos = (int *)(((int)pCommands + 3) & ~3);

					min.vx = *p_pos++ << 12;
					min.vy = *p_pos++ << 12;
					min.vz = *p_pos++ << 12;
					max.vx = *p_pos++ << 12;
					max.vy = *p_pos++ << 12;
					max.vz = *p_pos++ << 12;
					Utils_SetVisibilityInBox(min, max, on, in);

					pCommands = (ushort *)p_pos;
				}

				pCommands++;
				break;
			}

			case 0x66:
				DAT_800d1f14 = 1;
				break;

			case 0x67:
				DAT_800d1f14 = 0;
				break;

			case 0xab: {
				uint *p_checksum = (uint *)(((int)pCommands + 3) & ~3);
				uint checksum = *p_checksum++;
				CSVector ang_vel;

				pCommands = (ushort *)p_checksum;
				ang_vel.vx = *pCommands++;
				ang_vel.vy = *pCommands++;
				ang_vel.vz = *pCommands++;
				new CBackground(checksum, ang_vel);
				break;
			}

			case 0x83:
				Backgrnd_On(*pCommands++);
				break;

			case 0x84:
				Backgrnd_Off(*pCommands++);
				break;

			case 0x68:
				ZHither = *pCommands++;
				ZDpqMin = *pCommands++;
				Range = *pCommands++;
				NewFoggingParameters = 1;
				break;

			case 0xc8: {
				uint fadecolor = *pCommands++ << 16;

				fadecolor += *pCommands++;
				DAT_800d2174 = fadecolor;
				break;
			}

			case 0xca: {
				uint skycolor = *pCommands++ << 16;

				skycolor += *pCommands++;
				DAT_800d1a3c = skycolor;
				Db_UpdateSky();
				break;
			}

			case 0xc9: {
				uint *pChecksum = (uint *)(((int)pCommands + 3) & ~3);
				uint Checksum = *pChecksum++;
				int GapType;

				pCommands = (ushort *)pChecksum;
				GapType = *pCommands++;

				if (DAT_800bf318[0] != 2) {
					int i;

					for (i = 0; i < DAT_800d199c->mGaps; i++) {
						if (DAT_800d199c->mGapChecksum[i] &&
						    DAT_800d199c->mGapChecksum[i] == pCommandPoint->Checksum) {
							DAT_800d199c->mGapChecksum[i] = 0;

							if (!DAT_800d199c->mInBail) {
								SGapTrick *pGapTrick = DAT_800a8258;

								while (pGapTrick->Type != -1) {
									if (pGapTrick->Type == DAT_800d199c->mGapType[i])
										break;

									pGapTrick++;
								}

								if (pGapTrick->Type != -1) {
									if (pGapTrick->Type < 20000) {
										DAT_800d199c->Trick(77, pGapTrick->Name, -pGapTrick->Score,
										                    0);
										SFX_PlayX(161, 0x2000, 0);
									} else {
										DAT_800d199c->mpGrindGapTrick = pGapTrick;
									}
								}
							}
						}
					}

					if (Checksum && DAT_800d199c->mGaps < 10) {
						DAT_800d199c->mGapChecksum[DAT_800d199c->mGaps] = Checksum;
						DAT_800d199c->mGapType[DAT_800d199c->mGaps] = GapType;
						DAT_800d199c->mGaps++;
					}
				}

				break;
			}

			case 0x69:
				SFX_PlayX((short)*pCommands++, 0x2000, 0);
				break;

			case 0x6a:
				SFX_Stop((short)*pCommands++);
				break;

			case 0x96:
				SFX_MIDIChannelMute(*pCommands++);
				break;

			case 0x9b:
				SFX_MIDIFadeIn(*pCommands++);
				break;

			case 0x9c:
				SFX_MIDIFadeOut(*pCommands++);
				break;

			case 0x9d:
				SFX_SetReverbType(*pCommands++);
				break;

			case 0x9e:
				Game_Over();
				break;

			case 0xa3:
				if (DAT_800d19a4)
					DAT_800d19a4->mIgnoreBruceInputTimer = *pCommands++;

				break;

			case 0xb1:
				if (DAT_800d19a4)
					DAT_800d19a4->mIgnoreBruceInputFreezeTimer = *pCommands++;

				break;

			case 0x98: {
				CVector StartPos;
				CVector BestStartPos;
				CSVector *pBestAngles;
				CBruce *pBruce;
				int BestDist = 10000000;
				ushort *pLinks = Trig_GetLinksPointer(Node);

				if (*pLinks++) {
					pBestAngles = Trig_GetPosition(BestStartPos, *pLinks);
					BestDist = 1;
				} else {
					int n;

					for (n = 0; n < DAT_800d19dc; n++) {
						int i;

						for (i = 0; i < DAT_800d19ec; i++) {
							CVector Dummy;

							if (*DAT_800d19e8[i] == 8 &&
							    Utils_CompareStrings((char *)(Trig_GetPosition(Dummy, i) + 1),
							                         DAT_800a87d8[n], -1)) {
								CSVector *pAngles = Trig_GetPosition(StartPos, i);
								int Dist = (StartPos - DAT_800d199c->m1DC).Length();

								if (Dist < BestDist) {
									BestDist = Dist;
									BestStartPos = StartPos;
									pBestAngles = pAngles;
								}
							}
						}
					}
				}

				if (BestDist != 10000000) {
					pBruce = DAT_800d199c;
					pBruce->mPos = BestStartPos;
					pBruce->mVel.vx = 0;
					pBruce->mVel.vy = -16384;
					pBruce->mVel.vz = 0;
					pBruce->mAcc.vx = 0;
					pBruce->mAcc.vy = 0;
					pBruce->mAcc.vz = 0;
					pBruce->mPos.vy += -102400;
					pBruce->Bail();

					pBruce->mDoingATrick = 0;
					pBruce->mJumpPending = 0;
					pBruce->mJumpStrength = 0;
					pBruce->ResetTrickBuffers();

					pBruce->mStickToRail = 0;
					pBruce->mAngles = *pBestAngles;
					FudgeAngles(pBruce);

					pBruce->mOldPos = pBruce->mPos;
					pBruce->mSafePos = pBruce->mPos;
					pBruce->mInBail = 0;
					pBruce->mpCamera->ResetOrientation();
					pBruce->RunAnim(0, 0, -1, -1);
					pBruce->mPanelData.OutOfBounds();
				} else {
					Front_Restart();
				}

				break;
			}

			case 0x94:
				if (pCommandPoint->PulsesReceived != *pCommands++) {
					while (*pCommands != 0x95)
						pCommands = SkipCommand(pCommands);

					pCommands++;
				}

				break;

			case 0x86:
				if (!pCommandPoint->NumPulsesSet) {
					pCommandPoint->NumPulses = *pCommands;
					pCommandPoint->NumPulsesSet = 1;
				}

				pCommands++;
				break;

			case 0x03:
				if (pCommandPoint) {
					if (pCommandPoint->NumPulses) {
						Trig_SendPulse(Trig_GetLinksPointer(Node));

						if (pCommandPoint->NumPulses != 0xffff)
							pCommandPoint->NumPulses--;
					}
				} else {
					Trig_SendPulse(Trig_GetLinksPointer(Node));
				}

				break;

			case 0x04:
			case 0x05:
				SendSuspendOrActivate(Trig_GetLinksPointer(Node), Command);
				break;

			case 0x0a:
				SendSignalToLinks(Trig_GetLinksPointer(Node));
				break;

			case 0x0d:
				SendVisibleFromNode(Node, *pCommands++);
				break;

			case 0x0b:
				SendKillFromNode(Node, 0);
				break;

			case 0x0c:
				SendKillFromNode(Node, 1);
				break;

			case 0x77:
			case 0xa2:
				pCommands = (ushort *)SkipString((char *)pCommands);
				break;

			case 0xaa:
				DAT_800d19c0 = *pCommands++;
				break;

			case 0xa6:
				DAT_800d214c = *pCommands++;
				break;

			case 0xa9:
				DAT_800d214e = *pCommands++;
				break;

			case 0xad:
				if (DAT_800d2044)
					DAT_800d2044->mFocus = DAT_800d2044->mTripod;

				break;

			case 0xa7:
				if (DAT_800d2044) {
					ushort a = pCommands[0];
					ushort b = pCommands[1];

					pCommands += 2;
					DAT_800d2044->SetZoom(a, b);
				} else
					pCommands += 2;

				break;

			case 0xa8:
				if (DAT_800d2044)
					DAT_800d2044->SetPitchDamper(*pCommands);

				pCommands++;
				break;

			case 0xac:
				if (DAT_800d2044)
					DAT_800d2044->SetTripodPosYDamper(*pCommands);

				pCommands++;
				break;

			case 0x82:
				if (DAT_800d2044) {
					short a = pCommands[0];
					ushort b = pCommands[1];

					pCommands += 2;
					DAT_800d2044->SetCamAngle(a, b);
				} else
					pCommands += 2;

				break;

			case 0x87:
				if (DAT_800d2044) {
					ushort a = pCommands[0];
					ushort b = pCommands[1];

					pCommands += 2;
					DAT_800d2044->SetCamXZDistance(a, b);
				} else
					pCommands += 2;

				break;

			case 0x8f:
				if (DAT_800d2044) {
					short a = pCommands[0];
					ushort b = pCommands[1];

					pCommands += 2;
					DAT_800d2044->SetCamYDistance(a, b);
				} else
					pCommands += 2;

				break;

			case 0x90:
				if (DAT_800d2044) {
					short a = pCommands[0];
					ushort b = pCommands[1];

					pCommands += 2;
					DAT_800d2044->SetCamXOffset(a, b);
				} else
					pCommands += 2;

				break;

			case 0x91:
				if (DAT_800d2044) {
					short a = pCommands[0];
					ushort b = pCommands[1];

					pCommands += 2;
					DAT_800d2044->SetCamYOffset(a, b);
				} else
					pCommands += 2;

				break;

			case 0x92:
				if (DAT_800d2044) {
					short a = pCommands[0];
					ushort b = pCommands[1];

					pCommands += 2;
					DAT_800d2044->SetCamZOffset(a, b);
				} else
					pCommands += 2;

				break;

			case 0x99:
				if (DAT_800d2044)
					DAT_800d2044->SetCollisionRayLR((short)*pCommands++);
				else
					pCommands++;

				break;

			case 0x9a:
				if (DAT_800d2044)
					DAT_800d2044->SetCollisionRayBack((short)*pCommands++);
				else
					pCommands++;

				break;

			case 0xa4:
				if (DAT_800d2044)
					DAT_800d2044->SetCollisionAngLR(*pCommands++);
				else
					pCommands++;

				break;

			case 0xa5:
				if (DAT_800d2044)
					DAT_800d2044->SetCollisionAngBack(*pCommands++);
				else
					pCommands++;

				break;

			case 0xa0:
				if (DAT_800d2044)
					DAT_800d2044->mCameraMode = *pCommands;

				pCommands++;
				break;

			case 0xa1:
				if (DAT_800d2044)
					DAT_800d2044->SetComplexMode(*pCommands++);
				else
					pCommands++;

				break;

			case 0x93:
				DAT_800d1764 = *pCommands++;
				break;

			case 0x88:
				Redbook_XAAllow(1);
				break;

			case 0x89:
				Redbook_XAAllow(0);
				break;

			case 0xae:
				if (DAT_800d19a4)
					DAT_800d19a4->SetM8A4(pCommands[0], pCommands[1]);
			case 0x8b:
				pCommands += 2;
				break;

			case 0xaf:
				if (DAT_800d19a4)
					DAT_800d19a4->m8A4 = 0;

				break;
		}
	}

	if (NewFoggingParameters)
		M3dInit_SetFoggingParams(ZHither, ZDpqMin, Range);
}
