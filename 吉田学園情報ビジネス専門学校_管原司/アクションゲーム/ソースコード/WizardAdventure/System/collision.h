//******************************************************************************
// 当たり判定 [collision.h]
// Author : 管原　司
//******************************************************************************
#ifndef _COLLISION_H_
#define _COLLISION_H_
//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include"main.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// クラス
//*****************************************************************************
class CCollision
{
public:
	// どこの面に当たったか
	typedef enum
	{
		SURFACE_NONE = 0,
		SURFACE_UP,
		SURFACE_DOWN,
		SURFACE_RIGHT,
		SURFACE_LEFT,
	}SURFACE;

	static bool RectangleCollision(D3DXVECTOR3 pPos1, D3DXVECTOR3 size1, D3DXVECTOR3 pPos2, D3DXVECTOR3 size2);
	static bool SphereCollision(D3DXVECTOR3 pos1, float size1, D3DXVECTOR3 pos2, float size2);
	static int RectangleCollisionMove(D3DXVECTOR3 pPos1, D3DXVECTOR3 pPosOld, D3DXVECTOR3 size1, D3DXVECTOR3 pPos2, D3DXVECTOR3 size2);
private:

};
#endif