#pragma once

#ifndef _DEFAULT_CUBE_H
#define _DEFAULT_CUBE_H

#include <cstdint>

namespace Rendering
{
	struct PosColorVertex
	{
		float x, y, z; // position
		uint32_t abgr; // color
	};

	static PosColorVertex cubeVertices[] =
	{
		{-1.0f,  1.0f,  1.0f, 0xff000000 },
		{ 1.0f,  1.0f,  1.0f, 0xff0000ff },
		{-1.0f, -1.0f,  1.0f, 0xff00ff00 },
		{ 1.0f, -1.0f,  1.0f, 0xff00ffff },
		{-1.0f,  1.0f, -1.0f, 0xffff0000 },
		{ 1.0f,  1.0f, -1.0f, 0xffff00ff },
		{-1.0f, -1.0f, -1.0f, 0xffffff00 },
		{ 1.0f, -1.0f, -1.0f, 0xffffffff },
	};

	static const uint16_t s_cubeTriList[] =
	{
		0, 1, 2, // 0
		1, 3, 2,
		4, 6, 5, // 2
		5, 6, 7,
		0, 2, 4, // 4
		4, 2, 6,
		1, 5, 3, // 6
		5, 7, 3,
		0, 4, 1, // 8
		4, 5, 1,
		2, 3, 6, // 10
		6, 3, 7,
	};

	static const uint16_t s_cubeTriStrip[] =
	{
		0, 1, 2,
		3,
		7,
		1,
		5,
		0,
		4,
		2,
		6,
		7,
		4,
		5,
	};

	static const uint16_t s_cubeLineList[] =
	{
		0, 1,
		0, 2,
		0, 4,
		1, 3,
		1, 5,
		2, 3,
		2, 6,
		3, 7,
		4, 5,
		4, 6,
		5, 7,
		6, 7,
	};

	static const uint16_t s_cubeLineStrip[] =
	{
		0, 2, 3, 1, 5, 7, 6, 4,
		0, 2, 6, 4, 5, 7, 3, 1,
		0,
	};

	static const uint16_t s_cubePoints[] =
	{
		0, 1, 2, 3, 4, 5, 6, 7
	};

	static const char* s_ptNames[]
	{
		"Triangle List",
		"Triangle Strip",
		"Lines",
		"Line Strip",
		"Points",
	};

	static const uint64_t s_ptState[]
	{
		UINT64_C(0)
		/*BGFX_STATE_PT_TRISTRIP,
		BGFX_STATE_PT_LINES,
		BGFX_STATE_PT_LINESTRIP,
		BGFX_STATE_PT_POINTS,*/
	};

	class DefaultCube
	{
	public:
		DefaultCube();
		~DefaultCube();

		void DescribeMesh();

	private:

	};
}

#endif _DEFAULT_CUBE_H