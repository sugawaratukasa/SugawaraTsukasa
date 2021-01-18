//---------------------------------------------------
// Player
// player.cpp
// Author:	管原司
//---------------------------------------------------
#define	_CRT_SECURE_NO_WARNINGS	//scanfエラー
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
#include "sound.h"
#include "life.h"
#include "game.h"
#include "explosion.h"
#include "bomui.h"
#include "continue.h"
#include "score.h"
#include <stdio.h>
//-------------------------------------------------
//静的メンバ変数
//-------------------------------------------------
LPDIRECT3DTEXTURE9 CPlayer::m_apTexture[MAX_PLAYER_TEX] = {};
//----------------------------------------------------
//テクスチャ読み込み
//----------------------------------------------------
HRESULT CPlayer::Load(void)
{
	//レンダラー取得
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "data/Texture/Player003.png", &m_apTexture[TYPE_MAIN]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/Player002.png", &m_apTexture[TYPE_RIGHT]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/Player002.png", &m_apTexture[TYPE_LEFT]);
	return S_OK;
}
//---------------------------------------------------
//テクスチャの破棄
//---------------------------------------------------
void CPlayer::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_PLAYER_TEX; nCnt++)
	{
		// テクスチャの破棄
		if (m_apTexture[nCnt] != NULL)
		{
			//m_apTextureをRelease
			m_apTexture[nCnt]->Release();
			//m_apTextureをNULL
			m_apTexture[nCnt] = NULL;
		}
	}
}
//---------------------------------------------------
//コンストラクタ
//---------------------------------------------------
CPlayer::CPlayer(int nPriority) : CScene(nPriority)
{
	memset(m_apScene2D, 0, sizeof(m_apScene2D));
	m_Mainpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_WeponRightpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_WeponLeftpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nContinue = 0;
	m_nLife = 0;
	m_nCountAnim = 0;
	m_nCountAnimWepon = 0;
	m_nPatternAnim = 0;
	m_nPatternAnimWepon = 0;
	m_AttackCount = 0;
	m_nBeamCount = 0;
	m_nDamageCount = 0;
	m_nRespawnCount = 0;
	m_nNoDamageCount = 0;
	m_nBomCount = 0;
	m_nBom_possession_count = 0;
	m_nPlayerState = STATE_NONE;
	m_Level = LEVEL_NONE;
	m_bMove = false;
	m_bUseBeam = false;
	m_bUseBom = false;
	m_bBoss = false;
	m_bContinue = false;
}
//---------------------------------------------------
//デストラクタ
//---------------------------------------------------
CPlayer::~CPlayer()
{
}
//---------------------------------------------------
//Create
//---------------------------------------------------
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY)
{
	//CPlayerクラスのポインタ
	CPlayer * pPlayer;
	//メモリ確保
	pPlayer = new CPlayer;
	//初期化
	pPlayer->Init(pos, rot, sizeX, sizeY);
	//pPlayerを返す
	return pPlayer;
}
//---------------------------------------------------
//初期化
//---------------------------------------------------
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY)
{
	//メモリ確保
	m_apScene2D[TYPE_MAIN] = new CScene2d;
	m_apScene2D[TYPE_RIGHT] = new CScene2d;
	m_apScene2D[TYPE_LEFT] = new CScene2d;

	//RGBAの設定
	m_apScene2D[TYPE_MAIN]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_apScene2D[TYPE_RIGHT]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_apScene2D[TYPE_LEFT]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//テクスチャの受け渡し
	m_apScene2D[TYPE_MAIN]->BindTexture(m_apTexture[TYPE_MAIN]);
	m_apScene2D[TYPE_RIGHT]->BindTexture(m_apTexture[TYPE_RIGHT]);
	m_apScene2D[TYPE_LEFT]->BindTexture(m_apTexture[TYPE_LEFT]);

	//初期化
	m_apScene2D[TYPE_MAIN]->Init(pos, rot, sizeX, sizeY);
	m_apScene2D[TYPE_RIGHT]->Init(D3DXVECTOR3(pos.x + 40, pos.y + 40, pos.z), rot, PLAYER_WEPON_SIZE_X, PLAYER_WEPON_SIZE_Y);
	m_apScene2D[TYPE_LEFT]->Init(D3DXVECTOR3(pos.x - 40, pos.y + 40, pos.z), rot, PLAYER_WEPON_SIZE_X, PLAYER_WEPON_SIZE_Y);

	//オブジェクトタイプの設定
	m_apScene2D[TYPE_MAIN]->SetObjType(OBJTYPE_PLAYER);
	//プレイヤーのステートノーマル
	m_nPlayerState = STATE_NORMAL;
	//レベル1
	m_Level = LEVEL_1;
	//体力
	m_nLife = PLAYER_LIFE;
	return S_OK;
}
//---------------------------------------------------
//終了
//---------------------------------------------------
void CPlayer::Uninit(void)
{
	//終了
	Release();
}
//---------------------------------------------------
//更新
//---------------------------------------------------
void CPlayer::Update(void)
{
	//死亡状態でない時
	if (m_nPlayerState != STATE_DEAD)
	{
		//更新
		m_apScene2D[TYPE_MAIN]->Update();
		m_apScene2D[TYPE_RIGHT]->Update();
		m_apScene2D[TYPE_LEFT]->Update();
		//キーボード取得
		CInputKeyboard * pInputKeyboard = CSceneManager::GetInputKeyboard();
		//コントローラー取得
		DIJOYSTATE js;
		CInputJoystick * pInputJoystick = CSceneManager::GetInputJoystick();
		LPDIRECTINPUTDEVICE8 g_lpDIDevice = CInputJoystick::GetDevice();
		////サウンド取得
		//CSound * pSound = CSceneManager::GetSound();
		//CSound::SOUND_LABEL type;
		//type = CSound::SOUND_LABEL_SE_SHOT;
		//自機の中心
		m_Mainpos = m_apScene2D[TYPE_MAIN]->GetPosition();
		//自機の右
		m_WeponRightpos = m_apScene2D[TYPE_RIGHT]->GetPosition();
		//自機の左
		m_WeponLeftpos = m_apScene2D[TYPE_LEFT]->GetPosition();

		//位置設定
		m_apScene2D[TYPE_RIGHT]->SetPosition(D3DXVECTOR3(m_Mainpos.x + 40, m_Mainpos.y + 40, m_Mainpos.z));
		m_apScene2D[TYPE_LEFT]->SetPosition(D3DXVECTOR3(m_Mainpos.x - 40, m_Mainpos.y + 40, m_Mainpos.z));

		//テクスチャ更新
		m_apScene2D[TYPE_MAIN]->SetTexture(m_nPatternAnim * 0.2f, 0.0f, 0.2f, 1.0f);
		m_apScene2D[TYPE_RIGHT]->SetTexture(m_nPatternAnimWepon * 0.25f, 0.0f, 0.25f, 1.0f);
		m_apScene2D[TYPE_LEFT]->SetTexture(m_nPatternAnimWepon * 0.25f, 0.0f, 0.25f, 1.0f);

		if (g_lpDIDevice != NULL)
		{
			g_lpDIDevice->Poll();
			g_lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
		}
		//スコア取得
		CScore * pScore = CGame::GetScore();
		m_nScore = pScore->GetScore();
		//プレイヤーの情報を外部ファイルに書き込み
		SavePlayer();
		//カウントインクリメント
		m_nCountAnimWepon++;
		//カウントが25以上になった場合
		if (m_nCountAnimWepon > 7)
		{
			m_nCountAnimWepon = 0;
			//パターンが0以上の場合
			if (m_nPatternAnim >= 0)
			{
				//パターンをインクリメント
				m_nPatternAnimWepon++;
			}
		}
		//左右移動してない時
		if (m_bMove == false)
		{
			//アニメーションパターンを2にする
			m_nPatternAnim = 2;
		}
		//コントローラー
		//上
		if (g_lpDIDevice != NULL &&js.lY <= -500 || pInputKeyboard->GetKeyboardPress(DIK_W))
		{
			//falseに
			m_bMove = false;
			//ビームを発射してる時
			if (m_bUseBeam == true)
			{
				//5移動
				m_move.y = -PLAYER_BEAM_MOVE_Y;
			}
			//ビームを発射してない時
			else
			{
				//8移動
				m_move.y = -PLAYER_MOVE_Y;
			}
		}
		//下
		if (g_lpDIDevice != NULL &&js.lY >= 500 || pInputKeyboard->GetKeyboardPress(DIK_S))
		{
			m_bMove = false;
			if (m_bUseBeam == true)
			{
				m_move.y = PLAYER_BEAM_MOVE_Y;
			}
			else
			{
				m_move.y = PLAYER_MOVE_Y;
			}
		}
		//左
		if (g_lpDIDevice != NULL &&js.lX <= -500 || pInputKeyboard->GetKeyboardPress(DIK_A))
		{
			//trueに
			m_bMove = true;
			//ビームを発射している場合
			if (m_bUseBeam == true)
			{
				//5移動
				m_move.x = -PLAYER_BEAM_MOVE_X;
			}
			//ビームを発射してない場合
			else
			{
				//8移動
				m_move.x = -PLAYER_MOVE_X;
			}
			//アニメーションを1に
			m_nPatternAnim = 1;
			//カウントが10より大きい場合
			if (m_nCountAnim > 10)
			{
				//アニメカウントを0に
				m_nPatternAnim = 0;
			}
		}
		//左に移動してない時
		else
		{
			m_bMove = false;
		}
		//右
		if (g_lpDIDevice != NULL &&js.lX >= 500 || pInputKeyboard->GetKeyboardPress(DIK_D))
		{
			m_bMove = true;
			if (m_bUseBeam == true)
			{
				m_move.x = PLAYER_BEAM_MOVE_X;
			}
			else
			{
				m_move.x = PLAYER_MOVE_X;
			}
			m_nPatternAnim = 4;
			if (m_nCountAnim > 10)
			{
				m_nPatternAnim = 5;
			}
		}
		//右に移動してない時
		else
		{
			m_bMove = false;
		}
		//ボム使用状態
		if (m_bUseBom == false)
		{
			//Aボタンで弾発射
			if (m_bUseBeam == false)
			{
				//SPACEまたはAボタンを押した場合
				if (g_lpDIDevice != NULL &&pInputJoystick->GetJoystickTrigger(JS_A) || pInputKeyboard->GetKeyboardTrigger(DIK_SPACE))
				{
					//ショット音
					//pSound->PlaySound(CSound::SOUND_LABEL_SE_SHOT);
					//プレイヤーレベルが1の場合
					if (m_Level == LEVEL_1)
					{
						//弾の生成
						CBullet::Create(D3DXVECTOR3(m_Mainpos), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), BULLET_LEVEL1_SIZE_X, BULLET_LEVEL1_SIZE_Y, CBullet::TYPE_PLAYER, CBullet::PATTERN_TYPE_NORMAL, CBullet::TEX_TYPE_NORMAL, OBJTYPE_PLAYER_BULLET);
						CBullet::Create(D3DXVECTOR3(m_WeponRightpos), D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(-30.0f)), D3DXVECTOR3(7.5f, -10.0f, 0.0f), BULLET_LEVEL1_SIZE_X, BULLET_LEVEL1_SIZE_Y, CBullet::TYPE_PLAYER, CBullet::PATTERN_TYPE_NORMAL, CBullet::TEX_TYPE_NORMAL, OBJTYPE_PLAYER_BULLET);
						CBullet::Create(D3DXVECTOR3(m_WeponLeftpos), D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(30.0f)), D3DXVECTOR3(-7.5f, -10.0f, 0.0f), BULLET_LEVEL1_SIZE_X, BULLET_LEVEL1_SIZE_Y, CBullet::TYPE_PLAYER, CBullet::PATTERN_TYPE_NORMAL, CBullet::TEX_TYPE_NORMAL, OBJTYPE_PLAYER_BULLET);
					}
					//プレイヤーレベルが2の場合
					if (m_Level == LEVEL_2)
					{
						//弾の生成
						CBullet::Create(D3DXVECTOR3(m_Mainpos), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), BULLET_LEVEL2_SIZE_X, BULLET_LEVEL2_SIZE_Y, CBullet::TYPE_PLAYER, CBullet::PATTERN_TYPE_NORMAL, CBullet::TEX_TYPE_NORMAL, OBJTYPE_PLAYER_BULLET);
						CBullet::Create(D3DXVECTOR3(m_WeponRightpos), D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(-30.0f)), D3DXVECTOR3(7.5f, -10.0f, 0.0f), BULLET_LEVEL2_SIZE_X, BULLET_LEVEL2_SIZE_Y, CBullet::TYPE_PLAYER, CBullet::PATTERN_TYPE_NORMAL, CBullet::TEX_TYPE_NORMAL, OBJTYPE_PLAYER_BULLET);
						CBullet::Create(D3DXVECTOR3(m_WeponLeftpos), D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(30.0f)), D3DXVECTOR3(-7.5f, -10.0f, 0.0f), BULLET_LEVEL2_SIZE_X, BULLET_LEVEL2_SIZE_Y, CBullet::TYPE_PLAYER, CBullet::PATTERN_TYPE_NORMAL, CBullet::TEX_TYPE_NORMAL, OBJTYPE_PLAYER_BULLET);
					}
					//プレイヤーレベルが3の場合
					if (m_Level == LEVEL_3)
					{
						//弾の生成
						CBullet::Create(D3DXVECTOR3(m_Mainpos), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), BULLET_LEVEL3_SIZE_X, BULLET_LEVEL3_SIZE_Y, CBullet::TYPE_PLAYER, CBullet::PATTERN_TYPE_NORMAL, CBullet::TEX_TYPE_NORMAL, OBJTYPE_PLAYER_BULLET);
						CBullet::Create(D3DXVECTOR3(m_WeponRightpos), D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(-30.0f)), D3DXVECTOR3(7.5f, -10.0f, 0.0f), BULLET_LEVEL3_SIZE_X, BULLET_LEVEL3_SIZE_Y, CBullet::TYPE_PLAYER, CBullet::PATTERN_TYPE_NORMAL, CBullet::TEX_TYPE_NORMAL, OBJTYPE_PLAYER_BULLET);
						CBullet::Create(D3DXVECTOR3(m_WeponLeftpos), D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(30.0f)), D3DXVECTOR3(-7.5f, -10.0f, 0.0f), BULLET_LEVEL3_SIZE_X, BULLET_LEVEL3_SIZE_Y, CBullet::TYPE_PLAYER, CBullet::PATTERN_TYPE_NORMAL, CBullet::TEX_TYPE_NORMAL, OBJTYPE_PLAYER_BULLET);
					}
				}
			}
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
			//ビームのboolがtrueの時
			if (m_bUseBeam == true)
			{
				//カウントインクリメント
				m_AttackCount++;
				//武器のposを自機の前に
				m_apScene2D[TYPE_RIGHT]->SetPosition(D3DXVECTOR3(m_Mainpos.x + 15, m_Mainpos.y - 40, m_Mainpos.z));
				m_apScene2D[TYPE_LEFT]->SetPosition(D3DXVECTOR3(m_Mainpos.x - 15, m_Mainpos.y - 40, m_Mainpos.z));
				//カウントが2あまり0の時
				if (m_AttackCount % 2 == 0)
				{
					//ショット音生成
					//pSound->PlaySound(CSound::SOUND_LABEL_SE_SHOT);
					//playerレベルが1の時
					if (m_Level == LEVEL_1)
					{
						//弾生成
						CBullet::Create(D3DXVECTOR3(m_Mainpos.x, m_Mainpos.y - 45, m_Mainpos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -15.0f, 0.0f), BULLET_LEVEL1_BEAM_SIZE_X, BULLET_LEVEL1_BEAM_SIZE_Y, CBullet::TYPE_PLAYER, CBullet::PATTERN_TYPE_BEAM, CBullet::TEX_TYPE_BEAM, OBJTYPE_PLAYER_BULLET);
					}
					//playerレベルが2の時
					if (m_Level == LEVEL_2)
					{
						//弾生成
						CBullet::Create(D3DXVECTOR3(m_Mainpos.x, m_Mainpos.y - 45, m_Mainpos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -15.0f, 0.0f), BULLET_LEVEL2_BEAM_SIZE_X, BULLET_LEVEL2_BEAM_SIZE_Y, CBullet::TYPE_PLAYER, CBullet::PATTERN_TYPE_BEAM, CBullet::TEX_TYPE_BEAM, OBJTYPE_PLAYER_BULLET);
					}
					//playerレベルが3の時
					if (m_Level == LEVEL_3)
					{
						//弾生成
						CBullet::Create(D3DXVECTOR3(m_Mainpos.x, m_Mainpos.y - 45, m_Mainpos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -15.0f, 0.0f), BULLET_LEVEL3_BEAM_SIZE_X, BULLET_LEVEL3_BEAM_SIZE_Y, CBullet::TYPE_PLAYER, CBullet::PATTERN_TYPE_BEAM, CBullet::TEX_TYPE_BEAM, OBJTYPE_PLAYER_BULLET);
					}
				}
			}
			//ビームを使用してない時
			else
			{
				//位置設定
				m_apScene2D[TYPE_RIGHT]->SetPosition(D3DXVECTOR3(m_Mainpos.x + 40, m_Mainpos.y + 40, m_Mainpos.z));
				m_apScene2D[TYPE_LEFT]->SetPosition(D3DXVECTOR3(m_Mainpos.x - 40, m_Mainpos.y + 40, m_Mainpos.z));
			}
			//SPACEまたはコントローラAボタンを離したとき
			if (g_lpDIDevice != NULL &&pInputJoystick->GetJoystickRelease(JS_A) || pInputKeyboard->GetKeyboardRelease(DIK_SPACE))
			{
				//カウントを0に
				m_nBeamCount = 0;
				//ビームboolをfalseに
				m_bUseBeam = false;
				//ビームの使用状態を設定
				CBullet::SetUseBeam(m_bUseBeam);
			}
			//ボム所持数が0より多い場合
			if (m_nBom_possession_count > 0)
			{
				//キーボードのBまたはコントローラのBボタンを押した場合
				if (g_lpDIDevice != NULL &&pInputJoystick->GetJoystickTrigger(JS_B) || pInputKeyboard->GetKeyboardTrigger(DIK_B))
				{
					//ボムboolをtrueに
					m_bUseBom = true;
				}
			}
		}
		//ボムが使用中の場合
		if (m_bUseBom == true)
		{
			//ボムの所持数減算
			GetBom(-1);
			//ボス戦でない時
			if (m_bBoss == false)
			{
				//爆発音生成
				//pSound->PlaySound(CSound::SOUND_LABEL_SE_BOM);
				//ボム生成
				CBullet::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BULLET_BOM_SIZE_X, BULLET_BOM_SIZE_Y, CBullet::TYPE_PLAYER, CBullet::PATTERN_TYPE_BOM, CBullet::TEX_TYPE_BOM, OBJTYPE_PLAYER_BULLET);
				//ボムboolをfalseに
				m_bUseBom = false;
			}
			//ボス戦の時
			if (m_bBoss == true)
			{
				//ボムのカウントをインクリメント
				m_nBomCount++;
				//武器のposを自機の前に
				m_apScene2D[TYPE_RIGHT]->SetPosition(D3DXVECTOR3(m_Mainpos.x + 15, m_Mainpos.y - 40, m_Mainpos.z));
				m_apScene2D[TYPE_LEFT]->SetPosition(D3DXVECTOR3(m_Mainpos.x - 15, m_Mainpos.y - 40, m_Mainpos.z));
				if (m_nBomCount % 2 == 0)
				{
					//ビーム音生成
					//pSound->PlaySound(CSound::SOUND_LABEL_SE_SHOT);
					//弾の生成
					CBullet::Create(D3DXVECTOR3(m_WeponRightpos.x + 80, m_WeponRightpos.y, m_Mainpos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -15.0f, 0.0f), BULLET_BOSS_BOM_SIZE_X, BULLET_BOSS_BOM_SIZE_Y, CBullet::TYPE_PLAYER, CBullet::PATTERN_TYPE_BOSS_BOM, CBullet::TEX_TYPE_BEAM, OBJTYPE_PLAYER_BULLET);	
				}
				//カウントが200以上になったら
				if (m_nBomCount >= BOM_LAUNCH_TIME)
				{
					//ボムの使用状態をfalseに
					m_bUseBom = false;
					//ボムの使用状態を設定
					CBullet::SetUseBom(m_bUseBom);
					//ボムのカウントが0に
					m_nBomCount = 0;
				}
			}
		}
		//通常状態
		if (m_nPlayerState == STATE_NORMAL)
		{
			//カラー設定
			m_apScene2D[TYPE_MAIN]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_apScene2D[TYPE_RIGHT]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_apScene2D[TYPE_LEFT]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		//リスポン状態
		if (m_nPlayerState == STATE_RESPAWN)
		{
			//カウントインクリメント
			m_nRespawnCount++;
			//カウントが30になったとき
			if (m_nRespawnCount == DAMAGE_RESPAWN_COUNT)
			{
				//ダメージ状態に
				m_nPlayerState = STATE_DAMAGE;
				//自機のposに代入
				m_Mainpos = D3DXVECTOR3(SCREEN_WIDTH / 2, 600.0f, 0.0f);
				//カウントを0に
				m_nRespawnCount = 0;
			}
		}
		//ダメージ状態
		if (m_nPlayerState == STATE_DAMAGE)
		{
			//カウントインクリメント
			m_nDamageCount++;
			//ダメージのカウントが10になったら
			if (m_nDamageCount % 5 == 0)
			{
				//カラー設定
				m_apScene2D[TYPE_MAIN]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				m_apScene2D[TYPE_RIGHT]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				m_apScene2D[TYPE_LEFT]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			//ダメージのカウントが20になったら
			if (m_nDamageCount % 6 == 0)
			{
				//カラー設定
				m_apScene2D[TYPE_MAIN]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
				m_apScene2D[TYPE_RIGHT]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
				m_apScene2D[TYPE_LEFT]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
				m_nNoDamageCount = 0;
			}
			//無敵時間が終了したら
			if (m_nDamageCount == DAMAGE_COUNT)
			{
				m_apScene2D[TYPE_MAIN]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				m_apScene2D[TYPE_RIGHT]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				m_apScene2D[TYPE_LEFT]->SetRGBA(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				//stateをNormalに
				m_nPlayerState = STATE_NORMAL;
				//カウントを0に
				m_nDamageCount = 0;
			}
		}
		//位置更新
		m_Mainpos.x += m_move.x;
		m_Mainpos.y += m_move.y;

		//慣性
		m_move.x += (0.0f - m_move.x) * RATE_MOVE;
		m_move.y += (0.0f - m_move.y) * RATE_MOVE;

		//stateがNormalまたはDamageの時
		if (m_nPlayerState == STATE_NORMAL || m_nPlayerState == STATE_DAMAGE)
		{
			//上画面外に出たとき
			if (m_Mainpos.y - PLAYER_SIZE_Y < 0)
			{
				//プレイヤーのサイズ分ずらす
				m_Mainpos.y = PLAYER_SIZE_Y;
			}

			//もしプレイヤーが下画面外に行ったら
			if (m_Mainpos.y + PLAYER_SIZE_Y > SCREEN_HEIGHT)
			{
				//プレイヤーのサイズ分ずらす
				m_Mainpos.y = SCREEN_HEIGHT - PLAYER_SIZE_Y;
			}

			//もしプレイヤーが左画面外に行ったら
			if (m_Mainpos.x - PLAYER_SIZE_X - PLAYER_WEPON_SIZE_X / 2 < MIN_GAME_WIDTH)
			{
				//プレイヤーと武器のサイズ分ずらす
				m_Mainpos.x = MIN_GAME_WIDTH + PLAYER_SIZE_X + PLAYER_WEPON_SIZE_X / 2;
			}

			//もしプレイヤーが右画面外に行ったら
			if (m_Mainpos.x + PLAYER_SIZE_X + PLAYER_WEPON_SIZE_X / 2 > MAX_GAME_WIDTH)
			{
				//プレイヤーと武器のサイズ分ずらす
				m_Mainpos.x = MAX_GAME_WIDTH - PLAYER_SIZE_X - PLAYER_WEPON_SIZE_X / 2;
			}
		}
		// 位置更新
		m_apScene2D[TYPE_MAIN]->SetPosition(m_Mainpos);

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
		//コンティニュー状態をtrueに
		if (m_bContinue == true)
		{
			//死亡状態に
			m_nPlayerState = STATE_DEAD;
			//コンティニュー生成 
			CContinue::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CONTINUE_SIZE_X, CONTINUE_SIZE_Y);
		}
	}
	if (m_nPlayerState == STATE_DEAD)
	{
		m_apScene2D[TYPE_MAIN]->SetPosition(D3DXVECTOR3(-100.0f, -100.0f, 0.0f));
		if (m_nContinue == PLAYER_CONTINUE)
		{
			//スコア取得
			CScore * pScore = CGame::GetScore();
			pScore->AddScore(-3000);
			//ライフの取得
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
//---------------------------------------------------
//描画
//---------------------------------------------------
void CPlayer::Draw(void)
{
}
//----------------------------------------------------
//プレイヤーのダメージ判定
//----------------------------------------------------
void CPlayer::HitPlayer(void)
{
	if (m_nPlayerState == STATE_NORMAL)
	{
		//サウンド取得
		CSound * pSound = CSceneManager::GetSound();
		CSound::SOUND_LABEL type;
		type = CSound::SOUND_LABEL_SE_SHOT;
		//爆発音生成
		pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);
		//ライフの取得
		CLife * pLife = CGame::GetLife();
		//ライフ減算
		m_nLife--;
		//ライフUIの減算
		pLife->HitDamage(1);
		//爆発の生成
		CExplosion::Create(m_Mainpos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), EXPLOSION_SIZE_X, EXPLOSION_SIZE_Y);
		//位置座標設定
		m_apScene2D[TYPE_MAIN]->SetPosition(D3DXVECTOR3(-100.0f, -100.0f, 0.0f));
		//StateをRespawnに
		m_nPlayerState = STATE_RESPAWN;
	}
}
//--------------------------------------------------------------------------
//ボムの入手
//--------------------------------------------------------------------------
void CPlayer::GetBom(int nBom)
{
	CBom * pBom = CGame::GetBomUI();
	CScore * pScore = CGame::GetScore();

	//ボムの所持数の加算減算
	if (m_nBom_possession_count >= 0 && m_nBom_possession_count <= MAX_BOM_POSSESION)
	{
		m_nBom_possession_count += nBom;
		pBom->SetBomUI(m_nBom_possession_count);
	}

	if (m_nBom_possession_count >= MAX_BOM_POSSESION)
	{
		pScore->AddScore(5000);
	}
}
//-------------------------------------------------------------------------
//powerup入手
//-------------------------------------------------------------------------
void CPlayer::GetPowerUp(void)
{
	CScore * pScore = CGame::GetScore();
	if (m_Level < LEVEL_3)
	{
		//レベルアップ
		m_Level++;
	}
	//レベルが3の場合
	if (m_Level == LEVEL_3)
	{
		pScore->AddScore(3000);
	}
}
//--------------------------------------------
//コンティニューしたか
//--------------------------------------------
void CPlayer::SetContinue(int Continue)
{
	m_nContinue = Continue;
}
//--------------------------------------------
//Save関数
//--------------------------------------------
void CPlayer::SavePlayer(void)
{
	FILE * pFile;
	//ファイルの書き出し
	pFile = fopen("player.txt", "w");
	//ファイルが空じゃないか
	if (pFile != NULL)
	{
		//スコア書き込み
		fprintf(pFile, "%d\n", m_nScore);
		//ファイルを閉じる
		fclose(pFile);
	}
}
//-----------------------------------------------------------
//ボス戦か
//-----------------------------------------------------------
void CPlayer::SetBossBom(bool bBoss)
{
	m_bBoss = bBoss;
}
