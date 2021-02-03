//******************************************************************************
// 自機の武器 [player_wepon.cpp]
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
#include "player.h"
#include "bullet.h"
#include "normal_bullet.h"
#include "game.h"
#include "player_wepon.h"
#include "input.h"
#include "inputkeyboard.h"
#include "inputjoystick.h"
#include <stdio.h>
//******************************************************************************
// マクロ定義
//******************************************************************************
#define WEPON_BULLET_NORMAL_MOVE_VALUE	(D3DXVECTOR3(7.5f,15.0f,0.0f))
//******************************************************************************
// 静的メンバ変数
//******************************************************************************
LPDIRECT3DTEXTURE9 CPlayer_Wepon::m_pTexture= NULL;
//******************************************************************************
// コンストラクタ
//******************************************************************************
CPlayer_Wepon::CPlayer_Wepon(int nPriority)
{
	m_Type			= TYPE_NONE;
	m_nCountAnim	= 0;
	m_nPatternAnim	= 0;
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CPlayer_Wepon::~CPlayer_Wepon()
{
}
//******************************************************************************
// テクスチャ読み込み
//******************************************************************************
HRESULT CPlayer_Wepon::Load(void)
{
	//レンダラー取得
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "data/Texture/Player/Player002.png", &m_pTexture);
	return S_OK;
}
//******************************************************************************
// テクスチャ破棄
//******************************************************************************
void CPlayer_Wepon::Unload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		// m_pTextureをRelease
		m_pTexture->Release();
		// m_pTextureをNULL
		m_pTexture = NULL;
	}
}
//******************************************************************************
// 生成関数
//******************************************************************************
CPlayer_Wepon * CPlayer_Wepon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// CPlayer_Weponクラスのポインタ
	CPlayer_Wepon * pPlayer_Wepon;

	// メモリ確保
	pPlayer_Wepon = new CPlayer_Wepon;

	// 位置座標設定
	pPlayer_Wepon->SetPosition(pos);

	// サイズ設定
	pPlayer_Wepon->SetSize(size);

	// カラー設定
	pPlayer_Wepon->SetRGBA(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));

	// オブジェタイプ設定
	pPlayer_Wepon->SetObjType(OBJTYPE_PLAYER_WEPON);

	// タイプ設定
	pPlayer_Wepon->m_Type = type;

	// テクスチャ受け渡し
	pPlayer_Wepon->BindTexture(m_pTexture);

	// 初期化
	pPlayer_Wepon->Init();

	// ポインタを返す
	return pPlayer_Wepon;
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CPlayer_Wepon::Init(void)
{
	// 初期化
	CScene2d::Init();

	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CPlayer_Wepon::Uninit(void)
{
	// 終了
	CScene2d::Uninit();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CPlayer_Wepon::Update(void)
{
	// 更新
	CScene2d::Update();

	// 移動処理
	Move();

	// 弾発射処理
	Shot();

	// インクリメント
	m_nCountAnim++;

	//カウントが 7以上になった場合
	if (m_nCountAnim > 7)
	{
		m_nCountAnim = 0;
		//パターンが0以上の場合
		if (m_nPatternAnim >= 0)
		{
			//パターンをインクリメント
			m_nPatternAnim++;
		}
	}

	// テクスチャ設定
	SetTexture(m_nPatternAnim * 0.25f, 0.0f, 0.25f, 1.0f);
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CPlayer_Wepon::Draw(void)
{
	// 描画
	CScene2d::Draw();
}
//******************************************************************************
// 移動処理関数
//******************************************************************************
void CPlayer_Wepon::Move(void)
{

	// プレイヤーの取得
	CPlayer * pPlayer = CGame::GetPlayer();

	// プレイヤーの座標取得
	D3DXVECTOR3 PlayerPos;
	PlayerPos = pPlayer->GetPosition();

	// プレイヤーがビームを使用しているかを取得
	bool bPlayer_Use_Beam = pPlayer->GetUseBeam();

	// プレイヤーがボス専用のボムを使用しているかを取得
	bool bPlayer_Use_BossBom = pPlayer->GetUseBossBom();

	// ビームを使用中の場合
	if (bPlayer_Use_Beam == true || bPlayer_Use_BossBom == true)
	{
		// タイプが左の場合
  		if (m_Type == TYPE_LEFT)
		{
			// 武器のposを自機の前に
          	SetPosition(D3DXVECTOR3(PlayerPos.x - 15, PlayerPos.y - 40, PlayerPos.z));
		}
		// タイプが右の場合
		if (m_Type == TYPE_RIGHT)
		{
			// 武器のposを自機の前に
			SetPosition(D3DXVECTOR3(PlayerPos.x + 15, PlayerPos.y - 40, PlayerPos.z));
		}
	}
	// ビームを使用中の場合
	else if (bPlayer_Use_Beam == false)
	{
		// タイプが左の場合
		if (m_Type == TYPE_LEFT)
		{
			// 位置座標設定
			SetPosition(D3DXVECTOR3(PlayerPos.x - 40, PlayerPos.y + 40, PlayerPos.z));
		}
		// タイプが右の場合
		if (m_Type == TYPE_RIGHT)
		{
			// 位置座標設定
			SetPosition(D3DXVECTOR3(PlayerPos.x + 40, PlayerPos.y + 40, PlayerPos.z));
		}
	}
}
//******************************************************************************
// 弾発射処理関数
//******************************************************************************
void CPlayer_Wepon::Shot(void)
{
	// 位置座標取得
	D3DXVECTOR3 pos = GetPosition();

	// プレイヤーの取得
	CPlayer * pPlayer = CGame::GetPlayer();

	// キーボード取得
	CInputKeyboard * pInputKeyboard = CSceneManager::GetInputKeyboard();

	// コントローラー取得
	DIJOYSTATE js;
	CInputJoystick * pInputJoystick = CSceneManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 g_lpDIDevice = CInputJoystick::GetDevice();

	// プレイヤーがビームを使用しているかを取得
	bool bPlayer_Use_Shot = pPlayer->GetUseShot();

	// プレイヤーレベル取得
	int nPlayerLevel = pPlayer->GetLevel();

	// プレイヤーが通常弾を使用中の場合
	if (g_lpDIDevice != NULL &&pInputJoystick->GetJoystickTrigger(JS_A) || pInputKeyboard->GetKeyboardTrigger(DIK_SPACE))
	{
		// レベルが1の場合
		if (nPlayerLevel == CPlayer::LEVEL_1)
		{
			// タイプが左の場合
			if (m_Type == TYPE_LEFT)
			{
				// 弾生成
				CNormal_Bullet::Create(D3DXVECTOR3(pos),
					D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(30.0f)),
					BULLET_LEVEL1_SIZE,
					D3DXVECTOR3(-WEPON_BULLET_NORMAL_MOVE_VALUE.x, -WEPON_BULLET_NORMAL_MOVE_VALUE.y, WEPON_BULLET_NORMAL_MOVE_VALUE.z),
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
					, CBullet::TEX_TYPE_NORMAL);
			}
			// タイプが右の場合
			if (m_Type == TYPE_RIGHT)
			{
				CNormal_Bullet::Create(D3DXVECTOR3(pos),
					D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(-30.0f)),
					BULLET_LEVEL1_SIZE,
					D3DXVECTOR3(WEPON_BULLET_NORMAL_MOVE_VALUE.x, -WEPON_BULLET_NORMAL_MOVE_VALUE.y, WEPON_BULLET_NORMAL_MOVE_VALUE.z),
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
					CBullet::TEX_TYPE_NORMAL);
			}
		}

		// レベルが2の場合
		if (nPlayerLevel == CPlayer::LEVEL_2)
		{
			// タイプが左の場合
			if (m_Type == TYPE_LEFT)
			{
				CNormal_Bullet::Create(D3DXVECTOR3(pos),
					D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(30.0f)),
					BULLET_LEVEL2_SIZE,
					D3DXVECTOR3(-WEPON_BULLET_NORMAL_MOVE_VALUE.x, -WEPON_BULLET_NORMAL_MOVE_VALUE.y, WEPON_BULLET_NORMAL_MOVE_VALUE.z),
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
					CBullet::TEX_TYPE_NORMAL);
			}
			// タイプが右の場合
			if (m_Type == TYPE_RIGHT)
			{
				CNormal_Bullet::Create(D3DXVECTOR3(pos),
					D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(-30.0f)),
					BULLET_LEVEL2_SIZE,
					D3DXVECTOR3(WEPON_BULLET_NORMAL_MOVE_VALUE.x, -WEPON_BULLET_NORMAL_MOVE_VALUE.y, WEPON_BULLET_NORMAL_MOVE_VALUE.z),
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
					CBullet::TEX_TYPE_NORMAL);
			}
		}
		// プレイヤーレベルが3の場合
		if (nPlayerLevel == CPlayer::LEVEL_3)
		{
			// タイプが左の場合
			if (m_Type == TYPE_LEFT)
			{
				CNormal_Bullet::Create(D3DXVECTOR3(pos),
					D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(30.0f)),
					BULLET_LEVEL3_SIZE,
					D3DXVECTOR3(-WEPON_BULLET_NORMAL_MOVE_VALUE.x, -WEPON_BULLET_NORMAL_MOVE_VALUE.y, WEPON_BULLET_NORMAL_MOVE_VALUE.z),
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
					CBullet::TEX_TYPE_NORMAL);
			}
			// タイプが右の場合
			if (m_Type == TYPE_RIGHT)
			{
				CNormal_Bullet::Create(D3DXVECTOR3(pos),
					D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(-30.0f)),
					BULLET_LEVEL3_SIZE,
					D3DXVECTOR3(WEPON_BULLET_NORMAL_MOVE_VALUE.x, -WEPON_BULLET_NORMAL_MOVE_VALUE.y, WEPON_BULLET_NORMAL_MOVE_VALUE.z),
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
					CBullet::TEX_TYPE_NORMAL);
			}
		}
	}
}