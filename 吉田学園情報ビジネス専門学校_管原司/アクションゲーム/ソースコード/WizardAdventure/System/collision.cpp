//******************************************************************************
// 当たり判定 [collision.cpp]
// Author : 管原　司
//******************************************************************************
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "collision.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define DEVIDE_VALUE	(2)		// 割る数
#define SQUARE			(2.0f)	// 2乗
//******************************************************************************
// 立方体の当たり判定
//******************************************************************************
bool CCollision::RectangleCollision(D3DXVECTOR3 pPos1, D3DXVECTOR3 size1, D3DXVECTOR3 pPos2, D3DXVECTOR3 size2)
{
	bool bHit = false;

	D3DXVECTOR3 box1Max = D3DXVECTOR3(size1.x / DEVIDE_VALUE, size1.y / DEVIDE_VALUE, size1.z / DEVIDE_VALUE) + pPos1;          //ぶつかる側の最大値
	D3DXVECTOR3 box1Min = D3DXVECTOR3(-size1.x / DEVIDE_VALUE, -size1.y / DEVIDE_VALUE, -size1.z / DEVIDE_VALUE) + pPos1;       //ぶつかる側の最小値
	D3DXVECTOR3 box2Max = D3DXVECTOR3(size2.x / DEVIDE_VALUE, size2.y / DEVIDE_VALUE, size2.z / DEVIDE_VALUE) + pPos2;      //ぶつかられる側の最大値
	D3DXVECTOR3 box2Min = D3DXVECTOR3(-size2.x / DEVIDE_VALUE, -size2.y / DEVIDE_VALUE, -size2.z / DEVIDE_VALUE) + pPos2;   //ぶつかられる側の最小値

	if (box1Max.y > box2Min.y&&
		box1Min.y < box2Max.y&&
		box1Max.x > box2Min.x&&
		box1Min.x < box2Max.x&&
		box1Max.z > box2Min.z&&
		box1Min.z < box2Max.z)
	{
		bHit = true;
	}

	// 当たったかどうかを返す
	return bHit;
}
//******************************************************************************
// 円形の当たり判定
//******************************************************************************
bool CCollision::SphereCollision(D3DXVECTOR3 pos1, float size1, D3DXVECTOR3 pos2, float size2)
{
	// 位置
	float distance = powf(pos1.x - pos2.x, SQUARE) + powf(pos1.y - pos2.y, SQUARE) + powf(pos1.z - pos2.z, SQUARE);

	// 半径
	float radius = powf(size1 + size2, SQUARE);

	// めり込んでいるか
	return (distance < radius);
}
//******************************************************************************
// 立方体の当たり判定
//******************************************************************************
int CCollision::RectangleCollisionMove(D3DXVECTOR3 pPos1, D3DXVECTOR3 pPosOld, D3DXVECTOR3 size1, D3DXVECTOR3 pPos2, D3DXVECTOR3 size2)
{
	int nSurFace = INIT_INT;

	D3DXVECTOR3 box1Max = D3DXVECTOR3(size1.x / DEVIDE_VALUE, size1.y / DEVIDE_VALUE, size1.z / DEVIDE_VALUE) + pPos1;
	D3DXVECTOR3 box1Min = D3DXVECTOR3(-size1.x / DEVIDE_VALUE, -size1.y / DEVIDE_VALUE, -size1.z / DEVIDE_VALUE) + pPos1;
	D3DXVECTOR3 box2Max = D3DXVECTOR3(size2.x / DEVIDE_VALUE, size2.y / DEVIDE_VALUE, size2.z / DEVIDE_VALUE) + pPos2;
	D3DXVECTOR3 box2Min = D3DXVECTOR3(-size2.x / DEVIDE_VALUE, -size2.y / DEVIDE_VALUE, -size2.z / DEVIDE_VALUE) + pPos2;

	if (box1Max.y > box2Min.y &&	// 下
		box1Min.y < box2Max.y &&	// 上
		box1Max.x > box2Min.x &&	// 右から
		box1Min.x < box2Max.x &&	// 左から
		box1Max.z > box2Min.z &&	// 奥から
		box1Min.z < box2Max.z)		// 手前
	{
		
		// 下
		if (box1Max.y > box2Min.y && pPosOld.y <= box2Min.y)
		{
			// 下
			nSurFace = SURFACE_DOWN;
		}
		// 上
		if (box1Min.y < box2Max.y && pPosOld.y >= box2Max.y)
		{
			// 上
			nSurFace = SURFACE_UP;
		}
		// 左
		if (box1Max.x > box2Min.x && pPosOld.x <= box2Min.x)
		{
			// 左
			nSurFace = SURFACE_LEFT;
		}
		// 右
		if (box1Min.x < box2Max.x && pPosOld.x >= box2Max.x)
		{
			// 右
			nSurFace = SURFACE_RIGHT;
		}
	}
	// 当たった面を返す
	return nSurFace;
}
