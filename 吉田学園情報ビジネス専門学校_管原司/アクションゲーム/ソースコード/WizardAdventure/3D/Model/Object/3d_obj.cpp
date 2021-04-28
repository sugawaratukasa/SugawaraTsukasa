//******************************************************************************
// ブロック[block.cpp]
// Author : 管原 司
//******************************************************************************

//******************************************************************************
//インクルードファイル
//******************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "../3D/3DPolygon/scene3d.h"
#include "input.h"
#include "joystick.h"
#include "../3D/Model/model.h"
#include "../3D/3DPolygon/frame.h"
#include "collision.h"
#include "../3D/Model/player.h"
#include "../3D/Model/Block/block.h"
#include "camera.h"
#include "3d_obj.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define FLOOR_BLOCK		("data/Model/Object/floor_01.x")	// 床
#define NEEDLE_BLOCK	("data/Model/Object/Needle.x")		// 針
#define BLOCK_WOOD		("data/Model/Object/box.x")			// 木箱
#define BLOCK_STOON		("data/Model/Object/box_2.x")		// 石の箱
#define BUTTON			("data/Model/Object/Button.x")		// ボタン
#define GATE			("data/Model/Object/Gate_2.x")		// 扉
#define GATEROOF		("data/Model/Object/GateRoof.x")	// 扉屋根
#define TREE			("data/Model/Object/Tree.x")		// 木
#define STONE_0			("data/Model/Object/stone000.x")	// 石
#define STONE_1			("data/Model/Object/stone001.x")	// 石
#define STONE_2			("data/Model/Object/stone002.x")	// 石
#define WOOD			("data/Model/Object/wood.x")		// 木
//******************************************************************************
//静的メンバ変数
//******************************************************************************
LPD3DXMESH C3D_Obj::m_pMesh[TYPE_MAX] = {};
LPD3DXBUFFER C3D_Obj::m_pBuffMat[TYPE_MAX] = {};
DWORD C3D_Obj::m_nNumMat[TYPE_MAX] = {};
char* C3D_Obj::m_apFileName[TYPE_MAX] = { FLOOR_BLOCK,NEEDLE_BLOCK,BLOCK_WOOD, BLOCK_STOON ,BUTTON, GATE, GATEROOF, TREE,STONE_0, STONE_1, STONE_2, WOOD };
LPDIRECT3DTEXTURE9 C3D_Obj::m_apTexture[TYPE_MAX] = {};
//******************************************************************************
// コンストラクタ
//******************************************************************************
C3D_Obj::C3D_Obj(int nPriority) :CScene(nPriority)
{
	m_pos		= INIT_D3DXVECTOR3;
	m_rot		= INIT_D3DXVECTOR3;
	m_size		= INIT_D3DXVECTOR3;
	m_pModel	= NULL;
	m_Type		= TYPE_NONE;
	m_bDraw		= true;
	memset(m_mtxWorld, NULL, sizeof(m_mtxWorld));
}

//******************************************************************************
// デストラクタ
//******************************************************************************
C3D_Obj::~C3D_Obj()
{

}

//******************************************************************************
// モデルの読み込み
//******************************************************************************
HRESULT C3D_Obj::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	for (int nCnt = INIT_INT; nCnt < TYPE_MAX; nCnt++)
	{
		// Xファイルの読み込み
		D3DXLoadMeshFromX(m_apFileName[nCnt],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_pBuffMat[nCnt],
			NULL,
			&m_nNumMat[nCnt],
			&m_pMesh[nCnt]
		);
	}

	// 読み込みテクスチャ
	LoadTexture();

	return S_OK;
}
//******************************************************************************
// モデルの破棄
//******************************************************************************
void C3D_Obj::Unload(void)
{
	for (int nCnt = INIT_INT; nCnt < TYPE_MAX; nCnt++)
	{
		// メッシュの破棄
		if (m_pMesh[nCnt] != NULL)
		{
			m_pMesh[nCnt]->Release();
			m_pMesh[nCnt] = NULL;
		}
		// マテリアルの破棄
		if (m_pBuffMat[nCnt] != NULL)
		{
			m_pBuffMat[nCnt]->Release();
			m_pBuffMat[nCnt] = NULL;
		}
		if (m_nNumMat[nCnt] != NULL)
		{
			m_nNumMat[nCnt] = NULL;
		}
	}

	// テクスチャ破棄
	UnloadTexture();
}
//******************************************************************************
// テクスチャ読み込み
//******************************************************************************
HRESULT C3D_Obj::LoadTexture(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャ分回す
	for (int nCount = INIT_INT; nCount < TYPE_MAX; nCount++)
	{
		// マテリアル情報を取り出す
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)m_pBuffMat[nCount]->GetBufferPointer();
		for (int nCntMat = INIT_INT; nCntMat < (signed)m_nNumMat[nCount]; nCntMat++)
		{
			// 使用しているテクスチャがあれば読み込む
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				// テクスチャ読み込み
				if (FAILED(D3DXCreateTextureFromFile(
					pDevice,
					pMat[nCntMat].pTextureFilename,
					&m_apTexture[nCount])))
				{
					return E_FAIL;
				}
			}
		}
	}

	return S_OK;
}
//******************************************************************************
// テクスチャ読み込み
//******************************************************************************
void C3D_Obj::UnloadTexture(void)
{
	for (int nCnt = INIT_INT; nCnt < TYPE_MAX; nCnt++)
	{
		for (int nCntMat = INIT_INT; nCntMat < (signed)m_nNumMat[nCnt]; nCntMat++)
		{
			// NULLでない場合
			if (m_apTexture[nCnt] != NULL)
			{
				// テクスチャRelease
				m_apTexture[nCnt]->Release();

				// m_pTextureをNULLに
				m_apTexture[nCnt] = NULL;

			}
		}
	}
}

//******************************************************************************
// 初期化処理
//******************************************************************************
HRESULT C3D_Obj::Init(void)
{
	// モデルの生成
	m_pModel = CModel::Create();

	for (int nCntMat = INIT_INT; nCntMat < (signed)m_nNumMat[m_Type]; nCntMat++)
	{
		// テクスチャのバインド
		m_pModel->BindTexture(m_apTexture[m_Type]);
	}

	// モデルのバインド
	m_pModel->BindModel(m_pMesh[m_Type], m_pBuffMat[m_Type], m_nNumMat[m_Type], -1);

	// 情報設定
	m_pModel->SetModel(m_pos, m_rot, m_size);

	return S_OK;
}

//******************************************************************************
// 終了処理
//******************************************************************************
void C3D_Obj::Uninit(void)
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
void C3D_Obj::Update(void)
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
}

//******************************************************************************
// 描画処理
//******************************************************************************
void C3D_Obj::Draw(void)
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
// 情報設定
//******************************************************************************
void C3D_Obj::SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, TYPE type)
{
	m_pos = pos;
	m_rot = rot;
	m_size = size;
	m_Type = type;

	// オブジェクトタイプ設定
	SetObjType(OBJTYPE_MAP_OBJ);
}
//******************************************************************************
// 位置設定
//******************************************************************************
void C3D_Obj::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//******************************************************************************
// 向き設定
//******************************************************************************
void C3D_Obj::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}
//******************************************************************************
// サイズ設定
//******************************************************************************
void C3D_Obj::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}