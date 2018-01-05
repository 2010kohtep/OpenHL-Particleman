#include "particleman.h"
#include "pman_main.h"

IParticleMan *g_pParticleMan;
float g_flOldTime;

bool IsGamePaused()
{
	return gEngfuncs.GetClientTime() == g_flOldTime;
}