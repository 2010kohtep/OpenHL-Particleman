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

#include "vector.h"
#include <vector>

class CCoreTriangleEffect;

#define TRIANGLE_FPS 30

typedef struct visibleparticles_s
{
	CCoreTriangleEffect *pVisibleParticle;
} visibleparticles_t;

class MemoryBlock
{
private:
	char *m_pData;
public:
	MemoryBlock(long lBlockSize) : next(NULL), prev(NULL)
	{
		m_pData = new char[lBlockSize];
	}

	virtual ~MemoryBlock()
	{
		delete[] m_pData;
	}

	/**
	 * Returns current m_pData value.
	 */
	inline char *Memory(void) { return m_pData; }

	MemoryBlock * next;
	MemoryBlock * prev;
};

class MemList
{
public:
	MemList() : m_pHead(NULL) {}

	~MemList() { Reset(); }

	void Push(MemoryBlock * newItem)
	{
		if (!m_pHead)
		{
			m_pHead = newItem;
			newItem->next = NULL;
			newItem->prev = NULL;
			return;
		}

		MemoryBlock * temp = m_pHead;
		m_pHead = newItem;
		m_pHead->next = temp;
		m_pHead->prev = NULL;

		temp->prev = m_pHead;
	}

	/**
	 * Returns current m_pHead value.
	 */
	MemoryBlock * Front(void)
	{
		return m_pHead;
	}

	MemoryBlock * Pop(void)
	{
		if (!m_pHead)
			return NULL;

		MemoryBlock * temp = m_pHead;

		m_pHead = m_pHead->next;

		if (m_pHead)
			m_pHead->prev = NULL;

		temp->next = NULL;
		temp->prev = NULL;

		return(temp);
	}

	void Delete(MemoryBlock * pItem)
	{

		if (m_pHead == pItem)
		{
			MemoryBlock * temp = m_pHead;

			m_pHead = m_pHead->next;
			if (m_pHead)
				m_pHead->prev = NULL;

			temp->next = NULL;
			temp->prev = NULL;
			return;
		}

		MemoryBlock * prev = pItem->prev;
		MemoryBlock * next = pItem->next;

		if (prev)
			prev->next = next;

		if (next)
			next->prev = prev;

		pItem->next = NULL;
		pItem->prev = NULL;
	}

	void Reset(void)
	{
		while (m_pHead)
			Delete(m_pHead);
	}

private:
	MemoryBlock * m_pHead;
};

typedef std::vector<MemoryBlock *> VectorOfMemoryBlocks;
typedef VectorOfMemoryBlocks::iterator MemoryBlockIterator;

/* Singleton memory class. */
class CMiniMem
{
private:
	static VectorOfMemoryBlocks m_vecMemoryPool;

	static long m_lMemoryBlockSize;
	static long m_lMaxBlocks;
	static long m_lMemoryPoolSize;
	static CMiniMem *_instance;

	int m_iTotalParticles;
	int m_iParticlesDrawn;

	MemList m_ActiveMem;
	MemoryBlock* m_FreeMem;

protected:
	CMiniMem(long lMemoryPoolSize, long lMaxBlockSize);
	CMiniMem(long lMaxBlockSize);
	virtual ~CMiniMem();

	char *AllocateFreeBlock(void);
public:

	// Return a pointer to usable block of memory.
	char *newBlock(void);

	// Mark a target memory item as no longer "in use".
	void deleteBlock(MemoryBlock *p);

	// Return the remaining capacity of the memory pool as a percent.
	long PercentUsed(void);

	// Processes all.
	void ProcessAll(void);

	// Clears memory, setting all particles to not used.
	void Reset(void);

	static int ApplyForce(Vector vOrigin, Vector vDirection, float flRadius, float flStrength);

	static CMiniMem *Instance(void);
	static long MaxBlockSize(void);

	bool CheckSize(int iSize);

	int GetTotalParticles(void) { return m_iTotalParticles; }
	int GetDrawnParticles(void) { return m_iParticlesDrawn; }
	void IncreaseParticlesDrawn(void) { m_iParticlesDrawn++; }

	void Shutdown(void);

	visibleparticles_t *m_pVisibleParticles;
};