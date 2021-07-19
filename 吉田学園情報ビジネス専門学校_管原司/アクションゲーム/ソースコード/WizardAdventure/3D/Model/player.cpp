//******************************************************************************
// プレイヤーの処理 [player.h]
// Author : 管原　司
//******************************************************************************

//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "manager.h"
#include "renderer.h"
#include "motion.h"
#include "model.h"
#include "joystick.h"
#include "../3D/Model/Block/block.h"
#include "../3D/Model/Block/stone_block.h"
#include "../3D/3DPolygon/frame.h"
#include "collision.h"
#include "../3D/Model/Object/3d_obj.h"
#include "game.h"
#include "camera.h"
#include "../3D/3DPolygon/Particle/magic.h"
#include "../3D/3DPolygon/Particle/Particle_Emitter/particle_emitter.h"
#include "../2D/Gage/life_gage.h"
#include "../3D/Model/Block/floor_block.h"
#include "../3D/Model/Enemy/enemy_map.h"
#include "map.h"
#include "../3D/3DPolygon/Particle/Particle_Effect/particle_effect.h"
#include "magic_ui.h"
#include "sound.h"
#include "fade.h"
#include "player.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define UNDER_BODY				("data/MODEL/PLAYER/00_UnderBody.x")						// 下半身
#define BODY					("data/MODEL/PLAYER/01_Body.x")								// 上半身
#define HEAD					("data/MODEL/PLAYER/02_Head.x")								// 頭
#define SHOULDER_R				("data/MODEL/PLAYER/03_shoulder_R.x")						// 右肩
#define UP_ARM_R				("data/MODEL/PLAYER/04_up_arm_R.x")							// 右上腕
#define DOWN_ARM_R				("data/MODEL/PLAYER/05_down_arm_R.x")						// 右前腕	
#define SHOULDER_L				("data/MODEL/PLAYER/06_shoulder_L.x")						// 左肩
#define UP_ARM_L				("data/MODEL/PLAYER/07_up_arm_L.x")							// 左上腕
#define DOWN_ARM_L				("data/MODEL/PLAYER/08_down_arm_L.x")						// 左前腕
#define THIGTS_R				("data/MODEL/PLAYER/09_Thigts_R.x")							// 右太もも
#define KNEE_R					("data/MODEL/PLAYER/10_Knee_R.x")							// 右膝
#define FOOT_R					("data/MODEL/PLAYER/11_foot_R.x")							// 右足
#define THIGTS_L				("data/MODEL/PLAYER/12_Thigts_L.x")							// 左太もも
#define KNEE_L					("data/MODEL/PLAYER/13_Knee_L.x")							// 左膝
#define FOOT_L					("data/MODEL/PLAYER/14_foot_L.x")							// 左足
#define MOTION_PLAYER_TEXT		("data/MODEL/PLAYER/Motion/motion.txt")						// モーションのテキスト
#define LOAD_PLAYER_TEXT		("data/MODEL/PLAYER/Motion/player.txt")						// 各モデルパーツの初期値
#define BLOCK_CREATE_RIGHTPOS	(D3DXVECTOR3(m_pos.x + 20.0f,m_pos.y + 80,m_pos.z))			// 箱生成位置
#define BLOCK_CREATE_LEFTPOS	(D3DXVECTOR3(m_pos.x - 20.0f,m_pos.y + 80,m_pos.z))			// 箱生成位置
#define EFFECT_RIGHTPOS			(D3DXVECTOR3(m_pos.x + 20.0f,m_pos.y + 80,m_pos.z - 15.0f))	// 箱生成位置
#define EFFECT_LEFTPOS			(D3DXVECTOR3(m_pos.x - 20.0f,m_pos.y + 80,m_pos.z - 15.0f))	// 箱生成位置
#define RELAESE_POS				(D3DXVECTOR3(BlockPos.x,BlockPos.y,BlockPos.z - 15.0f))		// 破棄するブロックの位置
#define DEAD_POS				(D3DXVECTOR3(ObjPos.x,ObjPos.y + 15.0f,ObjPos.z - 15.0f))	// エフェクト位置
#define RESPOWN_POS				(D3DXVECTOR3(m_pos.x,m_pos.y + 30.0f,m_pos.z - 15.0f))		// エフェクト位置
#define BLOCK_ROT				(D3DXVECTOR3(0.0f,0.0f,0.0f))								// 箱の向き
#define BLOCK_SIZE				(D3DXVECTOR3(30.0f,30.0f,30.0f))							// 箱のサイズ
#define MOVE_VALUE				(D3DXVECTOR3(2.0f,2.0f,2.0f))								// 移動量
#define RIGHT_ROT				(D3DXVECTOR3(0.0f,D3DXToRadian(270.0f),0.0f))				// 向き
#define LEFT_ROT				(D3DXVECTOR3(0.0f,D3DXToRadian(90.0f),0.0f))				// 向き
#define GAGE_POS				(D3DXVECTOR3(400.0f,50.0f,0.0f))							// ゲージの位置
#define MIN_BLOCK_NUM			(0)															// ブロックの最小数
#define ARRAY_FIRST_NUM			(0)															// 配列の先頭
#define ARRAY_MOVE_NUMBER		(1)															// 配列の移動
#define ARRAY_SUB_VALUE			(1)															// 配列に合わせるための値
#define DEVIDE_VALUE			(2.0f)														// 割る数
#define MOVE_DEVIDE				(1.5f)														// 移動の割る数
#define PARENT_NUMBER			(-1)														// 親の数値
#define ROT_MOVE				(0.2f)														// 向きの移動
#define POW_VALUE				(2.0f)														// 二乗
#define MIN_MOVE_VALUE			(0.0f)														// 移動量の最小値
#define GRAVITY_VALUE			(-1.3f)														// 重力
#define JUMP_VALUE				(17.0f)														// ジャンプ量
#define JUMP_VALUE_2			(0.01f)														// ジャンプ量
#define DEAD_ZONE_MIN			(0)															// スティックのデッドゾーン最小値
#define MAGIC_MOTION_COUNT		(30)														// 魔法のモーションカウント
#define MAX_LIFE				(100)														// ライフの最大値
#define MIN_LIFE				(0)															// ライフの最小値
// 魔法の位置
#define MAGIC_POS				(D3DXVECTOR3(m_pModel[PARTS_DOWN_ARM_L]->GetMtxWorld()._41,m_pModel[PARTS_DOWN_ARM_L]->GetMtxWorld()._42,m_pModel[PARTS_DOWN_ARM_L]->GetMtxWorld()._43))
#define MAGIC_MOVE_RIGHT		(D3DXVECTOR3(2.5f,0.0f,0.0f))						// 魔法の移動量
#define MAGIC_MOVE_LEFT			(D3DXVECTOR3(-2.5f,0.0f,0.0f))						// 魔法の移動量
// パーティクルエミッター位置
#define EMITTER_POS_RIGHT		(D3DXVECTOR3(m_pModel[PARTS_DOWN_ARM_R]->GetMtxWorld()._41,m_pModel[PARTS_DOWN_ARM_R]->GetMtxWorld()._42,m_pModel[PARTS_DOWN_ARM_R]->GetMtxWorld()._43))
#define EMITTER_POS_LEFT		(D3DXVECTOR3(m_pModel[PARTS_DOWN_ARM_R]->GetMtxWorld()._41,m_pModel[PARTS_DOWN_ARM_R]->GetMtxWorld()._42,m_pModel[PARTS_DOWN_ARM_R]->GetMtxWorld()._43))
// 腰の位置
#define POS						(D3DXVECTOR3(m_pModel[PARTS_UNDER_BODY]->GetMtxWorld()._41,m_pModel[PARTS_UNDER_BODY]->GetMtxWorld()._42,m_pModel[PARTS_UNDER_BODY]->GetMtxWorld()._43))
#define MAGIC_UI_POS			(D3DXVECTOR3(m_pos.x, m_pos.y + 50.0f, m_pos.z - 20.0f))	// 魔法UIの位置
//******************************************************************************
// 静的メンバ変数
//******************************************************************************
LPD3DXMESH CPlayer::m_pMesh[PARTS_MAX] = {};
LPD3DXBUFFER CPlayer::m_pBuffMat[PARTS_MAX] = {};
DWORD CPlayer::m_nNumMat[PARTS_MAX] = {};
D3DXMATRIX CPlayer::m_mtxWorld[PARTS_MAX] = {};
int CPlayer::m_nldxModelParent[PARTS_MAX] = {};
char* CPlayer::m_apFileName[PARTS_MAX] = {
	UNDER_BODY,
	BODY,
	HEAD,
	SHOULDER_R,
	UP_ARM_R,
	DOWN_ARM_R,
	SHOULDER_L,
	UP_ARM_L,
	DOWN_ARM_L,
	THIGTS_R,
	KNEE_R,
	FOOT_R,
	THIGTS_L,
	KNEE_L,
	FOOT_L,
};
//******************************************************************************
// コンストラクタ
//******************************************************************************
CPlayer::CPlayer(int nPriority) : CScene(nPriority)
{
	m_pos					= INIT_D3DXVECTOR3;		
	m_posOld				= INIT_D3DXVECTOR3;
	m_RespawnPos			= INIT_D3DXVECTOR3;
	m_rot					= INIT_D3DXVECTOR3;		
	m_size					= INIT_D3DXVECTOR3;		
	m_move					= INIT_D3DXVECTOR3;		
	m_bAllMotion			= false;				
	m_pMotion				= NULL;					
	m_pBlock				= NULL;	
	m_pStoneBlock			= NULL;
	m_Blcok_Active			= BLOCK_ACTIVE_NONE;	
	m_nBlockNum				= INIT_INT;				
	m_nBlock_Select_Num		= INIT_INT;	
	m_nMotion_Count			= INIT_INT;
	m_nLife					= INIT_INT;
	m_bStick				= false;				
	m_Rot_State				= ROT_STATE_RIGHT;	
	m_MagicType				= MAGIC_TYPE_FIREBALL;
	m_Emitter_Type			= EMITTER_TYPE_NONE;
	m_bJump					= false;				
	m_bJumpValue			= false;
	m_bBlock_Move			= false;
	m_bMagic				= false;
	m_bParticle_Emitter		= false;
	m_bCollision			= false;
	m_bChange_MagicType		= false;
	m_bEnemyCreate			= false;
	m_bDash					= false;
	m_bEnd					= false;
	memset(m_pModel, NULL, sizeof(m_pModel));
	memset(m_apParticle_Emitter, NULL, sizeof(m_apParticle_Emitter));
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
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	// CPlayerのポインタ
	CPlayer *pPlayer = NULL;

	// NULLの場合
	if (pPlayer == NULL)
	{
		// メモリ確保
		pPlayer = new CPlayer;

		// NULLでない場合
		if (pPlayer != NULL)
		{
			// 情報設定
			pPlayer->SetPlayer(pos, rot, size);

			// 初期化
			pPlayer->Init();

			// ライフゲージ生成
			CLife_Gage::Create(GAGE_POS, pPlayer);
		}
	}
	// ポインタを返す
	return pPlayer;
}

