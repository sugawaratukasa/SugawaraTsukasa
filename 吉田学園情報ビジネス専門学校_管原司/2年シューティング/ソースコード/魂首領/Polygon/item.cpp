//******************************************************************************
// アイテム処理 [item.cpp]
// Author : 管原 司
//******************************************************************************

//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "../System/main.h"
#include "../System/manager.h"
#include "../System/renderer.h"
#include "../System/scene.h"
#include "../System/scene2d.h"
#include "../Player/player.h"
#include "../System/sound.h"
#include "../UI/score.h"
#include "../UI/life.h"
#include "../Mode/game.h"
#include "item.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define BOM_TEXTURE		( "data/Texture/UI/bom3.png")		// ボムテクスチャ
#define POWERUP_TEXTURE	( "data/Texture/UI/Powerup.png")	// パワーアップテクスチャ
#define ITEM_SIZE		(D3DXVECTOR3(40.0f,40.0f,0.0f))		// アイテムサイズ
#define COLOR			(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))	// 色
#define MOVE_VALUE		(3.0f)								// 移動量
#define DEVIDE_VALUE	(2)									// 除算値
#define GET_BOM_VALUE	(1)									// ボム取得数
//******************************************************************************
// 静的メンバ変数
//******************************************************************************
LPDIRECT3DTEXTURE9 CItem::m_apTexture[TYPE_MAX] = {};
//******************************************************************************
// テクスチャ読み込み
//******************************************************************************
HRESULT CItem::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, BOM_TEXTURE, &m_apTexture[TYPE_BOM]);
	D3DXCreateTextureFromFile(pDevice, POWERUP_TEXTURE, &m_apTexture[TYPE_POWERUP]);
	return S_OK;
}
//******************************************************************************
// テクスチャ破棄
//******************************************************************************
void CItem::Unload(void)
{
	// テクスチャの破棄
	for (int nCnt = INIT_INT; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}
//******************************************************************************
// 生成関数
//******************************************************************************
CItem * CItem::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// pItemクラスのポインタ
	CItem * pItem;

	// メモリ確保
	pItem = new CItem;

	// 位置座標設定
	pItem->SetPosition(pos);

	// サイズ設定
	pItem->SetSize(size);

	// タイプ設定
	pItem->m_type = type;

	// 弾の初期設定
	pItem->SetRGBA(COLOR);

	// テクスチャ受け渡し
	pItem->BindTexture(m_apTexture[pItem->m_type]);

	// オブジェクトタイプ設定
	pItem->SetObjType(CScene::OBJTYPE_ITEM);

	// 初期化
	pItem->Init();

	// pItemポインタを返す
	return pItem;
}
//******************************************************************************
// コンストラクタ
//******************************************************************************
CItem::CItem(int nPriority) : CScene2d(nPriority)
{
	m_move	= INIT_D3DXVECTOR3;
	m_bMove = false;
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CItem::~CItem()
{
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CItem::Init(void)
{
	// 初期化
	CScene2d::Init();

	return S_OK;
}
///******************************************************************************
// 終了関数
//******************************************************************************
void CItem::Uninit(void)
{
	// 終了
	CScene2d::Uninit();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CItem::Update(void)
{
	//更新
	CScene2d::Update();

	//サウンドの取得
	CSound * pSound = CSceneManager::GetSound();

	//座標の取得
	D3DXVECTOR3 pos;
	pos = GetPosition();

	// 当たり判定
	HitPlayer();

	// falseの場合
	if (m_bMove == false)
	{
		m_move.y = MOVE_VALUE;
	}
	// 画面の右に当たった時
	if (pos.x + ITEM_SIZE.x / DEVIDE_VALUE > MAX_GAME_WIDTH)
	{
		m_bMove = true;
		// 真ん中より低かったら
		if (pos.y + ITEM_SIZE.y/ DEVIDE_VALUE < SCREEN_HEIGHT / DEVIDE_VALUE)
		{
			m_move.x = -MOVE_VALUE;
			m_move.y = MOVE_VALUE;
		}
		// 真ん中より高かったら
		if (pos.y - ITEM_SIZE.y / DEVIDE_VALUE > SCREEN_HEIGHT / DEVIDE_VALUE)
		{
			m_move.x = -MOVE_VALUE;
			m_move.y = MOVE_VALUE;
		}
	}
	// 画面左に当たった時
	if (pos.x - ITEM_SIZE.x / DEVIDE_VALUE < MIN_GAME_WIDTH)
	{
		// trueにする
		m_bMove = true;
		// 真ん中より低かったら
		if (pos.y + ITEM_SIZE.y / DEVIDE_VALUE < SCREEN_HEIGHT / DEVIDE_VALUE)
		{
			m_move.x = MOVE_VALUE;
			m_move.y = MOVE_VALUE;
		}
		// 真ん中より高かったら
		if (pos.y - ITEM_SIZE.y / DEVIDE_VALUE > SCREEN_HEIGHT / DEVIDE_VALUE)
		{
			m_move.x = MOVE_VALUE;
			m_move.y = -MOVE_VALUE;
		}
	}
	//画面下に当たった時
	if (pos.y - ITEM_SIZE.y / DEVIDE_VALUE <= WINDOW_POS_Y)
	{
		// trueに
		m_bMove = true;
		// 真ん中より右
		if (pos.x + ITEM_SIZE.x / DEVIDE_VALUE > SCREEN_WIDTH / DEVIDE_VALUE)
		{
			m_move.x = MOVE_VALUE;
			m_move.y = MOVE_VALUE;
		}
		// 真ん中より左
		if (pos.x + ITEM_SIZE.x / DEVIDE_VALUE < SCREEN_WIDTH / DEVIDE_VALUE)
		{
			m_move.x = -MOVE_VALUE;
			m_move.y = MOVE_VALUE;
		}
	}
	//画面上に当たった時
	if (pos.y + ITEM_SIZE.y / DEVIDE_VALUE > SCREEN_HEIGHT)
	{
		// trueにする
		m_bMove = true;
		m_move.y = -MOVE_VALUE;
	}
	
	// 移動
	pos.x += m_move.x;
	pos.y += m_move.y;

	// 位置更新
	SetPosition(pos);
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CItem::Draw(void)
{
	// 描画
	CScene2d::Draw();
}
//******************************************************************************
// 当たり判定関数
//******************************************************************************
bool CItem::Collision(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR3 size1, D3DXVECTOR3 size2)
{
	bool bHit = false;  //当たったかどうか

	D3DXVECTOR3 box1Max = D3DXVECTOR3(size1.x / 2, size1.y, size1.z / 2) + pos1;          //ぶつかる側の最大値
	D3DXVECTOR3 box1Min = D3DXVECTOR3(-size1.x / 2, -size1.y, -size1.z / 2) + pos1;       //ぶつかる側の最小値
	D3DXVECTOR3 box2Max = D3DXVECTOR3(size2.x / 2, size2.y / 2, size2.z / 2) + pos2;      //ぶつかられる側の最大値
	D3DXVECTOR3 box2Min = D3DXVECTOR3(-size2.x / 2, -size2.y / 2, -size2.z / 2) + pos2;   //ぶつかられる側の最小値

	if (box1Max.y > box2Min.y&&
		box1Min.y < box2Max.y&&
		box1Max.x > box2Min.x&&
		box1Min.x < box2Max.x)
	{
		bHit = true;
	}

	return bHit;    //当たったかどうかを返す
}
//******************************************************************************
// プレイヤーと当たったとき
//******************************************************************************
void CItem::HitPlayer(void)
{
	// 位置座標取得
	D3DXVECTOR3 pos = GetPosition();

	// サイズ取得
	D3DXVECTOR3 size = GetSize();

	CPlayer * pPlayer = CGame::GetPlayer();

	// 座標とサイズ取得
	D3DXVECTOR3 PlayerPos = pPlayer->GetPosition();
	D3DXVECTOR3 PlayerSize = pPlayer->GetSize();

	// 当たり判定
	if (Collision(pos, PlayerPos, size, PlayerSize) == true)
	{
		// タイプがボムの場合
		if (m_type == TYPE_BOM)
		{
			// ボムの所持数の加算
			pPlayer->GetBom(GET_BOM_VALUE);
		}
		// タイプがパワーアップの場合
		if (m_type == TYPE_POWERUP)
		{
			// パワーアップ
			pPlayer->GetPowerUp();
		}

		// 弾を消す
		Uninit();
		return;
	}
}