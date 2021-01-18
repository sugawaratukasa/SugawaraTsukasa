//---------------------------------------------------
// Bullet
// Bullet.cpp
// Author:	管原司
//---------------------------------------------------

//---------------------------------------------------
//インクルードファイル
//---------------------------------------------------
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "input.h"
#include "inputkeyboard.h"
#include "player.h"
#include "bullet.h"
#include "explosion.h"
#include "sound.h"
//静的メンバ変数
LPDIRECT3DTEXTURE9 CExplosion::m_pTexture = NULL;
//---------------------------------------------------
//生成関数
//---------------------------------------------------
CExplosion * CExplosion::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY)
{
	//CPlayerクラスのポインタ
	CExplosion * pExplosion;
	//メモリ確保
	pExplosion = new CExplosion;
	//初期化
	pExplosion->Init(pos, rot, sizeX, sizeY);
	return pExplosion;
}
//---------------------------------------------------
//コンストラクタ
//---------------------------------------------------
CExplosion::CExplosion(int nPriority) : CScene2d(nPriority)
{
	m_nCountAnim = 0;
	m_nPatternAnim = 0;
	m_bUse = true;
}
//---------------------------------------------------
//デストラクタ
//---------------------------------------------------
CExplosion::~CExplosion()
{
}
//---------------------------------------------------
//初期化
//---------------------------------------------------
HRESULT CExplosion::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY)
{
	//初期化
	CScene2d::Init(pos, rot, sizeX, sizeY);
	//爆発の初期設定
	m_nCountAnim = 0;
	m_nPatternAnim = 0;
	m_bUse = true;
	SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	BindTexture(m_pTexture);
	SetObjType(CScene::OBJTYPE_EXPLOSION);
	return S_OK;
}
//---------------------------------------------------
//終了
//---------------------------------------------------
void CExplosion::Uninit(void)
{
	//終了
	CScene2d::Uninit();
}
//---------------------------------------------------
//更新
//---------------------------------------------------
void CExplosion::Update(void)
{
	//更新
	CScene2d::Update();
	//trueの場合
	if (m_bUse == true)
	{
		//カウントインクリメント
		m_nCountAnim++;
		//カウントが4以上になった場合
		if (m_nCountAnim > 4)
		{
			m_nCountAnim = 0;
			//テクスチャセット
			SetTexture(m_nPatternAnim * 0.125f, 0.0f, 0.125f, 1.0f);
			//パターンのインクリメント
			m_nPatternAnim++;
			//パターンが8になった場合
			if (m_nPatternAnim > 8)
			{
				m_bUse = false;
			}
		}
	}
	//falseの場合
	else
	{
		//終了
		Uninit();
	}
}
//---------------------------------------------------
//描画
//---------------------------------------------------
void CExplosion::Draw(void)
{
	//描画
	CScene2d::Draw();
}
//--------------------------------------------------
//テクスチャのロード
//--------------------------------------------------
HRESULT CExplosion::Load(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "data/Texture/explosion000.png", &m_pTexture);
	return S_OK;
}
//-------------------------------------------------
//テクスチャの破棄
//-------------------------------------------------
void CExplosion::Unload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}