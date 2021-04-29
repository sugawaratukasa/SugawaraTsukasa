//******************************************************************************
// ブロック[block.cpp]
// Author : 管原 司
//******************************************************************************

//******************************************************************************
//インクルードファイル
//******************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "../3D/Model/model.h"
#include "../3D/Model/Object/3d_obj.h"
#include "../3D/Model/Enemy/enemy_map.h"
#include "../3D/3DPolygon/Particle/Particle_Effect/particle_effect.h"
#include "floor_block.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define POS	(D3DXVECTOR3(pos.x,pos.y,pos.z - 15.0f))
//******************************************************************************
//静的メンバ変数
//******************************************************************************

//******************************************************************************
// コンストラクタ
//******************************************************************************
CFloor_Block::CFloor_Block(int nPriority) : C3D_Obj(nPriority)
{
	m_Type = TYPE_NORMAL;
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CFloor_Block::~CFloor_Block()
{

}
//******************************************************************************
// 生成関数
//******************************************************************************
CFloor_Block * CFloor_Block::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, TYPE type)
{
	// CObj_Floorのポインタ
	CFloor_Block *pFloor = NULL;

	// NULLの場合
	if (pFloor == NULL)
	{
		// メモリ確保
		pFloor = new CFloor_Block;

		// NULLでない場合
		if (pFloor != NULL)
		{
			// 情報設定
			pFloor->SetModel(pos, rot, size, C3D_Obj::TYPE_FLOOR_01);

			// 種類代入
			pFloor->m_Type = type;

			// 初期化
			pFloor->Init();
		}
	}
	// ポインタを返す
	return pFloor;
}
//******************************************************************************
// 初期化処理
//******************************************************************************
HRESULT CFloor_Block::Init(void)
{
	// 初期化
	C3D_Obj::Init();

	// 位置
	D3DXVECTOR3 pos = GetPos();

	// ENEMYの場合
	if (m_Type == TYPE_ENEMY)
	{
		// エフェクト生成
		CParticle_Effect::Create(POS, CParticle_Effect::TYPE_BLOCK_EFFECT);
	}
	return S_OK;
}
//******************************************************************************
// 終了処理
//******************************************************************************
void CFloor_Block::Uninit(void)
{
	// 終了
	C3D_Obj::Uninit();
}
//******************************************************************************
// 更新処理
//******************************************************************************
void CFloor_Block::Update(void)
{
	// 更新
	C3D_Obj::Update();

	// 位置
	D3DXVECTOR3 pos = GetPos();

	// ENEMYの場合
	if (m_Type == TYPE_ENEMY)
	{
		// CSceneのポインタ
		CScene *pScene = NULL;
		do 
		{
			// シーン取得
			pScene = GetScene(OBJTYPE_ENEMY_MAP);

			// NULLでない場合
			if (pScene != NULL)
			{
				// オブジェクトタイプ取得
				OBJTYPE objtype = pScene->GetObjType();

				// ENEMY_MAPの場合
				if (objtype == OBJTYPE_ENEMY_MAP)
				{
					// 判定取得
					bool bEnd = ((CEnemy_Map*)pScene)->GetbEnd();

					// trueの場合
					if (bEnd == true)
					{
						// エフェクト生成
						CParticle_Effect::Create(POS, CParticle_Effect::TYPE_BLOCK_EFFECT);

						// 終了
						Uninit();
						return;
					}
				}

			}
			// NULLになるまで繰り返す
		} while (pScene != NULL);
	}
}

//******************************************************************************
// 描画処理
//******************************************************************************
void CFloor_Block::Draw(void)
{
	// 描画
	C3D_Obj::Draw();
}