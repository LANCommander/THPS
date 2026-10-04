/* PutDataChunk__FP6CBruce (0x80069974) */
/* C++ (VIDEO.CPP). Locals, their order and types come from the demo's MAIN.SYM. */
#include <sys/types.h>
#include <libgte.h>

struct CVector { int vx, vy, vz; };
CVector operator>>(const CVector &, const int &);
enum ESoundCmdType { SOUNDCMD_NONE, SOUNDCMD_PLAY, SOUNDCMD_STOP };
struct SVideoInfo {
  int VideoMode;
  u_long *pBlockStart, *pStreamStart, *pStreamEnd, *pStream;
  u_long Bits;
  int BitsLeft;
  u_long NumFrames, FramesLeft;
  char pad24[0x78 - 0x24];
  int OldPhysicsState, OldAnim, OldFrame;
  SVECTOR Euler, OldEuler;
  CVector OldPos, OldPos2;
  int OldFlipAngle, FlipAngleDelta, OldXblanks, Yblanks, PlaybackFrozen;
};
struct CBruce {
  char pad0[4];
  CVector Pos;
  char pad10[0x134 - 0x10];
  u_long Flags;
  char pad138[0x144 - 0x138];
  short Frame;
  ushort Anim;
  char pad148[0x720 - 0x148];
  int Flipping, FlipAngle;
  char pad728[0x734 - 0x728];
  int PhysicsState;
  char pad738[0x78c - 0x738];
  MATRIX Matrix;
};

extern SVideoInfo DAT_800bf318, DAT_800bf3d8;
extern int DAT_800bf498[], DAT_800bf4b4[], DAT_800bf4d0[], DAT_800bf4ec[], DAT_800bf508[];
extern CBruce *DAT_800d19a4;
extern volatile int DAT_800d1a24;
int DAT_800d1dfc, DAT_800d1e00, DAT_800d1e04, DAT_800d1e08;
int BitsRequired(long);
void PutNBits(SVideoInfo *, long, int);
void Video_Stop(CBruce *);
void Matrix2Euler(MATRIX *, SVECTOR *);
void DequeueSoundCmd(ESoundCmdType &, int &);
extern "C" int FUN_80068df8(void);

