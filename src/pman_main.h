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

#pragma once

#include "particleman.h"
#include "pman_math.h"
#include "pman_triangleffect.h"
#include "vector.h"

struct ForceMember
{
	int m_iIndex;
	ForceMember* m_pNext;
	ForceMember* m_pPrevious;
	Vector m_vOrigin;
	Vector m_vDirection;
	float m_flRadius;
	float m_flStrength;
	float m_flDieTime;
};

struct ForceList
{
	int m_iElements;
	ForceMember* pFirst;
	ForceMember* pCurrent;
	ForceMember* pLast;
};

class IParticleMan_Active : public IParticleMan
{
protected:
	virtual ~IParticleMan_Active() {};
public:
	virtual void SetUp(struct cl_enginefunc_t* pEnginefuncs);
	virtual void Update();
	virtual void SetVariables(float flGravity, Vector vViewAngles);
	virtual void ResetParticles();
	virtual void ApplyForce(Vector vOrigin, Vector vDirection, float flRadius, float flStrength, float flDuration);
	virtual void AddCustomParticleClassSize(unsigned long lSize);
	virtual CBaseParticle *CreateParticle(Vector org, Vector normal, struct model_s * sprite, float size, float brightness, const char *classname);
	virtual char *RequestNewMemBlock(int iSize);
	virtual void CoreInitializeSprite(CCoreTriangleEffect *pParticle, Vector org, Vector normal, struct model_s *sprite, float size, float brightness);
	virtual void CoreThink(CCoreTriangleEffect *pParticle, float time);
	virtual void CoreDraw(CCoreTriangleEffect *pParticle);
	virtual void CoreAnimate(CCoreTriangleEffect *pParticle, float time);
	virtual void CoreAnimateAndDie(CCoreTriangleEffect *pParticle, float time);
	virtual void CoreExpand(CCoreTriangleEffect *pParticle, float time);
	virtual void CoreContract(CCoreTriangleEffect *pParticle, float time);
	virtual void CoreFade(CCoreTriangleEffect *pParticle, float time);
	virtual void CoreSpin(CCoreTriangleEffect *pParticle, float time);
	virtual void CoreCalculateVelocity(CCoreTriangleEffect *pParticle, float time);
	virtual void CoreCheckCollision(CCoreTriangleEffect *pParticle, float time);
	virtual void CoreTouch(CCoreTriangleEffect *pParticle, Vector pos, Vector normal, int index);
	virtual void CoreDie(CCoreTriangleEffect *pParticle);
	virtual void CoreForce(CCoreTriangleEffect *pParticle);
	virtual bool CoreCheckVisibility(CCoreTriangleEffect *pParticle);
	virtual void SetRender(int iRender);
};