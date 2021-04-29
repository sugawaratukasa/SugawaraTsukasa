//******************************************************************************
// ブロック [block.h]
// Author : 管原　司
//******************************************************************************
#ifndef _OBJ_H_
#define _OBJ_H_

//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "scene.h"
#include "../3D/Model/model.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define MAX_MATERIAL	(50)
//******************************************************************************
// 前方宣言
//******************************************************************************
class CModel;
//******************************************************************************
// プレイヤークラス
//******************************************************************************
class C3D_Obj :public CScene
{
public:
	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_FLOOR_01,
		TYPE_NEEDLE,
		TYPE_WOOD_BLOCK,
		TYPE_STONE_BLOCK,
		TYPE_BUTTON,
		TYPE_GATE,
		TYPE_GATE_ROOF,
		TYPE_TREE,
		TYPE_STONE_0,
		TYPE_STONE_1,
		TYPE_STONE_2,
		TYPE_WOOD,
		TYPE_MAX
	}TYPE;

	C3D_Obj(int nPriority = OBJTYPE_MAP_OBJ);
	~C3D_Obj();

	static HRESULT Load(void);
	static void Unload(void);
	static HRESULT LoadTexture(void);
	static void UnloadTexture(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	//***************************************
	// セッター
	//***************************************
	void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, TYPE type);
	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);
	void SetSize(D3DXVECTOR3 size);

	//***************************************
	// ゲッター
	//***************************************
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXVECTOR3 GetSize(void) { return m_size; }
	TYPE GetType(void) { return m_Type; }
private:
	static LPD3DXMESH m_pMesh[TYPE_MAX];									// メッシュ情報のポインタ
	static LPD3DXBUFFER m_pBuffMat[TYPE_MAX];								// マテリアル情報のポインタ
	static DWORD m_nNumMat[TYPE_MAX];										// マテリアル情報の数
	D3DXMATRIX m_mtxWorld;													// 行列計算用
	static char* m_apFileName[TYPE_MAX];									// ファイルの名前
	static LPDIRECT3DTEXTURE9 m_apTexture[TYPE_MAX];						// マテリアルの最大数
	D3DXVECTOR3 m_pos;														// 位置
	D3DXVECTOR3 m_rot;														// 角度
	D3DXVECTOR3 m_size;														// 大きさ
	CModel *m_pModel;														// モデルクラスのポインタ
	TYPE m_Type;															// 種類
	bool m_bDraw;															// 描画判定
};

#endif