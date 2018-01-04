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

CMiniMem::CMiniMem(long lMemoryPoolSize, long lMaxBlockSize)
{

}

CMiniMem::~CMiniMem()
{

}

char* CMiniMem::AllocateFreeBlock()
{
	return nullptr;
}

char* CMiniMem::newBlock(void)
{
	return nullptr;
}

void CMiniMem::deleteBlock(MemoryBlock *p)
{

}

long CMiniMem::PercentUsed(void)
{
	return 0;
}

void CMiniMem::ProcessAll(void)
{

}

void CMiniMem::Reset(void)
{

}

int CMiniMem::ApplyForce(Vector vOrigin, Vector vDirection, float flRadius, float flStrength)
{
	return 0;
}

CMiniMem* CMiniMem::Instance(void)
{
	return nullptr;
}

long CMiniMem::MaxBlockSize(void)
{
	return 0;
}

bool CMiniMem::CheckSize(int iSize)
{
	return false;
}

void CMiniMem::Shutdown(void)
{

}