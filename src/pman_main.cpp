/**
* Copyright (C) 2017, 2010kohtep
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include "pman_main.h"
#include "pman_particlemem.h"
#include "pman_triangleffect.h"
#include "interface.h"
#include "particleman.h"

int g_iRenderMode;

void IParticleMan_Active::SetUp(struct cl_enginefunc_t* pEnginefuncs)
{

}

void IParticleMan_Active::Update()
{

}

void IParticleMan_Active::SetVariables(float flGravity, Vector vViewAngles)
{

}

void IParticleMan_Active::ResetParticles()
{

}

void IParticleMan_Active::ApplyForce(Vector vOrigin, Vector vDirection, float flRadius, float flStrength, float flDuration)
{

}

void IParticleMan_Active::AddCustomParticleClassSize(unsigned long lSize)
{

}

CBaseParticle *IParticleMan_Active::CreateParticle(Vector org, Vector normal, struct model_s * sprite, float size, float brightness, const char *classname)
{
	return nullptr;
}

char *IParticleMan_Active::RequestNewMemBlock(int iSize)
{
	return nullptr;
}

void IParticleMan_Active::CoreInitializeSprite(CCoreTriangleEffect *pParticle, Vector org, Vector normal, struct model_s *sprite, float size, float brightness)
{

}

void IParticleMan_Active::CoreThink(CCoreTriangleEffect *pParticle, float time)
{

}

void IParticleMan_Active::CoreDraw(CCoreTriangleEffect *pParticle)
{

}

void IParticleMan_Active::CoreAnimate(CCoreTriangleEffect *pParticle, float time)
{

}

void IParticleMan_Active::CoreAnimateAndDie(CCoreTriangleEffect *pParticle, float time)
{

}

void IParticleMan_Active::CoreExpand(CCoreTriangleEffect *pParticle, float time)
{

}

void IParticleMan_Active::CoreContract(CCoreTriangleEffect *pParticle, float time)
{

}

void IParticleMan_Active::CoreFade(CCoreTriangleEffect *pParticle, float time)
{

}

void IParticleMan_Active::CoreSpin(CCoreTriangleEffect *pParticle, float time)
{

}

void IParticleMan_Active::CoreCalculateVelocity(CCoreTriangleEffect *pParticle, float time)
{

}

void IParticleMan_Active::CoreCheckCollision(CCoreTriangleEffect *pParticle, float time)
{

}

void IParticleMan_Active::CoreTouch(CCoreTriangleEffect *pParticle, Vector pos, Vector normal, int index)
{

}

void IParticleMan_Active::CoreDie(CCoreTriangleEffect *pParticle)
{

}

void IParticleMan_Active::CoreForce(CCoreTriangleEffect *pParticle)
{

}

bool IParticleMan_Active::CoreCheckVisibility(CCoreTriangleEffect *pParticle)
{
	return false;
}

void IParticleMan_Active::SetRender(int iRender)
{
	g_iRenderMode = iRender;
}

IBaseInterface* CreateParticleMan()
{
	return (IBaseInterface*)new IParticleMan_Active();
}

ForceList g_pForceList;

void main()
{
	g_pForceList.m_iElements = 0;
	g_pForceList.pFirst = 0;
	g_pForceList.pCurrent = 0;
	g_pForceList.pLast = 0;

	InterfaceReg::InterfaceReg(CreateParticleMan, "create_particleman");
}