/* SFX_ReverbOff__Fv (0x8004bafc) */
extern void SFX_SetReverbType__FUc(unsigned char);

void SFX_ReverbOff(void) {
	SFX_SetReverbType__FUc(0);
}
