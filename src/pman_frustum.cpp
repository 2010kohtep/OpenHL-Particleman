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

#include "pman_frustum.h"
#include <math.h>

void CFrustum::CalculateFrustum()
{
	float   proj[16]; // This will hold our projection matrix
	float   modl[16]; // This will hold our modelview matrix
	float   clip[16]; // This will hold the clipping planes

	// glGetFloatv(GL_PROJECTION_MATRIX, proj);
	// glGetFloatv(GL_MODELVIEW_MATRIX, modl);

	clip[0] = modl[0] * proj[0] + modl[1] * proj[4] + modl[2] * proj[8] + modl[3] * proj[12];
	clip[1] = modl[0] * proj[1] + modl[1] * proj[5] + modl[2] * proj[9] + modl[3] * proj[13];
	clip[2] = modl[0] * proj[2] + modl[1] * proj[6] + modl[2] * proj[10] + modl[3] * proj[14];
	clip[3] = modl[0] * proj[3] + modl[1] * proj[7] + modl[2] * proj[11] + modl[3] * proj[15];

	clip[4] = modl[4] * proj[0] + modl[5] * proj[4] + modl[6] * proj[8] + modl[7] * proj[12];
	clip[5] = modl[4] * proj[1] + modl[5] * proj[5] + modl[6] * proj[9] + modl[7] * proj[13];
	clip[6] = modl[4] * proj[2] + modl[5] * proj[6] + modl[6] * proj[10] + modl[7] * proj[14];
	clip[7] = modl[4] * proj[3] + modl[5] * proj[7] + modl[6] * proj[11] + modl[7] * proj[15];

	clip[8] = modl[8] * proj[0] + modl[9] * proj[4] + modl[10] * proj[8] + modl[11] * proj[12];
	clip[9] = modl[8] * proj[1] + modl[9] * proj[5] + modl[10] * proj[9] + modl[11] * proj[13];
	clip[10] = modl[8] * proj[2] + modl[9] * proj[6] + modl[10] * proj[10] + modl[11] * proj[14];
	clip[11] = modl[8] * proj[3] + modl[9] * proj[7] + modl[10] * proj[11] + modl[11] * proj[15];

	clip[12] = modl[12] * proj[0] + modl[13] * proj[4] + modl[14] * proj[8] + modl[15] * proj[12];
	clip[13] = modl[12] * proj[1] + modl[13] * proj[5] + modl[14] * proj[9] + modl[15] * proj[13];
	clip[14] = modl[12] * proj[2] + modl[13] * proj[6] + modl[14] * proj[10] + modl[15] * proj[14];
	clip[15] = modl[12] * proj[3] + modl[13] * proj[7] + modl[14] * proj[11] + modl[15] * proj[15];

	g_flFrustum[RIGHT][A] = clip[3] - clip[0];
	g_flFrustum[RIGHT][B] = clip[7] - clip[4];
	g_flFrustum[RIGHT][C] = clip[11] - clip[8];
	g_flFrustum[RIGHT][D] = clip[15] - clip[12];

	NormalizeFrustumPlane((float **)g_flFrustum, RIGHT);

	g_flFrustum[LEFT][A] = clip[3] + clip[0];
	g_flFrustum[LEFT][B] = clip[7] + clip[4];
	g_flFrustum[LEFT][C] = clip[11] + clip[8];
	g_flFrustum[LEFT][D] = clip[15] + clip[12];

	NormalizeFrustumPlane((float **)g_flFrustum, LEFT);

	g_flFrustum[BOTTOM][A] = clip[3] + clip[1];
	g_flFrustum[BOTTOM][B] = clip[7] + clip[5];
	g_flFrustum[BOTTOM][C] = clip[11] + clip[9];
	g_flFrustum[BOTTOM][D] = clip[15] + clip[13];

	NormalizeFrustumPlane((float **)g_flFrustum, BOTTOM);

	g_flFrustum[TOP][A] = clip[3] - clip[1];
	g_flFrustum[TOP][B] = clip[7] - clip[5];
	g_flFrustum[TOP][C] = clip[11] - clip[9];
	g_flFrustum[TOP][D] = clip[15] - clip[13];

	NormalizeFrustumPlane((float **)g_flFrustum, TOP);

	g_flFrustum[BACK][A] = clip[3] - clip[2];
	g_flFrustum[BACK][B] = clip[7] - clip[6];
	g_flFrustum[BACK][C] = clip[11] - clip[10];
	g_flFrustum[BACK][D] = clip[15] - clip[14];

	NormalizeFrustumPlane((float **)g_flFrustum, BACK);

	g_flFrustum[FRONT][A] = clip[3] + clip[2];
	g_flFrustum[FRONT][B] = clip[7] + clip[6];
	g_flFrustum[FRONT][C] = clip[11] + clip[10];
	g_flFrustum[FRONT][D] = clip[15] + clip[14];

	NormalizeFrustumPlane((float **)g_flFrustum, FRONT);
}

