//*****************************************************************************
// ツール [tool.cpp]
// Author : 管原　司
//*****************************************************************************

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "manager.h"
#include "renderer.h"
#include "time.h"
#include "mode.h"
#include "camera.h"
#include "scene.h"
#include "tool.h"
#include "ui.h"
#include "particle.h"
#include "particle_2.h"
#include <tchar.h>
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define ROT				(D3DXVECTOR3(0.0f,0.0f,0.0f))						// 向き
#define SIZE			(D3DXVECTOR3(50.0f,50.0f,0.0f))						// サイズ
#define COL				(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))					// 色
#define REMAINDER		(0)													// 余り
#define MIN_COLOR		(0.0f)												// 色の最小値
#define RANDOM_POS_MUT	(10.0f)												// 掛ける値
#define MUT				(2.0f)												// ２倍
//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CTool::CTool()
{
	m_pUi				= NULL;
	m_nCreateCount		= INIT_INT;
	m_nCreateCount_2	= INIT_INT;
}
//*****************************************************************************
//デストラクタ
//*****************************************************************************
CTool::~CTool()
{
}
//*****************************************************************************
//初期化処理
//*****************************************************************************
HRESULT CTool::Init(void)
{
	//カメラ
	CManager::CreateCamera();

	// UI生成
	m_pUi = CUI::Create();

	return S_OK;
}
//*****************************************************************************
//終了処理
//*****************************************************************************
void CTool::Uninit(void)
{
}
//*****************************************************************************
//更新処理
//*****************************************************************************
void CTool::Update(void)
{
	// パーティクル生成
	Particle_Create();
}
//*****************************************************************************
// 描画処理
//*****************************************************************************
void CTool::Draw(void)
{
}
//*****************************************************************************
// パーティクル生成処理
//*****************************************************************************
void CTool::Particle_Create(void)
{
	// エミッターがtrueの場合
	if (m_pUi->GetbEmitter() == true)
	{
		// インクリメント
		m_nCreateCount++;

		// 生成カウント
		int nDEVIDE = m_pUi->GetCreateCount();

		// 生成
		if (m_nCreateCount % nDEVIDE == REMAINDER)
		{
			// パーティクル生成
			CParticle::Create(m_pUi);
		}
	}
	// エフェクトがtrueの場合
	if (m_pUi->GetbEffect() == true)
	{
		// インクリメント
		m_nCreateCount++;

		// 生成カウント
		int nCreateCount = m_pUi->GetCreateCount();

		// 生成の総数
		int nCreateTotalCount = m_pUi->GetCreateTotalCount();

		// 生成
		if (m_nCreateCount == nCreateCount)
		{
			for (int nCnt = INIT_INT; nCnt < nCreateTotalCount; nCnt++)
			{
				// パーティクル生成
				CParticle::Create(m_pUi);
			}
			// 初期化
			m_nCreateCount = INIT_INT;
		}
		// m_nCreateCountがnCreateCountより大きい場合
		if (m_nCreateCount > nCreateCount)
		{
			// 初期化
			m_nCreateCount = INIT_INT;
		}
	}
	// エミッターがtrueの場合
	if (m_pUi->GetbEmitter_2() == true)
	{
		// インクリメント
		m_nCreateCount_2++;

		// 生成カウント
		int nDEVIDE = m_pUi->GetCreateCount_2();

		// 生成
		if (m_nCreateCount_2 % nDEVIDE == REMAINDER)
		{
			// パーティクル生成
			CParticle_2::Create(m_pUi);
		}
	}
	// エフェクトがtrueの場合
	if (m_pUi->GetbEffect_2() == true)
	{
		// インクリメント
		m_nCreateCount_2++;

		// 生成カウント
		int nCreateCount = m_pUi->GetCreateCount_2();

		// 生成の総数
		int nCreateTotalCount = m_pUi->GetCreateTotalCount_2();

		// 生成
		if (m_nCreateCount_2 == nCreateCount)
		{
			// 総数分繰り返す
			for (int nCnt = INIT_INT; nCnt < nCreateTotalCount; nCnt++)
			{
				// パーティクル生成
				CParticle_2::Create(m_pUi);
			}
			// 初期化
			m_nCreateCount_2 = INIT_INT;
		}
		// m_nCreateCountがnCreateCountより大きい場合
		if (m_nCreateCount_2 > nCreateCount)
		{
			// 初期化
			m_nCreateCount_2 = INIT_INT;
		}
	}
}