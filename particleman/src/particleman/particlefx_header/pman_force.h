#pragma once

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