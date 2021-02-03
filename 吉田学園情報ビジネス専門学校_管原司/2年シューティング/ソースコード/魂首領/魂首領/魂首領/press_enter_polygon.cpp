//******************************************************************************
// Press_Enterポリゴン [press_enter_polygon.cpp]
// Author : 管原　司
//******************************************************************************
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "sound.h"
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "polygon.h"
#include "press_enter_polygon.h"
//******************************************************************************
// コンストラクタ
//******************************************************************************
CPress_Enter_Polygon::CPress_Enter_Polygon(int nPriority) : CPolygon(nPriority)
{
	m_bColor = false;
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CPress_Enter_Polygon::~CPress_Enter_Polygon()
{
}
//******************************************************************************
// 生成関数
//******************************************************************************
CPress_Enter_Polygon * CPress_Enter_Polygon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, TEX_TYPE textype)
{
	//　CPress_Enter_Polygonクラスのポインタ
	CPress_Enter_Polygon *pTitle_Polygonn;

	// メモリ確保
	pTitle_Polygonn = new CPress_Enter_Polygon;

	// 情報設定
	pTitle_Polygonn->SetPolygon(pos, size, col, textype);

	// 初期化
	pTitle_Polygonn->Init();

	// ポインタを返す
	return pTitle_Polygonn;

}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CPress_Enter_Polygon::Init()
{
	//　初期化
	CPolygon::Init();

	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CPress_Enter_Polygon::Uninit(void)
{
	//　終了
	CPolygon::Uninit();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CPress_Enter_Polygon::Update(void)
{
	//　更新
	CPolygon::Update();

	// カラー取得
	D3DXCOLOR col = GetRGBA();

	// falseの場合
	if (m_bColor == false)
	{
		// α値減算
		col.a -= 0.05f;
		// 0.1以下の場合
		if (col.a <= 0.1f)
		{
			// trueにする
			m_bColor = true;
		}
	}
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
	}
	// カラー設定
	SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, col.a));
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CPress_Enter_Polygon::Draw(void)
{
	//　描画
	CPolygon::Draw();
}