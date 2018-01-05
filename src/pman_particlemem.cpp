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

#include "pman_particlemem.h"
#include "pman_main.h"
#include <stdlib.h> // qsort

long CMiniMem::m_lMemoryPoolSize = 0;
long CMiniMem::m_lMemoryBlockSize = 0;
long CMiniMem::m_lMaxBlocks = 0;
CMiniMem *CMiniMem::_instance = nullptr;

CMiniMem::CMiniMem(long lMemoryPoolSize, long lMaxBlockSize)
{
	// m_lMemoryPoolSize = lMemoryPoolSize;
	// m_lMemoryBlockSize = lMaxBlockSize;
	// m_lMaxBlocks = lMemoryPoolSize / sizeof MemoryBlock;
	// 
	// if (lMemoryPoolSize / 16 != 0)
	// {
	// 	int i = 0;
	// 
	// 	do
	// 	{
	// 		while (true)
	// 		{
	// 			auto block = new MemoryBlock(m_lMemoryBlockSize);
	// 			block->next = nullptr;
	// 			block->prev = nullptr;
	// 
	// 			// typedef std::vector<MemoryBlock *> VectorOfMemoryBlocks;
	// 			// typedef VectorOfMemoryBlocks::iterator MemoryBlockIterator;
	// 
	// 			// v7 = CMiniMem::m_vecMemoryPool.baseclass_0._M_impl._M_finish;
	// 
	// 			if (true /* v7 == CMiniMem::m_vecMemoryPool.baseclass_0._M_impl._M_end_of_storage */)
	// 			{
	// 
	// 			}
	// 			else
	// 			{
	// 				// std::allocator<MemoryBlock*>::pointer v8;
	// 			}
	// 		}
	// 
	// 		i++;
	// 	}
	// }
}

CMiniMem::CMiniMem(long lMaxBlockSize)
{

}

CMiniMem::~CMiniMem()
{

}

char* CMiniMem::AllocateFreeBlock()
{
	return nullptr;
}

// done, unchecked
char* CMiniMem::newBlock(void)
{
	if (!m_FreeMem)
	{
	Exit:
		gEngfuncs.Con_DPrintf("Particleman is out of memory, too many particles");
		return nullptr;
	}
	
	m_FreeMem = m_FreeMem->next;
	if (m_FreeMem)
		m_FreeMem->prev = nullptr;
	
	auto pHead = m_ActiveMem.Front();
	m_FreeMem->next = nullptr;
	m_FreeMem->prev = nullptr;

	if (pHead)
	{
		m_FreeMem->next = nullptr;
		pHead->prev = nullptr;
	}

	auto pRes = m_FreeMem->Memory();
	if (!pRes)
		goto Exit;

	return pRes;
}

void CMiniMem::deleteBlock(MemoryBlock *p)
{
	if (p == m_ActiveMem.Front())
	{
		
	}
}

// done, unchecked
long CMiniMem::PercentUsed(void)
{
	auto uCount = 0u;
	auto pMem = m_FreeMem;
	
	while (pMem)
	{
		uCount++;
		pMem = pMem->next;
	}

	return 100 * uCount / m_lMaxBlocks;
}

int __cdecl ParticleSortFn(const void* p1, const void* p2)
{
	auto fp1Dist = ((visibleparticles_t *)p1)->pVisibleParticle->GetPlayerDistance();
	auto fp2Dist = ((visibleparticles_t *)p2)->pVisibleParticle->GetPlayerDistance();

	if (fp2Dist >= fp1Dist)
		return fp2Dist != fp1Dist;
	else
		return -1;
}

// done, unchecked
void CMiniMem::ProcessAll(void)
{
	auto fClTime = gEngfuncs.GetClientTime();
	auto pHead = m_ActiveMem.Front();

	this->m_iTotalParticles = 0;
	this->m_iTotalParticles = 0;
	memset(this->m_pVisibleParticles, 0, m_lMaxBlocks * sizeof visibleparticles_t);

	while (pHead)
	{
		auto pParticle = (CCoreTriangleEffect *)pHead->Memory();

		if (pParticle)
		{
			auto pData = pHead->Memory();
			this->m_iTotalParticles++;

			if (pParticle->CheckVisibility())
			{
				Vector plyOrg = gEngfuncs.GetLocalPlayer()->origin; // Player origin
				Vector prtOrg = pParticle->m_vOrigin;               // Particle origin

				auto fDiffX = plyOrg.x - prtOrg.x;
				auto fDiffY = plyOrg.y - prtOrg.y;
				auto fDiffZ = plyOrg.z - prtOrg.z;
				auto fDistance = (fDiffX * fDiffX) + (fDiffY * fDiffY) + (fDiffZ + fDiffZ);

				pParticle->SetPlayerDistance(fDistance);
				this->m_pVisibleParticles->pVisibleParticle = pParticle;
				CMiniMem::Instance()->m_iParticlesDrawn++;
			}
		
			if (!IsGamePaused())
				pParticle->Think(fClTime);

			if (pParticle->m_flDieTime == 0.0f || pParticle->m_flDieTime > fClTime)
				pHead = pHead->next;
			else
			{
				pParticle->Die();
				auto pCurHead = pHead;
				pHead = pHead->next;
				CMiniMem::deleteBlock(pHead);
			}
		}
	}

	qsort(this->m_pVisibleParticles, this->m_iParticlesDrawn, sizeof visibleparticles_t, ParticleSortFn);

	if (this->m_iParticlesDrawn <= 0)
	{
		g_flOldTime = fClTime;
	}
	else
	{
		for (int i = 0; i < this->m_iParticlesDrawn; i++)
			this->m_pVisibleParticles[i].pVisibleParticle->Draw();

		g_flOldTime = fClTime;
	}
}

void CMiniMem::Reset(void)
{

}

int CMiniMem::ApplyForce(Vector vOrigin, Vector vDirection, float flRadius, float flStrength)
{
	return 0;
}

// TODO: move it to another place
unsigned int g_lMaxParticleClassSize;

// done, unchecked
CMiniMem* CMiniMem::Instance(void)
{
	auto instance = _instance;

	if (instance)
		return instance;

	instance = new CMiniMem(30000, g_lMaxParticleClassSize);
	return instance;
}

// done, unchecked
long CMiniMem::MaxBlockSize(void)
{
	return m_lMemoryBlockSize;
}

// done, unchecked
bool CMiniMem::CheckSize(int iSize)
{
	if (_instance)
		return iSize <= m_lMemoryBlockSize;

	auto instance = new CMiniMem(g_lMaxParticleClassSize);
	_instance = instance;

	return iSize <= m_lMemoryBlockSize;
}

// done, unchecked
void CMiniMem::Shutdown(void)
{
	if (_instance)
		_instance->~CMiniMem();
}