void CFrustum::NormalizeFrustumPlane(float** frustum, int side)
{
	float magnitude = (float)sqrt(frustum[side][A] * frustum[side][A] + frustum[side][B] * frustum[side][B] + frustum[side][C] * frustum[side][C]);
	
	frustum[side][A] /= magnitude;
	frustum[side][B] /= magnitude;
	frustum[side][C] /= magnitude;
	frustum[side][D] /= magnitude;
}

bool CFrustum::PlaneInsideFrustum(float x, float y, float z, float size)
{
	return true;
}

bool CFrustum::PointInsideFrustum(float x, float y, float z)
{
	if (g_flFrustum[0][A] * x + g_flFrustum[0][B] * y + g_flFrustum[0][C] * z + g_flFrustum[0][D] > 0.0f) return false;
	if (g_flFrustum[1][A] * x + g_flFrustum[1][B] * y + g_flFrustum[1][C] * z + g_flFrustum[1][D] > 0.0f) return false;
	if (g_flFrustum[2][A] * x + g_flFrustum[2][B] * y + g_flFrustum[2][C] * z + g_flFrustum[2][D] > 0.0f) return false;
	if (g_flFrustum[3][A] * x + g_flFrustum[3][B] * y + g_flFrustum[3][C] * z + g_flFrustum[3][D] > 0.0f) return false;
	if (g_flFrustum[4][A] * x + g_flFrustum[4][B] * y + g_flFrustum[4][C] * z + g_flFrustum[4][D] > 0.0f) return false;
	if (g_flFrustum[5][A] * x + g_flFrustum[5][B] * y + g_flFrustum[5][C] * z + g_flFrustum[5][D] > 0.0f) return false;

	return true;
}

bool CFrustum::SphereInsideFrustum(float x, float y, float z, float radius)
{
	radius *= 1.5f;
	if (g_flFrustum[0][A] * x + g_flFrustum[0][B] * y + g_flFrustum[0][C] * z + g_flFrustum[0][D] <= -radius) return false;
	if (g_flFrustum[1][A] * x + g_flFrustum[1][B] * y + g_flFrustum[1][C] * z + g_flFrustum[1][D] <= -radius) return false;
	if (g_flFrustum[2][A] * x + g_flFrustum[2][B] * y + g_flFrustum[2][C] * z + g_flFrustum[2][D] <= -radius) return false;
	if (g_flFrustum[3][A] * x + g_flFrustum[3][B] * y + g_flFrustum[3][C] * z + g_flFrustum[3][D] <= -radius) return false;
	if (g_flFrustum[4][A] * x + g_flFrustum[4][B] * y + g_flFrustum[4][C] * z + g_flFrustum[4][D] <= -radius) return false;
	if (g_flFrustum[5][A] * x + g_flFrustum[5][B] * y + g_flFrustum[5][C] * z + g_flFrustum[5][D] <= -radius) return false;

	return true;
}