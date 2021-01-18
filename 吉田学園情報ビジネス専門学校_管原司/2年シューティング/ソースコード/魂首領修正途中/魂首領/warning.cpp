//******************************************************************************
// ワーニング [warning.cpp]
// Author : 管原 司
//******************************************************************************

//******************************************************************************
// ファイルインクルード
//******************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "input.h"
#include "inputkeyboard.h"
#include "inputjoystick.h"
#include "player.h"
#include "bullet.h"
#include "sound.h"
#include "life.h"
#include "game.h"
#include "explosion.h"
#include "bomui.h"
#include "continue.h"
#include "score.h"
#include "boss.h"
#include "enemy.h"
#include "warning.h"
//******************************************************************************
// 静的メンバ変数
//******************************************************************************
LPDIRECT3DTEXTURE9 CWarning::m_pTexture = NULL;
//******************************************************************************
// テクスチャ読み込み
//******************************************************************************
HRESULT CWarning::Load(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "data/Texture/warning.png", &m_pTexture);
	return S_OK;
}
//******************************************************************************
// テクスチャ破棄
//******************************************************************************
void CWarning::Unload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
//******************************************************************************
// コンストラクタ
//******************************************************************************
CWarning::CWarning(int nPriority) : CScene2d(nPriority)
{
	m_bColor		= false;
	m_nWarnigCount	= 0;
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CWarning::~CWarning()
{
}
//******************************************************************************
// 生成関数
//******************************************************************************
CWarning * CWarning::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CWarningクラスのポインタ
	CWarning * pWarning;

	// メモリ確保
	pWarning = new CWarning;

	// 位置座標設定
	pWarning->SetPosition(pos);

	// 位置座標設定
	pWarning->SetSize(size);

	// 初期化
	pWarning->Init();

	// ポインタを返す
	return nullptr;
}

//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CWarning::Init(void)
{
	// カラー設定
	SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// テクスチャ受け渡し
	BindTexture(m_pTexture);

	// 初期化
	CScene2d::Init();

	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CWarning::Uninit(void)
{
	//終了
	CScene2d::Uninit();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CWarning::Update(void)
{
	// 更新
	CScene2d::Update();

	// カラー取得
	D3DXCOLOR col = GetRGBA();

	// falseの場合
	if (m_bColor == false)
	{
		// α値減算
		col.a -= 0.05f;
		// 0.1以下になった場合
		if (col.a <= 0.1f)
		{
			// trueにする
			m_bColor = true;
		}
	}
	// trueの場合
	else
	{
		// α値加算
		col.a += 0.05f;
		// 1.0f以上の場合
		if (col.a >= 1.0f)
		{
			// falseにする
			m_bColor = false;
		}
		// インクリメント
		m_nWarnigCount++;
	}
	// 50の場合
	if (m_nWarnigCount == 50)
	{
		// ボス取得
		CBoss *pBoss = CGame::GetBoss();
		// ボス更新開始
		pBoss->SetBoss(1);
		//終了
		Uninit();
		// 他の処理を通らないように
		return;
	}

	// カラー設定
	SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, col.a));
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CWarning::Draw(void)
{
	// 描画
	CScene2d::Draw();
}