//******************************************************************************
// 自機 [player.cpp]
// Author : 管原　司
//******************************************************************************
#define	_CRT_SECURE_NO_WARNINGS	//scanfエラー
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
#include "player.h"
#include "player_wepon.h"
#include "../Bullet/bullet.h"
#include "../Bullet/normal_bullet.h"
#include "../Beam/player_beam.h"
#include "../System/sound.h"
#include "../UI/life.h"
#include "../Mode/game.h"
#include "../UI/bomui.h"
#include "../UI/continue.h"
#include "../Bullet/bom.h"
#include "../UI/score.h"
#include "../Particle/particle.h"
#include "../Particle/particle_explosion.h"
#include "../Boss/boss.h"
#include "../Beam/beam.h"
#include "../Particle/particle_circle.h"
#include "../Beam/bom_beam.h"
#include <stdio.h>
//******************************************************************************
// マクロ定義
//******************************************************************************
#define PLAYER_TEXTURE					("data/Texture/Player/Player003.png")					// テクスチャ
#define BULLET_NORMAL_MOVE_VALUE		(D3DXVECTOR3(0.0f,15.0f,0.0f))							// 通常弾移動量
#define BEAM_BULLET_MOVE_VALUE			(D3DXVECTOR3(0.0f,15.0f,0.0f))							// ビーム移動量
#define EXPLOSION_SIZE					(D3DXVECTOR3(3.0f,3.0f,0.0f))							// 爆発サイズ
#define PLAYER_SIZE						(D3DXVECTOR3(50.0f,50.0f,0.0f))							// プレイヤーサイズ
#define PLAYER_COLLISION_SIZE			(D3DXVECTOR3(5.0f,5.0f,0.0f))							// プレイヤー判定サイズ
#define PLAYER_MOVE						(D3DXVECTOR3(8.0f,8.0f,0.0f))							// プレイヤーサイズ
#define PLAYER_BEAM_MOVE				(D3DXVECTOR3(5.0f,5.0f,0.0f))							// プレイヤービームサイズ
#define PLAYER_COLLISION_SIZE			(D3DXVECTOR3(5.0f,5.0f,0.0f))							// プレイヤー判定サイズ
#define PLAYER_DEATH_POS				(D3DXVECTOR3(-100.0f, -100.0f, 0.0f))					// 死亡時の位置
#define PLAYER_RESPAWN_POS				(D3DXVECTOR3(SCREEN_WIDTH / 2, 600.0f, 0.0f))			// リスポン位置
#define BEAM_POS						(D3DXVECTOR3(0.0f,-45.0f,0.0f))							// ビーム生成位置
#define BULLET_ROT						(D3DXVECTOR3(0.0f,0.0f,0.0f))							// 弾の向き
#define CONTINUE_POS					(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f))// コンティニュー位置
#define CONTINUE_SIZE					(D3DXVECTOR3(250.0f,250.0f,0.0f))						// サイズ
#define PLAYER_WEPON_POS				(D3DXVECTOR3(40.0f,40.0f,0.0f))							// プレイヤー武器の位置
#define PLAYER_BEAM_WEPON_POS			(D3DXVECTOR3(15.0f,40.0f,0.0f))							// プレイヤー武器の位置
#define PLAYER_WEPON_SIZE				(D3DXVECTOR3(25.0f,25.0f,0.0f))							// プレイヤー武器サイズ
#define BULLET_LEVEL1_BEAM_SIZE			(D3DXVECTOR3(40.0f,40.0f,0.0f))							//ビームのサイズ
#define BULLET_LEVEL2_BEAM_SIZE			(D3DXVECTOR3(50.0f,50.0f,0.0f))							//ビームのサイズ
#define BULLET_LEVEL3_BEAM_SIZE			(D3DXVECTOR3(60.0f,60.0f,0.0f))							//ビームのサイズ
#define BULLET_LEVEL1_SIZE				(D3DXVECTOR3(40.0f,40.0f,0.0f))							// レベル1の弾のサイズ
#define BULLET_LEVEL2_SIZE				(D3DXVECTOR3(50.0f,50.0f,0.0f))							// レベル2の弾のサイズ
#define BULLET_LEVEL3_SIZE				(D3DXVECTOR3(50.0f,50.0f,0.0f))							// レベル3の弾のサイズ
#define BOSS_BOM_SIZE					(D3DXVECTOR3(100.0f,100.0f,0.0f))						// サイズ
#define BOSS_BOM_ROT					(D3DXVECTOR3(0.0f,0.0f,0.0f))							// ボムの向き
#define BOM_POS							(D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,0.0f))	// ボムの位置
#define BOM_SIZE						(D3DXVECTOR3(800.0f,800.0f,0.0f))						// ボムのサイズ
#define BOM_ROT							(D3DXVECTOR3(0.0f,0.0f,0.0f))							// ボムの向き
#define COLOR							(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))						// カラー
#define BULLET_COLOR					(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))						// 弾の色
#define DAMAGE_COLOR					(D3DXCOLOR(1.0f,1.0f,1.0f,0.0f))						// ダメージ状態の時の色
#define GET_BOM_ADD_SCORE				(5000)													// ボム取得時の加算スコア値
#define GET_POWERUP_ADD_SCORE			(3000)													// パワーアップアイテム取得時の加算スコア値
#define CONTINUE_SUB_SCORE				(-3000)													// コンティニュー時のスコア減算値
#define JOYSTICK_DICISION				(500)													// ジョイスティック判定値
#define DAMAGE_COUNT					(300)													// ダメージカウント
#define BOM_LAUNCH_TIME					(200)													// ボムの待機時間
#define DAMAGE_RESPAWN_COUNT			(30)													// ダメージリスポンカウント
#define NODAMAGE_COUNT					(50)													// 無敵時間
#define BEAM_COUNT						(20)													// ビームカウント
#define BEAM_SHOT_COUNT					(2)														// ビームの弾生成カウント
#define INIT_BEAM_COUNT					(0)														// ビームカウント初期化
#define INIT_BOM_COUNT					(0)														// ボムのカウント初期化
#define NORMAL_ANIM_PATTERN_COUNT		(2)														// 通常時のアニメーションパターン
#define LEFT_MOVE_ANIM_PATTERN_COUNT	(0)														// 左移動中のアニメーションカウント
#define RIGHT_MOVE_ANIM_PATTERN_COUNT	(4)														// 右移動中のアニメーションカウント
#define MAX_BOM_POSSESION				(5)														// ボムの最大所持数
#define MIN_BOM_POSSESION				(0)														// ボムの最大所持数
#define HIT_DAMAGE_VALUE				(1)														// ダメージ量
#define PLAYER_LIFE						(3)														// プレイヤーライフ
#define PLAYER_CONTINUE					(1)														// プレイヤーのコンティニュー
#define DEVIDE_VALUE					(2)														// 除算値
#define REMAINDER_VALUE					(0)														// 余り値
#define INIT_PLAYER_RESPAWN_COUNT		(0)														// リスポーンカウント初期化
#define DAMAGE_COUNT_VEVIDE1			(5)														// ダメージカウントの除算値
#define DAMAGE_COUNT_VEVIDE2			(6)														// ダメージカウントの除算値
#define INIT_DAMAGE_COUNT				(0)														// ダメージカウント初期化
#define INIT_CONTINUE_COUNT				(0)														// コンティニューカウント初期化
#define MIN_LIFE_VALUE					(0)														// ライフの最小値
#define CONTINUE_BOM_POSSETION			(3)														// コンティニュー時のボムの所持数
#define SHOT_BOM						(-1)													// ボムの消費量
#define RATE_MOVE_BASE					(0.0f)													// 慣性の引かれる数字
#define RATE_MOVE						(0.4f)													// 慣性の移動量
#define TEX_1							(0.2f)													// テクスチャUV値1
#define TEX_2							(0.0f)													// テクスチャUV値2
#define TEX_3							(0.2f)													// テクスチャUV値3
#define TEX_4							(1.0f)													// テクスチャUV値4
#define CIRCLE_SIZE						(D3DXVECTOR3(30.0f,30.0f,0.0f))							// 円形パーティクルサイズ
#define CIRCLE_CREATE_NUM				(30)													// 円形パーティクル生成数
//******************************************************************************
// 静的メンバ変数
//******************************************************************************
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;
//******************************************************************************
// テクスチャ読み込み関数
//******************************************************************************
HRESULT CPlayer::Load(void)
{
	//レンダラー取得
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, PLAYER_TEXTURE, &m_pTexture);
	return S_OK;
}
//******************************************************************************
// テクスチャ破棄関数
//******************************************************************************
void CPlayer::Unload(void)
{
		// テクスチャの破棄
		if (m_pTexture != NULL)
		{
			// テクスチャのをRelease
			m_pTexture->Release();
			// テクスチャのをNULL
			m_pTexture= NULL;
		}
}
//******************************************************************************
// コンストラクタ
//******************************************************************************
CPlayer::CPlayer(int nPriority) : CScene2d(nPriority)
{
	m_pBeam					= NULL;	
	m_pBomBeam				= NULL;
	m_nContinue				= INIT_INT;
	m_nLife					= INIT_INT;
	m_nCountAnim			= INIT_INT;
	m_nPatternAnim			= INIT_INT;
	m_AttackCount			= INIT_INT;
	m_nBeamCount			= INIT_INT;
	m_nDamageCount			= INIT_INT;
	m_nRespawnCount			= INIT_INT;
	m_nBomCount				= INIT_INT;
	m_nBom_possession_count = INIT_INT;
	m_nPlayerState			= STATE_NONE;
	m_nPower					= LEVEL_NONE;
	m_bMove					= false;
	m_bUseShot				= false;
	m_bUseBeam				= false;
	m_bUseBom				= false;
	m_bBossBom				= false;
	m_bBoss					= false;
	m_bBossDeath			= false;
	m_bContinue				= false;
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CPlayer::~CPlayer()
{
}
//******************************************************************************
// 生成関数
//******************************************************************************
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CPlayerクラスのポインタ
	CPlayer * pPlayer;																			

	// メモリ確保
	pPlayer = new CPlayer;

	// pos代入
	pPlayer->SetPosition(pos);

	// サイズ代入
	pPlayer->SetSize(size);

	// カラー設定
	pPlayer->SetRGBA(COLOR);

	// テクスチャ設定
	pPlayer->BindTexture(m_pTexture);

	// オブジェクトタイプ設定
	pPlayer->SetObjType(OBJTYPE_PLAYER);

	// 初期化
	pPlayer->Init();

	// pPlayerを返す
	return pPlayer;
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CPlayer::Init(void)
{
	// プレイヤーのステートノーマル
	m_nPlayerState = STATE_NORMAL;

	// 当たり判定サイズ
	m_Collision_Size = PLAYER_COLLISION_SIZE;

	// レベル1
	m_nPower = LEVEL_1;

	// 体力
	m_nLife = PLAYER_LIFE;

	// 武器生成
	// 左
	CPlayer_Wepon::Create(D3DXVECTOR3(-PLAYER_WEPON_POS.x, PLAYER_WEPON_POS.y, PLAYER_WEPON_POS.z), PLAYER_WEPON_SIZE, CPlayer_Wepon::TYPE_LEFT);

	// 右
	CPlayer_Wepon::Create(D3DXVECTOR3(PLAYER_WEPON_POS.x, PLAYER_WEPON_POS.y, PLAYER_WEPON_POS.z), PLAYER_WEPON_SIZE, CPlayer_Wepon::TYPE_RIGHT);

	// 初期化
	CScene2d::Init();

	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CPlayer::Uninit(void)
{
	// 終了
	CScene2d::Uninit();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CPlayer::Update(void)
{
	// Stateが関係している処理
	PlayerState();
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CPlayer::Draw(void)
{
	// 描画
	CScene2d::Draw();
}
//******************************************************************************
// ヒット処理関数
//******************************************************************************
void CPlayer::HitPlayer(void)
{
	// 状態がノーマルの場合
	if (m_nPlayerState == STATE_NORMAL)
	{
		// 位置座標取得
		D3DXVECTOR3 pos = GetPosition();

		// サウンド取得
		CSound * pSound = CSceneManager::GetSound();
		CSound::SOUND_LABEL type;
		type = CSound::SOUND_LABEL_SE_SHOT;

		// 爆発音生成
		pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);

		// ライフの取得
		CLife * pLife = CGame::GetLife();

		// ライフ減算
		m_nLife--;

		// ライフUIの減算
		pLife->HitDamage(HIT_DAMAGE_VALUE);

		// 爆発の生成
		CParticle_Explosion::CreateExplosionEffect(pos, EXPLOSION_SIZE, CParticle_Explosion::TYPE_PLAYER);

		// パーティクル生成
		CParticle_Circle::PlayerDeathEffect(pos, CIRCLE_SIZE, CIRCLE_CREATE_NUM);

		// ダメージを受けた場合画面外に
		SetPosition(PLAYER_DEATH_POS);

		// StateをRespawnに
		m_nPlayerState = STATE_RESPAWN;
	}
}
//******************************************************************************
// ボム入手処理関数
//******************************************************************************
void CPlayer::GetBom(int nBom)
{
	// ボム取得
	CBomUI * pBom = CGame::GetBomUI();
	// スコア取得
	CScore * pScore = CGame::GetScore();

	// ボムの所持数の加算減算
	if (m_nBom_possession_count >= MIN_BOM_POSSESION && m_nBom_possession_count <= MAX_BOM_POSSESION)
	{
		// ボムの所持数加算
		m_nBom_possession_count += nBom;

		// ボムの所持数設定
		pBom->SetBomUI(m_nBom_possession_count);

	}
	// ボムの数が5より多くなった場合
	if (m_nBom_possession_count > MAX_BOM_POSSESION)
	{
		// ボムの数を5に設定
		m_nBom_possession_count = MAX_BOM_POSSESION;

		// ボムの所持数設定
		pBom->SetBomUI(m_nBom_possession_count);
	}

	// ボムの所持数がMAXの場合
	if (m_nBom_possession_count >= MAX_BOM_POSSESION)
	{
		// スコア加算
		pScore->AddScore(GET_BOM_ADD_SCORE);
	}
}
//******************************************************************************
// パワーアップ処理関数
//******************************************************************************
void CPlayer::GetPowerUp(void)
{
	CScore * pScore = CGame::GetScore();
	// レベルが3より低い場合
	if (m_nPower < LEVEL_3)
	{
		// レベルアップ
		m_nPower++;
	}
	// レベルが3の場合
	if (m_nPower == LEVEL_3)
	{
		// スコア加算
		pScore->AddScore(GET_POWERUP_ADD_SCORE);
	}
}
//******************************************************************************
// コンティニュー処理関数
//******************************************************************************
void CPlayer::SetContinue(int Continue)
{
	// 代入
	m_nContinue = Continue;
}
//******************************************************************************
// プレイヤー情報書き込み関数
//******************************************************************************
void CPlayer::SavePlayer(void)
{
	// ファイル
	FILE * pFile;

	// ファイルの書き出し
	pFile = fopen("player.txt", "w");

	// ファイルが空じゃないか
	if (pFile != NULL)
	{
		// スコア書き込み
		fprintf(pFile, "%d\n", m_nScore);

		// ファイルを閉じる
		fclose(pFile);
	}
}
//******************************************************************************
// ボス専用ボム処理関数
//******************************************************************************
void CPlayer::SetBossBom(bool bBoss)
{
	m_bBoss = bBoss;
}
//******************************************************************************
// 移動処理関数
//******************************************************************************
void CPlayer::Move(void)
{
	// 位置座標取得
	D3DXVECTOR3 pos = GetPosition();

	// 移動
	D3DXVECTOR3 move = INIT_D3DXVECTOR3;

	// キーボード取得
	CInputKeyboard * pInputKeyboard = CSceneManager::GetInputKeyboard();

	// コントローラー取得
	DIJOYSTATE js;
	CInputJoystick * pInputJoystick = CSceneManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 g_lpDIDevice = CInputJoystick::GetDevice();

	if (g_lpDIDevice != NULL)
	{
		g_lpDIDevice->Poll();
		g_lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}
	//左右移動してない時
	if (m_bMove == false)
	{
		//アニメーションパターンを2にする
		m_nPatternAnim = NORMAL_ANIM_PATTERN_COUNT;
	}
	// 上
	if (g_lpDIDevice != NULL &&js.lY <= -JOYSTICK_DICISION || pInputKeyboard->GetKeyboardPress(DIK_W))
	{
		//falseに
		m_bMove = false;

		// ビームを発射してる時
		if (m_bUseBeam == true)
		{
			// 移動
			move.y = -PLAYER_BEAM_MOVE.y;
		}
		// ビームを発射してない時
		else
		{
			// 移動
			move.y = -PLAYER_MOVE.y;
		}
	}
	// 下
	if (g_lpDIDevice != NULL &&js.lY >= JOYSTICK_DICISION || pInputKeyboard->GetKeyboardPress(DIK_S))
	{
		// falseに
		m_bMove = false;

		// ビームを発射してる時
		if (m_bUseBeam == true)
		{
			// 移動
			move.y = PLAYER_BEAM_MOVE.y;
		}
		// ビームを発射してない時
		else
		{
			// 移動
			move.y = PLAYER_MOVE.y;
		}
	}
	// 左
	if (g_lpDIDevice != NULL &&js.lX <= -JOYSTICK_DICISION || pInputKeyboard->GetKeyboardPress(DIK_A))
	{
		// trueに
		m_bMove = true;

		// ビームを発射している場合
		if (m_bUseBeam == true)
		{
			// 移動
			move.x = -PLAYER_BEAM_MOVE.x;
		}
		// ビームを発射してない場合
		else
		{
			// 移動
			move.x = -PLAYER_MOVE.x;
		}

		// アニメーションを0に
		m_nPatternAnim = LEFT_MOVE_ANIM_PATTERN_COUNT;
	}
	// 左に移動してない時
	else
	{
		m_bMove = false;
	}
	//右
	if (g_lpDIDevice != NULL &&js.lX >= JOYSTICK_DICISION || pInputKeyboard->GetKeyboardPress(DIK_D))
	{
		// m_bMoveをtrueに
		m_bMove = true;

		// ビームを発射している場合
		if (m_bUseBeam == true)
		{
			move.x = PLAYER_BEAM_MOVE.x;
		}
		// ビームを発射していない場合
		else
		{
			move.x = PLAYER_MOVE.x;
		}

		// アニメーション
		m_nPatternAnim = RIGHT_MOVE_ANIM_PATTERN_COUNT;
	}
	// 右に移動してない時
	else
	{
		m_bMove = false;
	}

	// 位置更新
	pos.x += move.x;
	pos.y += move.y;

	// 慣性
	move.x += (RATE_MOVE_BASE - move.x) * RATE_MOVE;
	move.y += (RATE_MOVE_BASE - move.y) * RATE_MOVE;

	// stateがNormalまたはDamageの時
	if (m_nPlayerState == STATE_NORMAL || m_nPlayerState == STATE_DAMAGE)
	{
		// 上画面外に出たとき
		if (pos.y - PLAYER_SIZE.y < WINDOW_POS_Y)
		{
			// プレイヤーのサイズ分ずらす
			pos.y = PLAYER_SIZE.y;
		}
		// もしプレイヤーが下画面外に行ったら
		if (pos.y + PLAYER_SIZE.y > SCREEN_HEIGHT)
		{
			// プレイヤーのサイズ分ずらす
			pos.y = SCREEN_HEIGHT - PLAYER_SIZE.y;
		}
		// もしプレイヤーが左画面外に行ったら
		if (pos.x - PLAYER_SIZE.x - PLAYER_WEPON_SIZE.x / DEVIDE_VALUE < MIN_GAME_WIDTH)
		{
			// プレイヤーと武器のサイズ分ずらす
			pos.x = MIN_GAME_WIDTH + PLAYER_SIZE.x + PLAYER_WEPON_SIZE.x / DEVIDE_VALUE;
		}
		// もしプレイヤーが右画面外に行ったら
		if (pos.x + PLAYER_SIZE.x + PLAYER_WEPON_SIZE.x / DEVIDE_VALUE > MAX_GAME_WIDTH)
		{
			// プレイヤーと武器のサイズ分ずらす
			pos.x = MAX_GAME_WIDTH - PLAYER_SIZE.x - PLAYER_WEPON_SIZE.x / DEVIDE_VALUE;
		}
	}
	// 位置設定
	SetPosition(pos);
}
//******************************************************************************
// 弾発射処理関数
//******************************************************************************
void CPlayer::Shot(void)
{
	// 位置座標取得
	D3DXVECTOR3 pos = GetPosition();

	// キーボード取得
	CInputKeyboard * pInputKeyboard = CSceneManager::GetInputKeyboard();

	// コントローラー取得
	CInputJoystick * pInputJoystick = CSceneManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 g_lpDIDevice = CInputJoystick::GetDevice();

	// サウンド取得
	CSound * pSound = CSceneManager::GetSound();
	CSound::SOUND_LABEL type;
	type = CSound::SOUND_LABEL_SE_SHOT;


	//*****************************************************************
	// ノーマル弾の処理
	//*****************************************************************
	// ボムを使用してない場合
	if (m_bUseBom == false)
	{
		// ビームを使用してない場合
		if (m_bUseBeam == false)
		{
			// ビーム
			// SPACEまたはコントローラーAボタン
			if (g_lpDIDevice != NULL &&pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_A) || pInputKeyboard->GetKeyboardTrigger(DIK_SPACE))
			{
				// ショットを使用状態に
				m_bUseShot = true;

				// ショット音
				pSound->PlaySound(CSound::SOUND_LABEL_SE_SHOT);

				// プレイヤーレベルが1の場合
				if (m_nPower == LEVEL_1)
				{
					// 弾の生成
					CNormal_Bullet::Create(D3DXVECTOR3(pos),
						BULLET_ROT,
						BULLET_LEVEL1_SIZE,
						D3DXVECTOR3(BULLET_NORMAL_MOVE_VALUE.x, -BULLET_NORMAL_MOVE_VALUE.y, BULLET_NORMAL_MOVE_VALUE.z),
						BULLET_COLOR
						, CBullet::TEX_TYPE_NORMAL);
				}
				// プレイヤーレベルが2の場合
				if (m_nPower == LEVEL_2)
				{
					// 弾の生成
					CNormal_Bullet::Create(D3DXVECTOR3(pos),
						BULLET_ROT,
						BULLET_LEVEL2_SIZE,
						D3DXVECTOR3(BULLET_NORMAL_MOVE_VALUE.x, -BULLET_NORMAL_MOVE_VALUE.y, BULLET_NORMAL_MOVE_VALUE.z),
						BULLET_COLOR,
						CBullet::TEX_TYPE_NORMAL);
				}
				// プレイヤーレベルが3の場合
				if (m_nPower == LEVEL_3)
				{
					// 弾の生成
					CNormal_Bullet::Create(D3DXVECTOR3(pos),
						BULLET_ROT,
						BULLET_LEVEL3_SIZE,
						D3DXVECTOR3(BULLET_NORMAL_MOVE_VALUE.x, -BULLET_NORMAL_MOVE_VALUE.y, BULLET_NORMAL_MOVE_VALUE.z),
						BULLET_COLOR,
						CBullet::TEX_TYPE_NORMAL);
				}

			}
			// コントローラーAボタンまたはキーボードSPACEを離した場合
			if (g_lpDIDevice != NULL &&pInputJoystick->GetJoystickRelease(CInputJoystick::JS_A) || pInputKeyboard->GetKeyboardRelease(DIK_SPACE))
			{
				// 通常弾の不使用状態に
				m_bUseShot = false;
			}
		}

		//*****************************************************************
		// ビーム発射の処理
		//*****************************************************************

		//ビーム
		//SPACE長押しまたはコントローラーAボタン
		if (g_lpDIDevice != NULL &&pInputJoystick->GetJoystickPress(CInputJoystick::JS_A) || pInputKeyboard->GetKeyboardPress(DIK_SPACE))
		{
			// falseの場合
			if (m_bUseBeam == false)
			{
				//ビームカウントインクリメント
				m_nBeamCount++;
				//カウントが20以上の時
				if (m_nBeamCount == BEAM_COUNT)
				{
					// ビーム音
					pSound->PlaySound(CSound::SOUND_LABEL_SE_BEAM);

					//ビームのboolをtrueに
					m_bUseBeam = true;
				}
			}
		}
		// ビームのboolがtrueの時
		if (m_bUseBeam == true)
		{
			// NULLの場合
			if (m_pBeam == NULL)
			{
				// レベル1の場合
				if (m_nPower == LEVEL_1)
				{
					// ビーム生成
					m_pBeam = CPlayer_Beam::Create(D3DXVECTOR3(pos.x, pos.y + BEAM_POS.y, pos.z),
						BULLET_LEVEL1_BEAM_SIZE);
				}
				// レベル2の場合
				if (m_nPower == LEVEL_2)
				{
					// ビーム生成
					m_pBeam = CPlayer_Beam::Create(D3DXVECTOR3(pos.x, pos.y + BEAM_POS.y, pos.z),
						BULLET_LEVEL2_BEAM_SIZE);
				}
				// レベル3の場合
				if (m_nPower == LEVEL_3)
				{
					// ビーム生成
					m_pBeam = CPlayer_Beam::Create(D3DXVECTOR3(pos.x, pos.y + BEAM_POS.y, pos.z),
						BULLET_LEVEL3_BEAM_SIZE);
				}
			}
		}
		// SPACEまたはコントローラAボタンを離したとき
		if (g_lpDIDevice != NULL &&pInputJoystick->GetJoystickRelease(CInputJoystick::JS_A) || pInputKeyboard->GetKeyboardRelease(DIK_SPACE))
		{
			// trueの場合
			if (m_bUseBeam == true)
			{
				// NULLの場合
				if (m_pBeam != NULL)
				{
					// ビーム破棄
					m_pBeam->ReleaseAllBeam();

					// NULLに
					m_pBeam = NULL;
				}

				// カウントを0に
				m_nBeamCount = INIT_BEAM_COUNT;

				// ビーム音停止
				pSound->StopSound(CSound::SOUND_LABEL_SE_BEAM);

				// ビームboolをfalseに
				m_bUseBeam = false;
			}
		}
		// キーボードのBまたはコントローラのBボタンを押した場合
		if (g_lpDIDevice != NULL &&pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_B) || pInputKeyboard->GetKeyboardTrigger(DIK_B))
		{
			// ボム所持数が0より多い場合
			if (m_nBom_possession_count > MIN_BOM_POSSESION)
			{
				// ボムboolをtrueに
				m_bUseBom = true;

				// ボムの所持数減算
				GetBom(SHOT_BOM);
			}
		}
	}
	// ボムが使用中の場合
	if (m_bUseBom == true)
	{
		// ボス戦でない時
		if (m_bBoss == false)
		{
			// 爆発音生成
			pSound->PlaySound(CSound::SOUND_LABEL_SE_BOM);

			// ボム生成
			CBom::Create(BOM_POS, BOM_ROT, BOM_SIZE, CBullet::TEX_TYPE_BOM);

			// falseに
			m_bUseBom = false;
		}
		// ボス戦の時
		else
		{
			// NULLの場合
			if (m_pBeam != NULL)
			{
				// ビーム破棄
				m_pBeam->ReleaseAllBeam();

				// NULLに
				m_pBeam = NULL;
			}
			// falseの場合
			if (m_bBossBom == false)
			{
				// NULLでない場合
				if (m_pBomBeam == NULL)
				{
					// 弾の生成
					m_pBomBeam = CBom_Beam::Create(D3DXVECTOR3(pos.x, pos.y + BEAM_POS.y, pos.z), BOSS_BOM_SIZE);
				}
				// ボス専用のボムを使用状態に
				m_bBossBom = true;
			}
			// trueの場合
			if (m_bBossBom == true)
			{
				// ボムのカウントをインクリメント
				m_nBomCount++;

				// カウントが200以上になったら
				if (m_nBomCount >= BOM_LAUNCH_TIME)
				{
					// ボムの使用状態をfalseに
					m_bUseBom = false;

					// falseに
					m_bBossBom = false;

					// ボムのカウントが0に
					m_nBomCount = INIT_BOM_COUNT;

					// NULLでない場合
					if (m_pBomBeam != NULL)
					{
						// ビーム破棄
						m_pBomBeam->ReleaseAllBeam();

						// NULLに
						m_pBomBeam = NULL;
					}
				}
			}
		}
	}
}

//******************************************************************************
// プレイヤーの状態処理関数
//******************************************************************************
void CPlayer::PlayerState(void)
{
	//死亡状態でない時
	if (m_nPlayerState != STATE_DEAD)
	{
		// 更新
		CScene2d::Update();

		//自機の中心
		D3DXVECTOR3 pos = GetPosition();

		//テクスチャ更新
		SetTexture(m_nPatternAnim * TEX_1, TEX_2, TEX_3, TEX_4);
	
		//スコア取得
		CScore * pScore = CGame::GetScore();
		m_nScore = pScore->GetScore();

		// プレイヤーの情報を外部ファイルに書き込み
		SavePlayer();

		// 移動処理
		Move();

		// 弾発射処理
		Shot();

		//通常状態
		if (m_nPlayerState == STATE_NORMAL)
		{
			//カラー設定
			SetRGBA(COLOR);
		}
		//リスポーン状態
		if (m_nPlayerState == STATE_RESPAWN)
		{
			//カウントインクリメント
			m_nRespawnCount++;

			//カウントが30になったとき
			if (m_nRespawnCount == DAMAGE_RESPAWN_COUNT)
			{
				// ダメージ状態に
				m_nPlayerState = STATE_DAMAGE;

				// リスポン位置設定
				SetPosition(PLAYER_RESPAWN_POS);

				// カウントを0に
				m_nRespawnCount = INIT_PLAYER_RESPAWN_COUNT;
			}
		}
		// ダメージ状態
		if (m_nPlayerState == STATE_DAMAGE)
		{
			// カウントインクリメント
			m_nDamageCount++;
			// ダメージのカウントが5あまり0になったら
			if (m_nDamageCount % DAMAGE_COUNT_VEVIDE1 == REMAINDER_VALUE)
			{
				// カラー設定
				SetRGBA(COLOR);
			}
			// ダメージのカウントが6あまり0になったら
			if (m_nDamageCount % DAMAGE_COUNT_VEVIDE2 == REMAINDER_VALUE)
			{
				// カラー設定
				SetRGBA(DAMAGE_COLOR);

			}
			// 無敵時間が終了したら
			if (m_nDamageCount == DAMAGE_COUNT)
			{
				// カラー設定
				SetRGBA(COLOR);

				// stateをNormalに
				m_nPlayerState = STATE_NORMAL;

				// カウントを0に
				m_nDamageCount = INIT_DAMAGE_COUNT;
			}
		}
		// コンティニュー状態がfalseの時
		if (m_bContinue == false)
		{
			// ライフが0以下の時
			if (m_nLife <= MIN_LIFE_VALUE)
			{
				// コンティニュー状態をtrueに
				m_bContinue = true;
			}
		}
		// コンティニュー状態をtrueに
		if (m_bContinue == true)
		{
			// コンティニュー生成 
			CContinue::Create(CONTINUE_POS, CONTINUE_SIZE);

			// 死亡状態に
			m_nPlayerState = STATE_DEAD;
		}
		// ボスがいる場合
		if (m_bBoss == true)
		{
			// プレイヤーの取得
			CBoss * pBoss = CGame::GetBoss();

			// NULLチェック
			if (pBoss != NULL)
			{
				// 状態取得
				int BossState = pBoss->GetState();

				// ボスが死亡状態の場合
				if (BossState == CBoss::STATE_DEATH_EFFECT || BossState == CBoss::STATE_DEATH)
				{
					// trueに
					m_bBossDeath = true;
				}
			}
		}
	}
	// 死亡状態の場合
	if (m_nPlayerState == STATE_DEAD)
	{
		// 画面外に移動させる
		SetPosition(PLAYER_DEATH_POS);

		// コンティニューした場合
		if (m_nContinue == PLAYER_CONTINUE)
		{
			// スコア取得
			CScore * pScore = CGame::GetScore();

			// スコア加算
			pScore->AddScore(CONTINUE_SUB_SCORE);

			// ライフの取得
			CLife * pLife = CGame::GetLife();

			// ライフを3に
			m_nLife = PLAYER_LIFE;

			// ライフを設定
			pLife->AddLife(m_nLife);

			// ボムの所持数を3に
			GetBom(CONTINUE_BOM_POSSETION);

			// コンティニュー状態をfalseに
			m_bContinue = false;

			// コンティニューのカウントを0に
			m_nContinue = INIT_CONTINUE_COUNT;

			// リスポーン状態に
			m_nPlayerState = STATE_RESPAWN;
		}
	}
}