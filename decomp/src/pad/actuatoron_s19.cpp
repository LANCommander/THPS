/* Pad_ActuatorOn__FUcUsUcUc (0x80070a80) */
typedef unsigned char uchar;
typedef unsigned short ushort;
struct SControl {
	char pad0[0x154];
	uchar Motor[2];
	uchar Lock;
	uchar AlignCalled;
	ushort MotorTimer[2];
	char pad1[0x16c - 0x15c];
};
extern SControl DAT_800c0a48[];
extern int DAT_800d16a4;
uchar DAT_800d1f6c[8];
extern "C" {
int PadGetState(int);
void PadSetAct(int, uchar *, int);
int PadSetActAlign(int, uchar *);
}
void Pad_ActuatorOn(uchar index, ushort time, uchar motor, uchar motor_value)
{
	int checkIndex = 0;
	int state;
	if (DAT_800d16a4 != 7)
		checkIndex = index;
	state = PadGetState(index ? 16 : 0);
	if (state != 0) {
		if (state == 1)
			DAT_800c0a48[checkIndex].AlignCalled = 0;
		if (!DAT_800c0a48[checkIndex].AlignCalled) {
			PadSetAct(index ? 16 : 0, &DAT_800c0a48[index].Motor[0], 2);
			if (state == 2)
				DAT_800c0a48[checkIndex].AlignCalled = 1;
			else if (state == 6)
				if (PadSetActAlign(index ? 16 : 0, DAT_800d1f6c))
					DAT_800c0a48[checkIndex].AlignCalled = 1;
		}
		{
			uchar *p_motor_value = &DAT_800c0a48[index].Motor[motor];
			ushort *p_motor_timer;
			ushort *q;
			*p_motor_value = motor_value;
			q = &DAT_800c0a48[index].MotorTimer[0];
			p_motor_timer = (ushort *)((motor << 1) + (int)q);
			*p_motor_timer = time;
		}
	}
}
