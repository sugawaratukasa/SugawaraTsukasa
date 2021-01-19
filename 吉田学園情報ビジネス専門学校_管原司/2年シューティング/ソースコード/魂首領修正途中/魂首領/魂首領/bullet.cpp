//******************************************************************************
// 弾 [bullet.cpp]
// Author : 管原　司
//******************************************************************************

//******************************************************************************
// ファイルインクルード
//******************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "game.h"
#include "bullet.h"
//******************************************************************************
// 静的メンバ変数
//******************************************************************************
LPDIRECT3DTEXTURE9 CBullet::m_apTexture[TEX_TYPE_MAX] = {};

//******************************************************************************
// テクスチャ読み込み関数
//******************************************************************************
HRESULT CBullet::Load(void)
{
	// レンダラー取得
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();

	// テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "data/Texture/Playerbullet001.png", &m_apTexture[TEX_TYPE_NORMAL]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/PlayerBeam001.png", &m_apTexture[TEX_TYPE_BEAM]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/bom.png", &m_apTexture[TEX_TYPE_BOM]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/EnemyBullet.png", &m_apTexture[TEX_TYPE_ENEMY_NORMAL]);
	return S_OK;
}
//******************************************************************************
// テクスチャ破棄関数
//******************************************************************************
void CBullet::Unload(void)
{
	// テクスチャの破棄
	for (int nCnt = 0; nCnt < TEX_TYPE_MAX; nCnt++)
	{
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}
//******************************************************************************
// コンストラクタ
//******************************************************************************
CBullet::CBullet(int nPriority) : CScene2d(nPriority)
{
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Textype = TEX_TYPE_NONE;
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CBullet::~CBullet()
{
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CBullet::Init()
{
	// 初期化
	CScene2d::Init();

	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CBullet::Uninit(void)
{
	// 終了
	CScene2d::Uninit();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CBullet::Update(void)
{
	// 更新
	CScene2d::Update();

	// 座標の取得
	D3DXVECTOR3 pos;
	pos = GetPosition();
	
	// 位置更新
	SetPosition(pos);

	// 画面外
	if (pos.x > MAX_GAME_WIDTH || pos.x < MIN_GAME_WIDTH || pos.y > SCREEN_HEIGHT || pos.y < 0)
	{
		//終了
		Uninit();
		return;
	}
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CBullet::Draw(void)
{
	// 描画
	CScene2d::Draw();
}
//******************************************************************************
// 弾の情報設定
//******************************************************************************
void CBullet::SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, TEX_TYPE textype, OBJTYPE objtype)
{
	// 位置座標設定
	SetPosition(pos);
	// 向き設定
	SetRot(rot);
	// サイズ設定
	SetSize(size);
	// カラー設定
	SetRGBA(col);
	// テクスチャタイプ設定
	m_Textype = textype;
	// テクスチャ設定
	BindTexture(m_apTexture[m_Textype]);
	// オブジェクトタイプ設定
	SetObjType(objtype);
}
//******************************************************************************
// 当たり判定
//******************************************************************************
bool CBullet::Collision(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR3 size1, D3DXVECTOR3 size2)
{
	bool bHit = false;  //当たったかどうか

	D3DXVECTOR3 box1Max = D3DXVECTOR3(size1.x / 2, size1.y, size1.z / 2) + pos1;          //ぶつかる側の最大値
	D3DXVECTOR3 box1Min = D3DXVECTOR3(-size1.x / 2, -size1.y, -size1.z / 2) + pos1;       //ぶつかる側の最小値
	D3DXVECTOR3 box2Max = D3DXVECTOR3(size2.x / 2, size2.y / 2, size2.z / 2) + pos2;      //ぶつかられる側の最大値
	D3DXVECTOR3 box2Min = D3DXVECTOR3(-size2.x / 2, -size2.y / 2, -size2.z / 2) + pos2;   //ぶつかられる側の最小値

	if (box1Max.y > box2Min.y&&
		box1Min.y < box2Max.y&&
		box1Max.x > box2Min.x&&
		box1Min.x < box2Max.x)
	{
		bHit = true;
	}

	return bHit;    //当たったかどうかを返す
}