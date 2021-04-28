//******************************************************************************
// 敵のライフゲージ [enemy_life_gage.cpp]
// Author : 管原司
//******************************************************************************
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "manager.h"
#include "ui_texture.h"
#include "../3D/Model/Enemy/enemy.h"
#include "3d_gage_back.h"
#include "enemy_life_gage.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define POS			(D3DXVECTOR3(EnemyPos.x,EnemyPos.y + 40.0f, EnemyPos.z - 10.0f))	// 位置
#define SIZE		(D3DXVECTOR3(30.0f,2.5f,0.0f))										// サイズ
#define SIZE_BACK	(D3DXVECTOR3(SIZE.x * 1.01f, SIZE.y * 1.15f, SIZE.z))				// ゲージの背景サイズ
#define ROT			(D3DXVECTOR3(0.0f,0.0f,0.0f))										// 向き
#define COL			(D3DXCOLOR(1.0f,0.0f,0.0f,1.0f))									// 色
#define MIN_LIFE	(0)																	// ライフの最小値
//******************************************************************************
// コンストラクタ
//******************************************************************************
CEnemy_Life_Gage::CEnemy_Life_Gage(int nPriority) : C3D_Gage(nPriority)
{
	m_pEnemy		= NULL;
	m_p3D_Gage_Back = NULL;
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CEnemy_Life_Gage::~CEnemy_Life_Gage()
{
}
//******************************************************************************
// 生成関数
//******************************************************************************
CEnemy_Life_Gage * CEnemy_Life_Gage::Create(D3DXVECTOR3 pos, CEnemy *pEnemy)
{
	// CLife_Gageのポインタ
	CEnemy_Life_Gage *pEnemy_Life_Gage = NULL;

	// NULLの場合
	if (pEnemy_Life_Gage == NULL)
	{
		// メモリ確保
		pEnemy_Life_Gage = new CEnemy_Life_Gage;

		// NULLでない場合
		if (pEnemy_Life_Gage != NULL)
		{
			// 代入
			pEnemy_Life_Gage->m_pEnemy = pEnemy;

			// ライフ
			int nLife = pEnemy_Life_Gage->m_pEnemy->GetLife();

			// 情報設定
			pEnemy_Life_Gage->SetGage(pos, ROT, SIZE, COL, nLife);

			// 初期化
			pEnemy_Life_Gage->Init();
		}
	}
	// ポインタを返す
	return pEnemy_Life_Gage;
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CEnemy_Life_Gage::Init(void)
{
	// 初期化
	C3D_Gage::Init();

	// 位置取得
	D3DXVECTOR3 pos = GetPosition();

	// ゲージ背景生成
	m_p3D_Gage_Back = C3D_Gage_Back::Create(pos, SIZE_BACK);
	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CEnemy_Life_Gage::Uninit(void)
{
	// 終了
	C3D_Gage::Uninit();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CEnemy_Life_Gage::Update(void)
{
	// 更新
	C3D_Gage::Update();

	// 位置取得
	D3DXVECTOR3 pos = GetPosition();

	// 敵の位置取得
	D3DXVECTOR3 EnemyPos = m_pEnemy->GetPos();

	// ライフ取得
	int nLife = m_pEnemy->GetLife();

	// ライフ設定
	SetGageNum(nLife);

	// 位置代入
	pos = POS;

	// 位置
	m_p3D_Gage_Back->SetPosition(pos);

	// 位置設定
	SetPosition(pos);

	// ライフが0以下になった場合
	if (nLife <= MIN_LIFE)
	{
		// 破棄
		m_p3D_Gage_Back->Uninit();

		// 終了
		Uninit();
		return;
	}
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CEnemy_Life_Gage::Draw(void)
{
	// 描画
	C3D_Gage::Draw();
}