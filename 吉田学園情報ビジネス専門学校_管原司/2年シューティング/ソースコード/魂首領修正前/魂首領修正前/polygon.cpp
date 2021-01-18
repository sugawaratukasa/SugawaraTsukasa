//---------------------------------------------------
// Polygon
// Polygon.cpp
// Author:	管原司
//---------------------------------------------------
#include "sound.h"
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "input.h"
#include "inputkeyboard.h"
#include "player.h"
#include "bullet.h"
#include "number.h"
#include "score.h"
#include "polygon.h"
//--------------------------------------------------
//コンストラクタ
//--------------------------------------------------
CPolygon::CPolygon(int nPriority) : CScene2d(nPriority)
{
}
//--------------------------------------------------
//デストラクタ
//--------------------------------------------------
CPolygon::~CPolygon()
{
}
//--------------------------------------------------
//生成
//--------------------------------------------------
CPolygon * CPolygon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY)
{
	//CPlayerクラスのポインタ
	CPolygon * pPolygon;
	//メモリ確保
	pPolygon = new CPolygon;
	//初期化
	pPolygon->Init(pos, rot, sizeX, sizeY);
	return pPolygon;
}
//--------------------------------------------------
//初期化
//--------------------------------------------------
HRESULT CPolygon::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY)
{
	//初期化
	CScene2d::Init(pos, rot, sizeX, sizeY);
	//弾の初期設定
	SetRGBA(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	return S_OK;
}
//--------------------------------------------------
//終了
//--------------------------------------------------
void CPolygon::Uninit(void)
{
	//終了
	CScene2d::Uninit();
}
//--------------------------------------------------
//更新
//--------------------------------------------------
void CPolygon::Update(void)
{
	//更新
	CScene2d::Update();
}
//--------------------------------------------------
//描画
//--------------------------------------------------
void CPolygon::Draw(void)
{
	//描画
	CScene2d::Draw();
}
