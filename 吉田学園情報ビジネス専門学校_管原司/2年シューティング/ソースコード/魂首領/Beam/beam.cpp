//******************************************************************************
// ビームの処理 [beam.cpp]
// Author : 管原　司
//******************************************************************************

//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "../System/main.h"
#include "../System/renderer.h"
#include "../System/scene.h"
#include "../System/manager.h"
#include "../System/scene.h"
#include "../System/scene2d.h"
#include "../Player/player.h"
#include "../Beam/beam.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define TEXTURE_01				("data/Texture/Bullet/beam.png")				// テクスチャ
#define TEXTURE_02				("data/Texture/Effect/particle008.png")			// テクスチャ
#define POS						(D3DXVECTOR3(0.0f,-35.0f,0.0f))					// 位置
//******************************************************************************
// 静的メンバ変数
//******************************************************************************
LPDIRECT3DTEXTURE9 CBeam::m_apTexture[TEX_TYPE_MAX] = {};
//******************************************************************************
// コンストラクタ
//******************************************************************************
CBeam::CBeam(int nPriority) : CBeam_Base(nPriority)
{
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CBeam::~CBeam()
{
}
//******************************************************************************
// テクスチャ読み込み
//******************************************************************************
HRESULT CBeam::Load(void)
{
	//レンダラー取得
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_01, &m_apTexture[TEX_TYPE_01]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_02, &m_apTexture[TEX_TYPE_02]);
	return S_OK;
}
//******************************************************************************
// テクスチャ破棄
//******************************************************************************
void CBeam::Unload(void)
{
	// 最大数分回す
	for (int nCnt = INIT_INT; nCnt < TEX_TYPE_MAX; nCnt++)
	{
		// テクスチャの破棄
		if (m_apTexture[TEX_TYPE_MAX] != NULL)
		{
			// テクスチャのをRelease
			m_apTexture[TEX_TYPE_MAX]->Release();
			// テクスチャのをNULL
			m_apTexture[TEX_TYPE_MAX] = NULL;
		}
	}
}
//******************************************************************************
// 生成関数
//******************************************************************************
CBeam * CBeam::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DCOLOR col, TEX_TYPE tex_type)
{
	// CBeamクラスのポインタ
	CBeam *pBeam;

	// メモリ確保
	pBeam = new CBeam;

	// 情報設定
	pBeam->SetBeam(pos, size, col);

	// テクスチャ受け渡し
	pBeam->BindTexture(m_apTexture[tex_type]);

	// 初期化
	pBeam->Init();

	// ポインタを返す
	return pBeam;
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CBeam::Init(void)
{
	// 初期化
	CBeam_Base::Init();

	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CBeam::Uninit(void)
{
	// 終了
	CBeam_Base::Uninit();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CBeam::Update(void)
{
	// 更新
	CBeam_Base::Update();

	// 位置取得
	D3DXVECTOR3 pos = GetPosition();

	// CScene型のポインタ
	CScene *pScene = NULL;

	// プレイヤーの取得
	do
	{
		// オブジェタイプが敵の場合
		pScene = GetScene(OBJTYPE_PLAYER);

		// NULLチェック
		if (pScene != NULL)
		{
			// オブジェタイプ取得
			OBJTYPE objType = pScene->GetObjType();

			// オブジェクトタイプがプレイヤー
			if (objType == OBJTYPE_PLAYER)
			{
				// プレイヤー位置取得
				D3DXVECTOR3 PlayerPos = ((CPlayer*)pScene)->GetPosition();

				// 位置設定
				SetPosition(D3DXVECTOR3(PlayerPos.x, PlayerPos.y + POS.y, pos.z));
			}
		}
	} while (pScene != NULL);
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CBeam::Draw(void)
{
	// レンダラー取得
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();

	// 加算合成の設定
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// 描画
	CBeam_Base::Draw();

	// 元に戻す
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
//******************************************************************************
// 破棄関数
//******************************************************************************
void CBeam::Release(void)
{
	// 終了
	Uninit();
	return;
}
