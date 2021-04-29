//******************************************************************************
// カメラ [camera.h]
// Author : 管原　司
//******************************************************************************
#ifndef _CAMERA_H_
#define _CAMERA_H_
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "main.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define CAMERA_POS_DEVIDE			(15)	// カメラの位置を割る数
#define CAMERA_POS_DEVIDE2			(2)		// カメラの位置を割る数
#define CAMERA_POS_DEVIDE3			(6.5f)	// カメラの位置を割る数
//******************************************************************************
// クラス
//******************************************************************************
class CCamera
{
public:
	CCamera();
	~CCamera();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Move(float fMove);
	D3DXVECTOR3 GetPos(void) { return m_posV; }
private:
	D3DXVECTOR3 m_posV;			// 位置
	D3DXVECTOR3 m_posR;			// 注視点
	D3DXVECTOR3 m_vecU;	
	D3DXMATRIX	m_mtxProjection;
	D3DXMATRIX	m_mtxView;
	float AddPosV;				// 位置加算
	float m_fDistance;			// 距離
	float m_fPhi;				// ファイ
	float m_fTheta;				// シータ
};

#endif