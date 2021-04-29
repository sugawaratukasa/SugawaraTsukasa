//******************************************************************************
// ポーズ [pause.cpp]
// Author : 管原司
//******************************************************************************
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "joystick.h"
#include "2d_polygon.h"
#include "fade.h"
#include "mode.h"
#include "game.h"
#include "../3D/Model/player.h"
#include "../2D/2D_Particle/2d_particle_emitter.h"
#include "magic_ui.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define POS			(D3DXVECTOR3(100.0f,50.0f,0.0f))	// 位置
#define EFFECT_POS	(D3DXVECTOR3(100.0f,60.0f,0.0f))	// 位置
#define SIZE		(D3DXVECTOR3(100.0f,100.0f,0.0f))	// サイズ
#define SIZE2		(D3DXVECTOR3(0.0f,0.0f,0.0f))		// サイズ2
#define COL			(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))	// 色
//******************************************************************************
// コンストラクタ
//******************************************************************************
CMagic_UI::CMagic_UI(int nPriority) : CScene(nPriority)
{
	m_p2D_Particle_Emitter	= NULL;
	m_nMagicType			= INIT_INT;
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CMagic_UI::~CMagic_UI()
{
}
//******************************************************************************
// 生成関数
//******************************************************************************
CMagic_UI * CMagic_UI::Create(void)
{
	// CMagic_UIのポインタ
	CMagic_UI *pMagic_UI = NULL;

	// NULLの場合
	if (pMagic_UI == NULL)
	{
		// メモリ確保
		pMagic_UI = new CMagic_UI;

		// NULLでない場合
		if (pMagic_UI != NULL)
		{
			// オブジェクトタイプ設定
			pMagic_UI->SetObjType(OBJTYPE_NOSTOP_UI);

			// 初期化
			pMagic_UI->Init();
		}
	}
	// ポインタを返す
	return pMagic_UI;
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CMagic_UI::Init(void)
{
	// 生成
	C2D_Polygon::Create(POS, SIZE, C2D_Polygon::TYPE_MAGIC_UI);

	// 放射体生成
	m_p2D_Particle_Emitter = C2D_Particle_Emitter::Create(EFFECT_POS, C2D_Particle_Emitter::TYPE_FIRE);
	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CMagic_UI::Uninit(void)
{
	// 破棄
	CScene::Release();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CMagic_UI::Update(void)
{
	// CSceneのポインタ
	CScene *pScene = NULL;

	// プレイヤー取得
	do 
	{
		// ポインタ取得
		pScene = GetScene(OBJTYPE_PLAYER);

		// NULLでない場合
		if (pScene != NULL)
		{
			// オブジェクトタイプ取得
			OBJTYPE objtype = pScene->GetObjType();

			// OBJTYPE_PLAYERの場合
			if (objtype == OBJTYPE_PLAYER)
			{
				// タイプ取得
				int nMagicType = ((CPlayer*)pScene)->GetMagicType();

				// 現在の種類と違う場合
				if (m_nMagicType != nMagicType)
				{
					// FIRE_BALLの場合
					if (nMagicType == CPlayer::MAGIC_TYPE_FIREBALL)
					{
						// NULLの場合
						if (m_p2D_Particle_Emitter != NULL)
						{
							// 破棄
							m_p2D_Particle_Emitter->Uninit();

							// NULLに
							m_p2D_Particle_Emitter = NULL;
						}
						// NULLの場合
						if (m_p2D_Particle_Emitter == NULL)
						{
							// 生成
							m_p2D_Particle_Emitter = C2D_Particle_Emitter::Create(EFFECT_POS, C2D_Particle_Emitter::TYPE_FIRE);
						}
					}
					// ICE_BALLの場合
					if (nMagicType == CPlayer::MAGIC_TYPE_ICEBALL)
					{
						// NULLの場合
						if (m_p2D_Particle_Emitter != NULL)
						{
							// 破棄
							m_p2D_Particle_Emitter->Uninit();

							// NULLに
							m_p2D_Particle_Emitter = NULL;
						}
						// NULLの場合
						if (m_p2D_Particle_Emitter == NULL)
						{
							// 生成
							m_p2D_Particle_Emitter = C2D_Particle_Emitter::Create(EFFECT_POS, C2D_Particle_Emitter::TYPE_ICE);
						}
					}

					// 代入
					m_nMagicType = nMagicType;
				}
			}
		}
		// NULLになるまで繰り返す
	} while (pScene != NULL);
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CMagic_UI::Draw(void)
{
}