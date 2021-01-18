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
#include "explosion.h"
#include "sound.h"
#include "enemy.h"
#include "score.h"
#include "life.h"
#include "game.h"
#include "item.h"
LPDIRECT3DTEXTURE9 CItem::m_apTexture[MAX_ITEM_TEX] = {};
//------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------
CItem::CItem(int nPriority) : CScene2d(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bMove = false;
}
//------------------------------------------------------------------
//デストラクタ
//------------------------------------------------------------------
CItem::~CItem()
{
}
//------------------------------------------------------------------
//生成
//------------------------------------------------------------------
CItem * CItem::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, int sizeX, int sizeY , TYPE type)
{
	//pItemクラスのポインタ
	CItem * pItem;
	//メモリ確保
	pItem = new CItem;
	//初期化
	pItem->Init(pos, rot, move, sizeX, sizeY, type);
	//pItemポインタを返す
	return pItem;
}
//------------------------------------------------------------------
//テクスチャ読み込み
//------------------------------------------------------------------
HRESULT CItem::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "data/Texture/star.png", &m_apTexture[TYPE_STAR]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/bom3.png", &m_apTexture[TYPE_BOM]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/Powerup.png", &m_apTexture[TYPE_POWER]);
	return S_OK;
}
//------------------------------------------------------------------
//テクスチャ破棄
//------------------------------------------------------------------
void CItem::Unload(void)
{
	// テクスチャの破棄
	for (int nCnt = 0; nCnt < MAX_ITEM_TEX; nCnt++)
	{
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}
//------------------------------------------------------------------
//初期化
//------------------------------------------------------------------
HRESULT CItem::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, int sizeX, int sizeY , TYPE type)
{
	//move
	m_move = move;
	//タイプ
	m_type = type;
	//初期化
	CScene2d::Init(pos, rot, sizeX, sizeY);
	//弾の初期設定
	SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	BindTexture(m_apTexture[m_type]);
	SetObjType(CScene::OBJTYPE_ITEM);
	return S_OK;
}
//------------------------------------------------------------------
//終了
//------------------------------------------------------------------
void CItem::Uninit(void)
{
	//終了
	CScene2d::Uninit();
}
//------------------------------------------------------------------
//更新
//------------------------------------------------------------------
void CItem::Update(void)
{
	//更新
	CScene2d::Update();
	//サウンドの取得
	CSound * pSound = CSceneManager::GetSound();
	//スコアの取得
	CScore * pScore = CGame::GetScore();
	CPlayer * pPlayer = CGame::GetPlayer();
	//座標の取得
	D3DXVECTOR3 pos;
	pos = GetPosition();
	//テクスチャのセット
	SetTexture(0.0f, 0.0f, 1.0f, 1.0f);
	for (int nCntPriority = 0; nCntPriority < PRIORITY_TYPE_MAX; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			//シーンの取得
			CScene * pScene = GetScene(nCntPriority, nCntScene);
			if (pScene != NULL)
			{
				//オブジェクトのタイプ取得
				OBJTYPE objType;
				objType = pScene->GetObjType();
				//座標の取得
				D3DXVECTOR3 ScenePos;
				ScenePos = pScene->GetPosition();
				//タイプ
				switch (m_type)
				{
					//タイプがスターの場合
				case TYPE_STAR:
					//オブジェクトがplayerの場合
					if (objType == OBJTYPE_PLAYER)
					{
						//敵と弾が当たった
						if (pos.x - STAR_SIZE_X / 2 < (ScenePos.x + PLAYER_SIZE_X / 2)
							&& pos.x + STAR_SIZE_X / 2 > (ScenePos.x - PLAYER_SIZE_X / 2)
							&& pos.y - STAR_SIZE_Y / 2 < (ScenePos.y + PLAYER_SIZE_Y / 2)
							&& pos.y + STAR_SIZE_Y / 2 > (ScenePos.y - PLAYER_SIZE_Y / 2))
						{
							//スコア加算
							pScore->AddScore(100);
							//終了
							Uninit();
							return;
						}
					}
				case TYPE_BOM:
					//オブジェクトがplayerの場合
					if (objType == OBJTYPE_PLAYER)
					{
						//敵と弾が当たった
						if (pos.x - BOM_SIZE_X / 2 < (ScenePos.x + PLAYER_SIZE_X / 2)
							&& pos.x + BOM_SIZE_X / 2 > (ScenePos.x - PLAYER_SIZE_X / 2)
							&& pos.y - BOM_SIZE_Y / 2 < (ScenePos.y + PLAYER_SIZE_Y / 2)
							&& pos.y + BOM_SIZE_Y / 2 > (ScenePos.y - PLAYER_SIZE_Y / 2))
						{
							//ボムの所持数の加算
							pPlayer->GetBom(1);
							//終了
							Uninit();
							return;
						}
					}
				case TYPE_POWER:
					//オブジェクトがplayerの場合
					if (objType == OBJTYPE_PLAYER)
					{
						//敵と弾が当たった
						if (pos.x - POWER_SIZE_X / 2 < (ScenePos.x + PLAYER_SIZE_X / 2)
							&& pos.x + POWER_SIZE_X / 2 > (ScenePos.x - PLAYER_SIZE_X / 2)
							&& pos.y - POWER_SIZE_Y / 2 < (ScenePos.y + PLAYER_SIZE_Y / 2)
							&& pos.y + POWER_SIZE_Y / 2 > (ScenePos.y - PLAYER_SIZE_Y / 2))
						{
							//パワーアップ
							pPlayer->GetPowerUp();
							//終了
							Uninit();
							return;
						}
					}
				}
			}
		}
	}
	if (m_bMove == false)
	{
		m_move.y = 3;
	}
	//画面の右に当たった時
	if (pos.x + ITEM_SIZE_X / 2 > MAX_GAME_WIDTH)
	{
		m_bMove = true;
		//真ん中より低かったら
		if (pos.y + ITEM_SIZE_Y / 2 < SCREEN_HEIGHT / 2)
		{
			m_move.x = -3;
			m_move.y = 3;
		}
		////真ん中より高かったら
		if (pos.y - ITEM_SIZE_Y / 2 > SCREEN_HEIGHT / 2)
		{
			m_move.x = -3;
			m_move.y = 3;
		}
	}
	//画面左に当たった時
	if (pos.x - ITEM_SIZE_X / 2 < MIN_GAME_WIDTH)
	{
		m_bMove = true;
		//真ん中より低かったら
		if (pos.y + ITEM_SIZE_Y / 2 < SCREEN_HEIGHT / 2)
		{
			m_move.x = 3;
			m_move.y = 3;
		}
		////真ん中より高かったら
		if (pos.y - ITEM_SIZE_Y / 2 > SCREEN_HEIGHT / 2)
		{
			m_move.x = 3;
			m_move.y = -3;
		}
	}
	//画面下に当たった時
	if (pos.y - ITEM_SIZE_Y / 2 <= 0)
	{
		m_bMove = true;
		if (pos.x + ITEM_SIZE_X / 2 > SCREEN_WIDTH / 2)
		{
			m_move.x = 3;
			m_move.y = 3;
		}
		if (pos.x + ITEM_SIZE_X / 2 < SCREEN_WIDTH / 2)
		{
			m_move.x = -3;
			m_move.y = 3;
		}
	}
	//画面上に当たった時
	if (pos.y + ITEM_SIZE_Y / 2 > SCREEN_HEIGHT)
	{
		m_bMove = true;
		m_move.y = -3;
	}
	pos.x += m_move.x;
	pos.y += m_move.y;
	SetPosition(pos);
}
//------------------------------------------------------------------
//描画
//------------------------------------------------------------------
void CItem::Draw(void)
{
	//描画
	CScene2d::Draw();
}