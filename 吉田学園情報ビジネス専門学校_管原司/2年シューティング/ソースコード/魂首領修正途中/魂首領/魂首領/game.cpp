//******************************************************************************
// ゲーム [game.cpp]
// Author : 管原 司
//******************************************************************************

//******************************************************************************
// ファイルインクルード
//******************************************************************************
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
#include "bg.h"
#include "explosion.h"
#include "sound.h"
#include "enemy.h"
#include "normal_enemy.h"
#include "circle_bullet_enemy.h"
#include "number.h"
#include "score.h"
#include "life.h"
#include "game.h"
#include "fade.h"
#include "item.h"
#include "bomui.h"
#include "polygon.h"
#include "ship.h"
#include "boss.h"
#include "warning.h"
#include "ship_battery.h"
//******************************************************************************
// 静的メンバ変数
//******************************************************************************
CScore * CGame::m_pScore = NULL;
CLife * CGame::m_pLife = NULL;
CPlayer * CGame::m_pPlayer = NULL;
CBomUI * CGame::m_pBom = NULL;
CShip * CGame::m_pShip = NULL;
CBoss * CGame::m_pBoss = NULL;
//******************************************************************************
// 生成関数
//******************************************************************************
CGame * CGame::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CGameクラスのポインタ
	CGame * pGame;

	// メモリ確保
	pGame = new CGame;

	// 位置座標代入
	pGame->m_pos = pos;

	// サイズ代入
	pGame->m_size = size;

	// 初期化
	pGame->Init();

	// ポインタを返す
	return pGame;
 }
//******************************************************************************
// コンストラクタ
//******************************************************************************
CGame::CGame(int nPriority) : CScene(nPriority)
{
	m_pos				= D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_size				= D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_nCount			= 0;
	m_nRespawn_Count	= 0;
	m_bfade				= false;
	m_bUseBoss			= false;
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CGame::~CGame()
{
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CGame::Init(void)
{
	//サウンド取得
	CSound * pSound = CSceneManager::GetSound();
	CSound::SOUND_LABEL type;
	type = CSound::SOUND_LABEL_SE_SHOT;
	//pSound->PlaySound(CSound::SOUND_LABEL_BGM000);
	CPolygon::Create(POLYGON_RIGHT_POS, POLYGON_SIZE);
	CPolygon::Create(POLYGON_LEFT_POS, POLYGON_SIZE);
	//背景
	CBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), BG_SIZE);
	//ボス
	m_pBoss = CBoss::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, -200.0f, 0.0f), BOSS_MAIN_SIZE);
	//自機
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(640.0f, 800, 0.0f), PLAYER_SIZE);
	//スコア
	m_pScore = CScore::Create(D3DXVECTOR3(940.0f, 50.0f, 0.0f), SCORE_SIZE);
	m_pScore->SetScore(0);
	//ライフ
	m_pLife = CLife::Create(D3DXVECTOR3(350.0f, 50.0f, 0.0f), LIFE_SIZE);
	//ボムUI
	m_pBom = CBomUI::Create(D3DXVECTOR3(340.0f, 700.0f, 0.0f), BOM_UI_SIZE);

	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CGame::Uninit(void)
{
	//終了
	Release();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CGame::Update(void)
{
	//プレイヤー取得
	CPlayer * pPlayer = GetPlayer();
	//State
	int nPlayerState = 0;
	//State取得
	nPlayerState = pPlayer->GetPlayerState();

	// プレイヤーが死亡状態でない場合
	if (nPlayerState != CPlayer::STATE_DEAD)
	{
		// falseの場合
		if (m_bUseBoss == false)
		{
			// インクリメント
			m_nRespawn_Count++;

			// 150あまり0のとき
			if (m_nRespawn_Count % 150 == 0)
			{
				// 敵生成
				CNormal_Enemy::Create(D3DXVECTOR3(900.0f, -300.0f, 0.0f),
					D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(0.0f)),
					NORMAL_ENEMY_SIZE,
					NORMAL_ENEMY_LIFE,
					CEnemy::TEX_TYPE_NORMAL);

				CNormal_Enemy::Create(D3DXVECTOR3(540.0f, -150.0f, 0.0f),
					D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(0.0f)),
					NORMAL_ENEMY_SIZE,
					NORMAL_ENEMY_LIFE,
					CEnemy::TEX_TYPE_NORMAL);

				CNormal_Enemy::Create(D3DXVECTOR3(440.0f, -200.0f, 0.0f),
					D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(0.0f)),
					NORMAL_ENEMY_SIZE,
					NORMAL_ENEMY_LIFE,
					CEnemy::TEX_TYPE_NORMAL);
			}
			// 400あまり0のとき
			if (m_nRespawn_Count % 400 == 0)
			{
				CNormal_Enemy::Create(D3DXVECTOR3(840.0f, -100.0f, 0.0f),
					D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(0.0f)),
					NORMAL_ENEMY_SIZE,
					NORMAL_ENEMY_LIFE,
					CEnemy::TEX_TYPE_NORMAL);

				CNormal_Enemy::Create(D3DXVECTOR3(740.0f, -50.0f, 0.0f),
					D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(0.0f)),
					NORMAL_ENEMY_SIZE,
					NORMAL_ENEMY_LIFE,
					CEnemy::TEX_TYPE_NORMAL);

				CNormal_Enemy::Create(D3DXVECTOR3(640.0f, -100.0f, 0.0f),
					D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(0.0f)),
					NORMAL_ENEMY_SIZE,
					NORMAL_ENEMY_LIFE,
					CEnemy::TEX_TYPE_NORMAL);

			}
			// 300あまり0のとき
			if (m_nRespawn_Count % 300 == 0)
			{
				// 敵生成
				CCirecle_Bullet_Enemy::Create(D3DXVECTOR3(480.0f, -100.0f, 0.0f),
					D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(0.0f)),
					CIRCLE_BULLET_ENEMY_SIZE,
					CIRCLE_BULLET_ENEMY_LIFE,
					CEnemy::TEX_TYPE_BLUE,
					CCirecle_Bullet_Enemy::DROP_ITEM_BOM);
			}
			// 500あまり0のとき
			if (m_nRespawn_Count % 500 == 0)
			{
				// 敵生成
				CCirecle_Bullet_Enemy::Create(D3DXVECTOR3(600.0f, -100.0f, 0.0f),
					D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(0.0f)),
					CIRCLE_BULLET_ENEMY_SIZE,
					CIRCLE_BULLET_ENEMY_LIFE,
					CEnemy::TEX_TYPE_RED,
					CCirecle_Bullet_Enemy::DROP_ITEM_POWERUP);
			}
			// 1500カウント
			if (m_nRespawn_Count == 1500)
			{
				// 船生成
				m_pShip = CShip::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, -1000.0f, 0.0f), SHIP_SIZE);
			}
			//カウントが
			if (m_nRespawn_Count == 3300)
			{
				m_bUseBoss = true;
			}
		}
	}
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CGame::Draw(void)
{
}