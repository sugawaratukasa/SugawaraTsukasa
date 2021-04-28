//******************************************************************************
// 船 [ship.cpp]
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
#include "ship.h"
#include "ship_battery.h"
#include "../UI/warning.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define SHIP_TEXTURE		("data/Texture/Enemy/Ship.png")							// 船のテクスチャ
#define COLOR_VALUE			(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))						// 色の値
#define ROT_VALUE			(D3DXVECTOR3(0.0f,0.0f, D3DXToRadian(180.0f)))			// 向きの値
#define MOVE_VALUE			(D3DXVECTOR3(0.0f,1.0f,0.0f))							// 移動量
#define SHIP_SIZE			(D3DXVECTOR3(1000.0f,1800.0f,0.0f))						// 船のサイズ
#define SHIP_BATTERY_POS1	(D3DXVECTOR3(150.0f,400.0f,0.0f))						// 砲台の位置1
#define SHIP_BATTERY_POS2	(D3DXVECTOR3(-150.0f,400.0f,0.0f))						// 砲台の位置2
#define SHIP_BATTERY_POS3	(D3DXVECTOR3(280.0f,-20.0f,0.0f))						// 砲台の位置3
#define SHIP_BATTERY_POS4	(D3DXVECTOR3(-280.0f,-20.0f,0.0f))						// 砲台の位置4
#define SHIP_BATTERY_POS5	(D3DXVECTOR3(-280.0f,-550.0f,0.0f))						// 砲台の位置5
#define SHIP_BATTERY_POS6	(D3DXVECTOR3(280.0f,-550.0f,0.0f))						// 砲台の位置6
#define SHIP_BATTERY_SIZE	(D3DXVECTOR3(100.0f,200.0f,0.0f))						// 船の砲台のサイズ
#define SHIP_BATTERY_ROT	(D3DXVECTOR3(0.0f,0.0f,0.0f))							// 船の砲台の向き
#define WARNING_POS			(D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2, 0.0f))	// 位置座標
#define WARNING_SIZE		(D3DXVECTOR3(500.0f,300.0f,0.0f))						// サイズ
#define SHIP_BATTERY_LIFE	(100)													// 船の砲台のライフ
#define DEVIDE_VAlUE		(2)														// 除算値
#define TEX_X				(0.0f)													// テクスチャX
#define TEX_Y				(0.0f)													// テクスチャY
#define TEX_ANIM_X			(1.0f)													// テクスチャX
#define TEX_ANIM_Y			(1.0f)													// テクスチャY
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
	D3DXCreateTextureFromFile(pDevice, SHIP_TEXTURE, &m_pTexture);
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
	pShip->SetRot(ROT_VALUE);

	// カラー設定
	pShip->SetRGBA(COLOR_VALUE);

	// テクスチャ受け渡し
	pShip->BindTexture(m_pTexture);

	// オブジェクトタイプ設定
	pShip->SetObjType(OBJTYPE_SHIP);

	// 初期化
	pShip->Init();

	// 砲台生成
	pShip->BatteryCreate();

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
	D3DXVECTOR3 move = MOVE_VALUE;

	// 画面外にでたら
	if (pos.y - SHIP_SIZE.y / DEVIDE_VAlUE >= SCREEN_HEIGHT)
	{
		// Warning生成
		CWarning::Create(WARNING_POS, WARNING_SIZE);

		// 終了
		Uninit();
		return;
	}

	// 移動
	pos.y += move.y;

	// テクスチャ
	SetTexture(TEX_X, TEX_Y, TEX_ANIM_X, TEX_ANIM_Y);

	// 位置座標設定
	SetPosition(pos);
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CShip::Draw(void)
{
	// 描画
	CScene2d::Draw();
}
//******************************************************************************
// 砲台生成
//******************************************************************************
void CShip::BatteryCreate(void)
{
	// 砲台生成
	CShip_Battery::Create(SHIP_BATTERY_POS1, SHIP_BATTERY_ROT, SHIP_BATTERY_SIZE, SHIP_BATTERY_LIFE, CEnemy::TEX_TYPE_SHIP_BATTERY);
	CShip_Battery::Create(SHIP_BATTERY_POS2, SHIP_BATTERY_ROT, SHIP_BATTERY_SIZE, SHIP_BATTERY_LIFE, CEnemy::TEX_TYPE_SHIP_BATTERY);
	CShip_Battery::Create(SHIP_BATTERY_POS3, SHIP_BATTERY_ROT, SHIP_BATTERY_SIZE, SHIP_BATTERY_LIFE, CEnemy::TEX_TYPE_SHIP_BATTERY);
	CShip_Battery::Create(SHIP_BATTERY_POS4, SHIP_BATTERY_ROT, SHIP_BATTERY_SIZE, SHIP_BATTERY_LIFE, CEnemy::TEX_TYPE_SHIP_BATTERY);
	CShip_Battery::Create(SHIP_BATTERY_POS5, SHIP_BATTERY_ROT, SHIP_BATTERY_SIZE, SHIP_BATTERY_LIFE, CEnemy::TEX_TYPE_SHIP_BATTERY);
	CShip_Battery::Create(SHIP_BATTERY_POS6, SHIP_BATTERY_ROT, SHIP_BATTERY_SIZE, SHIP_BATTERY_LIFE, CEnemy::TEX_TYPE_SHIP_BATTERY);

}