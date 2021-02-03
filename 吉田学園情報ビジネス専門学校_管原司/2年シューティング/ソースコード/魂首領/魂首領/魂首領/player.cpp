//******************************************************************************
// 自機 [player.cpp]
// Author : 管原　司
//******************************************************************************
#define	_CRT_SECURE_NO_WARNINGS	//scanfエラー
//******************************************************************************
// インクルードファイル
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
#include "player_wepon.h"
#include "bullet.h"
#include "normal_bullet.h"
#include "player_beam.h"
#include "sound.h"
#include "life.h"
#include "game.h"
#include "bomui.h"
#include "continue.h"
#include "bom.h"
#include "score.h"
#include "boss_bom.h"
#include "particle.h"
#include "particle_explosion.h"
#include <stdio.h>
//******************************************************************************
// マクロ定義
//******************************************************************************
#define BULLET_NORMAL_MOVE_VALUE	(D3DXVECTOR3(0.0f,15.0f,0.0f))		// 通常弾移動量
#define BEAM_BULLET_MOVE_VALUE		(D3DXVECTOR3(0.0f,15.0f,0.0f))		// ビーム移動量
#define INIT_VARIABLE				(0)									// 変数0初期化
#define COLOR						(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))	// カラー
#define JOYSTICK_DICISION			(500)								// ジョイスティック判定値
#define EXPLOSION_SIZE				(D3DXVECTOR3(3.0f,3.0f,0.0f))		// 爆発サイズ
#define PLAYER_SIZE					(D3DXVECTOR3(50.0f,50.0f,0.0f))	// プレイヤーサイズ
#define PLAYER_COLLISION_SIZE		(D3DXVECTOR3(5.0f,5.0f,0.0f))	// プレイヤー判定サイズ
#define PLAYER_MOVE					(D3DXVECTOR3(8.0f,8.0f,0.0f))	// プレイヤーサイズ
#define PLAYER_BEAM_MOVE			(D3DXVECTOR3(5.0f,5.0f,0.0f))	// プレイヤービームサイズ
#define PLAYER_COLLISION_SIZE		(D3DXVECTOR3(5.0f,5.0f,0.0f))	// プレイヤー判定サイズ
#define RATE_MOVE					(0.4f)							// 慣性の移動量
#define DAMAGE_RESPAWN_COUNT		(30)							// ダメージリスポンカウント
#define NODAMAGE_COUNT				(50)							// 無敵時間
#define DAMAGE_COUNT				(300)							// ダメージカウント
#define BOM_LAUNCH_TIME				(200)							// ボムの待機時間
#define MAX_BOM_POSSESION			(5)								// ボムの最大所持数
#define PLAYER_LIFE					(3)								// プレイヤーライフ
#define PLAYER_CONTINUE				(1)								// プレイヤーのコンティニュー
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
	D3DXCreateTextureFromFile(pDevice, "data/Texture/Player/Player003.png", &m_pTexture);
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
	m_nContinue				= INIT_VARIABLE;
	m_nLife					= INIT_VARIABLE;
	m_nCountAnim			= INIT_VARIABLE;
	m_nPatternAnim			= INIT_VARIABLE;
	m_AttackCount			= INIT_VARIABLE;
	m_nBeamCount			= INIT_VARIABLE;
	m_nDamageCount			= INIT_VARIABLE;
	m_nRespawnCount			= INIT_VARIABLE;
	m_nBomCount				= INIT_VARIABLE;
	m_nBom_possession_count = INIT_VARIABLE;
	m_nPlayerState			= STATE_NONE;
	m_Level					= LEVEL_NONE;
	m_bMove					= false;
	m_bUseShot				= false;
	m_bUseBeam				= false;
	m_bUseBom				= false;
	m_bBossBom				= false;
	m_bBoss					= false;
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
	m_Level = LEVEL_1;

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
		pLife->HitDamage(1);

		// 爆発の生成
		CParticle_Explosion::CreateExplosionEffect(pos, EXPLOSION_SIZE, CParticle_Explosion::TYPE_PLAYER);

		// 位置座標設定
		SetPosition(D3DXVECTOR3(-100.0f, -100.0f, 0.0f));

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
	if (m_nBom_possession_count >= 0 && m_nBom_possession_count <= MAX_BOM_POSSESION)
	{
		m_nBom_possession_count += nBom;
		pBom->SetBomUI(m_nBom_possession_count);
	}

	// ボムの所持数がMAXの場合
	if (m_nBom_possession_count >= MAX_BOM_POSSESION)
	{
		// スコア加算
		pScore->AddScore(5000);
	}
}
//******************************************************************************
// パワーアップ処理関数
//******************************************************************************
void CPlayer::GetPowerUp(void)
{
	CScore * pScore = CGame::GetScore();
	// レベルが3より低い場合
	if (m_Level < LEVEL_3)
	{
		// レベルアップ
		m_Level++;
	}
	// レベルが3の場合
	if (m_Level == LEVEL_3)
	{
		// スコア加算
		pScore->AddScore(3000);
	}
}
//******************************************************************************
// コンティニュー処理関数
//******************************************************************************
void CPlayer::SetContinue(int Continue)
{
	m_nContinue = Continue;
}
//******************************************************************************
// プレイヤー情報書き込み関数
//******************************************************************************
void CPlayer::SavePlayer(void)
{
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
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f,0.0f,0.0f);

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
		m_nPatternAnim = 2;
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
		m_nPatternAnim = 0;
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
		m_nPatternAnim = 4;
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
	move.x += (0.0f - move.x) * RATE_MOVE;
	move.y += (0.0f - move.y) * RATE_MOVE;

	// stateがNormalまたはDamageの時
	if (m_nPlayerState == STATE_NORMAL || m_nPlayerState == STATE_DAMAGE)
	{
		// 上画面外に出たとき
		if (pos.y - PLAYER_SIZE.y < 0)
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
		if (pos.x - PLAYER_SIZE.x - PLAYER_WEPON_SIZE.x / 2 < MIN_GAME_WIDTH)
		{
			// プレイヤーと武器のサイズ分ずらす
			pos.x = MIN_GAME_WIDTH + PLAYER_SIZE.x + PLAYER_WEPON_SIZE.x / 2;
		}
		// もしプレイヤーが右画面外に行ったら
		if (pos.x + PLAYER_SIZE.x + PLAYER_WEPON_SIZE.x / 2 > MAX_GAME_WIDTH)
		{
			// プレイヤーと武器のサイズ分ずらす
			pos.x = MAX_GAME_WIDTH - PLAYER_SIZE.x - PLAYER_WEPON_SIZE.x / 2;
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
			if (g_lpDIDevice != NULL &&pInputJoystick->GetJoystickTrigger(JS_A) || pInputKeyboard->GetKeyboardTrigger(DIK_SPACE))
			{
				// ショットを使用状態に
				m_bUseShot = true;
				// ショット音
				pSound->PlaySound(CSound::SOUND_LABEL_SE_SHOT);

				// プレイヤーレベルが1の場合
				if (m_Level == LEVEL_1)
				{
					// 弾の生成
					CNormal_Bullet::Create(D3DXVECTOR3(pos),
						D3DXVECTOR3(0.0f, 0.0f, 0.0f), 
						BULLET_LEVEL1_SIZE, 
						D3DXVECTOR3(BULLET_NORMAL_MOVE_VALUE.x, -BULLET_NORMAL_MOVE_VALUE.y, BULLET_NORMAL_MOVE_VALUE.z),
						D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
						, CBullet::TEX_TYPE_NORMAL);
				}
				// プレイヤーレベルが2の場合
				if (m_Level == LEVEL_2)
				{
					// 弾の生成
					CNormal_Bullet::Create(D3DXVECTOR3(pos),
						D3DXVECTOR3(0.0f, 0.0f, 0.0f),
						BULLET_LEVEL2_SIZE, 
						D3DXVECTOR3(BULLET_NORMAL_MOVE_VALUE.x, -BULLET_NORMAL_MOVE_VALUE.y, BULLET_NORMAL_MOVE_VALUE.z),
						D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
						CBullet::TEX_TYPE_NORMAL);
				}
				// プレイヤーレベルが3の場合
				if (m_Level == LEVEL_3)
				{
					// 弾の生成
					CNormal_Bullet::Create(D3DXVECTOR3(pos),
						D3DXVECTOR3(0.0f, 0.0f, 0.0f),
						BULLET_LEVEL3_SIZE,
						D3DXVECTOR3(BULLET_NORMAL_MOVE_VALUE.x, -BULLET_NORMAL_MOVE_VALUE.y, BULLET_NORMAL_MOVE_VALUE.z),
						D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
						CBullet::TEX_TYPE_NORMAL);
				}

			}
			// コントローラーAボタンまたはキーボードSPACEを離した場合
			if (g_lpDIDevice != NULL &&pInputJoystick->GetJoystickRelease(JS_A) || pInputKeyboard->GetKeyboardRelease(DIK_SPACE))
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
		if (g_lpDIDevice != NULL &&pInputJoystick->GetJoystickPress(JS_A) || pInputKeyboard->GetKeyboardPress(DIK_SPACE))
		{
			//ビームカウントインクリメント
			m_nBeamCount++;
			//カウントが20以上の時
			if (m_nBeamCount >= 20)
			{
				//ビームのboolをtrueに
				m_bUseBeam = true;
			}
		}
		// SPACEまたはコントローラAボタンを離したとき
		if (g_lpDIDevice != NULL &&pInputJoystick->GetJoystickRelease(JS_A) || pInputKeyboard->GetKeyboardRelease(DIK_SPACE))
		{
			// カウントを0に
			m_nBeamCount = 0;
			// ビームboolをfalseに
			m_bUseBeam = false;
			// ビームの使用状態を設定
			CPlayer_Beam::SetUseBeam(m_bUseBeam);
		}
		// ビームのboolがtrueの時
		if (m_bUseBeam == true)
		{
			// カウントインクリメント
			m_AttackCount++;
			//カウントが2あまり0の時
			if (m_AttackCount % 2 == 0)
			{
				// ショット音生成
				pSound->PlaySound(CSound::SOUND_LABEL_SE_SHOT);
				// playerレベルが1の時
				if (m_Level == LEVEL_1)
				{
					// 弾生成
					CPlayer_Beam::Create(D3DXVECTOR3(pos.x, pos.y - 45, pos.z),
						D3DXVECTOR3(0.0f, 0.0f, 0.0f),
						BULLET_LEVEL1_BEAM_SIZE,
						D3DXVECTOR3(BEAM_BULLET_MOVE_VALUE.x, -BEAM_BULLET_MOVE_VALUE.y, BEAM_BULLET_MOVE_VALUE.z),
						D3DXCOLOR (1.0f,1.0f,1.0f,1.0f),
						CBullet::TEX_TYPE_BEAM);
				}
				// playerレベルが2の時
				if (m_Level == LEVEL_2)
				{
					// 弾生成
					CPlayer_Beam::Create(D3DXVECTOR3(pos.x, pos.y - 45, pos.z),
						D3DXVECTOR3(0.0f, 0.0f, 0.0f),
						BULLET_LEVEL2_BEAM_SIZE,
						D3DXVECTOR3(BEAM_BULLET_MOVE_VALUE.x, -BEAM_BULLET_MOVE_VALUE.y, BEAM_BULLET_MOVE_VALUE.z),
						D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
						CBullet::TEX_TYPE_BEAM);
				}
				// playerレベルが3の時
				if (m_Level == LEVEL_3)
				{
					// 弾生成
					CPlayer_Beam::Create(D3DXVECTOR3(pos.x, pos.y - 45, pos.z),
						D3DXVECTOR3(0.0f, 0.0f, 0.0f),
						BULLET_LEVEL3_BEAM_SIZE,
						D3DXVECTOR3(BEAM_BULLET_MOVE_VALUE.x, -BEAM_BULLET_MOVE_VALUE.y, BEAM_BULLET_MOVE_VALUE.z),
						D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
						CBullet::TEX_TYPE_BEAM);
				}
			}
		}

		// キーボードのBまたはコントローラのBボタンを押した場合
		if (g_lpDIDevice != NULL &&pInputJoystick->GetJoystickTrigger(JS_B) || pInputKeyboard->GetKeyboardTrigger(DIK_B))
		{
			// ボム所持数が0より多い場合
			if (m_nBom_possession_count > 0)
			{
				// ボムboolをtrueに
				m_bUseBom = true;
			}
		}
	}

	// ボムが使用中の場合
	if (m_bUseBom == true)
	{
		// ボムの所持数減算
		GetBom(-1);
		// ボス戦でない時
		if (m_bBoss == false)
		{
			// 爆発音生成
			pSound->PlaySound(CSound::SOUND_LABEL_SE_BOM);
			// ボム生成
			CBom::Create(BOM_POS, BOM_ROT, BOM_SIZE,CBullet::TEX_TYPE_BOM);
			m_bUseBom = false;
		}
		// ボス戦の時
		if (m_bBoss == true)
		{
			// ボムのカウントをインクリメント
			m_nBomCount++;

			// ボス専用のボムを使用状態に
			m_bBossBom = true;

			// 2あまり0の時
			if (m_nBomCount % 2 == 0)
			{
				// ビーム音生成
				//pSound->PlaySound(CSound::SOUND_LABEL_SE_SHOT);
				// 弾の生成
				CBoss_Bom::Create(D3DXVECTOR3(pos.x, pos.y - 45, pos.z),
					D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					BOSS_BOM_SIZE,
					D3DXVECTOR3(BEAM_BULLET_MOVE_VALUE.x, -BEAM_BULLET_MOVE_VALUE.y, BEAM_BULLET_MOVE_VALUE.z),
					CBullet::TEX_TYPE_BEAM);
			}
			// カウントが200以上になったら
			if (m_nBomCount >= BOM_LAUNCH_TIME)
			{
				// ボムの使用状態をfalseに
				m_bUseBom = false;
				// ボムの使用状態を設定
				CBoss_Bom::SetUseBoss_Bom(m_bUseBom);
				// ボムのカウントが0に
				m_nBomCount = 0;
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
		SetTexture(m_nPatternAnim * 0.2f, 0.0f, 0.2f, 1.0f);
	
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
			SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
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
				SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, 600.0f, 0.0f));

				// カウントを0に
				m_nRespawnCount = 0;
			}
		}
		// ダメージ状態
		if (m_nPlayerState == STATE_DAMAGE)
		{
			// カウントインクリメント
			m_nDamageCount++;
			// ダメージのカウントが5あまり0になったら
			if (m_nDamageCount % 5 == 0)
			{
				// カラー設定
				SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			// ダメージのカウントが6あまり0になったら
			if (m_nDamageCount % 6 == 0)
			{
				// カラー設定
				SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

			}
			// 無敵時間が終了したら
			if (m_nDamageCount == DAMAGE_COUNT)
			{
				// カラー設定
				SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

				// stateをNormalに
				m_nPlayerState = STATE_NORMAL;

				// カウントを0に
				m_nDamageCount = 0;
			}
		}
		// コンティニュー状態がfalseの時
		if (m_bContinue == false)
		{
			// ライフが0以下の時
			if (m_nLife <= 0)
			{
				// コンティニュー状態をtrueに
				m_bContinue = true;
			}
		}
		// コンティニュー状態をtrueに
		if (m_bContinue == true)
		{
			// 死亡状態に
			m_nPlayerState = STATE_DEAD;
			// コンティニュー生成 
			CContinue::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), CONTINUE_SIZE);
		}
	}
	// 死亡状態の場合
	if (m_nPlayerState == STATE_DEAD)
	{
		// 画面外に移動させる
		SetPosition(D3DXVECTOR3(-100.0f, -100.0f, 0.0f));
		// コンティニューした場合
		if (m_nContinue == PLAYER_CONTINUE)
		{
			// スコア取得
			CScore * pScore = CGame::GetScore();
			pScore->AddScore(-3000);

			// ライフの取得
			CLife * pLife = CGame::GetLife();

			//ライフを3に
			m_nLife = PLAYER_LIFE;

			//ライフを設定
			pLife->AddLife(m_nLife);

			//ボムの所持数を3に
			GetBom(3);

			//コンティニュー状態をfalseに
			m_bContinue = false;
			m_nContinue = 0;
			m_nPlayerState = STATE_RESPAWN;
		}
	}
}