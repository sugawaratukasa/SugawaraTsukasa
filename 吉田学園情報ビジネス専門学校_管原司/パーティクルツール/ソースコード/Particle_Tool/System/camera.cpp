//******************************************************************************
// カメラ [camera.cpp]
// Author : 管原司
//******************************************************************************

//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "manager.h"
#include "renderer.h"
#include "scene.h"
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
//******************************************************************************
// コンストラクタ
//******************************************************************************
CCamera::CCamera()
{
	posV		= INIT_D3DXVECTOR3;
	posR		= INIT_D3DXVECTOR3;
	vecU		= INIT_D3DXVECTOR3;
	m_fPhi		= INIT_FLOAT;
	m_fTheta	= INIT_FLOAT;
	memset(mtxProjection, NULL, sizeof(mtxProjection));
	memset(mtxView, NULL, sizeof(mtxView));
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
	posV = INIT_D3DXVECTOR3;
	posR = INIT_D3DXVECTOR3;
	vecU = VECU_VALUE;
	m_fPhi = PHI_VALUE;
	m_fTheta = THETA_VALUE;
	memset(mtxProjection, NULL, sizeof(mtxProjection));
	memset(mtxView, NULL, sizeof(mtxView));
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

	// 注視点
	posR.x = (sinf(m_fTheta)*cosf(m_fPhi));
	posR.y = cosf(m_fTheta);
	posR.z = (sinf(m_fTheta)*sinf(m_fPhi));

	// 距離
	m_fDistance = DISTANCE_VALUE;

	// 視点	
	posV.x = m_fDistance*(sinf(m_fTheta)*cosf(m_fPhi));
	posV.y = m_fDistance*cosf(m_fTheta);
	posV.z = m_fDistance*(sinf(m_fTheta)*sinf(m_fPhi));

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&mtxView, &posV, &posR, &vecU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &mtxView);

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&mtxProjection);

	//プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&mtxProjection, FOV_VALUE, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, MIN_DRAW_DISTANCE, MAX_DRAW_DISTANCE);

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);
}