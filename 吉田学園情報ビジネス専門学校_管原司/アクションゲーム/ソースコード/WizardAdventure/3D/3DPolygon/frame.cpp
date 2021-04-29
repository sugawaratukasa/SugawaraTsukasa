//******************************************************************************
// フレーム[frame.cpp]
// Author : 管原司
//******************************************************************************
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "keyboard.h"
#include "scene.h"
#include "scene3d.h"
#include "../3D/Model/Block/block.h"
#include "frame.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define MOVE_VALUE	(D3DXVECTOR3(2.0f, 2.0f, 0.0f))
#define POS			(D3DXVECTOR3(pos.x,pos.y,pos.z - 15.0f))
#define FRAME_ROT1	(D3DXVECTOR3(0.0f,D3DXToRadian(0.0f),0.0f))
#define FRAME_ROT2	(D3DXVECTOR3(0.0f,D3DXToRadian(90.0f),0.0f))
#define FRAME_ROT3	(D3DXVECTOR3(0.0f,D3DXToRadian(270.0f),0.0f))
#define FRAME_ROT4	(D3DXVECTOR3(D3DXToRadian(90.0f),0.0f,0.0f))
#define MAX_FRAME	(2)
#define RADIUS		(15.0f)
//******************************************************************************
// 静的メンバ変数初期化
//******************************************************************************
LPDIRECT3DTEXTURE9 CFrame::m_pTexture = NULL;
//******************************************************************************
// コンストラクタ
//******************************************************************************
CFrame::CFrame(int nPriority) : CScene3d(nPriority)
{
	m_pBlock = NULL;
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CFrame::~CFrame()
{
}
//******************************************************************************
// テクスチャ読み込み関数
//******************************************************************************
HRESULT CFrame::Load(void)
{
	// レンダラー取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "data/Texture/frame.png", &m_pTexture);
	return S_OK;
}
//******************************************************************************
// テクスチャ破棄関数
//******************************************************************************
void CFrame::Unload(void)
{
	// NULLチェック
	if (m_pTexture != NULL)
	{
		// 破棄
		m_pTexture->Release();

		// NULL
		m_pTexture = NULL;
	}
}
//******************************************************************************
// 生成関数
//******************************************************************************
CFrame * CFrame::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, CBlock *pBlock)
{
	// CPolygonのポインタ
	CFrame *pFrame;

	// メモリ確保
	pFrame = new CFrame;

	// 情報設定
	pFrame->SetPolygon(pos, rot, size, col);

	// ブロックのポインタ設定
	pFrame->m_pBlock = pBlock;

	// テクスチャ
	pFrame->BindTexture(m_pTexture);

	// 初期化
	pFrame->Init();

	// ポインタを返す
	return pFrame;
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CFrame::Init(void)
{
	// 初期化
	CScene3d::Init();

	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CFrame::Uninit(void)
{
	// 終了
	CScene3d::Uninit();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CFrame::Update(void)
{
	// 更新
	CScene3d::Update();

	// 位置座標取得
	D3DXVECTOR3 pos = m_pBlock->GetPos();

	// 位置代入
	pos = POS;

	// 位置更新
	SetPosition(pos);
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CFrame::Draw(void)
{
	// レンダラー取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 加算合成の設定
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// 描画
	CScene3d::Draw();

	// 元に戻す
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}
//******************************************************************************
// 選択中の色に設定
//******************************************************************************
void CFrame::SetSelectingColor(D3DXCOLOR col)
{
	SetColor(col);
}