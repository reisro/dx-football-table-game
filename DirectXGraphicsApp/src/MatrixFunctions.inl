#pragma once

#ifndef MATRIXHELPER_H
#define MATRIXHELPER_H

#include <DirectXMath.h>
#include <DirectXPackedVector.h>

class MatrixHelper
{
public:
	static DirectX::XMMATRIX InverseTranspose(DirectX::CXMMATRIX M)
	{
		using namespace DirectX;
		XMMATRIX A = M;
		A.r[3] = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
		XMVECTOR det = XMMatrixDeterminant(A);
		return XMMatrixTranspose(XMMatrixInverse(&det, A));
	}
};

#endif MATRIXHELPER_H