void PutDataChunk(CBruce *pSkater)
{
  int i, bx, by, bz;
  int PredX, PredY, PredZ;
  int DeltaX, DeltaY, DeltaZ;
  CVector PredPos, DeltaPos;
  SVideoInfo *VInfo;

  if (pSkater == DAT_800d19a4) VInfo = &DAT_800bf318;
  else VInfo = &DAT_800bf3d8;
  if (VInfo->pStream + 6 >= VInfo->pStreamStart + 6000) {
    Video_Stop(pSkater);
    return;
  }
  VInfo->NumFrames++;

  PredX = VInfo->OldPos.vx * 2 - VInfo->OldPos2.vx;
  PredY = VInfo->OldPos.vy * 2 - VInfo->OldPos2.vy;
  PredZ = VInfo->OldPos.vz * 2 - VInfo->OldPos2.vz;
  DeltaX = (pSkater->Pos.vx >> 12) - PredX;
  DeltaY = (pSkater->Pos.vy >> 12) - PredY;
  DeltaZ = (pSkater->Pos.vz >> 12) - PredZ;
  VInfo->OldPos2 = VInfo->OldPos;
  VInfo->OldPos = pSkater->Pos >> 12;
  bx = BitsRequired(DeltaX);
  by = BitsRequired(DeltaY);
  bz = BitsRequired(DeltaZ);
  if (bx < by) bx = by;
  if (bx < bz) bx = bz;
  for (i = 0; i < 6; i++) if (DAT_800bf498[i] >= bx) break;
  PutNBits(VInfo, DAT_800bf4ec[i], DAT_800bf508[i]);
  PutNBits(VInfo, DeltaX, DAT_800bf498[i]);
  PutNBits(VInfo, DeltaY, DAT_800bf498[i]);
  PutNBits(VInfo, DeltaZ, DAT_800bf498[i]);

  Matrix2Euler(&pSkater->Matrix, &VInfo->Euler);
  DeltaX = ((VInfo->Euler.vx & 0xfff) - VInfo->OldEuler.vx + 0x4000) & 0xfff;
  DeltaY = ((VInfo->Euler.vy & 0xfff) - VInfo->OldEuler.vy + 0x4000) & 0xfff;
  DeltaZ = ((VInfo->Euler.vz & 0xfff) - VInfo->OldEuler.vz + 0x4000) & 0xfff;
  VInfo->Euler.vx &= 0xfff;
  VInfo->Euler.vy &= 0xfff;
  VInfo->Euler.vz &= 0xfff;
  if (DeltaX >= 2048) DeltaX -= 4096;
  if (DeltaY >= 2048) DeltaY -= 4096;
  if (DeltaZ >= 2048) DeltaZ -= 4096;
  VInfo->OldEuler = VInfo->Euler;
  bx = BitsRequired(DeltaX);
  by = BitsRequired(DeltaY);
  bz = BitsRequired(DeltaZ);
  if (bx < by) bx = by;
  if (bx < bz) bx = bz;
  for (i = 0; i < 6; i++) if (DAT_800bf4b4[i] >= bx) break;
  PutNBits(VInfo, DAT_800bf4ec[i], DAT_800bf508[i]);
  PutNBits(VInfo, DeltaX, DAT_800bf4b4[i]);
  PutNBits(VInfo, DeltaY, DAT_800bf4b4[i]);
  PutNBits(VInfo, DeltaZ, DAT_800bf4b4[i]);

  if (pSkater->PhysicsState == VInfo->OldPhysicsState) PutNBits(VInfo, 0, 1);
  else PutNBits(VInfo, (pSkater->PhysicsState << 1) | 1, 5);
  VInfo->OldPhysicsState = pSkater->PhysicsState;
  if (pSkater->Anim == VInfo->OldAnim) PutNBits(VInfo, 0, 1);
  else PutNBits(VInfo, (pSkater->Anim << 1) | 1, 8);
  VInfo->OldAnim = pSkater->Anim;
  DeltaX = pSkater->Frame - VInfo->OldFrame;
  if ((unsigned)DeltaX < 4) PutNBits(VInfo, DeltaX << 1, 3);
  else PutNBits(VInfo, (pSkater->Frame << 1) | 1, 9);
  VInfo->OldFrame = pSkater->Frame;
  PutNBits(VInfo, (pSkater->Flags >> 1) & 1, 1);

  if (!pSkater->Flipping) {
    PutNBits(VInfo, 0, 1);
    VInfo->OldFlipAngle = 0;
    VInfo->FlipAngleDelta = 0;
  } else {
    PutNBits(VInfo, 1, 1);
    {
      int Delta, Bits;
      Delta = pSkater->FlipAngle - (VInfo->OldFlipAngle + VInfo->FlipAngleDelta);
      Bits = 0;
      if (Delta) Bits = BitsRequired(Delta);
      for (i = 0; i < 6; i++) if (DAT_800bf4d0[i] >= Bits) break;
      PutNBits(VInfo, DAT_800bf4ec[i], DAT_800bf508[i]);
      PutNBits(VInfo, Delta, DAT_800bf4d0[i]);
      VInfo->OldFlipAngle = pSkater->FlipAngle;
      VInfo->FlipAngleDelta = Delta;
    }
  }

  DeltaX = DAT_800d1a24 - VInfo->OldXblanks;
  if (DeltaX >= 6) {
    VInfo->OldXblanks = DAT_800d1a24 - (DeltaX - 5);
    DeltaX = 5;
  } else VInfo->OldXblanks = DAT_800d1a24;
  PutNBits(VInfo, DeltaX - 2, 2);

  if (FUN_80068df8()) {
    PutNBits(VInfo, 1, 1);
    {
      ESoundCmdType SoundCmdType;
      int SoundNum;
      DequeueSoundCmd(SoundCmdType, SoundNum);
      if (SoundCmdType == SOUNDCMD_PLAY) {
        PutNBits(VInfo, 1, 1);
        PutNBits(VInfo, SoundNum, 8);
      } else if (SoundCmdType == SOUNDCMD_STOP) {
        PutNBits(VInfo, 0, 1);
        PutNBits(VInfo, SoundNum, 8);
      }
    }
  } else PutNBits(VInfo, 0, 1);

  if (DAT_800d1dfc == -1 && DAT_800d1e00 == DAT_800d1dfc && DAT_800d1e04 == DAT_800d1e00 && DAT_800d1e08 == DAT_800d1e04) {
    PutNBits(VInfo, 0, 1);
    return;
  }
  PutNBits(VInfo, 1, 1);
  if (pSkater == DAT_800d19a4) {
    if (DAT_800d1dfc != -1) {
      PutNBits(VInfo, 1, 1);
      PutNBits(VInfo, DAT_800d1dfc, 2);
      DAT_800d1dfc = -1;
    } else PutNBits(VInfo, 0, 1);
  } else {
    if (DAT_800d1e00 != -1) {
      PutNBits(VInfo, 1, 1);
      PutNBits(VInfo, DAT_800d1e00, 2);
      DAT_800d1e00 = -1;
    } else PutNBits(VInfo, 0, 1);
  }
  if (pSkater == DAT_800d19a4) {
    if (DAT_800d1e04 != -1) {
      PutNBits(VInfo, 1, 1);
      PutNBits(VInfo, DAT_800d1e04, 8);
      DAT_800d1e04 = -1;
      return;
    }
  } else {
    if (DAT_800d1e08 != -1) {
      PutNBits(VInfo, 1, 1);
      PutNBits(VInfo, DAT_800d1e08, 8);
      DAT_800d1e08 = -1;
      return;
    }
  }
  PutNBits(VInfo, 0, 1);
}
