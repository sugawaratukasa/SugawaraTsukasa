//******************************************************************************
// ビームが当たった時のパーティクル [particle_beam.cpp]
// Author : 管原　司
//******************************************************************************

//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "../System/main.h"
#include "../System/manager.h"
#include "../System/renderer.h"
#include "../System/scene.h"
#include "../System/scene2d.h"
#include "particle.h"
#include "particle_beam.h"
#include "particle_circle.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define LIFE_VALUE			(5)																							// ライフ値
#define MIN_LIFE			(0)																							// ライフの最小値
#define EFFECT_SIZE			(D3DXVECTOR3(30.0f,30.0f,0.0f))																// サイズ
#define EFFECT_ROT			(D3DXVECTOR3(0.0f,0.0f,0.0f))																// 向き
#define EFFECT_COL			(D3DXCOLOR(0.0f,0.5f,1.0f,1.0f))															// 色
#define SPEED_DIVIDE		(100)																						// 移動
#define EFFECT_RANDUM_COUNT	(10)																						// エフェクトカウントランダム
#define EFFECT_COUNT		(2)																							// エフェクトカウント
#define RANDUM_ANGLE		(270 - 90)																					// 角度ランダム
#define RANDUM_SPEED		(1000 - 500)																				// 移動量ランダム
#define EFFECT_MOVE			(D3DXVECTOR3(cosf(D3DXToRadian(fAngle))*fSpeed, sinf(D3DXToRadian(fAngle))*fSpeed, 0.0f))	// 移動量
//******************************************************************************
// コンストラクタ
//******************************************************************************
CParticle_Beam::CParticle_Beam(int nPrirority) : CParticle(nPrirority)
{
	m_nLife = INIT_INT;
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CParticle_Beam::~CParticle_Beam()
{
}
//******************************************************************************
// 生成関数
//******************************************************************************
CParticle_Beam * CParticle_Beam::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, CParticle::TEX_TYPE TexType)
{
	// CParticle_Beamクラスのポインタ
	CParticle_Beam *pParticle_Beam;

	// メモリ確保
	pParticle_Beam = new CParticle_Beam;

	// パーティクル情報設定
	pParticle_Beam->SetParticle(pos, size, rot, col, TexType);

	// 初期化
	pParticle_Beam->Init();

	// ポインタを返す
	return pParticle_Beam;
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CParticle_Beam::Init(void)
{
	// 初期化
	CParticle::Init();

	// ライフ設定
	m_nLife = LIFE_VALUE;

	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CParticle_Beam::Uninit(void)
{
	// 終了
	CParticle::Uninit();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CParticle_Beam::Update(void)
{
	// 更新
	CParticle::Update();

	// 位置取得
	D3DXVECTOR3 pos = GetPosition();
	int nNum = rand() % EFFECT_RANDUM_COUNT;

	if (nNum == EFFECT_COUNT)
	{
		// 角度を360度ランダムに
		float fAngle = float(rand() % RANDUM_ANGLE);

		// スピードを10から-10でランダムに
		float fSpeed = float(rand() % RANDUM_SPEED);
		fSpeed = fSpeed / SPEED_DIVIDE;

		CParticle_Circle::Create(pos, EFFECT_SIZE, EFFECT_ROT, EFFECT_COL, EFFECT_MOVE, CParticle::TEX_TYPE_CIRCLE);
	}
	// デクリメント
	m_nLife--;

	// 0以下の場合
	if (m_nLife <= MIN_LIFE)
	{
		// 終了
		Uninit();
		return;
	}
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CParticle_Beam::Draw(void)
{
	// レンダラー取得
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();

	// 加算合成の設定
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// 描画
	CParticle::Draw();

	// 元に戻す
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}