//******************************************************************************
// 読み込み関数
//******************************************************************************
HRESULT CPlayer::Load(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// パーツ数分繰り返す
	for (int nCount = INIT_INT; nCount < PARTS_MAX; nCount++)
	{
		// Xファイルの読み込み
		D3DXLoadMeshFromX(m_apFileName[nCount],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_pBuffMat[nCount],
			NULL,
			&m_nNumMat[nCount],
			&m_pMesh[nCount]
		);
	}
	
	return S_OK;
}

//******************************************************************************
// 読み込み破棄関数
//******************************************************************************
void CPlayer::Unload(void)
{
	for (int nCount = INIT_INT; nCount < PARTS_MAX; nCount++)
	{
		// メッシュの破棄
		if (m_pMesh[nCount] != NULL)
		{
			m_pMesh[nCount]->Release();
			m_pMesh[nCount] = NULL;
		}

		// マテリアルの破棄
		if (m_pBuffMat[nCount] != NULL)
		{
			m_pBuffMat[nCount]->Release();
			m_pBuffMat[nCount] = NULL;
		}

		if (m_nNumMat[nCount] != NULL)
		{
			m_nNumMat[nCount] = NULL;
		}
	}
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CPlayer::Init(void)
{
	// Magic_UI生成
	CMagic_UI::Create();

	// ライフ代入
	m_nLife = MAX_LIFE;

	// モーションの生成
	m_pMotion = CMotion::Create();

	// モーションの読み込み
	m_pMotion->Load(LOAD_PLAYER_TEXT);
	m_pMotion->LoadMotion(MOTION_PLAYER_TEXT);

	// モーションの初期設定
	m_pMotion->SetMotion(CMotion::MOTION_IDLE);

	// パーツ数分繰り返す
	for (int nCount = INIT_INT; nCount < PARTS_MAX; nCount++)
	{
		// モデルの生成
		m_pModel[nCount] = CModel::Create();

		// ペアレントの受け取り
		m_nldxModelParent[nCount] = m_pMotion->GetParents(nCount);

		// モデルのバインド
		m_pModel[nCount]->BindModel(m_pMesh[nCount], m_pBuffMat[nCount], m_nNumMat[nCount], m_nldxModelParent[nCount]);

		// モデルのパーツごとの座標と回転を受け取る
		m_pModel[nCount]->SetModel(m_pMotion->GetPos(nCount), m_pMotion->GetRot(nCount) + m_pModel[nCount]->GetRot(), m_size);
	}

	// 座標、回転、サイズのセット
	m_pModel[PARTS_UNDER_BODY]->SetModel(m_pMotion->GetPos(PARTS_UNDER_BODY) + m_pos, m_pMotion->GetRot(PARTS_UNDER_BODY) + m_rot, m_size);

	return S_OK;
}

//******************************************************************************
// 終了関数
//******************************************************************************
void CPlayer::Uninit(void)
{
	// パーツ数分繰り返す
	for (int nCount = INIT_INT; nCount < PARTS_MAX; nCount++)
	{
		if (m_pModel[nCount] != NULL)
		{
			// モデルクラスの終了処理
			m_pModel[nCount]->Uninit();
			m_pModel[nCount] = NULL;
		}
	}
	// NULLチェック
	if (m_pMotion != NULL)
	{
		// モーションクラスの終了処理
		m_pMotion->Uninit();
		m_pMotion = NULL;
	}

	// リリース
	Release();
}

//******************************************************************************
// 更新関数
//******************************************************************************
void CPlayer::Update(void)
{
	//サウンド取得
	CSound * pSound = CManager::GetSound();

	// 位置代入
	m_posOld = m_pModel[PARTS_UNDER_BODY]->GetPos();

	// コントローラー取得
	CInputJoystick * pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 g_lpDIDevice = CInputJoystick::GetDevice();

	if (g_lpDIDevice != NULL)
	{
		g_lpDIDevice->Poll();
	}

	// モーションの更新処理
	m_pMotion->UpdateMotion();

	// 右向きの場合
	if (m_Rot_State == ROT_STATE_RIGHT)
	{
		// ブロックで何もしていない状態
		if (m_Blcok_Active == BLOCK_ACTIVE_NONE)
		{
			// 右向きの時ブロックを最も近いブロックを選択中にする処理
			RightSelectBlock();
		}
		// NULLでない場合
		if (m_pBlock != NULL)
		{
			// falseの場合
			if (m_bMagic == false)
			{
				// LTを押した場合
				if (g_lpDIDevice != NULL && pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_LT))
				{
					// 0に
					m_nBlock_Select_Num = MIN_BLOCK_NUM;

					// 選択中の状態に
					m_Blcok_Active = BLOCK_ACTIVE_SELECT;
				}
				// 選択中の状態の場合
				if (m_Blcok_Active == BLOCK_ACTIVE_SELECT)
				{
					// 箱の選択処理
					RightSelectionBlock();
				}

				// 箱の処理
				RightBlock();
			}
		}
	}
	// 左向きの場合
	if (m_Rot_State == ROT_STATE_LEFT)
	{
		// ブロックで何もしていない状態
		if (m_Blcok_Active == BLOCK_ACTIVE_NONE)
		{
			// 左向きの時ブロックを最も近いブロックを選択中にする処理
			LeftSelectBlock();
		}
		// NULLでない場合
		if (m_pBlock != NULL)
		{
			// falseの場合
			if (m_bMagic == false)
			{
				// LTを押した場合
				if (g_lpDIDevice != NULL && pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_LT))
				{
					// 0に
					m_nBlock_Select_Num = MIN_BLOCK_NUM;

					// 選択中の状態に
					m_Blcok_Active = BLOCK_ACTIVE_SELECT;
				}
				// 選択中の状態の場合
				if (m_Blcok_Active == BLOCK_ACTIVE_SELECT)
				{
					// 箱の選択処理
					LeftSelectionBlock();
				}

				// 箱の処理
				LeftBlock();
			}
		}
	}
	// Xボタンが押された場合
	if (g_lpDIDevice != NULL && pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_X))
	{
		// 生成音再生
		pSound->PlaySoundA(CSound::SOUND_LABEL_SE_BLOCK_CREATE);
		// ブロック生成
		Block_Create();
	}
	// ブロック選択中でない場合
	if (m_Blcok_Active != BLOCK_ACTIVE_SELECT)
	{
		// 魔法
		Magic();
	}

	// 移動処理
	Move();

	// パーツ数分回す
	for (int nCount = INIT_INT; nCount < PARTS_MAX; nCount++)
	{
		// モデルのパーツごとの座標と回転を受け取る
		m_pModel[nCount]->SetModel(m_pMotion->GetPos(nCount), m_pMotion->GetRot(nCount), m_size);
	}

	// 座標、回転、サイズのセット
	m_pModel[PARTS_UNDER_BODY]->SetModel(m_pMotion->GetPos(PARTS_UNDER_BODY) + m_pos, m_pMotion->GetRot(PARTS_UNDER_BODY) + m_rot, m_size);

	// 当たり判定
	Collision();
}

