//******************************************************************************
// パーティクル処理 [particle_circle.cpp]
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
#include "particle_circle.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define EFFECT_ROT				(D3DXVECTOR3(0.0f,0.0f,sinf(fAngle)))							// 向き
#define EFFECT_MOVE				(D3DXVECTOR3(cosf(D3DXToRadian(fAngle))*fSpeed, sinf(D3DXToRadian(fAngle))*fSpeed, 0.0f))	// 移動量
#define SCALE_MIN_VALUE			(0.0f)															// 拡大率最小値
#define RANDUM_ANGLE_MAX		(360)															// 弧度最大値
#define RANDUM_ANGLE_MIN		(180)															// 弧度最小値
#define RANDUM_SPEED_MAX		(1500)															// 移動量の最大値
#define RANDUM_SPEED_MIN		(1000)															// 移動量の最小値
#define SPEED_DIVIDE			(100)															// 移動量除算値
#define RANDUM_COLOR			(255)															// 色ランダム
#define A_COLOR					(255)															// α値
#define SUB_SCALE_VALUE			(0.03f)															// 拡大率加算量
#define SUBTRACT_COLOR_VALUE	(0.01f)															// カラー減算量
#define COLOR_MIN_VALUE			(0.0f)															// カラー最小値
#define MAX_PARTICLE			(3)																// 爆発最大数

#define RANDUM_ANGLE	(RANDUM_ANGLE_MAX - RANDUM_ANGLE_MIN)									// 弧度ランダム
#define RANDUM_SPEED	(RANDUM_SPEED_MAX - RANDUM_SPEED_MIN)									// 移動量ランダム
//******************************************************************************
// コンストラクタ
//******************************************************************************
CParticle_Circle::CParticle_Circle(int nPrirority) : CParticle(nPrirority)
{
	m_move = INIT_D3DXVECTOR3;
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CParticle_Circle::~CParticle_Circle()
{
}
//******************************************************************************
// 生成関数
//******************************************************************************
CParticle_Circle * CParticle_Circle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXVECTOR3 move, CParticle::TEX_TYPE TexType)
{
	// CParticle_Explosionクラスのポインタ
	CParticle_Circle *pParticle_Explosion;

	// メモリ確保
	pParticle_Explosion = new CParticle_Circle;

	// パーティクル情報設定
	pParticle_Explosion->SetParticle(pos, size, rot, col, TexType);

	// 移動量代入
	pParticle_Explosion->m_move = move;

	// 初期化
	pParticle_Explosion->Init();

	// ポインタを返す
	return pParticle_Explosion;
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CParticle_Circle::Init(void)
{
	// 初期化
	CParticle::Init();

	return S_OK;

}
//******************************************************************************
// 終了関数
//******************************************************************************
void CParticle_Circle::Uninit(void)
{
	// 終了
	CParticle::Uninit();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CParticle_Circle::Update(void)
{
	// 更新
	CParticle::Update();

	// 位置座標取得
	D3DXVECTOR3 pos = GetPosition();

	// 色取得
	D3DXCOLOR col = GetRGBA();

	// 拡大率取得
	float fScale = GetScale();

	// 拡大率加算値
	float fSubScale = SUB_SCALE_VALUE;

	// カラー減算値
	float fMinColor = SUBTRACT_COLOR_VALUE;

	// サイズ加算
	fScale -= fSubScale;

	// カラー値減算
	col.a -= fMinColor;
	col.r -= fMinColor;
	col.g -= fMinColor;

	// サイズ設定
	SetScale(fScale);

	// 色設定
	SetRGBA(col);

	// 位置更新
	pos += m_move;

	// 位置座標設定
	SetPosition(pos);

	// 拡大率が0.0f以下の場合
	if (fScale <= SCALE_MIN_VALUE)
	{
		// 終了
		Uninit();
		return;
	}
	// カラーが0.0f以下の場合
	if (col.a <= COLOR_MIN_VALUE)
	{
		Uninit();
		return;
	}
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CParticle_Circle::Draw(void)
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
//******************************************************************************
// 生成処理関数
//******************************************************************************
void CParticle_Circle::CreateParticleEffect(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nCreateCount)
{
		// 5回繰り返す
		for (int nCount = INIT_INT; nCount < nCreateCount; nCount++)
		{
			// 角度を360度ランダムに
			float fAngle = float(rand() % RANDUM_ANGLE_MAX);

			// スピードを10から-10でランダムに
			float fSpeed = float(rand() % RANDUM_SPEED);
			fSpeed = fSpeed / SPEED_DIVIDE;

			// 色をランダム
			int fColorRed = int(rand() % RANDUM_COLOR);
			int fColorGreen = int(rand() % RANDUM_COLOR);
			int fColorBlue = int(rand() % RANDUM_COLOR);
			int fColorA	= A_COLOR;

			// 色
			D3DXCOLOR color = D3DCOLOR_RGBA(fColorRed, fColorGreen, fColorBlue, fColorA);

			// 生成
			Create(pos,
				size,
				EFFECT_ROT,
				color,
				EFFECT_MOVE,
				CParticle::TEX_TYPE_CIRCLE);
		}
}
//******************************************************************************
// 生成処理関数
//******************************************************************************
void CParticle_Circle::PlayerDeathEffect(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nCreateCount)
{
	// 5回繰り返す
	for (int nCount = INIT_INT; nCount < nCreateCount; nCount++)
	{
		// 角度を360度ランダムに
		float fAngle = float(rand() % RANDUM_ANGLE);

		// スピードを10から-10でランダムに
		float fSpeed = float(rand() % RANDUM_SPEED);
		fSpeed = fSpeed / SPEED_DIVIDE;

		// 色
		D3DXCOLOR col = D3DXCOLOR(0.0f, 0.5f, 1.0f, 1.0f);
		// 生成
		Create(pos,
			size,
			EFFECT_ROT,
			col,
			EFFECT_MOVE,
			CParticle::TEX_TYPE_CIRCLE);
	}
}