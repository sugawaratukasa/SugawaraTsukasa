//******************************************************************************
// カメラ [camera.cpp]
// Author : 管原司
//******************************************************************************

//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "scene.h"
#include "../3D/Model/player.h"
#include "camera.h"

//******************************************************************************
// マクロ定義
//******************************************************************************
#define VECU_VALUE			(D3DXVECTOR3(0.0f,1.0f,0.0f))	// vecu値
#define ROT_VALUE			(D3DXToRadian(1.0f))			// カメラの球面座標の移動
#define PHI_VALUE			(D3DXToRadian(90.0f))			// phi値
#define THETA_VALUE			(D3DXToRadian(270.0f))			// theta値
#define DISTANCE_VALUE		(500.0f)						// 距離
#define FOV_VALUE			(45.0f)							// 視野角
#define MAX_DRAW_DISTANCE	(5000.0f)						// 最大描画距離
#define MIN_DRAW_DISTANCE	(10.0f)							// 最小描画距離
#define DEVIDE_VALUE		(3)								// 割る数
#define MOVE_VALUE			(2.0f)							// 移動量
//******************************************************************************
// コンストラクタ
//******************************************************************************
CCamera::CCamera()
{
	m_posV		= INIT_D3DXVECTOR3;
	m_posR		= INIT_D3DXVECTOR3;
	m_vecU		= INIT_D3DXVECTOR3;
	AddPosV		= INIT_FLOAT;
	m_fPhi		= INIT_FLOAT;
	m_fTheta	= INIT_FLOAT;
	memset(m_mtxProjection, NULL, sizeof(m_mtxProjection));
	memset(m_mtxView, NULL, sizeof(m_mtxView));
}

//******************************************************************************
// デクリメント
//******************************************************************************
CCamera::~CCamera()
{

}

//******************************************************************************
// 初期化処理
//******************************************************************************
void CCamera::Init(void)
{
	m_posV		= INIT_D3DXVECTOR3;
	m_posR		= INIT_D3DXVECTOR3;
	m_vecU		= VECU_VALUE;
	m_fPhi		= PHI_VALUE;
	m_fTheta	= THETA_VALUE;
	memset(m_mtxProjection, NULL, sizeof(m_mtxProjection));
	memset(m_mtxView, NULL, sizeof(m_mtxView));
}

//******************************************************************************
// 終了処理
//******************************************************************************
void CCamera::Uninit(void)
{

}

//******************************************************************************
// 更新処理
//******************************************************************************
void CCamera::Update(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//キーボードの取得
	CInputKeyboard *pKeyborad = CManager::GetInputKeyboard();

	// シーン
	CScene *pScene = NULL;

	D3DXVECTOR3 PlayerPos;
	do
	{
		// オブジェタイプがPLAYERの場合
		pScene = CScene::GetScene(CScene::OBJTYPE_PLAYER);

		// NULLチェック
		if (pScene != NULL)
		{
			// オブジェタイプ取得
			CScene::OBJTYPE objType = pScene->GetObjType();

			// オブジェクトタイプが敵
			if (objType == CScene::OBJTYPE_PLAYER)
			{
				// 座標とサイズ取得
				PlayerPos = ((CPlayer*)pScene)->GetPos();
			}
		}
	} while (pScene != NULL);

	// 注視点
	m_posR.x = AddPosV + (sinf(m_fTheta)*cosf(m_fPhi));
	m_posR.y = cosf(m_fTheta);
	m_posR.z = (sinf(m_fTheta)*sinf(m_fPhi));

	// 距離
	m_fDistance = DISTANCE_VALUE;

	// 視点	
	m_posV.x = AddPosV + (sinf(m_fTheta)*cosf(m_fPhi)) *  m_fDistance;
	m_posV.y = (cosf(m_fTheta)) * m_fDistance;
	m_posV.z = (sinf(m_fTheta)*sinf(m_fPhi))  * m_fDistance;

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);
	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_mtxView, &m_posV, &m_posR, &m_vecU);
	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);
	//プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection, FOV_VALUE, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, MIN_DRAW_DISTANCE, MAX_DRAW_DISTANCE);
	//D3DXMatrixOrthoLH(&m_mtxProjection, (float)SCREEN_WIDTH / DEVIDE_VALUE, (float)SCREEN_HEIGHT / DEVIDE_VALUE, MIN_DRAW_DISTANCE, MAX_DRAW_DISTANCE);
	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
}
//******************************************************************************
// 移動処理関数
//******************************************************************************
void CCamera::Move(float fMove)
{
	// 移動
	AddPosV += fMove;
}