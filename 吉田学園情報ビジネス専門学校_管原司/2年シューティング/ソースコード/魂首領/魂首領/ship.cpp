//******************************************************************************
// 船 [ship.cpp]
// Author : 管原　司
//******************************************************************************
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "ship.h"
#include "ship_battery.h"
#include "warning.h"
//******************************************************************************
// 静的メンバ変数
//******************************************************************************
LPDIRECT3DTEXTURE9 CShip::m_pTexture = NULL;
//******************************************************************************
// コンストラクタ
//******************************************************************************
CShip::CShip(int nPriority) : CScene2d(nPriority)
{
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CShip::~CShip()
{
}
//******************************************************************************
// テクスチャ読み込み
//******************************************************************************
HRESULT CShip::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "data/Texture/Ship.png", &m_pTexture);
	return S_OK;
}
//******************************************************************************
// テクスチャ破棄
//******************************************************************************
void CShip::Unload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
//******************************************************************************
// 生成関数
//******************************************************************************
CShip * CShip::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CShipクラスのポインタ
	CShip * pShip;

	// メモリ確保
	pShip = new CShip;

	// 位置座標設定
	pShip->SetPosition(pos);

	// 位置座標設定
	pShip->SetSize(size);

	// 向き設定
	pShip->SetRot(D3DXVECTOR3(0.0f,0.0f, D3DXToRadian(180.0f)));

	// カラー設定
	pShip->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// テクスチャ受け渡し
	pShip->BindTexture(m_pTexture);

	// オブジェクトタイプ設定
	pShip->SetObjType(OBJTYPE_SHIP);

	// 初期化
	pShip->Init();

	// ポインタを返す
	return pShip;
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CShip::Init(void)
{
	// 初期化
	CScene2d::Init();

	// 砲台生成
	CShip_Battery::Create(SHIP_BATTERY_POS1, SHIP_BATTERY_ROT,SHIP_BATTERY_SIZE,SHIP_BATTERY_LIFE,CEnemy::TEX_TYPE_SHIP_BATTERY);
	CShip_Battery::Create(SHIP_BATTERY_POS2, SHIP_BATTERY_ROT, SHIP_BATTERY_SIZE, SHIP_BATTERY_LIFE, CEnemy::TEX_TYPE_SHIP_BATTERY);
	CShip_Battery::Create(SHIP_BATTERY_POS3, SHIP_BATTERY_ROT, SHIP_BATTERY_SIZE, SHIP_BATTERY_LIFE, CEnemy::TEX_TYPE_SHIP_BATTERY);
	CShip_Battery::Create(SHIP_BATTERY_POS4, SHIP_BATTERY_ROT, SHIP_BATTERY_SIZE, SHIP_BATTERY_LIFE, CEnemy::TEX_TYPE_SHIP_BATTERY);
	CShip_Battery::Create(SHIP_BATTERY_POS5, SHIP_BATTERY_ROT, SHIP_BATTERY_SIZE, SHIP_BATTERY_LIFE, CEnemy::TEX_TYPE_SHIP_BATTERY);
	CShip_Battery::Create(SHIP_BATTERY_POS6, SHIP_BATTERY_ROT, SHIP_BATTERY_SIZE, SHIP_BATTERY_LIFE, CEnemy::TEX_TYPE_SHIP_BATTERY);

	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CShip::Uninit(void)
{
	// 終了
	CScene2d::Uninit();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CShip::Update(void)
{
	// 更新
	CScene2d::Update();

	// 位置座標取得
	D3DXVECTOR3 pos = GetPosition();

	// 移動用変数
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f,1.0f,0.0f);

	// 移動
	pos.y += move.y;

	// 位置座標設定
	SetPosition(pos);

	// 画面外にでたら
	if (pos.y - SHIP_SIZE.y / 2 >= SCREEN_HEIGHT)
	{
		// Warning生成
		CWarning::Create(WARNING_POS, WARNING_SIZE);

		// 終了
		Uninit();
		return;
	}
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CShip::Draw(void)
{
	// 描画
	CScene2d::Draw();
}