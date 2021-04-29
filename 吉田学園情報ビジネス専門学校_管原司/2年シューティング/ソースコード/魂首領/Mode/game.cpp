//******************************************************************************
// ゲーム [game.cpp]
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
#include "../Input/input.h"
#include "../Input/inputkeyboard.h"
#include "../Input/inputjoystick.h"
#include "../Player/player.h"
#include "../Bullet/bullet.h"
#include "../Polygon/bg.h"
#include "../System/sound.h"
#include "../Enemy/enemy.h"
#include "../Enemy/normal_enemy.h"
#include "../Enemy/circle_bullet_enemy.h"
#include "../System/number.h"
#include "../UI/score.h"
#include "../UI/life.h"
#include "game.h"
#include "../Polygon/fade.h"
#include "../Polygon/item.h"
#include "../UI/bomui.h"
#include "../Polygon/polygon.h"
#include "../Enemy/ship.h"
#include "../Boss/boss.h"
#include "warning.h"
#include "../Enemy/ship_battery.h"
#include "../Particle/particle.h"
#include "../Particle/particle_explosion.h"
#include "../Polygon/black_polygon.h"
#include "mode.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define PLAYER_POS					(D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2 + 200, 0.0))	// プレイヤーの位置
#define PLAYER_SIZE					(D3DXVECTOR3(50.0f,50.0f,0.0f))									// プレイヤーサイズ
#define BOSS_POS					(D3DXVECTOR3(SCREEN_WIDTH / 2, -200.0f, 0.0f))					// ボスの位置
#define BOSS_MAIN_SIZE				(D3DXVECTOR3(150.0f,150.0f,0.0f))								// ボスの中央のサイズ
#define BG_POS						(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f))		// 背景位置
#define SCORE_POS					(D3DXVECTOR3(940.0f, 50.0f, 0.0f))								// スコア位置
#define LIFE_POS					(D3DXVECTOR3(350.0f, 50.0f, 0.0f))								// ライフ位置
#define BOM_UI_POS					(D3DXVECTOR3(340.0f, 700.0f, 0.0f))								// ボムのUI位置
#define ENEMY_ROT					(D3DXVECTOR3(0.0f,0.0f,0.0f))									// 敵の向き
#define ENEMY_RESPWAN_POS_1			(D3DXVECTOR3(900.0f, -300.0f, 0.0f))							// 敵の生成位置1
#define ENEMY_RESPWAN_POS_2			(D3DXVECTOR3(540.0f, -150.0f, 0.0f))							// 敵の生成位置2
#define ENEMY_RESPAWN_POS_3			(D3DXVECTOR3(480.0f, -100.0f, 0.0f))							// 敵の生成位置3
#define ENEMY_RESPWAN_POS_4			(D3DXVECTOR3(840.0f, -100.0f, 0.0f))							// 敵の生成位置4
#define ENEMY_RESPWAN_POS_5			(D3DXVECTOR3(740.0f, -50.0f, 0.0f))								// 敵の生成位置5
#define ENEMY_RESPWAN_POS_6			(D3DXVECTOR3(600.0f, -100.0f, 0.0f))							// 敵の生成位置6
#define SHIP_RESPAWN_POS			(D3DXVECTOR3(SCREEN_WIDTH / 2, -1000.0f, 0.0f))					// 船生成位置
#define SHIP_SIZE					(D3DXVECTOR3(1000.0f,1800.0f,0.0f))								// 船のサイズ
#define BG_SIZE						(D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT,0.0f))				// 背景サイズ
#define SCORE_SIZE					(D3DXVECTOR3 (30.0f,30.0f,0.0f))								// スコアサイズ
#define LIFE_SIZE					(D3DXVECTOR3(30.0f,30.0f,0.0f))									// ライフサイズ
#define BOM_UI_SIZE					(D3DXVECTOR3(40.0f,40.0f,0.0f))									// サイズ
#define NORMAL_ENEMY_SIZE			(D3DXVECTOR3(50.0f,50.0f,0.0f))									// 通常の敵サイズ
#define CIRCLE_BULLET_ENEMY_SIZE	(D3DXVECTOR3(50.0f,50.0f,0.0f))									// サイズ
#define RESPAWN_COUNT_DEVIDE		(150)															// 敵生成カウント
#define RESPAWN_COUNT_DEVIDE2		(300)															// 敵生成カウント2
#define RESPAWN_COUNT_DEVIDE3		(400)															// 敵生成カウント3
#define RESPAWN_COUNT_DEVIDE4		(500)															// 敵生成カウント4
#define SHIP_RESPAWN				(1000)															// 船生成カウント
#define ENEMY_NO_RESPAWN_COUNT		(3300)															// 敵の生成を止めるカウント
#define NORMAL_ENEMY_LIFE			(20)															// 通常の敵のライフ
#define CIRCLE_BULLET_ENEMY_LIFE	(50)															// ライフ
#define RESPAWN_COUNT_REMAINDER		(0)																// 余り
#define INIT_SCORE					(0)																// 初期スコア
//******************************************************************************
// 静的メンバ変数
//******************************************************************************
CScore * CGame::m_pScore	= NULL;
CLife * CGame::m_pLife		= NULL;
CPlayer * CGame::m_pPlayer	= NULL;
CBomUI * CGame::m_pBom		= NULL;
CShip * CGame::m_pShip		= NULL;
CBoss * CGame::m_pBoss		= NULL;
//******************************************************************************
// コンストラクタ
//******************************************************************************
CGame::CGame()
{
	m_nCount			= INIT_INT;
	m_nRespawn_Count	= INIT_INT;
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

	// サウンド再生
	pSound->PlaySound(CSound::SOUND_LABEL_BGM000);

	// 黒ポリゴン生成
	CBlack_Polygon::Create(POLYGON_RIGHT_POS, POLYGON_SIZE, BLACK_POLYGON_COLOR,CPolygon::TEX_TYPE_MAX);
	CBlack_Polygon::Create(POLYGON_LEFT_POS, POLYGON_SIZE, BLACK_POLYGON_COLOR, CPolygon::TEX_TYPE_MAX);

	//背景
	CBg::Create(BG_POS, BG_SIZE);

	//自機
	m_pPlayer = CPlayer::Create(PLAYER_POS, PLAYER_SIZE);

	//スコア
	m_pScore = CScore::Create(SCORE_POS, SCORE_SIZE);

	// スコア設定
	m_pScore->SetScore(INIT_SCORE);

	//ライフ
	m_pLife = CLife::Create(LIFE_POS, LIFE_SIZE);

	//ボムUI
	m_pBom = CBomUI::Create(BOM_UI_POS, BOM_UI_SIZE);

	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CGame::Uninit(void)
{
	//サウンドの停止
	CSceneManager::GetSound()->StopSound();

	// フェード以外破棄
	CScene::DesignationReleaseAll(CScene::OBJTYPE_FADE);
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CGame::Update(void)
{
	// プレイヤー取得
	CPlayer * pPlayer = GetPlayer();

	// State
	int nPlayerState = INIT_INT;

	// State取得
	nPlayerState = pPlayer->GetPlayerState();

	// プレイヤーが死亡状態でない場合
	if (nPlayerState != CPlayer::STATE_DEAD)
	{
		// falseの場合
		if (m_bUseBoss == false)
		{
			// 敵生成関数
			Enemy_Respawn();
		}
	}
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CGame::Draw(void)
{
}
//******************************************************************************
// ボス生成
//******************************************************************************
void CGame::CreateBoss(void)
{
	// ボス生成
	m_pBoss = CBoss::Create(BOSS_POS, BOSS_MAIN_SIZE);
}
//******************************************************************************
// 敵生成処理関数
//******************************************************************************
void CGame::Enemy_Respawn(void)
{
	// インクリメント
	m_nRespawn_Count++;

	// 150あまり0のとき
	if (m_nRespawn_Count % RESPAWN_COUNT_DEVIDE == RESPAWN_COUNT_REMAINDER)
	{
		// 敵生成
		CNormal_Enemy::Create(ENEMY_RESPWAN_POS_1,
			ENEMY_ROT,
			NORMAL_ENEMY_SIZE,
			NORMAL_ENEMY_LIFE,
			CEnemy::TEX_TYPE_NORMAL);

		CNormal_Enemy::Create(ENEMY_RESPWAN_POS_2,
			ENEMY_ROT,
			NORMAL_ENEMY_SIZE,
			NORMAL_ENEMY_LIFE,
			CEnemy::TEX_TYPE_NORMAL);
	}
	// 300あまり0のとき
	if (m_nRespawn_Count % RESPAWN_COUNT_DEVIDE2 == RESPAWN_COUNT_REMAINDER)
	{
		// 敵生成
		CCirecle_Bullet_Enemy::Create(ENEMY_RESPAWN_POS_3,
			ENEMY_ROT,
			CIRCLE_BULLET_ENEMY_SIZE,
			CIRCLE_BULLET_ENEMY_LIFE,
			CEnemy::TEX_TYPE_BLUE,
			CCirecle_Bullet_Enemy::DROP_ITEM_BOM);
	}
	// 400あまり0のとき
	if (m_nRespawn_Count % RESPAWN_COUNT_DEVIDE3 == RESPAWN_COUNT_REMAINDER)
	{
		// 敵生成
		CNormal_Enemy::Create(ENEMY_RESPWAN_POS_4,
			ENEMY_ROT,
			NORMAL_ENEMY_SIZE,
			NORMAL_ENEMY_LIFE,
			CEnemy::TEX_TYPE_NORMAL);

		CNormal_Enemy::Create(ENEMY_RESPWAN_POS_5,
			ENEMY_ROT,
			NORMAL_ENEMY_SIZE,
			NORMAL_ENEMY_LIFE,
			CEnemy::TEX_TYPE_NORMAL);

	}
	// 500あまり0のとき
	if (m_nRespawn_Count % RESPAWN_COUNT_DEVIDE4 == RESPAWN_COUNT_REMAINDER)
	{
		// 敵生成
		CCirecle_Bullet_Enemy::Create(ENEMY_RESPWAN_POS_6,
			ENEMY_ROT,
			CIRCLE_BULLET_ENEMY_SIZE,
			CIRCLE_BULLET_ENEMY_LIFE,
			CEnemy::TEX_TYPE_RED,
			CCirecle_Bullet_Enemy::DROP_ITEM_POWERUP);
	}
	// 1500カウント
	if (m_nRespawn_Count == SHIP_RESPAWN)
	{
		// 船生成
		m_pShip = CShip::Create(SHIP_RESPAWN_POS, SHIP_SIZE);
	}
	// 3300になった場合
	if (m_nRespawn_Count == ENEMY_NO_RESPAWN_COUNT)
	{
		// trueに
		m_bUseBoss = true;
	}
}