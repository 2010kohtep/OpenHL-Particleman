#include "pman_main.h"

#include "interface.h"

#include "pman_force.h"
#include "particleman.h"

ForceList g_pForceList;

auto CreateParticleMan()
{
	return (IBaseInterface *)new IParticleMan_Active();
}

EXPOSE_INTERFACE_FN(CreateParticleMan, IParticleMan_Active, PARTICLEMAN_INTERFACE);