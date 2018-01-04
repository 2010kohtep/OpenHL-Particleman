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

enum FrustumSide
{
	RIGHT = 0,  // The RIGHT side of the frustum
	LEFT = 1,   // The LEFT      side of the frustum
	BOTTOM = 2, // The BOTTOM side of the frustum
	TOP = 3,    // The TOP side of the frustum
	BACK = 4,   // The BACK     side of the frustum
	FRONT = 5   // The FRONT side of the frustum
};


enum PlaneData
{
	A = 0, // The X value of the plane's normal
	B = 1, // The Y value of the plane's normal
	C = 2, // The Z value of the plane's normal
	D = 3  // The distance the plane is from the origin
};

class CFrustum
{
private:
	float g_flFrustum[6][4];
public:
	void CalculateFrustum();
	void NormalizeFrustumPlane(float** frustum, int side); // float* frustum[4]
	bool PlaneInsideFrustum(float x, float y, float z, float size);
	bool PointInsideFrustum(float x, float y, float z);
	bool SphereInsideFrustum(float x, float y, float z, float radius);
};