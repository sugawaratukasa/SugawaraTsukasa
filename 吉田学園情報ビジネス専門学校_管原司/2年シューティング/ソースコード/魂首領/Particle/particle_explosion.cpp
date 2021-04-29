//******************************************************************************
// 爆発処理 [particle_explosion.cpp]
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
#include "particle_explosion.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define EFFECT_ROT				(D3DXVECTOR3(0.0f,0.0f,sinf(fAngle)))							// 向き
#define EFFECT_MOVE				(D3DXVECTOR3(fSpeed, sinf(D3DXToRadian(fAngle))*fSpeed, 0.0f))	// 移動量
#define ENEMY_EXPLOSION_COLOR	(D3DCOLOR_RGBA(255, 150, 0, 255))								// カラー(赤)
#define PLAYER_EXPLOSION_COLOR	(D3DCOLOR_RGBA(0, 200, 255, 255))								// カラー(青)
#define RANDUM_ANGLE_MAX		(360)															// 弧度最大値
#define RANDUM_ANGLE_MIN		(180)															// 弧度最小値
#define RANDUM_SPEED_MAX		(200)															// 移動量の最大値
#define RANDUM_SPEED_MIN		(100)															// 移動量の最小値
#define SPEED_DIVIDE			(100)															// 移動量除算値
#define SCALE_MIN_VALUE			(0.0f)															// 拡大率最小値
#define ADD_SCALE_VALUE			(1.5f)															// 拡大率加算量
#define SUBTRACT_COLOR_VALUE	(0.04f)															// カラー減算量
#define COLOR_MIN_VALUE			(0.0f)															// カラー最小値
#define MAX_EXPLOSION			(10)															// 爆発最大数
#define SIZE_MUT				(1.5f)															// 爆発のサイズの倍率
#define RANDUM_ANGLE	(RANDUM_ANGLE_MAX - RANDUM_ANGLE_MIN)									// 弧度ランダム
#define RANDUM_SPEED	(RANDUM_SPEED_MAX - RANDUM_SPEED_MIN)									// 移動量ランダム
//******************************************************************************
// コンストラクタ
//******************************************************************************
CParticle_Explosion::CParticle_Explosion(int nPrirority) : CParticle(nPrirority)
{
	m_move = INIT_D3DXVECTOR3;
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CParticle_Explosion::~CParticle_Explosion()
{
}
//******************************************************************************
// 生成関数
//******************************************************************************
CParticle_Explosion * CParticle_Explosion::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXVECTOR3 move, CParticle::TEX_TYPE TexType)
{
	// CParticle_Explosionクラスのポインタ
	CParticle_Explosion *pParticle_Explosion;

	// メモリ確保
	pParticle_Explosion = new CParticle_Explosion;

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
HRESULT CParticle_Explosion::Init(void)
{
	// 初期化
	CParticle::Init();

	return S_OK;

}
//******************************************************************************
// 終了関数
//******************************************************************************
void CParticle_Explosion::Uninit(void)
{
	// 終了
	CParticle::Uninit();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CParticle_Explosion::Update(void)
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
	float fAddScale = ADD_SCALE_VALUE;

	// カラー減算値
	float fMinColor = SUBTRACT_COLOR_VALUE;

	// サイズ加算
	fScale += fAddScale;

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
void CParticle_Explosion::Draw(void)
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
// 爆発生成処理関数
//******************************************************************************
void CParticle_Explosion::CreateExplosionEffect(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	TYPE Type = type;
	switch (Type)
	{
	case TYPE_ENEMY:
		// 15回繰り返す
		for (int nCount = INIT_INT; nCount < MAX_EXPLOSION; nCount++)
		{
			// 角度を360度ランダムに
			float fAngle = float(rand() % RANDUM_ANGLE);
			// スピードを10から-10でランダムに
			float fSpeed = float(rand() % RANDUM_SPEED);
			fSpeed = fSpeed / SPEED_DIVIDE;

			// 生成
			Create(pos,
				size * SIZE_MUT,
				EFFECT_ROT,
				ENEMY_EXPLOSION_COLOR,
				EFFECT_MOVE,
				CParticle::TEX_TYPE_EXPLOSION);
		}
		break;

	case TYPE_PLAYER:
		// 15回繰り返す
		for (int nCount = INIT_INT; nCount < MAX_EXPLOSION; nCount++)
		{
			// 角度を360度ランダムに
			float fAngle = float(rand() % RANDUM_ANGLE);
			// スピードを10から-10でランダムに
			float fSpeed = float(rand() % RANDUM_SPEED);
			fSpeed = fSpeed / SPEED_DIVIDE;
			
			// 生成
			Create(pos,
				size * SIZE_MUT,
				EFFECT_ROT,
				PLAYER_EXPLOSION_COLOR,
				EFFECT_MOVE,
				CParticle::TEX_TYPE_EXPLOSION);
		}
		break;
	}
}