//******************************************************************************
// 描画関数
//******************************************************************************
void CPlayer::Draw(void)
{
	D3DXMATRIX mtxRot, mtxTrans;

	// パーツ数分繰り返す
	for (int nCount = INIT_INT; nCount < PARTS_MAX; nCount++)
	{
		//ワールドマトリクスの初期化
		D3DXMatrixIdentity(&m_mtxWorld[nCount]);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_mtxWorld[nCount], &m_mtxWorld[nCount], &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
		D3DXMatrixMultiply(&m_mtxWorld[nCount], &m_mtxWorld[nCount], &mtxTrans);

		// 親のモデルパーツ以外のペアレントをセット
		if (m_nldxModelParent[nCount] != PARENT_NUMBER)
		{
			m_pModel[nCount]->SetParent(m_pModel[m_nldxModelParent[nCount]]);
		}

		// モデルクラスの描画処理
		m_pModel[nCount]->Draw();
	}
}
//******************************************************************************
// ヒット
//******************************************************************************
void CPlayer::Hit(int nLife)
{
	// ライフ減算
	m_nLife -= nLife;

	// 0以下になった場合
	if (m_nLife <= MIN_LIFE)
	{
		//サウンド取得
		CSound * pSound = CManager::GetSound();

		// 体力を最小値に
		m_nLife = MIN_LIFE;

		// リスポーン音再生
		pSound->PlaySoundA(CSound::SOUND_LABEL_SE_RESPAWN);

		// リスポーン位置に
		m_pos = m_RespawnPos;

		// エフェクト生成
		CParticle_Effect::Create(RESPOWN_POS, CParticle_Effect::TYPE_STAR_EFFECT2);
	}
}
//******************************************************************************
// 情報設定
//******************************************************************************
void CPlayer::SetPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 rot ,D3DXVECTOR3 size)
{
	m_pos			= pos;
	m_RespawnPos	= pos;
	m_rot			= rot;
	m_size			= size;

	// オブジェクトタイプ設定
	SetObjType(OBJTYPE_PLAYER);
}
//******************************************************************************
// パーツの位置取得
//******************************************************************************
D3DXMATRIX CPlayer::GetMtxWorld(PLAYER_PARTS Parts)
{
	return m_pModel[Parts]->GetMtxWorld();
}
//******************************************************************************
// 箱の選択
//******************************************************************************
void CPlayer::RightSelectBlock(void)
{
	// カメラの位置取得
	D3DXVECTOR3 CameraPos = CManager::GetCamera()->GetPos();

	// CSceneのポインタ
	CScene *pScene = NULL;

	// 箱
	do
	{
		// オブジェタイプが敵の場合
		pScene = GetScene(OBJTYPE_BLOCK);

		// NULLの場合
		if (pScene != NULL)
		{
			// オブジェクトタイプ取得
			OBJTYPE objType = pScene->GetObjType();
			// オブジェクトタイプがBLOCKの場合
			if (objType == OBJTYPE_BLOCK)
			{
				// 座標とサイズ取得
				D3DXVECTOR3 BlockPos = ((CBlock*)pScene)->GetPos();

				// 範囲内の場合
				if (BlockPos.x < CameraPos.x + SCREEN_WIDTH / CAMERA_POS_DEVIDE3 && BlockPos.x > CameraPos.x - SCREEN_WIDTH / CAMERA_POS_DEVIDE3)
				{
					// プレイヤーが正面を向いていて箱の位置が前にある場合
					if (m_pos.x < BlockPos.x)
					{
						// インクリメント
						m_nBlockNum++;
					}
					// プレイヤーが正面を向いていて箱の位置が前後ろにある場合
					if (m_pos.x > BlockPos.x)
					{
						((CBlock*)pScene)->UnSelected();
					}
				}
			}
		}
	} while (pScene != NULL);

	// ブロック数が0より多い場合
	if (m_nBlockNum > MIN_BLOCK_NUM)
	{
		// NULLに
		CBlock **apBlock = NULL;

		// NULLの場合
		if (apBlock == NULL)
		{
			// メモリ確保
			apBlock = new CBlock*[m_nBlockNum];

			// 最小数に
			m_nBlockNum = MIN_BLOCK_NUM;

			// NULLでない場合
			if (apBlock != NULL)
			{
				do
				{
					// オブジェタイプが敵の場合
					pScene = GetScene(OBJTYPE_BLOCK);
					// NULLでない場合
					if (pScene != NULL)
					{
						// オブジェクトタイプ取得
						OBJTYPE objType = pScene->GetObjType();

						// オブジェクトタイプがBLOCKの場合
						if (objType == OBJTYPE_BLOCK)
						{
							// 座標とサイズ取得
							D3DXVECTOR3 BlockPos = ((CBlock*)pScene)->GetPos();

							// 範囲内の場合
							if (BlockPos.x < CameraPos.x + SCREEN_WIDTH / CAMERA_POS_DEVIDE3 && BlockPos.x > CameraPos.x - SCREEN_WIDTH / CAMERA_POS_DEVIDE3)
							{
								// プレイヤーが右を向いていて箱の位置が前にある場合
								if (m_pos.x < BlockPos.x)
								{
									// ポインタ代入
									apBlock[m_nBlockNum] = (CBlock*)pScene;

									// インクリメント
									m_nBlockNum++;
								}
							}
						}
					}
				} while (pScene != NULL);

				// floatのポインタ
				float *anLength = NULL;

				// NULLの場合
				if (anLength == NULL)
				{
					// メモリ確保
					anLength = new float[m_nBlockNum];
					// NULLでない場合
					if (anLength != NULL)
					{
						// ブロック数分回す
						for (int nCnt = INIT_INT; nCnt < m_nBlockNum; nCnt++)
						{
							// 位置座標
							D3DXVECTOR3 BlockPos = apBlock[nCnt]->GetPos();
							// プレイヤーとの距離
							anLength[nCnt] = sqrtf(powf(m_pos.x - BlockPos.x, POW_VALUE) + powf(m_pos.y - BlockPos.y, POW_VALUE));
						}

						// 配列の先頭
						int nFirst_Array;

						// 最小値
						int nMin_Length;

						// 一時保存
						float fArray_Move;

						// 一時保存
						CBlock *pBlock_Save;

						// ブロック数分回す
						for (nFirst_Array = INIT_INT; nFirst_Array < m_nBlockNum - ARRAY_MOVE_NUMBER; nFirst_Array++)
						{
							// 配列の先頭を最小値に
							nMin_Length = nFirst_Array;

							// 比較
							for (int nCnt = nFirst_Array + ARRAY_MOVE_NUMBER; nCnt < m_nBlockNum; nCnt++)
							{
								// 距離が最小値より近い場合
								if (anLength[nCnt] < anLength[nMin_Length])
								{
									// 代入
									nMin_Length = nCnt;
								}
							}
							// 先頭の配列の値をを保存
							fArray_Move = anLength[nFirst_Array];
							pBlock_Save = apBlock[nFirst_Array];

							// 先頭の配列に最小値代入
							anLength[nFirst_Array] = anLength[nMin_Length];
							apBlock[nFirst_Array] = apBlock[nMin_Length];

							// 最小値に元の先頭の値を代入
							anLength[nMin_Length] = fArray_Move;
							apBlock[nMin_Length] = pBlock_Save;
						}
					}
					// メモリ破棄
					delete[]anLength;

					// NULLに
					anLength = NULL;
				}
				// 0番目以外未選択状態に
				for (int nCnt = INIT_INT; nCnt < m_nBlockNum; nCnt++)
				{
					// 未選択状態に
					apBlock[nCnt]->UnSelected();
				}

				// 配列の先頭を代入
				m_pBlock = apBlock[ARRAY_FIRST_NUM];

			}
			// メモリ破棄
			delete[]apBlock;

			// NULLに
			apBlock = NULL;
		}
	}
	// 最小数に
	m_nBlockNum = MIN_BLOCK_NUM;
}
//******************************************************************************
// ブロック処理関数
//******************************************************************************
void CPlayer::RightBlock(void)
{
	// カメラの位置取得
	D3DXVECTOR3 CameraPos = CManager::GetCamera()->GetPos();

	// コントローラー取得
	DIJOYSTATE js;
	CInputJoystick * pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 g_lpDIDevice = CInputJoystick::GetDevice();

	if (g_lpDIDevice != NULL)
	{
		g_lpDIDevice->Poll();
		g_lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}

	// NULLでない場合
	if (m_pBlock != NULL)
	{
		// 箱の位置取得
		D3DXVECTOR3 BlockPos = m_pBlock->GetPos();

		// 範囲内の場合
		if (BlockPos.x < CameraPos.x + SCREEN_WIDTH / CAMERA_POS_DEVIDE3 && BlockPos.x > CameraPos.x - SCREEN_WIDTH / CAMERA_POS_DEVIDE3)
		{
			// プレイヤーが右を向いていて箱の位置が前にある場合
			if (m_pos.x < BlockPos.x)
			{
				// 選択中の場合
				m_pBlock->Selecting();

				// 生成時の場合
				if (m_Blcok_Active == BLOCK_ACTIVE_CREATE)
				{
					// trueに
					m_pBlock->SetbMove(true);

					// 移動する処理
					m_pBlock->Create_Move();

					// 放射体生成
					Emitter_Create(EMITTER_TYPE_STAR);
				}
			}
			// RTを押した場合
			if (pInputJoystick->GetJoystickPress(CInputJoystick::JS_RT))
			{
				// 選択状態以外の場合
				if (m_Blcok_Active != BLOCK_ACTIVE_SELECT)
				{
					// 移動の判定設定
					m_pBlock->SetbMove(true);

					// 移動状態に
					m_Blcok_Active = BLOCK_ACTIVE_MOVE;

					// ブロックの移動
					m_pBlock->Move();
				}
				// falseの場合
				if (m_bBlock_Move == false)
				{
					// プレイヤーより左にある場合
					if (m_pos.x > BlockPos.x)
					{
						m_Rot_State = ROT_STATE_LEFT;
					}
				}
				// trueの場合
				if (m_bBlock_Move == true)
				{
					// プレイヤーより左にある場合
					if (m_pos.x > BlockPos.x)
					{
						// 移動の判定設定
						m_pBlock->SetbMove(false);

						// ブロックで行動してない状態に
						m_Blcok_Active = BLOCK_ACTIVE_NONE;

						// NULLに
						m_pBlock = NULL;
					}
				}
			}
			else
			{
				// 移動の判定設定
				m_pBlock->SetbEmitter(false);

				// 移動の判定設定
				m_pBlock->SetbMove(false);

				// プレイヤーが右を向いていて箱の位置が後ろにある場合
				if (m_pos.x > BlockPos.x)
				{
					// 選択外に
					m_pBlock->UnSelected();

					// ブロックを通常状態に
					m_Blcok_Active = BLOCK_ACTIVE_NONE;
				}
			}
		}
		// 範囲外の場合
		if (BlockPos.x > CameraPos.x + SCREEN_WIDTH / CAMERA_POS_DEVIDE3 || BlockPos.x < CameraPos.x - SCREEN_WIDTH / CAMERA_POS_DEVIDE3)
		{
			// 放射体の判定設定
			m_pBlock->SetbEmitter(false);

			// 移動の判定設定
			m_pBlock->SetbMove(false);

			// 選択外に
			m_pBlock->UnSelected();

			// ブロックを通常状態に
			m_Blcok_Active = BLOCK_ACTIVE_NONE;

			// NULLに
			m_pBlock = NULL;
		}
	}
}
//******************************************************************************
// 動かすブロックを選択中
//******************************************************************************
void CPlayer::RightSelectionBlock(void)
{
	//サウンド取得
	CSound * pSound = CManager::GetSound();

	// カメラの位置取得
	D3DXVECTOR3 CameraPos = CManager::GetCamera()->GetPos();

	// コントローラー取得
	DIJOYSTATE js;
	js.lY = INIT_INT;
	js.lX = INIT_INT;
	CInputJoystick * pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 g_lpDIDevice = CInputJoystick::GetDevice();

	if (g_lpDIDevice != NULL)
	{
		g_lpDIDevice->Poll();
		g_lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}

	// CSceneのポインタ
	CScene *pScene = NULL;

	// 箱
	do
	{
		// オブジェタイプが敵の場合
		pScene = GetScene(OBJTYPE_BLOCK);

		// NULLの場合
		if (pScene != NULL)
		{
			// オブジェクトタイプ取得
			OBJTYPE objType = pScene->GetObjType();

			// オブジェクトタイプがBLOCKの場合
			if (objType == OBJTYPE_BLOCK)
			{
				// 座標とサイズ取得
				D3DXVECTOR3 BlockPos = ((CBlock*)pScene)->GetPos();

				// 範囲内の場合
				if (BlockPos.x < CameraPos.x + SCREEN_WIDTH / CAMERA_POS_DEVIDE3 && BlockPos.x > CameraPos.x - SCREEN_WIDTH / CAMERA_POS_DEVIDE3)
				{
					// プレイヤーが正面を向いていて箱の位置が前にある場合
					if (m_pos.x < BlockPos.x)
					{
						// インクリメント
						m_nBlockNum++;
					}
					// プレイヤーが正面を向いていて箱の位置が前後ろにある場合
					if (m_pos.x > BlockPos.x)
					{
						((CBlock*)pScene)->UnSelected();
					}
				}
			}
		}
	} while (pScene != NULL);

	// 0より多い場合
	if (m_nBlockNum > MIN_BLOCK_NUM)
	{
		// NULLに
		CBlock **apBlock = NULL;

		// NULLの場合
		if (apBlock == NULL)
		{
			// メモリ確保
			apBlock = new CBlock*[m_nBlockNum];

			// 最小数に
			m_nBlockNum = MIN_BLOCK_NUM;

			// NULLでない場合
			if (apBlock != NULL)
			{
				do
				{
					// オブジェタイプが敵の場合
					pScene = GetScene(OBJTYPE_BLOCK);

					// NULLでない場合
					if (pScene != NULL)
					{
						// オブジェクトタイプ取得
						OBJTYPE objType = pScene->GetObjType();

						// オブジェクトタイプがBLOCKの場合
						if (objType == OBJTYPE_BLOCK)
						{
							// 座標とサイズ取得
							D3DXVECTOR3 BlockPos = ((CBlock*)pScene)->GetPos();

							// 範囲内の場合
							if (BlockPos.x < CameraPos.x + SCREEN_WIDTH / CAMERA_POS_DEVIDE3 && BlockPos.x > CameraPos.x - SCREEN_WIDTH / CAMERA_POS_DEVIDE3)
							{
								// プレイヤーが右を向いていて箱の位置が前にある場合
								if (m_pos.x < BlockPos.x)
								{
									// ポインタ代入
									apBlock[m_nBlockNum] = (CBlock*)pScene;

									// インクリメント
									m_nBlockNum++;
								}
							}
						}
					}
				} while (pScene != NULL);

				// floatのポインタ
				float *anLength = NULL;

				// NULLの場合
				if (anLength == NULL)
				{
					// メモリ確保
					anLength = new float[m_nBlockNum];

					// NULLでない場合
					if (anLength != NULL)
					{
						// ブロック数分回す
						for (int nCnt = INIT_INT; nCnt < m_nBlockNum; nCnt++)
						{
							// 位置座標
							D3DXVECTOR3 BlockPos = apBlock[nCnt]->GetPos();

							// プレイヤーとの距離
							anLength[nCnt] = sqrtf(powf(m_pos.x - BlockPos.x, POW_VALUE));
						}

						// 配列の先頭
						int nFirst_Array;

						// 最小値
						int nMin_Length;

						// 一時保存
						float fArray_Move;

						// 一時保存
						CBlock *pBlock_Save;

						// ブロック数分回す
						for (nFirst_Array = INIT_INT; nFirst_Array < m_nBlockNum - ARRAY_MOVE_NUMBER; nFirst_Array++)
						{
							// 配列の先頭を最小値に
							nMin_Length = nFirst_Array;

							// 比較
							for (int nCnt = nFirst_Array + ARRAY_MOVE_NUMBER; nCnt < m_nBlockNum; nCnt++)
							{
								// 距離が最小値より近い場合
								if (anLength[nCnt] > anLength[nMin_Length])
								{
									// 代入
									nMin_Length = nCnt;
								}
							}
							// 先頭の配列の値をを保存
							fArray_Move = anLength[nFirst_Array];
							pBlock_Save = apBlock[nFirst_Array];

							// 先頭の配列に最小値代入
							anLength[nFirst_Array] = anLength[nMin_Length];
							apBlock[nFirst_Array] = apBlock[nMin_Length];

							// 最小値に元の先頭の値を代入
							anLength[nMin_Length] = fArray_Move;
							apBlock[nFirst_Array] = pBlock_Save;
						}
					}
					// メモリ破棄
					delete[]anLength;

					// NULLに
					anLength = NULL;
				}
				// 0番目以外未選択状態に
				for (int nCnt = INIT_INT; nCnt < m_nBlockNum; nCnt++)
				{
					// 未選択状態に
					apBlock[nCnt]->PlayerSelection();
				}
				// 選択終了状態でない場合
				if (g_lpDIDevice != NULL && pInputJoystick->GetJoystickRelease(CInputJoystick::JS_LT))
				{
					// 0番目以外未選択状態に
					for (int nCnt = INIT_INT; nCnt < m_nBlockNum; nCnt++)
					{
						// 選択終了の色に
						apBlock[nCnt]->UnSelected();
					}

					// 選択した状態
					m_Blcok_Active = BLOCK_ACTIVE_SELECTED;
				}
				// 色選択中の色に
				apBlock[m_nBlock_Select_Num]->Selecting();

				// 選択しているブロックの配列を代入
				m_pBlock = apBlock[m_nBlock_Select_Num];
			}
			// メモリ破棄
			delete[]apBlock;

			// NULLに
			apBlock = NULL;
		}
	}

	// 数保存
	m_nSelect_Save_Num = m_nBlockNum;

	// 最小数に
	m_nBlockNum = MIN_BLOCK_NUM;

	if (g_lpDIDevice != NULL)
	{
		// falseの場合
		if (m_bStick == false)
		{
			// 右スティックを左に倒す
			
			if (js.lZ <= -STICK_REACTION)
			{
				// 0番目の場合
				if (m_nBlock_Select_Num > MIN_BLOCK_NUM)
				{
					// 選択音再生
					pSound->PlaySoundA(CSound::SOUND_LABEL_SE_SELECT);

					// デクリメント
					m_nBlock_Select_Num--;
				}
				// 0番目の場合
				if (m_nBlock_Select_Num == MIN_BLOCK_NUM)
				{
					// ブロックの最大値にする
					m_nBlock_Select_Num = MIN_BLOCK_NUM;
				}

				// trueに
				m_bStick = true;
			}
			// 右スティックを右に倒す
			if (js.lZ >= STICK_REACTION)
			{
				// 最大値の場合
				if (m_nBlock_Select_Num < m_nSelect_Save_Num - ARRAY_SUB_VALUE)
				{
					// 選択音再生
					pSound->PlaySoundA(CSound::SOUND_LABEL_SE_SELECT);

					// インクリメント
					m_nBlock_Select_Num++;
				}
				// 最大値の場合
				if (m_nBlock_Select_Num >= m_nSelect_Save_Num - ARRAY_SUB_VALUE)
				{
					// 0番目に設定
					m_nBlock_Select_Num = m_nSelect_Save_Num - ARRAY_SUB_VALUE;
				}

				// trueに
				m_bStick = true;
			}
		}
		// trueの場合
		if (m_bStick == true)
		{
			// -500より大きく0より小さい場合
			if (js.lZ > -STICK_REACTION && js.lZ <= DEAD_ZONE_MIN)
			{
				m_bStick = false;
			}
			// 500より小さく0より大きい場合
			if (js.lZ < STICK_REACTION && js.lZ >= DEAD_ZONE_MIN)
			{
				m_bStick = false;
			}
		}
		// 0より低い場合
		if (m_nBlock_Select_Num < MIN_BLOCK_NUM)
		{
			// 0に設定
			m_nBlock_Select_Num = MIN_BLOCK_NUM;
		}
		// 箱の数より大きい場合
		if (m_nBlock_Select_Num > m_nSelect_Save_Num)
		{
			// 箱の数と同じにする
			m_nBlock_Select_Num = m_nSelect_Save_Num;
		}
	}
}
//******************************************************************************
// 左箱の選択
//******************************************************************************
void CPlayer::LeftSelectBlock(void)
{
	// カメラの位置取得
	D3DXVECTOR3 CameraPos = CManager::GetCamera()->GetPos();

	// CSceneのポインタ
	CScene *pScene = NULL;

	// 箱
	do
	{
		// オブジェタイプが敵の場合
		pScene = GetScene(OBJTYPE_BLOCK);

		// NULLの場合
		if (pScene != NULL)
		{
			// オブジェクトタイプ取得
			OBJTYPE objType = pScene->GetObjType();

			// オブジェクトタイプがBLOCKの場合
			if (objType == OBJTYPE_BLOCK)
			{
				// 座標とサイズ取得
				D3DXVECTOR3 BlockPos = ((CBlock*)pScene)->GetPos();

				// 範囲内の場合
				if (BlockPos.x < CameraPos.x + SCREEN_WIDTH / CAMERA_POS_DEVIDE3 && BlockPos.x > CameraPos.x - SCREEN_WIDTH / CAMERA_POS_DEVIDE3)
				{
					// プレイヤーが左を向いていて箱の位置が前にある場合
					if (m_pos.x > BlockPos.x)
					{
						// インクリメント
						m_nBlockNum++;
					}
					// プレイヤーが左を向いていて箱の位置が前後ろにある場合
					if (m_pos.x < BlockPos.x)
					{
						((CBlock*)pScene)->UnSelected();
					}
				}
			}
		}
		// NULLになるまで繰り返す
	} while (pScene != NULL);

	// ブロック数が0より多い場合
	if (m_nBlockNum > MIN_BLOCK_NUM)
	{
		// NULLに
		CBlock **apBlock = NULL;

		// NULLの場合
		if (apBlock == NULL)
		{
			// メモリ確保
			apBlock = new CBlock*[m_nBlockNum];

			// 最小数に
			m_nBlockNum = MIN_BLOCK_NUM;

			// NULLでない場合
			if (apBlock != NULL)
			{
				do
				{
					// オブジェタイプが敵の場合
					pScene = GetScene(OBJTYPE_BLOCK);

					// NULLでない場合
					if (pScene != NULL)
					{
						// オブジェクトタイプ取得
						OBJTYPE objType = pScene->GetObjType();

						// オブジェクトタイプがBLOCKの場合
						if (objType == OBJTYPE_BLOCK)
						{
							// 座標とサイズ取得
							D3DXVECTOR3 BlockPos = ((CBlock*)pScene)->GetPos();

							// 範囲内の場合
							if (BlockPos.x < CameraPos.x + SCREEN_WIDTH / CAMERA_POS_DEVIDE3 && BlockPos.x > CameraPos.x - SCREEN_WIDTH / CAMERA_POS_DEVIDE3)
							{
								// プレイヤーが左を向いていて箱の位置が前にある場合
								if (m_pos.x > BlockPos.x)
								{
									// ポインタ代入
									apBlock[m_nBlockNum] = (CBlock*)pScene;

									// インクリメント
									m_nBlockNum++;
								}
							}
						}
					}
				} while (pScene != NULL);

				// floatのポインタ
				float *anLength = NULL;

				// NULLの場合
				if (anLength == NULL)
				{
					// メモリ確保
					anLength = new float[m_nBlockNum];
					// NULLでない場合
					if (anLength != NULL)
					{
						// ブロック数分回す
						for (int nCnt = INIT_INT; nCnt < m_nBlockNum; nCnt++)
						{
							// 位置座標
							D3DXVECTOR3 BlockPos = apBlock[nCnt]->GetPos();

							// プレイヤーとの距離
							anLength[nCnt] = sqrtf(powf(m_pos.x - BlockPos.x, POW_VALUE));
						}

						// 配列の先頭
						int nFirst_Array;

						// 最小値
						int nMin_Length;

						// 一時保存
						float fArray_Move;

						// 一時保存
						CBlock *pBlock_Save;

						// ブロック数分回す
						for (nFirst_Array = INIT_INT; nFirst_Array < m_nBlockNum - ARRAY_MOVE_NUMBER; nFirst_Array++)
						{
							// 配列の先頭を最小値に
							nMin_Length = nFirst_Array;

							// 比較
							for (int nCnt = nFirst_Array + ARRAY_MOVE_NUMBER; nCnt < m_nBlockNum; nCnt++)
							{
								// 距離が最小値より近い場合
								if (anLength[nCnt] < anLength[nMin_Length])
								{
									// 代入
									nMin_Length = nCnt;
								}
							}
							// 先頭の配列の値をを保存
							fArray_Move = anLength[nFirst_Array];
							pBlock_Save = apBlock[nFirst_Array];

							// 先頭の配列に最小値代入
							anLength[nFirst_Array] = anLength[nMin_Length];
							apBlock[nFirst_Array] = apBlock[nMin_Length];

							// 最小値に元の先頭の値を代入
							anLength[nMin_Length] = fArray_Move;
							apBlock[nMin_Length] = pBlock_Save;
						}
					}
					// メモリ破棄
					delete[]anLength;

					// NULLに
					anLength = NULL;
				}
				// 0番目以外未選択状態に
				for (int nCnt = INIT_INT; nCnt < m_nBlockNum; nCnt++)
				{
					// 未選択状態に
					apBlock[nCnt]->UnSelected();
				}

				// 配列の先頭を代入
				m_pBlock = apBlock[ARRAY_FIRST_NUM];

			}
			// メモリ破棄
			delete[]apBlock;

			// NULLに
			apBlock = NULL;
		}
	}
	// 最小数に
	m_nBlockNum = MIN_BLOCK_NUM;
}
//******************************************************************************
// ブロック処理関数
//******************************************************************************
void CPlayer::LeftBlock(void)
{
	// カメラの位置取得
	D3DXVECTOR3 CameraPos = CManager::GetCamera()->GetPos();

	// コントローラー取得
	DIJOYSTATE js;
	CInputJoystick * pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 g_lpDIDevice = CInputJoystick::GetDevice();

	if (g_lpDIDevice != NULL)
	{
		g_lpDIDevice->Poll();
		g_lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}

	// NULLでない場合
	if (m_pBlock != NULL)
	{
		// 箱の位置取得
		D3DXVECTOR3 BlockPos = m_pBlock->GetPos();

		// 範囲内の場合
		if (BlockPos.x < CameraPos.x + SCREEN_WIDTH / CAMERA_POS_DEVIDE3 && BlockPos.x > CameraPos.x - SCREEN_WIDTH / CAMERA_POS_DEVIDE3)
		{
			// プレイヤーが左を向いていて箱の位置が前にある場合
			if (m_pos.x > BlockPos.x)
			{
				// 選択中の場合
				m_pBlock->Selecting();

				// 生成時の場合
				if (m_Blcok_Active == BLOCK_ACTIVE_CREATE)
				{
					// trueに
					m_pBlock->SetbMove(true);

					// 移動する処理
					m_pBlock->Create_Move();

					// 放射体生成
					Emitter_Create(EMITTER_TYPE_STAR);
				}
			}
			// RTを押した場合
			if (pInputJoystick->GetJoystickPress(CInputJoystick::JS_RT))
			{
				// 選択状態以外の場合
				if (m_Blcok_Active != BLOCK_ACTIVE_SELECT)
				{
					// 移動の判定設定
					m_pBlock->SetbMove(true);

					// 移動状態に
					m_Blcok_Active = BLOCK_ACTIVE_MOVE;

					// ブロックの移動
					m_pBlock->Move();
				}
				// falseの場合
				if (m_bBlock_Move == false)
				{
					// プレイヤーより右にある場合
					if (m_pos.x < BlockPos.x)
					{
						m_Rot_State = ROT_STATE_RIGHT;
					}
				}
				// trueの場合
				if (m_bBlock_Move == true)
				{
					// プレイヤーより左にある場合
					if (m_pos.x < BlockPos.x)
					{
						// 移動の判定設定
						m_pBlock->SetbMove(false);

						// ブロックで行動してない状態に
						m_Blcok_Active = BLOCK_ACTIVE_NONE;

						// NULLに
						m_pBlock = NULL;
					}
				}
			}
			else
			{
				// 放射体の判定設定
				m_pBlock->SetbEmitter(false);

				// 移動の判定設定
				m_pBlock->SetbMove(false);

				// プレイヤーが左を向いていて箱の位置が後ろにある場合
				if (m_pos.x < BlockPos.x)
				{
					// 選択外に
					m_pBlock->UnSelected();

					// ブロックを移動状態に
					m_Blcok_Active = BLOCK_ACTIVE_NONE;
				}
			}
		}
		// 範囲外の場合
		if (BlockPos.x > CameraPos.x + SCREEN_WIDTH / CAMERA_POS_DEVIDE3 || BlockPos.x < CameraPos.x - SCREEN_WIDTH / CAMERA_POS_DEVIDE3)
		{
			// 放射体の判定設定
			m_pBlock->SetbEmitter(false);

			// 移動の判定設定
			m_pBlock->SetbMove(false);

			// 選択外に
			m_pBlock->UnSelected();

			// ブロックを通常状態に
			m_Blcok_Active = BLOCK_ACTIVE_NONE;

			// NULLに
			m_pBlock = NULL;
		}
	}
}
//******************************************************************************
// 動かすブロックを選択中
//******************************************************************************
void CPlayer::LeftSelectionBlock(void)
{
	//サウンド取得
	CSound * pSound = CManager::GetSound();

	// コントローラー取得
	DIJOYSTATE js;
	// 初期化
	js.lY = DEAD_ZONE_MIN;
	js.lX = DEAD_ZONE_MIN;
	CInputJoystick * pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 g_lpDIDevice = CInputJoystick::GetDevice();

	if (g_lpDIDevice != NULL)
	{
		g_lpDIDevice->Poll();
		g_lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}

	// カメラの位置取得
	D3DXVECTOR3 CameraPos = CManager::GetCamera()->GetPos();

	// CSceneのポインタ
	CScene *pScene = NULL;

	// ブロック
	do
	{
		// オブジェタイプが敵の場合
		pScene = GetScene(OBJTYPE_BLOCK);

		// NULLの場合
		if (pScene != NULL)
		{
			// オブジェクトタイプ取得
			OBJTYPE objType = pScene->GetObjType();

			// オブジェクトタイプがBLOCKの場合
			if (objType == OBJTYPE_BLOCK)
			{
				// 座標とサイズ取得
				D3DXVECTOR3 BlockPos = ((CBlock*)pScene)->GetPos();

				// 範囲内の場合
				if (BlockPos.x < CameraPos.x + SCREEN_WIDTH / CAMERA_POS_DEVIDE3 && BlockPos.x > CameraPos.x - SCREEN_WIDTH / CAMERA_POS_DEVIDE3)
				{
					// プレイヤーが正面を向いていて箱の位置が前にある場合
					if (m_pos.x > BlockPos.x)
					{
						// インクリメント
						m_nBlockNum++;
					}
					// プレイヤーが正面を向いていて箱の位置が前後ろにある場合
					if (m_pos.x < BlockPos.x)
					{
						((CBlock*)pScene)->UnSelected();
					}
				}
			}
		}
		// NULLになるまで繰り返す
	} while (pScene != NULL);

	// 0より多い場合
	if (m_nBlockNum > MIN_BLOCK_NUM)
	{
		// NULLに
		CBlock **apBlock = NULL;

		// NULLの場合
		if (apBlock == NULL)
		{
			// メモリ確保
			apBlock = new CBlock*[m_nBlockNum];

			// 最小数に
			m_nBlockNum = MIN_BLOCK_NUM;

			// NULLでない場合
			if (apBlock != NULL)
			{
				do
				{
					// オブジェタイプが敵の場合
					pScene = GetScene(OBJTYPE_BLOCK);

					// NULLでない場合
					if (pScene != NULL)
					{
						// オブジェクトタイプ取得
						OBJTYPE objType = pScene->GetObjType();

						// オブジェクトタイプがBLOCKの場合
						if (objType == OBJTYPE_BLOCK)
						{
							// 座標とサイズ取得
							D3DXVECTOR3 BlockPos = ((CBlock*)pScene)->GetPos();

							// 範囲内の場合
							if (BlockPos.x < CameraPos.x + SCREEN_WIDTH / CAMERA_POS_DEVIDE3 && BlockPos.x > CameraPos.x - SCREEN_WIDTH / CAMERA_POS_DEVIDE3)
							{
								// プレイヤーが左を向いていて箱の位置が前にある場合
								if (m_pos.x > BlockPos.x)
								{
									// ポインタ代入
									apBlock[m_nBlockNum] = (CBlock*)pScene;

									// インクリメント
									m_nBlockNum++;
								}
							}
						}
					}
					// NULLになるまで繰り返す
				} while (pScene != NULL);

				// floatのポインタ
				float *afLength = NULL;

				// NULLの場合
				if (afLength == NULL)
				{
					// メモリ確保
					afLength = new float[m_nBlockNum];

					// NULLでない場合
					if (afLength != NULL)
					{
						// ブロック数分回す
						for (int nCnt = INIT_INT; nCnt < m_nBlockNum; nCnt++)
						{
							// 位置座標
							D3DXVECTOR3 BlockPos = apBlock[nCnt]->GetPos();

							// プレイヤーとの距離
							afLength[nCnt] = sqrtf(powf(m_pos.x - BlockPos.x, POW_VALUE) + powf(m_pos.y - BlockPos.y, POW_VALUE));
						}

						// 配列の先頭
						int nFirst_Array;

						// 最小値
						int nMin_Length;

						// 一時保存
						float fArray_Move;

						// 一時保存
						CBlock *pBlock_Save;

						// ブロック数分回す
						for (nFirst_Array = INIT_INT; nFirst_Array < m_nBlockNum; nFirst_Array++)
						{
							// 配列の先頭を最小値に
							nMin_Length = nFirst_Array;

							// 比較
							for (int nCnt = nFirst_Array + ARRAY_MOVE_NUMBER; nCnt < m_nBlockNum; nCnt++)
							{
								// 距離が最小値より近い場合
								if (afLength[nCnt] > afLength[nMin_Length])
								{
									// 代入
									nMin_Length = nCnt;
								}
							}
							// 先頭の配列の値をを保存
							fArray_Move = afLength[nFirst_Array];
							pBlock_Save = apBlock[nFirst_Array];

							// 先頭の配列に最小値代入
							afLength[nFirst_Array] = afLength[nMin_Length];
							apBlock[nFirst_Array] = apBlock[nMin_Length];

							// 最小値に元の先頭の値を代入
							afLength[nMin_Length] = fArray_Move;
							apBlock[nFirst_Array] = pBlock_Save;
						}
					}
					// メモリ破棄
					delete[]afLength;

					// NULLに
					afLength = NULL;
				}
				// 0番目以外未選択状態に
				for (int nCnt = INIT_INT; nCnt < m_nBlockNum; nCnt++)
				{
					// 未選択状態に
					apBlock[nCnt]->PlayerSelection();
				}
				// 選択終了状態でない場合
				if (g_lpDIDevice != NULL && pInputJoystick->GetJoystickRelease(CInputJoystick::JS_LT))
				{
					// 0番目以外未選択状態に
					for (int nCnt = INIT_INT; nCnt < m_nBlockNum; nCnt++)
					{
						// 選択終了の色に
						apBlock[nCnt]->UnSelected();
					}

					// 選択した状態
					m_Blcok_Active = BLOCK_ACTIVE_SELECTED;
				}
				// 色選択中の色に
				apBlock[m_nBlockNum - ARRAY_SUB_VALUE - m_nBlock_Select_Num]->Selecting();

				// 選択しているブロックの配列を代入
				m_pBlock = apBlock[m_nBlockNum - ARRAY_SUB_VALUE - m_nBlock_Select_Num];
			}
			// メモリ破棄
			delete[]apBlock;

			// NULLに
			apBlock = NULL;
		}
	}

	// 数保存
	m_nSelect_Save_Num = m_nBlockNum;

	// 最小数に
	m_nBlockNum = MIN_BLOCK_NUM;

	if (g_lpDIDevice != NULL)
	{
		// falseの場合
		if (m_bStick == false)
		{
			// 右スティックを左に倒す
			if (js.lZ <= -STICK_REACTION)
			{
				// 最大値の場合
				if (m_nBlock_Select_Num < m_nSelect_Save_Num - ARRAY_SUB_VALUE)
				{
					// 選択音再生
					pSound->PlaySoundA(CSound::SOUND_LABEL_SE_SELECT);

					// インクリメント
					m_nBlock_Select_Num++;
				}
				// 最大値の場合
				if (m_nBlock_Select_Num >= m_nSelect_Save_Num - ARRAY_SUB_VALUE)
				{
					// 0番目に設定
					m_nBlock_Select_Num = m_nSelect_Save_Num - ARRAY_SUB_VALUE;
				}
				// trueに
				m_bStick = true;
			}
		// 右スティックを右に倒す
		if (js.lZ >= STICK_REACTION)
		{
				// 0番目の場合
				if (m_nBlock_Select_Num > MIN_BLOCK_NUM)
				{
					// 選択音再生
					pSound->PlaySoundA(CSound::SOUND_LABEL_SE_SELECT);

					// デクリメント
					m_nBlock_Select_Num--;
				}
				// 0番目の場合
				if (m_nBlock_Select_Num == MIN_BLOCK_NUM)
				{
					// ブロックの最大値にする
					m_nBlock_Select_Num = MIN_BLOCK_NUM;
				}
				// trueに
				m_bStick = true;
			}
		}
		// trueの場合
		if (m_bStick == true)
		{
			// -500より大きく0より小さい場合
			if (js.lZ > -STICK_REACTION && js.lZ <= DEAD_ZONE_MIN)
			{
				m_bStick = false;
			}
			// 500より小さく0より大きい場合
			if (js.lZ < STICK_REACTION && js.lZ >= DEAD_ZONE_MIN)
			{
				m_bStick = false;
			}
		}
		// 0より引く場合
		if (m_nBlock_Select_Num < MIN_BLOCK_NUM)
		{
			// 0に設定
			m_nBlock_Select_Num = MIN_BLOCK_NUM;
		}
		// 箱の数より大きい場合
		if (m_nBlock_Select_Num > m_nSelect_Save_Num)
		{
			// 箱の数と同じにする
			m_nBlock_Select_Num = m_nSelect_Save_Num;
		}
	}
}
//******************************************************************************
// ブロック生成関数
//******************************************************************************
void CPlayer::Block_Create(void)
{
	// 生成状態に
	m_Blcok_Active = BLOCK_ACTIVE_CREATE;

	// NULLの場合
	if (m_pStoneBlock == NULL)
	{
		// 右向きの場合
		if (m_Rot_State == ROT_STATE_RIGHT)
		{
			// エフェクト生
			CParticle_Effect::Create(EFFECT_RIGHTPOS, CParticle_Effect::TYPE_STAR_EFFECT);

			// 生成
			m_pStoneBlock = CStone_Block::Create(BLOCK_CREATE_RIGHTPOS, BLOCK_ROT, BLOCK_SIZE);
		}
		// 左向きの場合
		if (m_Rot_State == ROT_STATE_LEFT)
		{
			// エフェクト生
			CParticle_Effect::Create(EFFECT_LEFTPOS, CParticle_Effect::TYPE_STAR_EFFECT);

			// 生成
			m_pStoneBlock = CStone_Block::Create(BLOCK_CREATE_LEFTPOS, BLOCK_ROT, BLOCK_SIZE);
		}
		// 代入
		m_pBlock = m_pStoneBlock;
	}
	// NULLでない場合
	if (m_pStoneBlock != NULL)
	{
		// 位置取得
		D3DXVECTOR3 BlockPos = m_pStoneBlock->GetPos();

		// エフェクト生
		CParticle_Effect::Create(RELAESE_POS, CParticle_Effect::TYPE_STAR_EFFECT);

		// 破棄
		m_pStoneBlock->ReleaseBlock();

		// 右向きの場合
		if (m_Rot_State == ROT_STATE_RIGHT)
		{
			// エフェクト生
			CParticle_Effect::Create(EFFECT_RIGHTPOS, CParticle_Effect::TYPE_STAR_EFFECT);

			// 生成
			m_pStoneBlock = CStone_Block::Create(BLOCK_CREATE_RIGHTPOS, BLOCK_ROT, BLOCK_SIZE);
		}
		// 左向きの場合
		if (m_Rot_State == ROT_STATE_LEFT)
		{
			// エフェクト生
			CParticle_Effect::Create(EFFECT_LEFTPOS, CParticle_Effect::TYPE_STAR_EFFECT);

			// 生成
			m_pStoneBlock = CStone_Block::Create(BLOCK_CREATE_LEFTPOS, BLOCK_ROT, BLOCK_SIZE);
		}
		// 代入
		m_pBlock = m_pStoneBlock;
	}
}												   
//******************************************************************************
// 当たり判定処理関数
//******************************************************************************
void CPlayer::Collision(void)
{
	//サウンド取得
	CSound * pSound = CManager::GetSound();

	// 位置
	D3DXVECTOR3 pos = m_pModel[PARTS_UNDER_BODY]->GetPos();

	// ブロックとの当たり判定
	CScene *pScene = NULL;

	// ブロックとの当たり判定
	do
	{
		// オブジェタイプがブロックの場合
		pScene = GetScene(OBJTYPE_BLOCK);

		// NULLチェック
		if (pScene != NULL)
		{
			// オブジェタイプ取得
			OBJTYPE objType = pScene->GetObjType();

			// オブジェクトタイプが敵
			if (objType == OBJTYPE_BLOCK)
			{
				// 座標とサイズ取得
				D3DXVECTOR3 BlockPos = ((CBlock*)pScene)->GetPos();
				D3DXVECTOR3 BlockSize = ((CBlock*)pScene)->GetSize();

				 //どこの面に当たったか取得
				 //下
				if (CCollision::RectangleCollisionMove(pos, m_posOld, m_size, BlockPos, BlockSize) == CCollision::SURFACE_DOWN)
				{
					// 移動量0
					m_move.y = MIN_MOVE_VALUE;

					// 位置
					m_pos.y = (-BlockSize.y / DEVIDE_VALUE + BlockPos.y) - (m_size.y / DEVIDE_VALUE);

				}
				// 上
				else if (CCollision::RectangleCollisionMove(m_pos, m_posOld, m_size, BlockPos, BlockSize) == CCollision::SURFACE_UP)
				{
					// 移動量0
					m_move.y = MIN_MOVE_VALUE;

					// 位置
					m_pos.y = (BlockSize.y / DEVIDE_VALUE + BlockPos.y) - (m_size.y / DEVIDE_VALUE);

					// trueの場合
					if (m_bJump == true)
					{
						// falseに
						m_bJump = false;

						// falseに
						m_bJumpValue = false;
					}
				}
				// 左
				else if (CCollision::RectangleCollisionMove(pos, m_posOld, m_size, BlockPos, BlockSize) == CCollision::SURFACE_LEFT)
				{
					// 移動量0
					m_move.x = MIN_MOVE_VALUE;

					// 位置
					m_pos.x = (-BlockSize.x / DEVIDE_VALUE + BlockPos.x) - (m_size.x / DEVIDE_VALUE);

					// falseの場合
					if (m_bCollision == false)
					{
						// trueに
						m_bCollision = true;
					}
				}
				// 右
				else if (CCollision::RectangleCollisionMove(pos, m_posOld, m_size, BlockPos, BlockSize) == CCollision::SURFACE_RIGHT)
				{
					// 移動量0
					m_move.x = MIN_MOVE_VALUE;

					// 位置
					m_pos.x = (BlockSize.x / DEVIDE_VALUE + BlockPos.x) + (m_size.x / DEVIDE_VALUE);

					// falseの場合
					if (m_bCollision == false)
					{
						// trueに
						m_bCollision = true;
					}
				}
				// 左右の面に当たってない場合
				if (CCollision::RectangleCollisionMove(pos, m_posOld, m_size, BlockPos, BlockSize) != CCollision::SURFACE_LEFT ||
					CCollision::RectangleCollisionMove(pos, m_posOld, m_size, BlockPos, BlockSize) != CCollision::SURFACE_RIGHT)
				{
					// trueの場合
					if (m_bCollision == true)
					{
						// falseに
						m_bCollision = false;
					}
				}
			}
		}
	} while (pScene != NULL);

	// 3Dオブジェクトとの当たり判定
	do
	{
		// オブジェタイプがブロックの場合
		pScene = GetScene(OBJTYPE_MAP_OBJ);

		// NULLチェック
		if (pScene != NULL)
		{
			// オブジェタイプ取得
			OBJTYPE objType = pScene->GetObjType();

			// オブジェクトタイプが敵
			if (objType == OBJTYPE_MAP_OBJ)
			{
				// 位置座標取得
				D3DXVECTOR3 ObjPos = ((C3D_Obj*)pScene)->GetPos();
				// サイズ取得
				D3DXVECTOR3 ObjSize = ((C3D_Obj*)pScene)->GetSize();

				//どこの面に当たったか取得
				//下
				if (CCollision::RectangleCollisionMove(pos, m_posOld, m_size, ObjPos, ObjSize) == CCollision::SURFACE_DOWN)
				{
					// 移動量0
					m_move.y = MIN_MOVE_VALUE;

					// 位置
					m_pos.y = (m_size.y / DEVIDE_VALUE) -  (ObjPos.y + ObjSize.y / DEVIDE_VALUE);
				}
				// 上
				else if (CCollision::RectangleCollisionMove(m_pos, m_posOld, m_size, ObjPos, ObjSize) == CCollision::SURFACE_UP)
				{
					// タイプ取得
					int n3D_ObjType = ((C3D_Obj*)pScene)->GetType();

					// タイプが床ブロックの場合
					if (n3D_ObjType == C3D_Obj::TYPE_FLOOR_01)
					{
						// 床ブロックのタイプ取得
						int nType = ((CFloor_Block*)pScene)->GetType();

						// チェックポイントの場合
						if (nType == CFloor_Block::TYPE_CHECK_POINT)
						{
							// 位置保存
							m_RespawnPos.x = ((CFloor_Block*)pScene)->GetPos().x;
						}
						// 敵生成の場合
						if (nType == CFloor_Block::TYPE_ENEMY_CREATE)
						{
							// 位置保存
							m_RespawnPos.x = ((CFloor_Block*)pScene)->GetPos().x;

							// falseの場合
							if (m_bEnemyCreate == false)
							{
								// 敵生成
								CEnemy_Map::Create(ObjPos);

								// trueに
								m_bEnemyCreate = true;
							}
						}
						// 終了の場合
						if (nType == CFloor_Block::TYPE_END)
						{
							// falseの場合
							if (m_bEnd == false)
							{
								// 遷移
								CFade::Create(CManager::MODE_RESULT);

								// trueに
								m_bEnd = true;
							}
						}
					}
					// タイプが針の場合
					if (n3D_ObjType == C3D_Obj::TYPE_NEEDLE)
					{
						// エフェクト生成
						CParticle_Effect::Create(DEAD_POS, CParticle_Effect::TYPE_STAR_EFFECT2);

						// リスポーン音再生
						pSound->PlaySoundA(CSound::SOUND_LABEL_SE_RESPAWN);

						// リスポーン位置に移動
						m_pos = m_RespawnPos;

						// エフェクト生成
						CParticle_Effect::Create(RESPOWN_POS, CParticle_Effect::TYPE_STAR_EFFECT2);
					}
					// 移動量0
					m_move.y = MIN_MOVE_VALUE;

					// 位置
					m_pos.y = (-m_size.y / DEVIDE_VALUE) + (ObjPos.y + ObjSize.y / DEVIDE_VALUE);

					// trueの場合
					if (m_bJump == true)
					{
						// falseに
						m_bJump = false;

						// falseに
						m_bJumpValue = false;
					}
				}
				// 左
				else if (CCollision::RectangleCollisionMove(pos, m_posOld, m_size, ObjPos, ObjSize) == CCollision::SURFACE_LEFT)
				{
					// 移動量0
					m_move.x = MIN_MOVE_VALUE;

					// 位置
					m_pos.x = (-m_size.x / DEVIDE_VALUE) + (ObjPos.x - ObjSize.x / DEVIDE_VALUE);

					// falseの場合
					if (m_bCollision == false)
					{
						// trueに
						m_bCollision = true;
					}
				}
				// 右
				else if (CCollision::RectangleCollisionMove(pos, m_posOld, m_size, ObjPos, ObjSize) == CCollision::SURFACE_RIGHT)
				{
					// 移動量0
					m_move.x = MIN_MOVE_VALUE;

					// 位置
					m_pos.x = (m_size.x / DEVIDE_VALUE) + (ObjPos.x + ObjSize.x / DEVIDE_VALUE);

					// falseの場合
					if (m_bCollision == false)
					{
						// trueに
						m_bCollision = true;
					}
				}
				// 左右の面に当たってない場合
				if (CCollision::RectangleCollisionMove(pos, m_posOld, m_size, ObjPos, ObjSize) != CCollision::SURFACE_LEFT ||
					CCollision::RectangleCollisionMove(pos, m_posOld, m_size, ObjPos, ObjSize) != CCollision::SURFACE_RIGHT)
				{
					// trueの場合
					if (m_bCollision == true)
					{
						// falseに
						m_bCollision = false;
					}
				}
			}
		}
		// pSceneがNULLの場合
	} while (pScene != NULL);
}
//******************************************************************************
// 移動処理関数
//******************************************************************************
void CPlayer::Move(void)
{
	//サウンド取得
	CSound * pSound = CManager::GetSound();

	// コントローラー取得
	DIJOYSTATE js;
	js.lY = INIT_INT;
	js.lX = INIT_INT;
	CInputJoystick * pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 g_lpDIDevice = CInputJoystick::GetDevice();

	if (g_lpDIDevice != NULL)
	{
		g_lpDIDevice->Poll();
		g_lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}

	// 目的の向き
	D3DXVECTOR3 RotDest = m_rot;

	// カメラ取得
	CCamera *pCamera = CManager::GetCamera();

	// カメラの位置取得
	D3DXVECTOR3 CameraPos = pCamera->GetPos();

	if (g_lpDIDevice != NULL)
	{
		// ブロック選択中でない場合
		if (m_Blcok_Active != BLOCK_ACTIVE_SELECT)
		{
			// falseの場合
			if (m_bMagic == false)
			{
				// 左
				if (js.lX <= -STICK_REACTION)
				{
					// falseの場合
					if (m_bDash == false)
					{
						// 歩行音再生
						pSound->PlaySoundA(CSound::SOUND_LABEL_SE_WALK);

						// trueに
						m_bDash = true;
					}

					// trueに
					m_bBlock_Move = true;

					// falseの場合
					if (m_bCollision == false)
					{
						// カメラの位置より低い場合
						if (m_pos.x < CameraPos.x - SCREEN_WIDTH / CAMERA_POS_DEVIDE)
						{
							pCamera->Move(-MOVE_VALUE.x);
						}
					}
					// NULLでない場合
					if (m_pBlock != NULL)
					{
						// Rトリガーが押されている場合
						if (pInputJoystick->GetJoystickPress(CInputJoystick::JS_RT))
						{
							// 右向きの場合
							if (m_Rot_State == ROT_STATE_LEFT)
							{
								// 移動モーション
								m_pMotion->SetMotion(CMotion::MOTION_BLOCK_RUN);

								// 後ろ
								m_move.x = -MOVE_VALUE.x;
							}
							// 左向きの場合
							if (m_Rot_State == ROT_STATE_RIGHT)
							{
								// 移動モーション
								m_pMotion->SetMotion(CMotion::MOTION_BACKRUN);

								// 後ろ
								m_move.x = -MOVE_VALUE.x / MOVE_DEVIDE;
							}
						}
					}
					// NULLの場合
					if (m_pBlock == NULL)
					{
						// Rトリガーが押されている場合
						if (pInputJoystick->GetJoystickPress(CInputJoystick::JS_RT))
						{
							// 左向きの状態
							m_Rot_State = ROT_STATE_LEFT;

							// 生成時でない場合
							if (m_Blcok_Active != BLOCK_ACTIVE_CREATE)
							{
								// 移動モーション
								m_pMotion->SetMotion(CMotion::MOTION_RUN);
							}

							// 後ろ
							m_move.x = -MOVE_VALUE.x;
						}
					}
					// RTが押されていない場合
					if (!pInputJoystick->GetJoystickPress(CInputJoystick::JS_RT))
					{
						// 左向きの状態
						m_Rot_State = ROT_STATE_LEFT;

						// 生成時の場合
						if (m_Blcok_Active == BLOCK_ACTIVE_CREATE)
						{
							// ブロック移動モーション
							m_pMotion->SetMotion(CMotion::MOTION_BLOCK_RUN);
						}
						// 生成時でない場合
						if (m_Blcok_Active != BLOCK_ACTIVE_CREATE)
						{
							// 移動モーション
							m_pMotion->SetMotion(CMotion::MOTION_RUN);
						}

						// 後ろ
						m_move.x = -MOVE_VALUE.x;
					}
				}
				// 右
				if (js.lX >= STICK_REACTION)
				{
					// falseの場合
					if (m_bDash == false)
					{
						// 歩行音再生
						pSound->PlaySoundA(CSound::SOUND_LABEL_SE_WALK);

						// trueに
						m_bDash = true;
					}

					// trueに
					m_bBlock_Move = true;

					// falseの場合
					if (m_bCollision == false)
					{
						// カメラの位置より引く場合
						if (m_pos.x > CameraPos.x + SCREEN_WIDTH / CAMERA_POS_DEVIDE)
						{
							pCamera->Move(MOVE_VALUE.x);
						}
					}
					// NULLでない場合
					if (m_pBlock != NULL)
					{
						// Rトリガーが押されている場合
						if (pInputJoystick->GetJoystickPress(CInputJoystick::JS_RT))
						{
							// 左向きの場合
							if (m_Rot_State == ROT_STATE_RIGHT)
							{
								// 移動モーション
								m_pMotion->SetMotion(CMotion::MOTION_BLOCK_RUN);

								// 後ろ
								m_move.x = MOVE_VALUE.x;
							}
							// 右向きの場合
							if (m_Rot_State == ROT_STATE_LEFT)
							{
								// 移動モーション
								m_pMotion->SetMotion(CMotion::MOTION_BACKRUN);

								// 後ろ
								m_move.x = MOVE_VALUE.x / MOVE_DEVIDE;
							}
						}
					}
					// NULLの場合
					if (m_pBlock == NULL)
					{
						// Rトリガーが押されている場合
						if (pInputJoystick->GetJoystickPress(CInputJoystick::JS_RT))
						{
							// 左向きの状態
							m_Rot_State = ROT_STATE_RIGHT;

							// 生成時でない場合
							if (m_Blcok_Active != BLOCK_ACTIVE_CREATE)
							{
								// 移動モーション
								m_pMotion->SetMotion(CMotion::MOTION_RUN);
							}

							// 後ろ
							m_move.x = MOVE_VALUE.x;
						}
					}
					// RTが押されていない場合
					if (!pInputJoystick->GetJoystickPress(CInputJoystick::JS_RT))
					{
						// 右向きの状態
						m_Rot_State = ROT_STATE_RIGHT;

						// 生成時の場合
						if (m_Blcok_Active == BLOCK_ACTIVE_CREATE)
						{
							// ブロック移動モーション
							m_pMotion->SetMotion(CMotion::MOTION_BLOCK_RUN);
						}
						// 生成時でない場合
						if (m_Blcok_Active != BLOCK_ACTIVE_CREATE)
						{
							// 移動モーション
							m_pMotion->SetMotion(CMotion::MOTION_RUN);
						}

						// 前に進む
						m_move.x = MOVE_VALUE.x;
					}
				}
				// スティックの範囲外の場合
				if (js.lX > -STICK_REACTION && js.lX < STICK_REACTION)
				{
					// falseの場合
					if (m_bDash == true)
					{
						// 歩行音再生
						pSound->StopSound(CSound::SOUND_LABEL_SE_WALK);

						// falseに
						m_bDash = false;
					}

					// trueに
					m_bBlock_Move = false;

					// 移動量0
					m_move.x = MIN_MOVE_VALUE;

					// NULLでない場合
					if (m_pBlock != NULL)
					{
						// Rトリガーが押されている場合
						if (pInputJoystick->GetJoystickPress(CInputJoystick::JS_RT))
						{

							// ブロックのニュートラルモーション
							m_pMotion->SetMotion(CMotion::MOTION_BLOCK_IDLE);
						}
					}
					// NULLの場合
					if (m_pBlock == NULL)
					{
						// Rトリガーが押されている場合
						if (pInputJoystick->GetJoystickPress(CInputJoystick::JS_RT))
						{

							// ブロックのニュートラルモーション
							m_pMotion->SetMotion(CMotion::MOTION_IDLE);
						}
					}
					// RTが押されていない場合
					if (!pInputJoystick->GetJoystickPress(CInputJoystick::JS_RT))
					{
						// 生成時の場合
						if (m_Blcok_Active == BLOCK_ACTIVE_CREATE)
						{
							// ブロック移動モーション
							m_pMotion->SetMotion(CMotion::MOTION_BLOCK_IDLE);
						}
						// 生成時でない場合
						if (m_Blcok_Active != BLOCK_ACTIVE_CREATE)
						{
							// ニュートラルモーション
							m_pMotion->SetMotion(CMotion::MOTION_IDLE);
						}
					}
				}
				// ジャンプ
				if (m_bJump == false)
				{
					// Aボタンを押した場合
					if (pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_A))
					{
						// trueに
						m_bJump = true;
						// falseの場合
						if (m_bJumpValue == false)
						{
							// 移動
							m_move.y += JUMP_VALUE;

							m_bJumpValue = true;
						}
						// trueの場合
						if (m_bJumpValue == true)
						{
							// 移動
							m_move.y += JUMP_VALUE_2;
						}
					}
				}
			}
			// trueの場合
			if (m_bMagic == true)
			{
				// 移動量を0.0fに
				m_move.x = MIN_MOVE_VALUE;
			}
		}
	}
	// 右を向いてる場合
	if (m_Rot_State == ROT_STATE_RIGHT)
	{
		// 向き
		RotDest.y = RIGHT_ROT.y;
	}
	// 左を向いてる場合
	if (m_Rot_State == ROT_STATE_LEFT)
	{
		// 向き
		RotDest.y = LEFT_ROT.y;
	}

	// 向き
	m_rot += (RotDest - m_rot) * ROT_MOVE;

	// 重力
	m_move.y += GRAVITY_VALUE;

	// 移動
	m_pos.x += m_move.x;
	m_pos.y += m_move.y;
}
//******************************************************************************
// 魔法処理関数
//******************************************************************************
void CPlayer::Magic(void)
{
	//サウンド取得
	CSound * pSound = CManager::GetSound();

	// コントローラー取得
	DIJOYSTATE js;
	js.lY = INIT_INT;
	js.lX = INIT_INT;
	CInputJoystick * pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 g_lpDIDevice = CInputJoystick::GetDevice();

	if (g_lpDIDevice != NULL)
	{
		g_lpDIDevice->Poll();
		g_lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}

	// falseの場合
	if (m_bMagic == false)
	{
		// Bを押した場合ボタンを押した場合
		if (pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_B))
		{
			// trueに
			m_bMagic = true;

			// 魔法攻撃モーション
			m_pMotion->SetMotion(CMotion::MOTION_MAGIC_ACTION);
		}
		// ファイアーボールの場合
		if (m_MagicType == MAGIC_TYPE_FIREBALL)
		{
			// falseの場合
			if (m_bChange_MagicType == false)
			{
				// RBまたはLBが押された場合
				if (pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_RB) || pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_LB))
				{
					// trueに
					m_bChange_MagicType = true;

					// アイスボールに
					m_MagicType = MAGIC_TYPE_ICEBALL;

					// 放射体生成
					Emitter_Create(EMITTER_TYPE_ICE);
				}
			}
			// trueの場合
			if (m_bChange_MagicType == true)
			{
				// RBまたはLBが離された場合
				if (pInputJoystick->GetJoystickRelease(CInputJoystick::JS_RB) || pInputJoystick->GetJoystickRelease(CInputJoystick::JS_LB))
				{
					// falseに
					m_bChange_MagicType = false;
				}
			}
		}
		// アイスボールの場合
		if (m_MagicType == MAGIC_TYPE_ICEBALL)
		{
			// falseの場合
			if (m_bChange_MagicType == false)
			{
				// RBまたはLBが押された場合
				if (pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_RB) || pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_LB))
				{
					// trueに
					m_bChange_MagicType = true;

					// ファイアーボールに
					m_MagicType = MAGIC_TYPE_FIREBALL;

					// 放射体生成
					Emitter_Create(EMITTER_TYPE_FIRE);
				}
			}
			// trueの場合
			if (m_bChange_MagicType == true)
			{
				// RBまたはLBが離された場合
				if (pInputJoystick->GetJoystickRelease(CInputJoystick::JS_RB) || pInputJoystick->GetJoystickRelease(CInputJoystick::JS_LB))
				{
					// falseに
					m_bChange_MagicType = false;
				}
			}
		}
	}
	// trueの場合
	if (m_bMagic == true)
	{
		// インクリメント
		m_nMotion_Count++;

		// 30カウントになった場合
		if (m_nMotion_Count == MAGIC_MOTION_COUNT)
		{
			// falseに
			m_bMagic = false;

			// 右向きの場合
			if (m_Rot_State == ROT_STATE_RIGHT)
			{
				// ファイアボールの場合
				if (m_MagicType == MAGIC_TYPE_FIREBALL)
				{
					// 火の球音再生
					pSound->PlaySoundA(CSound::SOUND_LABEL_SE_FIRE_BALL);

					// ファイアーボール生成
					CMagic::Create(MAGIC_POS, MAGIC_MOVE_RIGHT, CMagic::TYPE_FIRE_BALL);
				}
				// アイスボールの場合
				if (m_MagicType == MAGIC_TYPE_ICEBALL)
				{
					// 火の球音再生
					pSound->PlaySoundA(CSound::SOUND_LABEL_SE_FIRE_BALL);

					// アイスボールの生成
					CMagic::Create(MAGIC_POS, MAGIC_MOVE_RIGHT, CMagic::TYPE_ICE_BALL);
				}
			}
			// 左向きの場合
			if (m_Rot_State == ROT_STATE_LEFT)
			{
				// ファイアボールの場合
				if (m_MagicType == MAGIC_TYPE_FIREBALL)
				{
					// 火の球音再生
					pSound->PlaySoundA(CSound::SOUND_LABEL_SE_FIRE_BALL);

					// ファイアーボール生成
					CMagic::Create(MAGIC_POS, MAGIC_MOVE_LEFT, CMagic::TYPE_FIRE_BALL);
				}
				// アイスボールの場合
				if (m_MagicType == MAGIC_TYPE_ICEBALL)
				{
					// 火の球音再生
					pSound->PlaySoundA(CSound::SOUND_LABEL_SE_FIRE_BALL);

					// アイスボールの生成
					CMagic::Create(MAGIC_POS, MAGIC_MOVE_LEFT, CMagic::TYPE_ICE_BALL);
				}
			}
			// 初期化
			m_nMotion_Count = INIT_INT;
		}
	}
}
//******************************************************************************
// 放射体生成関数
//******************************************************************************
void CPlayer::Emitter_Create(EMITTER_TYPE EmitterType)
{
	// NULLの場合
	if (m_apParticle_Emitter[PARTICLE_EMITTER_RIGHT] == NULL && m_apParticle_Emitter[PARTICLE_EMITTER_LEFT] == NULL)
	{
		// 代入
		m_Emitter_Type = EmitterType;

		// 星の場合
		if (m_Emitter_Type == EMITTER_TYPE_STAR)
		{
			// 右手
			m_apParticle_Emitter[PARTICLE_EMITTER_RIGHT] = CParticle_Emitter::Create(EMITTER_POS_RIGHT, CParticle_Emitter::TYPE_STAR_RIGHT);

			// 左手
			m_apParticle_Emitter[PARTICLE_EMITTER_LEFT] = CParticle_Emitter::Create(EMITTER_POS_LEFT, CParticle_Emitter::TYPE_STAR_LEFT);
		}
		// 火の場合
		if (m_Emitter_Type == EMITTER_TYPE_FIRE)
		{
			// 右手
			m_apParticle_Emitter[PARTICLE_EMITTER_RIGHT] = CParticle_Emitter::Create(EMITTER_POS_RIGHT, CParticle_Emitter::TYPE_FIRE_RIGHT);

			// 左手
			m_apParticle_Emitter[PARTICLE_EMITTER_LEFT] = CParticle_Emitter::Create(EMITTER_POS_LEFT, CParticle_Emitter::TYPE_FIRE_LEFT);
		}
		// 氷の場合
		if (m_Emitter_Type == EMITTER_TYPE_ICE)
		{
			// 右手
			m_apParticle_Emitter[PARTICLE_EMITTER_RIGHT] = CParticle_Emitter::Create(EMITTER_POS_RIGHT, CParticle_Emitter::TYPE_ICE_RIGHT);

			// 左手
			m_apParticle_Emitter[PARTICLE_EMITTER_LEFT] = CParticle_Emitter::Create(EMITTER_POS_LEFT, CParticle_Emitter::TYPE_ICE_LEFT);
		}
	}
	// NULLでない場合
	if (m_apParticle_Emitter[PARTICLE_EMITTER_RIGHT] != NULL && m_apParticle_Emitter[PARTICLE_EMITTER_LEFT] != NULL)
	{
		// 同じ種類でない場合
		if (m_Emitter_Type != EmitterType)
		{
			// 代入
			m_Emitter_Type = EmitterType;

			// 2回繰り返す
			for (int nCnt = INIT_INT; nCnt < PARTICLE_EMITTER_MAX; nCnt++)
			{
				// 破棄
				m_apParticle_Emitter[nCnt]->Release();

				// NULLに
				m_apParticle_Emitter[nCnt] = NULL;
			}

			// NULLの場合
			if (m_apParticle_Emitter[PARTICLE_EMITTER_RIGHT] == NULL && m_apParticle_Emitter[PARTICLE_EMITTER_LEFT] == NULL)
			{
				// 星の場合
				if (m_Emitter_Type == EMITTER_TYPE_STAR)
				{
					// 右手
					m_apParticle_Emitter[PARTICLE_EMITTER_RIGHT] = CParticle_Emitter::Create(EMITTER_POS_RIGHT, CParticle_Emitter::TYPE_STAR_RIGHT);

					// 左手
					m_apParticle_Emitter[PARTICLE_EMITTER_LEFT] = CParticle_Emitter::Create(EMITTER_POS_LEFT, CParticle_Emitter::TYPE_STAR_LEFT);
				}
				// 火の場合
				if (m_Emitter_Type == EMITTER_TYPE_FIRE)
				{
					// 右手
					m_apParticle_Emitter[PARTICLE_EMITTER_RIGHT] = CParticle_Emitter::Create(EMITTER_POS_RIGHT, CParticle_Emitter::TYPE_FIRE_RIGHT);

					// 左手
					m_apParticle_Emitter[PARTICLE_EMITTER_LEFT] = CParticle_Emitter::Create(EMITTER_POS_LEFT, CParticle_Emitter::TYPE_FIRE_LEFT);
				}
				// 氷の場合
				if (m_Emitter_Type == EMITTER_TYPE_ICE)
				{
					// 右手
					m_apParticle_Emitter[PARTICLE_EMITTER_RIGHT] = CParticle_Emitter::Create(EMITTER_POS_RIGHT, CParticle_Emitter::TYPE_ICE_RIGHT);

					// 左手
					m_apParticle_Emitter[PARTICLE_EMITTER_LEFT] = CParticle_Emitter::Create(EMITTER_POS_LEFT, CParticle_Emitter::TYPE_ICE_LEFT);
				}
			}
		}
	}
}