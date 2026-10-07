/* ReadControllers__Fv (0x80070d10) */
/* C++ (PAD.CPP). Demo twin. Multitap ports (type 0x80) read four controllers; otherwise read one and mark the other three absent. */
typedef unsigned char uchar;
struct ControllerData {
	uchar status;
	uchar type;
	uchar button1;
	uchar button2;
	uchar analog0;
	uchar analog1;
	uchar analog2;
	uchar analog3;
};
struct ControllerBuffer {
	uchar pad[34];
};
extern ControllerBuffer DAT_800c0d20[2];
extern ControllerData DAT_800c0d64[8];
void ReadController(ControllerData *, uchar *);

void ReadControllers()
{
	int controller_port;
	for (controller_port = 0; controller_port < 2; controller_port++) {
		if (DAT_800c0d20[controller_port].pad[1] == 0x80) {
			ReadController(&DAT_800c0d64[controller_port * 4 + 0], &DAT_800c0d20[controller_port].pad[2]);
			ReadController(&DAT_800c0d64[controller_port * 4 + 1], &DAT_800c0d20[controller_port].pad[10]);
			ReadController(&DAT_800c0d64[controller_port * 4 + 2], &DAT_800c0d20[controller_port].pad[18]);
			ReadController(&DAT_800c0d64[controller_port * 4 + 3], &DAT_800c0d20[controller_port].pad[26]);
		} else {
			ReadController(&DAT_800c0d64[controller_port * 4], DAT_800c0d20[controller_port].pad);
			DAT_800c0d64[controller_port * 4 + 1].type = 0;
			DAT_800c0d64[controller_port * 4 + 2].type = 0;
			DAT_800c0d64[controller_port * 4 + 3].type = 0;
		}
	}
}
