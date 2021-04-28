//******************************************************************************
// モデルの階層構造の処理 [model_hierarchy.h]
// Author : 管原司
//******************************************************************************
#ifndef _MODEL_HIERARCHY_H_
#define _MODEL_HIERARCHY_H_

//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "../3DPolygon/scene3d.h"

//******************************************************************************
// インクルードファイル
//******************************************************************************
#define MAX_PARTS (14)	// パーツの最大数
//******************************************************************************
// モデルヒエラルキークラス
//******************************************************************************
class CModelhierarchy :public CScene3d
{
public:
	CModelhierarchy(int nPriority = CScene::OBJTYPE_NONE);
	~CModelhierarchy();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void BindModel(LPD3DXMESH pMesh, LPD3DXBUFFER pBuffMat, DWORD nNumMat, int nldxModelParent);
	void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);
	void SetModelParts(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nCount);
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXVECTOR3 GetSize(void) { return m_size; }
private:
	typedef struct
	{
		LPD3DXMESH m_pMeshParts;	  // メッシュ情報のポインタ
		LPD3DXBUFFER m_pBuffMatParts; // マテリアル情報のポインタ
		DWORD m_nNumMatParts;		  // マテリアル情報の数
		D3DXMATRIX m_mtxWorldParts;	  // 行列計算用
		int m_nldxModelParent;		  // 親モデルのインデックス
	}MODEL;

	typedef struct {
		D3DXVECTOR3 m_pos;	   // 位置
		D3DXVECTOR3 m_rot;	   // 角度
	}MODELPARENT;

	D3DXVECTOR3 m_pos;							// 座標
	D3DXVECTOR3 m_rot;							// 回転
	D3DXVECTOR3 m_size;							// サイズ
	D3DXMATRIX m_mtxWorld;						// 行列計算用
	int m_nNumModel;							// モデルの数
	MODEL m_Model[MAX_PARTS];					// モデルのパーツごとの情報
	MODELPARENT m_modelParent[MAX_PARTS];		// 親
};

#endif