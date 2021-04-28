//******************************************************************************
// 敵[enemy.cpp]
// Author : 管原 司
//******************************************************************************

//******************************************************************************
//インクルードファイル
//******************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "../3D/Model/model.h"
#include "collision.h"
#include "camera.h"
#include "enemy.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define GHOST_TEXT	("data/Model/Enemy/Ghost.x")	// パス
#define MIN_LIFE	(0)								// ライフの最小値
//******************************************************************************
//静的メンバ変数
//******************************************************************************
LPD3DXMESH CEnemy::m_pMesh = NULL;
LPD3DXBUFFER CEnemy::m_pBuffMat = NULL;
DWORD CEnemy::m_nNumMat = NULL;
char* CEnemy::m_apFileName = { GHOST_TEXT };
LPDIRECT3DTEXTURE9 CEnemy::m_apTexture = NULL;
//******************************************************************************
// コンストラクタ
//******************************************************************************
CEnemy::CEnemy(int nPriority) :CScene(nPriority)
{
	m_pos		= INIT_D3DXVECTOR3;
	m_rot		= INIT_D3DXVECTOR3;
	m_size		= INIT_D3DXVECTOR3;
	m_pModel	= NULL;
	m_State		= STATE_NORMAL;
	m_nLife		= INIT_INT;
	m_bDraw		= true;
	memset(m_mtxWorld, NULL, sizeof(m_mtxWorld));
}

//******************************************************************************
// デストラクタ
//******************************************************************************
CEnemy::~CEnemy()
{

}

//******************************************************************************
// モデルの読み込み
//******************************************************************************
HRESULT CEnemy::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

		// Xファイルの読み込み
		D3DXLoadMeshFromX(m_apFileName,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_pBuffMat,
			NULL,
			&m_nNumMat,
			&m_pMesh
		);

	// 読み込みテクスチャ
	LoadTexture();

	return S_OK;
}
//******************************************************************************
// モデルの破棄
//******************************************************************************
void CEnemy::Unload(void)
{
		// メッシュの破棄
		if (m_pMesh != NULL)
		{
			m_pMesh->Release();
			m_pMesh = NULL;
		}
		// マテリアルの破棄
		if (m_pBuffMat != NULL)
		{
			m_pBuffMat->Release();
			m_pBuffMat = NULL;
		}
		if (m_nNumMat != NULL)
		{
			m_nNumMat = NULL;
		}


	// テクスチャ破棄
	UnloadTexture();
}
//******************************************************************************
// テクスチャ読み込み
//******************************************************************************
HRESULT CEnemy::LoadTexture(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

		// マテリアル情報を取り出す
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

		for (int nCntMat = INIT_INT; nCntMat < (signed)m_nNumMat; nCntMat++)
		{
			// 使用しているテクスチャがあれば読み込む
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				// テクスチャ読み込み
				if (FAILED(D3DXCreateTextureFromFile(
					pDevice,
					pMat[nCntMat].pTextureFilename,
					&m_apTexture)))
				{
					return E_FAIL;
				}
			}
		}

	return S_OK;
}
//******************************************************************************
// テクスチャ読み込み
//******************************************************************************
void CEnemy::UnloadTexture(void)
{
	for (int nCntMat = INIT_INT; nCntMat < (signed)m_nNumMat; nCntMat++)
	{
		// NULLでない場合
		if (m_apTexture!= NULL)
		{
			// テクスチャRelease
			m_apTexture->Release();

			// m_pTextureをNULLに
			m_apTexture= NULL;

		}
	}
}

//******************************************************************************
// 初期化処理
//******************************************************************************
HRESULT CEnemy::Init(void)
{
	// モデルの生成
	m_pModel = CModel::Create();

	for (int nCntMat = INIT_INT; nCntMat < (signed)m_nNumMat; nCntMat++)
	{
		// テクスチャのバインド
		m_pModel->BindTexture(m_apTexture);
	}

	// モデルのバインド
	m_pModel->BindModel(m_pMesh, m_pBuffMat, m_nNumMat, -1);

	// 情報設定
	m_pModel->SetModel(m_pos, m_rot, m_size);

	return S_OK;
}

//******************************************************************************
// 終了処理
//******************************************************************************
void CEnemy::Uninit(void)
{
	// NULLでない場合
	if (m_pModel != NULL)
	{
		// モデルクラスの終了処理
		m_pModel->Uninit();

		// NULLに
		m_pModel = NULL;
	}
	// 破棄
	Release();
}

//******************************************************************************
// 更新処理
//******************************************************************************
void CEnemy::Update(void)
{
	// 位置更新
	m_pModel->SetModel(m_pos, m_rot, m_size);

	// カメラの位置取得
	D3DXVECTOR3 CameraPos = CManager::GetCamera()->GetPos();

	// 描画判定
	// 範囲外の場合
	if (m_pos.x > CameraPos.x + SCREEN_WIDTH / CAMERA_POS_DEVIDE2 || m_pos.x < CameraPos.x - SCREEN_WIDTH / CAMERA_POS_DEVIDE2)
	{
		// trueの場合
		if (m_bDraw == true)
		{
			// falseに
			m_bDraw = false;
		}
	}
	// 範囲内の場合
	if (m_pos.x < CameraPos.x + SCREEN_WIDTH / CAMERA_POS_DEVIDE2 && m_pos.x > CameraPos.x - SCREEN_WIDTH / CAMERA_POS_DEVIDE2)
	{
		// falseの場合
		if (m_bDraw == false)
		{
			// trueに
			m_bDraw = true;
		}
	}
	// ライフが最小値以下になったら
	if (m_nLife <= MIN_LIFE)
	{
		// 状態を死亡状態に
		m_State = STATE_DEAD;

		// 終了
		Uninit();
		return;
	}
}

//******************************************************************************
// 描画処理
//******************************************************************************
void CEnemy::Draw(void)
{
	//レンダラー取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;

	//ワールドマトリクスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	m_pModel->SetWorldMatrix(m_mtxWorld);

	// trueの場合
	if (m_bDraw == true)
	{
		// モデルクラスの描画処理
		m_pModel->Draw();
	}
}
//******************************************************************************
// ヒット
//******************************************************************************
void CEnemy::Hit(int nDamage)
{
	// 減算
	m_nLife -= nDamage;
}
//******************************************************************************
// 情報設定
//******************************************************************************
void CEnemy::SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nLife)
{
	m_pos	= pos;
	m_rot	= rot;
	m_size	= size;
	m_nLife = nLife;
	// オブジェクトタイプ設定
	SetObjType(OBJTYPE_ENEMY);
}
//******************************************************************************
// 位置設定
//******************************************************************************
void CEnemy::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//******************************************************************************
// 向き設定
//******************************************************************************
void CEnemy::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}
//******************************************************************************
// サイズ設定
//******************************************************************************
void CEnemy::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}
//******************************************************************************
// 体力設定
//******************************************************************************
void CEnemy::SetLife(int nLife)
{
	m_nLife = nLife;
}