//******************************************************************************
// ポリゴン [polygon.cpp]
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
#include "polygon.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define TITLE_TEXTURE			("data/Texture/UI/Title.png")		// タイトルテクスチャ
#define PRESS_ENTER_TEXTURE		("data/Texture/UI/PressEnter.png")	// プレスエンターテクスチャ
#define TUTRIAL_TEXTURE			("data/Texture/UI/Tutrial.png")		// チュートリアルテクスチャ
#define RANKING_TEXTURE			("data/Texture/UI/Ranking.png")		// ランキングテクスチャ
#define CONTINUE_TEXTURE		("data/Texture/UI/continue.png")	// コンティニューテクスチャ
//******************************************************************************
// 静的メンバ変数
//******************************************************************************
LPDIRECT3DTEXTURE9 CPolygon::m_apTexture[TEX_TYPE_MAX] = {};
//******************************************************************************
// コンストラクタ
//******************************************************************************
CPolygon::CPolygon(int nPriority) : CScene2d(nPriority)
{
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CPolygon::~CPolygon()
{
}
//******************************************************************************
// テクスチャ読み込み
//******************************************************************************
HRESULT CPolygon::Load(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE, &m_apTexture[TEX_TYPE_TITLE]);
	D3DXCreateTextureFromFile(pDevice, PRESS_ENTER_TEXTURE, &m_apTexture[TEX_TYPE_PRESS_ENTER]);
	D3DXCreateTextureFromFile(pDevice, TUTRIAL_TEXTURE, &m_apTexture[TEX_TYPE_TUTRIAL]);
	D3DXCreateTextureFromFile(pDevice, RANKING_TEXTURE, &m_apTexture[TEX_TYPE_RANKING]);
	D3DXCreateTextureFromFile(pDevice, CONTINUE_TEXTURE, &m_apTexture[TEX_TYPE_CONTINUE]);
	return S_OK;
}
//******************************************************************************
// テクスチャ破棄
//******************************************************************************
void CPolygon::Unload(void)
{
	for (int nCnt = 0; nCnt < TEX_TYPE_MAX; nCnt++)
	{
		// テクスチャの破棄
		if (m_apTexture[nCnt] != NULL)
		{
			//テクスチャリリース
			m_apTexture[nCnt]->Release();
			//m_pTextureをNULLに
			m_apTexture[nCnt] = NULL;
		}
	}
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CPolygon::Init()
{
	//　初期化
	CScene2d::Init();
	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CPolygon::Uninit(void)
{
	//　終了
	CScene2d::Uninit();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CPolygon::Update(void)
{
	//　更新
	CScene2d::Update();
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CPolygon::Draw(void)
{
	//　描画
	CScene2d::Draw();
}
//******************************************************************************
// 情報設定
//******************************************************************************
void CPolygon::SetPolygon(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, TEX_TYPE textype)
{
	// 位置座標設定
	SetPosition(pos);

	// サイズ設定
	SetSize(size);

	// カラー設定
	SetRGBA(col);

	m_TexType = textype;

	BindTexture(m_apTexture[m_TexType]);

	SetObjType(OBJTYPE_UI);
}