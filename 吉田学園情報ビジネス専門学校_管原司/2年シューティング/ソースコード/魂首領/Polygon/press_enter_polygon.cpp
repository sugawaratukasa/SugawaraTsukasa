//******************************************************************************
// Press_Enterポリゴン [press_enter_polygon.cpp]
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
#include "press_enter_polygon.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define COLOR_RATE	(0.05f)								// a加算減算値
#define COLOR_MIN	(D3DXCOLOR(1.0f,1.0f,1.0f,0.1f))	// 色の最小値
#define	COLOR_MAX	(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))	// 色の最大値
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
		col.a -= COLOR_RATE;
		// 0.1以下の場合
		if (col.a <= COLOR_MIN.a)
		{
			// 0.1fに
			col.a = COLOR_MIN.a;

			// trueにする
			m_bColor = true;
		}
	}
	else
	{
		// α値加算
		col.a += COLOR_RATE;
		// 1.0f以上の場合
		if (col.a >= COLOR_MAX.a)
		{
			// 1.0fに
			col.a = COLOR_MAX.a;

			// falseにする
			m_bColor = false;
		}
	}
	// カラー設定
	SetRGBA(col);
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CPress_Enter_Polygon::Draw(void)
{
	//　描画
	CPolygon::Draw();
}