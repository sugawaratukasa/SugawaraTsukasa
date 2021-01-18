//---------------------------------------------------
// Bullet
// Bullet.cpp
// Author:	管原司
//---------------------------------------------------

//---------------------------------------------------
//インクルードファイル
//---------------------------------------------------
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
#include "ship.h"
#include "boss.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//-------------------------------------------------
//静的メンバ変数
//-------------------------------------------------
LPDIRECT3DTEXTURE9 CBullet::m_apTexture[MAX_BULLET_TEX] = {};
bool CBullet::m_bUseBeam = true;
bool CBullet::m_bUseBom = true;
//--------------------------------------------------
//テクスチャのロード
//--------------------------------------------------
HRESULT CBullet::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "data/Texture/Playerbullet001.png", &m_apTexture[TEX_TYPE_NORMAL]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/PlayerBeam001.png", &m_apTexture[TEX_TYPE_BEAM]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/bom.png", &m_apTexture[TEX_TYPE_BOM]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/EnemyBullet.png", &m_apTexture[TEX_TYPE_ENEMY_NORMAL]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/Bullet003test.png", &m_apTexture[TEX_TYPE_ENEMY_WAVE]);
	return S_OK;
}
//-------------------------------------------------
//テクスチャの破棄
//-------------------------------------------------
void CBullet::Unload(void)
{
	// テクスチャの破棄
	for (int nCnt = 0; nCnt < MAX_BULLET_TEX; nCnt++)
	{
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}
//---------------------------------------------------
//生成関数
//---------------------------------------------------
CBullet * CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, int sizeX, int sizeY, TYPE type, PATTERN_TYPE pattern , TEX_TYPE texType , OBJTYPE objtype)
{
	//CPlayerクラスのポインタ
	CBullet * pBullet;
	//メモリ確保
	pBullet = new CBullet;
	//初期化
	pBullet->Init(pos, rot, move, sizeX, sizeY, type, pattern, texType, objtype);
	return pBullet;
}
//---------------------------------------------------
//コンストラクタ
//---------------------------------------------------
CBullet::CBullet(int nPriority) : CScene2d(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_type = TYPE_NONE;
	m_textype = TEX_TYPE_NONE;
	m_objtype = OBJTYPE_NONE;
	m_PatternType = PATTERN_TYPE_NONE;
	m_bUseBeam = true;
	m_bUseBom = true;
	m_nEffectCount = 0;
	m_nDifCount = 0;
	m_nBom_Anim_Count = 0;
	m_nPattern_Bom_Anim = 0;
	m_nAddMove = 0;
	m_nMinMove = 0.0f;
	m_rad = 0.0f;
	m_fAngle = 0.0f;
	m_fMoveX = 0.0f;
	m_fMoveY = 0.0f;
	m_bWavemove = false;
}
//---------------------------------------------------
//デストラクタ
//---------------------------------------------------
CBullet::~CBullet()
{
}
//---------------------------------------------------
//初期化
//---------------------------------------------------
HRESULT CBullet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, int sizeX, int sizeY, TYPE type, PATTERN_TYPE pattern , TEX_TYPE texType , OBJTYPE objtype)
{
	//move
	m_move = move;
	//向き
	m_rot = rot;
	//タイプ
	m_type = type;
	//パターンのタイプ
	m_PatternType = pattern;
	//テクスチャタイプ
	m_textype = texType;
	//初期化
	CScene2d::Init(pos, rot, sizeX, sizeY);
	//弾の初期設定
	SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	BindTexture(m_apTexture[texType]);
	SetObjType(objtype);
	//プレイヤーの取得
	CPlayer * pPlayer = CGame::GetPlayer();
	//プレイヤーの座標取得
	D3DXVECTOR3 PlayerPos;
	PlayerPos = pPlayer->GetPosition();
	/*m_fAngle = atan2f(1000 - pos.y, 100 - pos.x);*/
	m_fAngle = atan2f(PlayerPos.y - pos.y, PlayerPos.x - pos.x);
	return S_OK;
}
//---------------------------------------------------
//終了
//---------------------------------------------------
void CBullet::Uninit(void)
{
	//終了
	CScene2d::Uninit();
}
//---------------------------------------------------
//更新
//---------------------------------------------------
void CBullet::Update(void)
{
	//更新
	CScene2d::Update();
	//サウンドの取得
	CSound * pSound = CSceneManager::GetSound();
	//スコアの取得
	CScore * pScore = CGame::GetScore();
	//ゲーム取得
	CGame * pGame = CSceneManager::GetGame();
	//プレイヤーの取得
	CPlayer * pPlayer = CGame::GetPlayer();
	//ボスの取得
	CBoss * pBoss = CGame::GetBoss();
	//船の取得
	CShip * pShip = CGame::GetShip();
	//プレイヤーの座標取得
	D3DXVECTOR3 PlayerPos;
	PlayerPos = pPlayer->GetPosition();
	//プレイヤーの状態取得
	int nPlayerState = 0;
	nPlayerState = pPlayer->GetPlayerState();
	//プレイヤーのレベル取得
	int PlayerLevel = 0;
	PlayerLevel = pPlayer->GetLevel();
	//座標の取得
	D3DXVECTOR3 pos;
	pos = GetPosition();
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
				//敵の取得
				CEnemy * pEnemy = (CEnemy*)(pScene);
				//タイプ
				switch (m_type)
				{
					//Playerの場合
				case TYPE_PLAYER:
					//通常弾の場合
					if (m_PatternType == PATTERN_TYPE_NORMAL)
					{
						//オブジェクトが敵の場合
						if (objType == OBJTYPE_ENEMY)
						{
							//レベルが1の場合
							if (PlayerLevel == CPlayer::LEVEL_1)
							{
								//敵と弾が当たった
								if (pos.x - BULLET_LEVEL1_SIZE_X / 2 < (ScenePos.x + ENEMY_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL1_SIZE_X / 2 > (ScenePos.x - ENEMY_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL1_SIZE_Y / 2 < (ScenePos.y + ENEMY_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL1_SIZE_Y / 2 > (ScenePos.y - ENEMY_SIZE_Y / 2))
								{
									////爆発音
									//pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);
									//爆発の生成
									CExplosion::Create(ScenePos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), EXPLOSION_SIZE_X, EXPLOSION_SIZE_Y);
									//スコア加算
									pScore->AddScore(100);
									pEnemy->HitEnemy(20);
									//終了
									Uninit();
									return;
								}
							}
							//レベルが2の場合
							if (PlayerLevel == CPlayer::LEVEL_2)
							{
								//敵と弾が当たった
								if (pos.x - BULLET_LEVEL2_SIZE_X / 2 < (ScenePos.x + ENEMY_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL2_SIZE_X / 2 > (ScenePos.x - ENEMY_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL2_SIZE_Y / 2 < (ScenePos.y + ENEMY_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL2_SIZE_Y / 2 > (ScenePos.y - ENEMY_SIZE_Y / 2))
								{
									////爆発音
									//pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);
									//爆発の生成
									CExplosion::Create(ScenePos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), EXPLOSION_SIZE_X, EXPLOSION_SIZE_Y);
									//スコア加算
									pScore->AddScore(100);
									//ダメージ
									pEnemy->HitEnemy(20);
									//終了
									Uninit();
									return;
								}
							}
							//レベル3の場合
							if (PlayerLevel == CPlayer::LEVEL_3)
							{
								//敵と弾が当たった
								if (pos.x - BULLET_LEVEL3_SIZE_X / 2 < (ScenePos.x + ENEMY_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL3_SIZE_X / 2 > (ScenePos.x - ENEMY_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL3_SIZE_Y / 2 < (ScenePos.y + ENEMY_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL3_SIZE_Y / 2 > (ScenePos.y - ENEMY_SIZE_Y / 2))
								{
									////爆発音
									//pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);
									//爆発の生成
									CExplosion::Create(ScenePos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), EXPLOSION_SIZE_X, EXPLOSION_SIZE_Y);
									//スコア加算
									pScore->AddScore(100);
									//ダメージ
									pEnemy->HitEnemy(20);
									//終了
									Uninit();
									return;
								}
							}
						}
						//タイプがオブジェクト
						if (objType == OBJTYPE_BOSS)
						{
							//レベルが1の場合
							if (PlayerLevel == CPlayer::LEVEL_1)
							{
								//敵と弾が当たった
								if (pos.x - BULLET_LEVEL1_SIZE_X / 2 < (ScenePos.x + BOSS_MAIN_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL1_SIZE_X / 2 > (ScenePos.x - BOSS_MAIN_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL1_SIZE_Y / 2 < (ScenePos.y + BOSS_MAIN_SIZE_Y / 2 - 80)
									&& pos.y + BULLET_LEVEL1_SIZE_Y / 2 > (ScenePos.y - BOSS_MAIN_SIZE_Y / 2))
								{
									//スコア加算
									pScore->AddScore(100);
									//ダメージ
									pBoss->HitBoss(40);
									//終了
									Uninit();
									return;
								}
							}
							//レベルが1の場合
							if (PlayerLevel == CPlayer::LEVEL_2)
							{
								//敵と弾が当たった
								if (pos.x - BULLET_LEVEL2_SIZE_X / 2 < (ScenePos.x + BOSS_MAIN_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL2_SIZE_X / 2 > (ScenePos.x - BOSS_MAIN_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL2_SIZE_Y / 2 < (ScenePos.y + BOSS_MAIN_SIZE_Y / 2 - 80)
									&& pos.y + BULLET_LEVEL2_SIZE_Y / 2 > (ScenePos.y - BOSS_MAIN_SIZE_Y / 2))
								{
									//スコア加算
									pScore->AddScore(100);
									//ダメージ
									pBoss->HitBoss(40);
									//終了
									Uninit();
									return;
								}
							}
							//レベルが1の場合
							if (PlayerLevel == CPlayer::LEVEL_3)
							{
								//敵と弾が当たった
								if (pos.x - BULLET_LEVEL3_SIZE_X / 2 < (ScenePos.x + BOSS_MAIN_SIZE_X / 2 )
									&& pos.x + BULLET_LEVEL3_SIZE_X / 2 > (ScenePos.x - BOSS_MAIN_SIZE_X / 2 )
									&& pos.y - BULLET_LEVEL3_SIZE_Y / 2 < (ScenePos.y + BOSS_MAIN_SIZE_Y / 2 - 80)
									&& pos.y + BULLET_LEVEL3_SIZE_Y / 2 > (ScenePos.y - BOSS_MAIN_SIZE_Y / 2 ))
								{
									//スコア加算
									pScore->AddScore(100);
									//ダメージ
									pBoss->HitBoss(40);
									//終了
									Uninit();
									return;
								}
							}
						}
						//ボスの右
						if (objType == OBJTYPE_BOSS_RIGHT)
						{
							//レベルが1の場合
							if (PlayerLevel == CPlayer::LEVEL_1)
							{
								//敵と弾が当たった
								if (pos.x - BULLET_LEVEL1_SIZE_X / 2 < (ScenePos.x + BOSS_RIGHT_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL1_SIZE_X / 2 > (ScenePos.x - BOSS_RIGHT_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL1_SIZE_Y / 2 < (ScenePos.y + BOSS_RIGHT_SIZE_Y / 2 - 30)
									&& pos.y + BULLET_LEVEL1_SIZE_Y / 2 > (ScenePos.y - BOSS_RIGHT_SIZE_Y / 2))
								{
									//スコア加算
									pScore->AddScore(100);
									//ダメージ
									pBoss->HitBoss(20);
									//終了
									Uninit();
									return;
								}
							}
							//レベルが2の場合
							if (PlayerLevel == CPlayer::LEVEL_2)
							{
								//敵と弾が当たった
								if (pos.x - BULLET_LEVEL2_SIZE_X / 2 < (ScenePos.x + BOSS_RIGHT_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL2_SIZE_X / 2 > (ScenePos.x - BOSS_RIGHT_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL2_SIZE_Y / 2 < (ScenePos.y + BOSS_RIGHT_SIZE_Y / 2 - 30)
									&& pos.y + BULLET_LEVEL2_SIZE_Y / 2 > (ScenePos.y - BOSS_RIGHT_SIZE_Y / 2))
								{
									//スコア加算
									pScore->AddScore(100);
									//ダメージ
									pBoss->HitBoss(20);
									//終了
									Uninit();
									return;
								}
							}
							//レベルが3の場合
							if (PlayerLevel == CPlayer::LEVEL_3)
							{
								//敵と弾が当たった
								if (pos.x - BULLET_LEVEL3_SIZE_X / 2 < (ScenePos.x + BOSS_RIGHT_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL3_SIZE_X / 2 > (ScenePos.x - BOSS_RIGHT_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL3_SIZE_Y / 2 < (ScenePos.y + BOSS_RIGHT_SIZE_Y / 2 - 30)
									&& pos.y + BULLET_LEVEL3_SIZE_Y / 2 > (ScenePos.y - BOSS_RIGHT_SIZE_Y / 2))
								{
									//スコア加算
									pScore->AddScore(100);
									//ダメージ
									pBoss->HitBoss(20);
									//終了
									Uninit();
									return;
								}
							}
						}
						//ボスの左
						if (objType == OBJTYPE_BOSS_LEFT)
						{
							//レベルが1の場合
							if (PlayerLevel == CPlayer::LEVEL_1)
							{
								//敵と弾が当たった
								if (pos.x - BULLET_LEVEL1_SIZE_X / 2 < (ScenePos.x + BOSS_LEFT_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL1_SIZE_X / 2 > (ScenePos.x - BOSS_LEFT_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL1_SIZE_Y / 2 < (ScenePos.y + BOSS_LEFT_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL1_SIZE_Y / 2 > (ScenePos.y - BOSS_LEFT_SIZE_Y / 2))
								{
									//スコア加算
									pScore->AddScore(100);
									//ダメージ
									pBoss->HitBoss(20);
									//終了
									Uninit();
									return;
								}
							}
							//レベルが2の場合
							if (PlayerLevel == CPlayer::LEVEL_2)
							{
								//敵と弾が当たった
								if (pos.x - BULLET_LEVEL2_SIZE_X / 2 < (ScenePos.x + BOSS_LEFT_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL2_SIZE_X / 2 > (ScenePos.x - BOSS_LEFT_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL2_SIZE_Y / 2 < (ScenePos.y + BOSS_LEFT_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL2_SIZE_Y / 2 > (ScenePos.y - BOSS_LEFT_SIZE_Y / 2))
								{
									//スコア加算
									pScore->AddScore(100);
									//ダメージ
									pBoss->HitBoss(20);
									//終了
									Uninit();
									return;
								}
							}
							//レベルが3の場合
							if (PlayerLevel == CPlayer::LEVEL_3)
							{
								//敵と弾が当たった
								if (pos.x - BULLET_LEVEL3_SIZE_X / 2 < (ScenePos.x + BOSS_LEFT_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL3_SIZE_X / 2 > (ScenePos.x - BOSS_LEFT_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL3_SIZE_Y / 2 < (ScenePos.y + BOSS_LEFT_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL3_SIZE_Y / 2 > (ScenePos.y - BOSS_LEFT_SIZE_Y / 2))
								{
									//スコア加算
									pScore->AddScore(100);
									//ダメージ
									pBoss->HitBoss(20);
									//終了
									Uninit();
									return;
								}
							}
						}
						//タイプがSHIPWEPON1の場合
						if (objType == OBJTYPE_SHIP_WEPON1)
						{
							//レベルが1の場合
							if (PlayerLevel == CPlayer::LEVEL_1)
							{
								//敵と弾が当たった
								if (pos.x - BULLET_LEVEL1_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL1_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL1_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL1_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//ダメージ
									pShip->HitWepon1(10);
									//終了
									Uninit();
									return;
								}
							}
							//レベルが1の場合
							if (PlayerLevel == CPlayer::LEVEL_2)
							{
								//敵と弾が当たった
								if (pos.x - BULLET_LEVEL2_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL2_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL2_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL2_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//ダメージ
									pShip->HitWepon1(10);
									//終了
									Uninit();
									return;
								}
							}
							//レベルが1の場合
							if (PlayerLevel == CPlayer::LEVEL_3)
							{
								//敵と弾が当たった
								if (pos.x - BULLET_LEVEL3_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL3_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL3_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL3_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//ダメージ
									pShip->HitWepon1(10);
									//終了
									Uninit();
									return;
								}
							}
						}
						//タイプがSHIPWEPON2の場合
						if (objType == OBJTYPE_SHIP_WEPON2)
						{
							//レベルが1の場合
							if (PlayerLevel == CPlayer::LEVEL_1)
							{
								//敵と弾が当たった
								if (pos.x - BULLET_LEVEL1_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL1_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL1_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL1_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//ダメージ
									pShip->HitWepon2(10);
									//終了
									Uninit();
									return;
								}
							}
							//レベルが1の場合
							if (PlayerLevel == CPlayer::LEVEL_2)
							{
								//敵と弾が当たった
								if (pos.x - BULLET_LEVEL2_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL2_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL2_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL2_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//ダメージ
									pShip->HitWepon2(10);
									//終了
									Uninit();
									return;
								}
							}
							//レベルが1の場合
							if (PlayerLevel == CPlayer::LEVEL_3)
							{
								//敵と弾が当たった
								if (pos.x - BULLET_LEVEL3_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL3_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL3_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL3_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//ダメージ
									pShip->HitWepon2(10);
									//終了
									Uninit();
									return;
								}
							}
						}
						//タイプがSHIPWEPON3の場合
						if (objType == OBJTYPE_SHIP_WEPON3)
						{
							//レベルが1の場合
							if (PlayerLevel == CPlayer::LEVEL_1)
							{
								//敵と弾が当たった
								if (pos.x - BULLET_LEVEL1_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL1_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL1_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL1_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//ダメージ
									pShip->HitWepon3(10);
									//終了
									Uninit();
									return;
								}
							}
							//レベルが1の場合
							if (PlayerLevel == CPlayer::LEVEL_2)
							{
								//敵と弾が当たった
								if (pos.x - BULLET_LEVEL2_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL2_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL2_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL2_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//ダメージ
									pShip->HitWepon3(10);
									//終了
									Uninit();
									return;
								}
							}
							//レベルが1の場合
							if (PlayerLevel == CPlayer::LEVEL_3)
							{
								//敵と弾が当たった
								if (pos.x - BULLET_LEVEL3_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL3_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL3_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL3_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//ダメージ
									pShip->HitWepon3(10);
									//終了
									Uninit();
									return;
								}
							}
						}
						//SHIP_WEPON_4
						if (objType == OBJTYPE_SHIP_WEPON4)
						{
							//レベルが1の場合
							if (PlayerLevel == CPlayer::LEVEL_1)
							{
								//敵と弾が当たった
								if (pos.x - BULLET_LEVEL1_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL1_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL1_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL1_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//ダメージ
									pShip->HitWepon4(10);
									//終了
									Uninit();
									return;
								}
							}
							//レベルが1の場合
							if (PlayerLevel == CPlayer::LEVEL_2)
							{
								//敵と弾が当たった
								if (pos.x - BULLET_LEVEL2_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL2_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL2_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL2_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//ダメージ
									pShip->HitWepon4(10);
									//終了
									Uninit();
									return;
								}
							}
							//レベルが1の場合
							if (PlayerLevel == CPlayer::LEVEL_3)
							{
								//敵と弾が当たった
								if (pos.x - BULLET_LEVEL3_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL3_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL3_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL3_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//ダメージ
									pShip->HitWepon4(10);
									//終了
									Uninit();
									return;
								}
							}
						}
						//SHIP_WEPON_4
						if (objType == OBJTYPE_SHIP_WEPON5)
						{
							//レベルが1の場合
							if (PlayerLevel == CPlayer::LEVEL_1)
							{
								//敵と弾が当たった
								if (pos.x - BULLET_LEVEL1_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL1_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL1_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL1_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//ダメージ
									pShip->HitWepon5(10);
									//終了
									Uninit();
									return;
								}
							}
							//レベルが1の場合
							if (PlayerLevel == CPlayer::LEVEL_2)
							{
								//敵と弾が当たった
								if (pos.x - BULLET_LEVEL2_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL2_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL2_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL2_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//ダメージ
									pShip->HitWepon5(10);
									//終了
									Uninit();
									return;
								}
							}
							//レベルが3の場合
							if (PlayerLevel == CPlayer::LEVEL_3)
							{
								//敵と弾が当たった
								if (pos.x - BULLET_LEVEL3_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL3_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL3_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL3_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//ダメージ
									pShip->HitWepon5(10);
									//終了
									Uninit();
									return;
								}
							}
						}
						//SHIP_WEPON_6
						if (objType == OBJTYPE_SHIP_WEPON6)
						{
							//レベルが1の場合
							if (PlayerLevel == CPlayer::LEVEL_1)
							{
								//敵と弾が当たった
								if (pos.x - BULLET_LEVEL1_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL1_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL1_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL1_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//ダメージ
									pShip->HitWepon6(10);
									//終了
									Uninit();
									return;
								}
							}
							//レベルが2の場合
							if (PlayerLevel == CPlayer::LEVEL_2)
							{
								//敵と弾が当たった
								if (pos.x - BULLET_LEVEL2_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL2_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL2_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL2_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//ダメージ
									pShip->HitWepon6(10);
									//終了
									Uninit();
									return;
								}
							}
							//レベルが3の場合
							if (PlayerLevel == CPlayer::LEVEL_3)
							{
								//敵と弾が当たった
								if (pos.x - BULLET_LEVEL3_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL3_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL3_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL3_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//ダメージ
									pShip->HitWepon6(10);
									//終了
									Uninit();
									return;
								}
							}
						}
					}
					//ビームの場合
					if (m_PatternType == PATTERN_TYPE_BEAM)
					{
						pos.x = PlayerPos.x;
						//オブジェクトがボスの場合
						if (objType == OBJTYPE_BOSS)
						{
							//レベルが1の場合
							if (PlayerLevel == CPlayer::LEVEL_1)
							{
								//敵と弾が当たった
								if ((pos.x - BULLET_LEVEL1_BEAM_SIZE_X / 2) < (ScenePos.x + BOSS_MAIN_SIZE_X / 2 )
									&& (pos.x + BULLET_LEVEL1_BEAM_SIZE_X / 2) > (ScenePos.x - BOSS_MAIN_SIZE_X / 2)
									&& (pos.y - BULLET_LEVEL1_BEAM_SIZE_Y / 2) < (ScenePos.y + BOSS_MAIN_SIZE_Y / 2 - 80)
									&& (pos.y + BULLET_LEVEL1_BEAM_SIZE_Y / 2) > (ScenePos.y - BOSS_MAIN_SIZE_Y / 2))
								{
									//スコアの加算
									pScore->AddScore(100);
									//敵の終了処理
									pBoss->HitBoss(20);
									//終了
									Uninit();
									return;
								}
							}
							//レベルが2の場合
							if (PlayerLevel == CPlayer::LEVEL_2)
							{
								//敵と弾が当たった
								if ((pos.x - BULLET_LEVEL2_BEAM_SIZE_X / 2) < (ScenePos.x + BOSS_MAIN_SIZE_X / 2)
									&& (pos.x + BULLET_LEVEL2_BEAM_SIZE_X / 2) > (ScenePos.x - BOSS_MAIN_SIZE_X / 2)
									&& (pos.y - BULLET_LEVEL2_BEAM_SIZE_Y / 2) < (ScenePos.y + BOSS_MAIN_SIZE_Y / 2 - 80)
									&& (pos.y + BULLET_LEVEL2_BEAM_SIZE_Y / 2) > (ScenePos.y - BOSS_MAIN_SIZE_Y / 2))
								{
									//スコアの加算
									pScore->AddScore(100);
									//敵の終了処理
									pBoss->HitBoss(20);
									//終了
									Uninit();
									return;
								}
							}
							//レベルが3の場合
							if (PlayerLevel == CPlayer::LEVEL_3)
							{
								//敵と弾が当たった
								if ((pos.x - BULLET_LEVEL3_BEAM_SIZE_X / 2) < (ScenePos.x + BOSS_MAIN_SIZE_X / 2)
									&& (pos.x + BULLET_LEVEL3_BEAM_SIZE_X / 2) > (ScenePos.x - BOSS_MAIN_SIZE_X / 2)
									&& (pos.y - BULLET_LEVEL3_BEAM_SIZE_Y / 2) < (ScenePos.y + BOSS_MAIN_SIZE_Y / 2 - 80)
									&& (pos.y + BULLET_LEVEL3_BEAM_SIZE_Y / 2) > (ScenePos.y - BOSS_MAIN_SIZE_Y / 2))
								{
									//スコアの加算
									pScore->AddScore(100);
									//敵の終了処理
									pBoss->HitBoss(20);
									//終了
									Uninit();
									return;
								}
							}
						}
						//ボスの右
						if (objType == OBJTYPE_BOSS_RIGHT)
						{
							//レベルが1の場合
							if (PlayerLevel == CPlayer::LEVEL_1)
							{
								//敵と弾が当たった
								if ((pos.x - BULLET_LEVEL1_BEAM_SIZE_X / 2) < (ScenePos.x + BOSS_RIGHT_SIZE_X / 2)
									&& (pos.x + BULLET_LEVEL1_BEAM_SIZE_X / 2) > (ScenePos.x - BOSS_RIGHT_SIZE_X / 2)
									&& (pos.y - BULLET_LEVEL1_BEAM_SIZE_Y / 2) < (ScenePos.y + BOSS_RIGHT_SIZE_Y / 2 - 30)
									&& (pos.y + BULLET_LEVEL1_BEAM_SIZE_Y / 2) > (ScenePos.y - BOSS_RIGHT_SIZE_Y / 2))
								{
									//スコアの加算
									pScore->AddScore(100);
									//ダメージ
									pBoss->HitBoss(10);
									//終了
									Uninit();
									return;
								}
							}
							//レベルが2の場合
							if (PlayerLevel == CPlayer::LEVEL_2)
							{
								//敵と弾が当たった
								if ((pos.x - BULLET_LEVEL2_BEAM_SIZE_X / 2) < (ScenePos.x + BOSS_RIGHT_SIZE_X / 2)
									&& (pos.x + BULLET_LEVEL2_BEAM_SIZE_X / 2) > (ScenePos.x - BOSS_RIGHT_SIZE_X / 2)
									&& (pos.y - BULLET_LEVEL2_BEAM_SIZE_Y / 2) < (ScenePos.y + BOSS_RIGHT_SIZE_Y / 2 - 30)
									&& (pos.y + BULLET_LEVEL2_BEAM_SIZE_Y / 2) > (ScenePos.y - BOSS_RIGHT_SIZE_Y / 2))
								{
									//スコアの加算
									pScore->AddScore(100);
									//ダメージ
									pBoss->HitBoss(10);
									//終了
									Uninit();
									return;
								}
							}
							//レベルが3の場合
							if (PlayerLevel == CPlayer::LEVEL_3)
							{
								//敵と弾が当たった
								if ((pos.x - BULLET_LEVEL3_BEAM_SIZE_X / 2) < (ScenePos.x + BOSS_RIGHT_SIZE_X / 2)
									&& (pos.x + BULLET_LEVEL3_BEAM_SIZE_X / 2) > (ScenePos.x - BOSS_RIGHT_SIZE_X / 2)
									&& (pos.y - BULLET_LEVEL3_BEAM_SIZE_Y / 2) < (ScenePos.y + BOSS_RIGHT_SIZE_Y / 2 - 30)
									&& (pos.y + BULLET_LEVEL3_BEAM_SIZE_Y / 2) > (ScenePos.y - BOSS_RIGHT_SIZE_Y / 2))
								{
									//スコアの加算
									pScore->AddScore(100);
									//ダメージ
									pBoss->HitBoss(10);
									//終了
									Uninit();
									return;
								}
							}
						}
						//ボスの左
						if (objType == OBJTYPE_BOSS_LEFT)
						{
							//レベルが1の場合
							if (PlayerLevel == CPlayer::LEVEL_1)
							{
								//敵と弾が当たった
								if ((pos.x - BULLET_LEVEL1_BEAM_SIZE_X / 2) < (ScenePos.x + BOSS_LEFT_SIZE_X / 2)
									&& (pos.x + BULLET_LEVEL1_BEAM_SIZE_X / 2) > (ScenePos.x - BOSS_LEFT_SIZE_X / 2)
									&& (pos.y - BULLET_LEVEL1_BEAM_SIZE_Y / 2) < (ScenePos.y + BOSS_LEFT_SIZE_Y / 2 - 30)
									&& (pos.y + BULLET_LEVEL1_BEAM_SIZE_Y / 2) > (ScenePos.y - BOSS_LEFT_SIZE_Y / 2))
								{
									//スコアの加算
									pScore->AddScore(100);
									//ダメージ
									pBoss->HitBoss(10);
									//終了
									Uninit();
									return;
								}
							}
							//レベルが2の場合
							if (PlayerLevel == CPlayer::LEVEL_2)
							{
								//敵と弾が当たった
								if ((pos.x - BULLET_LEVEL2_BEAM_SIZE_X / 2) < (ScenePos.x + BOSS_LEFT_SIZE_X / 2)
									&& (pos.x + BULLET_LEVEL2_BEAM_SIZE_X / 2) > (ScenePos.x - BOSS_LEFT_SIZE_X / 2)
									&& (pos.y - BULLET_LEVEL2_BEAM_SIZE_Y / 2) < (ScenePos.y + BOSS_LEFT_SIZE_Y / 2 - 30)
									&& (pos.y + BULLET_LEVEL2_BEAM_SIZE_Y / 2) > (ScenePos.y - BOSS_LEFT_SIZE_Y / 2))
								{
									//スコアの加算
									pScore->AddScore(100);
									//ダメージ
									pBoss->HitBoss(10);
									//終了
									Uninit();
									return;
								}
							}
							//レベルが3の場合
							if (PlayerLevel == CPlayer::LEVEL_3)
							{
								//敵と弾が当たった
								if ((pos.x - BULLET_LEVEL3_BEAM_SIZE_X / 2) < (ScenePos.x + BOSS_LEFT_SIZE_X / 2)
									&& (pos.x + BULLET_LEVEL3_BEAM_SIZE_X / 2) > (ScenePos.x - BOSS_LEFT_SIZE_X / 2)
									&& (pos.y - BULLET_LEVEL3_BEAM_SIZE_Y / 2) < (ScenePos.y + BOSS_LEFT_SIZE_Y / 2 - 30)
									&& (pos.y + BULLET_LEVEL3_BEAM_SIZE_Y / 2) > (ScenePos.y - BOSS_LEFT_SIZE_Y / 2))
								{
									//スコアの加算
									pScore->AddScore(100);
									//ダメージ
									pBoss->HitBoss(10);
									//終了
									Uninit();
									return;
								}
							}
						}
						//オブジェクトが敵の場合
						if (objType == OBJTYPE_ENEMY)
						{
							//レベルが1の場合
							if (PlayerLevel == CPlayer::LEVEL_1)
							{
								//敵と弾が当たった
								if ((pos.x - BULLET_LEVEL1_BEAM_SIZE_X / 2) < (ScenePos.x + ENEMY_SIZE_X / 2)
									&& (pos.x + BULLET_LEVEL1_BEAM_SIZE_X / 2) > (ScenePos.x - ENEMY_SIZE_X / 2)
									&& (pos.y - BULLET_LEVEL1_BEAM_SIZE_Y / 2) < (ScenePos.y + ENEMY_SIZE_Y / 2)
									&& (pos.y + BULLET_LEVEL1_BEAM_SIZE_Y / 2) > (ScenePos.y - ENEMY_SIZE_Y / 2))
								{
									//サウンド生成
									/*pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);*/
									//爆発生成
									CExplosion::Create(ScenePos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), EXPLOSION_SIZE_X, EXPLOSION_SIZE_Y);
									//スコアの加算
									pScore->AddScore(100);
									//敵の終了処理
									pEnemy->HitEnemy(5);
									//終了
									Uninit();
									return;
								}
							}
							//レベルが1の場合
							if (PlayerLevel == CPlayer::LEVEL_2)
							{
								//敵と弾が当たった
								if ((pos.x - BULLET_LEVEL2_BEAM_SIZE_X / 2) < (ScenePos.x + ENEMY_SIZE_X / 2)
									&& (pos.x + BULLET_LEVEL2_BEAM_SIZE_X / 2) > (ScenePos.x - ENEMY_SIZE_X / 2)
									&& (pos.y - BULLET_LEVEL2_BEAM_SIZE_Y / 2) < (ScenePos.y + ENEMY_SIZE_Y / 2)
									&& (pos.y + BULLET_LEVEL2_BEAM_SIZE_Y / 2) > (ScenePos.y - ENEMY_SIZE_Y / 2))
								{
									//サウンド生成
									/*pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);*/
									//爆発生成
									CExplosion::Create(ScenePos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), EXPLOSION_SIZE_X, EXPLOSION_SIZE_Y);
									//スコアの加算
									pScore->AddScore(100);
									//敵の終了処理
									pEnemy->HitEnemy(5);
									//終了
									Uninit();
									return;
								}
							}
							//レベルが1の場合
							if (PlayerLevel == CPlayer::LEVEL_3)
							{
								//敵と弾が当たった
								if ((pos.x - BULLET_LEVEL3_BEAM_SIZE_X / 2) < (ScenePos.x + ENEMY_SIZE_X / 2)
									&& (pos.x + BULLET_LEVEL3_BEAM_SIZE_X / 2) > (ScenePos.x - ENEMY_SIZE_X / 2)
									&& (pos.y - BULLET_LEVEL3_BEAM_SIZE_Y / 2) < (ScenePos.y + ENEMY_SIZE_Y / 2)
									&& (pos.y + BULLET_LEVEL3_BEAM_SIZE_Y / 2) > (ScenePos.y - ENEMY_SIZE_Y / 2))
								{
									//サウンド生成
									/*pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);*/
									//爆発生成
									CExplosion::Create(ScenePos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), EXPLOSION_SIZE_X, EXPLOSION_SIZE_Y);
									//スコアの加算
									pScore->AddScore(100);
									//敵の終了処理
									pEnemy->HitEnemy(5);
									//終了
									Uninit();
									return;
								}
							}
						}
						//タイプがSHIPWEPON1の場合
						if (objType == OBJTYPE_SHIP_WEPON1)
						{
							//レベルが1の場合
							if (PlayerLevel == CPlayer::LEVEL_1)
							{
								//敵と弾が当たった
								if (pos.x - BULLET_LEVEL1_BEAM_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL1_BEAM_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL1_BEAM_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL1_BEAM_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//ダメージ
									pShip->HitWepon1(10);
									//終了
									Uninit();
									return;
								}
							}
							//レベルが2の場合
							if (PlayerLevel == CPlayer::LEVEL_2)
							{
								//敵と弾が当たった
								if (pos.x - BULLET_LEVEL2_BEAM_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL2_BEAM_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL2_BEAM_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL2_BEAM_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//ダメージ
									pShip->HitWepon1(10);
									//終了
									Uninit();
									return;
								}
							}
							//レベルが3の場合
							if (PlayerLevel == CPlayer::LEVEL_3)
							{
								//敵と弾が当たった
								if (pos.x - BULLET_LEVEL3_BEAM_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL3_BEAM_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL3_BEAM_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL3_BEAM_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//ダメージ
									pShip->HitWepon1(10);
									//終了
									Uninit();
									return;
								}
							}
						}
					}
						//タイプがSHIPWEPON2の場合
						if (objType == OBJTYPE_SHIP_WEPON2)
						{
							//レベルが1の場合
							if (PlayerLevel == CPlayer::LEVEL_1)
							{
								//敵と弾が当たった
								if (pos.x - BULLET_LEVEL1_BEAM_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL1_BEAM_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL1_BEAM_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL1_BEAM_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//ダメージ
									pShip->HitWepon2(10);
									//終了
									Uninit();
									return;
								}
							}
							//レベルが2の場合
							if (PlayerLevel == CPlayer::LEVEL_2)
							{
								//敵と弾が当たった
								if (pos.x - BULLET_LEVEL2_BEAM_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL2_BEAM_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL2_BEAM_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL2_BEAM_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//ダメージ
									pShip->HitWepon2(10);
									//終了
									Uninit();
									return;
								}
							}
							//レベルが3の場合
							if (PlayerLevel == CPlayer::LEVEL_3)
							{
								//敵と弾が当たった
								if (pos.x - BULLET_LEVEL3_BEAM_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL3_BEAM_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL3_BEAM_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL3_BEAM_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//ダメージ
									pShip->HitWepon2(10);
									//終了
									Uninit();
									return;
								}
							}
						}
						//タイプがSHIPWEPON3の場合
						if (objType == OBJTYPE_SHIP_WEPON3)
						{
							//レベルが1の場合
							if (PlayerLevel == CPlayer::LEVEL_1)
							{
								//敵と弾が当たった
								if (pos.x - BULLET_LEVEL1_BEAM_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL1_BEAM_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL1_BEAM_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL1_BEAM_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//ダメージ
									pShip->HitWepon3(10);
									//終了
									Uninit();
									return;
								}
							}
							//レベルが2の場合
							if (PlayerLevel == CPlayer::LEVEL_2)
							{
								//敵と弾が当たった
								if (pos.x - BULLET_LEVEL2_BEAM_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL2_BEAM_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL2_BEAM_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL2_BEAM_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//ダメージ
									pShip->HitWepon3(10);
									//終了
									Uninit();
									return;
								}
							}
							//レベルが3の場合
							if (PlayerLevel == CPlayer::LEVEL_3)
							{
								//敵と弾が当たった
								if (pos.x - BULLET_LEVEL3_BEAM_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL3_BEAM_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL3_BEAM_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL3_BEAM_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//ダメージ
									pShip->HitWepon3(10);
									//終了
									Uninit();
									return;
								}
							}
						}
						//SHIP_WEPON_4
						if (objType == OBJTYPE_SHIP_WEPON4)
						{
							//レベルが1の場合
							if (PlayerLevel == CPlayer::LEVEL_1)
							{
								//敵と弾が当たった
								if (pos.x - BULLET_LEVEL1_BEAM_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL1_BEAM_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL1_BEAM_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL1_BEAM_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//ダメージ
									pShip->HitWepon4(10);
									//終了
									Uninit();
									return;
								}
							}
							//レベルが2の場合
							if (PlayerLevel == CPlayer::LEVEL_2)
							{
								//敵と弾が当たった
								if (pos.x - BULLET_LEVEL2_BEAM_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL2_BEAM_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL2_BEAM_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL2_BEAM_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//ダメージ
									pShip->HitWepon4(10);
									//終了
									Uninit();
									return;
								}
							}
							//レベルが3の場合
							if (PlayerLevel == CPlayer::LEVEL_3)
							{
								//敵と弾が当たった
								if (pos.x - BULLET_LEVEL3_BEAM_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL3_BEAM_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL3_BEAM_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL3_BEAM_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//ダメージ
									pShip->HitWepon4(10);
									//終了
									Uninit();
									return;
								}
							}
						}
						//SHIP_WEPON_4
						if (objType == OBJTYPE_SHIP_WEPON5)
						{
							//レベルが1の場合
							if (PlayerLevel == CPlayer::LEVEL_1)
							{
								//敵と弾が当たった
								if (pos.x - BULLET_LEVEL1_BEAM_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL1_BEAM_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL1_BEAM_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL1_BEAM_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//ダメージ
									pShip->HitWepon5(10);
									//終了
									Uninit();
									return;
								}
							}
							//レベルが2の場合
							if (PlayerLevel == CPlayer::LEVEL_2)
							{
								//敵と弾が当たった
								if (pos.x - BULLET_LEVEL2_BEAM_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL2_BEAM_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL2_BEAM_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL2_BEAM_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//ダメージ
									pShip->HitWepon5(10);
									//終了
									Uninit();
									return;
								}
							}
							//レベルが3の場合
							if (PlayerLevel == CPlayer::LEVEL_3)
							{
								//敵と弾が当たった
								if (pos.x - BULLET_LEVEL3_BEAM_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL3_BEAM_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL3_BEAM_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL3_BEAM_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//ダメージ
									pShip->HitWepon5(10);
									//終了
									Uninit();
									return;
								}
							}
						}
						//SHIP_WEPON_6
						if (objType == OBJTYPE_SHIP_WEPON6)
						{
							//レベルが1の場合
							if (PlayerLevel == CPlayer::LEVEL_1)
							{
								//敵と弾が当たった
								if (pos.x - BULLET_LEVEL1_BEAM_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL1_BEAM_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL1_BEAM_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL1_BEAM_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//ダメージ
									pShip->HitWepon6(10);
									//終了
									Uninit();
									return;
								}
							}
							//レベルが2の場合
							if (PlayerLevel == CPlayer::LEVEL_2)
							{
								//敵と弾が当たった
								if (pos.x - BULLET_LEVEL2_BEAM_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL2_BEAM_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL2_BEAM_SIZE_Y / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL2_BEAM_SIZE_Y / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//ダメージ
									pShip->HitWepon6(10);
									//終了
									Uninit();
									return;
								}
							}
							//レベルが3の場合
							if (PlayerLevel == CPlayer::LEVEL_3)
							{
								//敵と弾が当たった
								if (pos.x - BULLET_LEVEL3_BEAM_SIZE_X / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + BULLET_LEVEL3_BEAM_SIZE_X / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - BULLET_LEVEL3_BEAM_SIZE_X / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + BULLET_LEVEL3_BEAM_SIZE_X / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//ダメージ
									pShip->HitWepon6(10);
									//終了
									Uninit();
									return;
								}
							}
						}
						//ボム
						if (m_PatternType == PATTERN_TYPE_BOM)
						{
							//敵の弾
							if (objType == OBJTYPE_ENEMY_BULLET)
							{
								//敵と弾が当たった
								if ((pos.x - MAX_GAME_WIDTH / 2) < (ScenePos.x + ENEMY_BULLET_SIZE_X / 2)
									&& (pos.x + MAX_GAME_WIDTH / 2) > (ScenePos.x - ENEMY_BULLET_SIZE_X / 2)
									&& (pos.y - SCREEN_HEIGHT / 2) < (ScenePos.y + ENEMY_BULLET_SIZE_Y / 2)
									&& (pos.y + SCREEN_HEIGHT / 2) > (ScenePos.y - ENEMY_BULLET_SIZE_Y / 2))
								{
									//敵の弾の終了
									pScene->Uninit();
								}
							}

							//オブジェクトが敵の場合
							if (objType == OBJTYPE_ENEMY)
							{
								//敵と弾が当たった
								if ((pos.x - MAX_GAME_WIDTH / 2) < (ScenePos.x + ENEMY_SIZE_X / 2)
									&& (pos.x + MAX_GAME_WIDTH / 2) > (ScenePos.x - ENEMY_SIZE_X / 2)
									&& (pos.y - SCREEN_HEIGHT / 2) < (ScenePos.y + ENEMY_SIZE_Y / 2)
									&& (pos.y + SCREEN_HEIGHT / 2) > (ScenePos.y - ENEMY_SIZE_Y / 2))
								{
									//ダメージ
									pEnemy->HitEnemy(50);
								}
							}
							//タイプがSHIPWEPON1の場合
							if (objType == OBJTYPE_SHIP_WEPON1)
							{
								//敵と弾が当たった
								if (pos.x - MAX_GAME_WIDTH / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + MAX_GAME_WIDTH / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - SCREEN_HEIGHT / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + SCREEN_HEIGHT / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//ダメージ
									pShip->HitWepon1(50);
								}
							}
							//タイプがSHIPWEPON2の場合
							if (objType == OBJTYPE_SHIP_WEPON2)
							{
								//敵と弾が当たった
								if (pos.x - MAX_GAME_WIDTH / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + MAX_GAME_WIDTH / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - SCREEN_HEIGHT / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + SCREEN_HEIGHT / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//ダメージ
									pShip->HitWepon2(50);
								}
							}
							//タイプがSHIPWEPON3の場合
							if (objType == OBJTYPE_SHIP_WEPON3)
							{
								//敵と弾が当たった
								if (pos.x - MAX_GAME_WIDTH / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + MAX_GAME_WIDTH / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - SCREEN_HEIGHT / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + SCREEN_HEIGHT / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//ダメージ
									pShip->HitWepon3(50);
								}
							}
							//タイプがSHIPWEPON4の場合
							if (objType == OBJTYPE_SHIP_WEPON4)
							{
								//敵と弾が当たった
								if (pos.x - MAX_GAME_WIDTH / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + MAX_GAME_WIDTH / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - SCREEN_HEIGHT / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + SCREEN_HEIGHT / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//ダメージ
									pShip->HitWepon4(50);
								}
							}
							//タイプがSHIPWEPON5の場合
							if (objType == OBJTYPE_SHIP_WEPON5)
							{
								//敵と弾が当たった
								if (pos.x - MAX_GAME_WIDTH / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + MAX_GAME_WIDTH / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - SCREEN_HEIGHT / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + SCREEN_HEIGHT / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//ダメージ
									pShip->HitWepon5(50);
								}
							}
							//タイプがSHIPWEPON6の場合
							if (objType == OBJTYPE_SHIP_WEPON6)
							{
								//敵と弾が当たった
								if (pos.x - MAX_GAME_WIDTH / 2 < (ScenePos.x + SHIP_WEPON_SIZE_X / 2)
									&& pos.x + MAX_GAME_WIDTH / 2 > (ScenePos.x - SHIP_WEPON_SIZE_X / 2)
									&& pos.y - SCREEN_HEIGHT / 2 < (ScenePos.y + SHIP_WEPON_SIZE_Y / 2)
									&& pos.y + SCREEN_HEIGHT / 2 > (ScenePos.y - SHIP_WEPON_SIZE_Y / 2))
								{
									//ダメージ
									pShip->HitWepon6(50);
								}
							}
						}
					//ビームの場合
					if (m_PatternType == PATTERN_TYPE_BOSS_BOM)
					{
						pos.x = PlayerPos.x;
						//オブジェクトが敵の場合
						if (objType == OBJTYPE_BOSS)
						{
							//敵と弾が当たった
							if ((pos.x - BULLET_BOSS_BOM_SIZE_X / 2) < (ScenePos.x + BOSS_MAIN_SIZE_X / 2)
								&& (pos.x + BULLET_BOM_SIZE_X / 2) > (ScenePos.x - BOSS_MAIN_SIZE_X / 2)
								&& (pos.y - BULLET_BOSS_BOM_SIZE_Y / 2) < (ScenePos.y + BOSS_MAIN_SIZE_Y / 2)
								&& (pos.y + BULLET_BOSS_BOM_SIZE_Y / 2) > (ScenePos.y - BOSS_MAIN_SIZE_Y / 2))
							{
								//爆発生成
								CExplosion::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), EXPLOSION_SIZE_X, EXPLOSION_SIZE_Y);
								//スコアの加算
								pScore->AddScore(10);
								//ボスにダメージ
								pBoss->HitBoss(30);
								//終了
								Uninit();
								return;
							}
						}
						if (objType == OBJTYPE_BOSS_RIGHT)
						{
							//敵と弾が当たった
							if ((pos.x - BULLET_BOSS_BOM_SIZE_X / 2) < (ScenePos.x + BOSS_RIGHT_SIZE_X / 2)
								&& (pos.x + BULLET_BOM_SIZE_X / 2) > (ScenePos.x - BOSS_RIGHT_SIZE_X / 2)
								&& (pos.y - BULLET_BOSS_BOM_SIZE_Y / 2) < (ScenePos.y + BOSS_RIGHT_SIZE_Y / 2)
								&& (pos.y + BULLET_BOSS_BOM_SIZE_Y / 2) > (ScenePos.y - BOSS_RIGHT_SIZE_Y / 2))
							{
								//スコアの加算
								pScore->AddScore(10);
								//ボスにダメージ
								pBoss->HitBoss(20);
								//終了
								Uninit();
								return;
							}
						}
						if (objType == OBJTYPE_BOSS_LEFT)
						{
							//敵と弾が当たった
							if ((pos.x - BULLET_BOSS_BOM_SIZE_X / 2) < (ScenePos.x + BOSS_LEFT_SIZE_X / 2)
								&& (pos.x + BULLET_BOM_SIZE_X / 2) > (ScenePos.x - BOSS_LEFT_SIZE_X / 2)
								&& (pos.y - BULLET_BOSS_BOM_SIZE_Y / 2) < (ScenePos.y + BOSS_LEFT_SIZE_Y / 2)
								&& (pos.y + BULLET_BOSS_BOM_SIZE_Y / 2) > (ScenePos.y - BOSS_LEFT_SIZE_Y / 2))
							{
								//スコアの加算
								pScore->AddScore(10);
								//ボスにダメージ
								pBoss->HitBoss(20);
								//終了
								Uninit();
								return;
							}
						}
						if (objType == OBJTYPE_ENEMY_BULLET)
						{
							//敵と弾が当たった
							if ((pos.x - BULLET_BOSS_BOM_SIZE_X / 2) < (ScenePos.x + ENEMY_BULLET_SIZE_X / 2)
								&& (pos.x + BULLET_BOSS_BOM_SIZE_X / 2) > (ScenePos.x - ENEMY_BULLET_SIZE_X / 2)
								&& (pos.y - BULLET_BOSS_BOM_SIZE_Y / 2) < (ScenePos.y + ENEMY_BULLET_SIZE_Y / 2)
								&& (pos.y + BULLET_BOSS_BOM_SIZE_Y / 2) > (ScenePos.y - ENEMY_BULLET_SIZE_Y / 2))
							{
								//敵の弾の終了
								pScene->Uninit();
								//終了
								Uninit();
								return;
							}
						}
					}
					break;
					//敵
				case TYPE_ENEMY:
					//テクスチャのセット
					SetTexture(0.0f, 0.0f, 1.0f,1.0f);
					//通常弾の場合
					if (m_PatternType == PATTERN_TYPE_ENEMY_NORMAL)
					{
						//オブジェクトが敵の場合
						if (objType == OBJTYPE_PLAYER)
						{
							//敵と弾が当たった
							if ((pos.x - BULLET_ENEMY_COLLISION_X / 2) < (ScenePos.x + PLAYER_COLLISION_SIZE_X / 2)
								&& (pos.x + BULLET_ENEMY_COLLISION_X / 2) > (ScenePos.x - PLAYER_COLLISION_SIZE_X / 2)
								&& (pos.y - BULLET_ENEMY_COLLISION_Y / 2) < (ScenePos.y + PLAYER_COLLISION_SIZE_X / 2)
								&& (pos.y + BULLET_ENEMY_COLLISION_Y / 2) > (ScenePos.y - PLAYER_COLLISION_SIZE_X / 2))
							{
								pPlayer->HitPlayer();
								//終了
								Uninit();
								return;
							}
						}
					}
					//狙い撃ち
					if (m_PatternType == PATTERN_TYPE_ENEMY_TRAKING)
					{
						//オブジェクトが敵の場合
						if (objType == OBJTYPE_PLAYER)
						{
							//敵と弾が当たった
							if ((pos.x - BULLET_ENEMY_COLLISION_X / 2) < (ScenePos.x + PLAYER_COLLISION_SIZE_X / 2)
								&& (pos.x + BULLET_ENEMY_COLLISION_X / 2) > (ScenePos.x - PLAYER_COLLISION_SIZE_X / 2)
								&& (pos.y - BULLET_ENEMY_COLLISION_Y / 2) < (ScenePos.y + PLAYER_COLLISION_SIZE_X / 2)
								&& (pos.y + BULLET_ENEMY_COLLISION_Y / 2) > (ScenePos.y - PLAYER_COLLISION_SIZE_X / 2))
							{
								//プレイヤーダメージ
								pPlayer->HitPlayer();
								//終了
								Uninit();
								return;
							}
						}
					}
					//波状
					if (m_PatternType == PATTERN_TYPE_ENEMY_WAVE)
					{
						//オブジェクトが敵の場合
						if (objType == OBJTYPE_PLAYER)
						{
							//敵と弾が当たった
							if ((pos.x - BULLET_ENEMY_COLLISION_X / 2) < (ScenePos.x + PLAYER_COLLISION_SIZE_X / 2)
								&& (pos.x + BULLET_ENEMY_COLLISION_X / 2) > (ScenePos.x - PLAYER_COLLISION_SIZE_X / 2)
								&& (pos.y - BULLET_ENEMY_COLLISION_Y / 2) < (ScenePos.y + PLAYER_COLLISION_SIZE_X / 2)
								&& (pos.y + BULLET_ENEMY_COLLISION_Y / 2) > (ScenePos.y - PLAYER_COLLISION_SIZE_X / 2))
							{
								//プレイヤーダメージ
								pPlayer->HitPlayer();
								//終了
								Uninit();
								return;
							}
						}
					}
					break;
					//例外の場合
				default:
					break;
					return;
				}
			}
		}
	}
	//追尾
	if (m_PatternType == PATTERN_TYPE_ENEMY_TRAKING)
	{
		m_rad = m_fAngle;
	}
	//拡散弾
	if (m_PatternType == PATTERN_TYPE_ENEMY_DIFFUSION)
	{
		m_nDifCount++;
		if (m_nDifCount >= 80)
		{
			for (int nCount = 0; nCount < 20; nCount++)
			{
				CBullet::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(180.0f)), D3DXVECTOR3(cosf(D3DXToRadian(nCount * (360 / 20)))*5.0f, sinf(D3DXToRadian(nCount * (360 / 20)))*5.0f, 0.0f), ENEMY_BULLET_SIZE_X, ENEMY_BULLET_SIZE_Y, CBullet::TYPE_ENEMY, CBullet::PATTERN_TYPE_ENEMY_NORMAL, CBullet::TEX_TYPE_ENEMY_NORMAL, OBJTYPE_ENEMY_BULLET);
			}
			//終了
			Uninit();
			return;
		}
	}

	//ビームの場合
	if (m_PatternType == PATTERN_TYPE_BEAM)
	{
		//falseの場合
		if (m_bUseBeam == false)
		{
			//終了
			Uninit();
			return;
		}
	}
	//ボムの場合
	if (m_PatternType == PATTERN_TYPE_BOSS_BOM)
	{
		//falseの場合
		if (m_bUseBom == false)
		{
			//終了
			Uninit();
			return;
		}
	}
	//プレイヤー、ランダム、ノーマルの場合
	if (m_type == TYPE_PLAYER || m_PatternType == PATTERN_TYPE_ENEMY_DIFFUSION || m_PatternType == PATTERN_TYPE_ENEMY_NORMAL)
	{
		//位置更新
		pos.x += m_move.x;
		pos.y += m_move.y;
	}
	//ランダム2
	if (m_PatternType == PATTERN_TYPE_ENEMY_TRAKING)
	{
		//位置更新
		pos.x += m_move.x * cosf(m_rad);
		pos.y += m_move.y * sinf(m_rad);
	}
	//波状
	if (m_PatternType == PATTERN_TYPE_ENEMY_WAVE)
	{
		//falseの場合
		if (m_bWavemove == false)
		{
			m_nMinMove -= 0.5f;
		}
		//
		if (m_nMinMove == -7.0f)
		{
			m_bWavemove = true;
			m_nMinMove = 0;
		}
		if (m_bWavemove == true)
		{
			m_nMinMove += 0.5f;
		}
		if (m_nMinMove == 7.0f)
		{
			m_bWavemove = false;
			m_nMinMove = 0;
		}
		//位置更新
		pos.x += m_move.x + m_nMinMove;
		pos.y += m_move.y;
	}
	//テクスチャ
	if (m_textype == TEX_TYPE_BEAM || m_textype == TEX_TYPE_NORMAL || m_type == TYPE_ENEMY)
	{
		//テクスチャの設定
		SetTexture(0.0f, 0.0f, 1.0f, 1.0f);
	}
	//ボムの場合
	if (m_PatternType == PATTERN_TYPE_BOM)
	{
		m_nBom_Anim_Count++;
		//カウントが4以上になったら
		if (m_nBom_Anim_Count > 4)
		{
			m_nBom_Anim_Count = 0;
			//パターンが4以下の場合
			if (m_nPattern_Bom_Anim <= 4)
			{
				//テクスチャ設定
				SetTexture(m_nPattern_Bom_Anim * 0.2f, 0.0, 0.2f, 0.5f);
			}
			//パターンが5以上の場合
			if (m_nPattern_Bom_Anim >= 5)
			{
				//テクスチャの設定
				SetTexture(m_nPattern_Bom_Anim * 0.2f, 0.5, 0.2f, 1.0f);

			}
			//パターンのインクリメント
			m_nPattern_Bom_Anim++;
		}
		//パターンが10以上になったら
		if (m_nPattern_Bom_Anim >= 10)
		{
			//終了処理
			Uninit();
			return;
		}
	}
	if (nPlayerState == CPlayer::STATE_DEAD)
	{
		Uninit();
		return;
	}
	//位置更新
	SetPosition(pos);
	//画面外
	if (pos.x > MAX_GAME_WIDTH || pos.x < MIN_GAME_WIDTH || pos.y > SCREEN_HEIGHT || pos.y < 0)
	{
		//終了
		Uninit();
		return;
	}
}
//---------------------------------------------------
//描画
//---------------------------------------------------
void CBullet::Draw(void)
{
	//描画
	CScene2d::Draw();
}
//---------------------------------------------------
//ビームの使用状態の取得
//---------------------------------------------------
void CBullet::SetUseBeam(bool bUseBeam)
{
	m_bUseBeam = bUseBeam;
}
//---------------------------------------------------
//ボムの使用状態の取得
//---------------------------------------------------
void CBullet::SetUseBom(bool bUseBom)
{
	m_bUseBom = bUseBom;
}