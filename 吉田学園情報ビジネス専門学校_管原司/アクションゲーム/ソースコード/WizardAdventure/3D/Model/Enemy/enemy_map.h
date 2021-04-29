//******************************************************************************
// 敵マップ[enemy_map.h]
// Author : 管原司
//******************************************************************************
#ifndef _ENEMY_MAP_H_
#define _ENEMY_MAP_H_
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "scene.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define MAX_ENEMY	(3)	// 敵の最大数
//******************************************************************************
// 前方宣言
//******************************************************************************
class CEnemy;
//******************************************************************************
// クラス
//******************************************************************************
class CEnemy_Map : public CScene
{
public:

	// 種類
	enum OBJ_TYPE
	{
		OBJ_TYPE_NONE = 0,		// 無し
		OBJ_TYPE_BLOCK,			// ブロック
		OBJ_TYPE_ENEMY_FIRE,	// 火の敵
		OBJ_TYPE_ENEMY_ICE,		// 氷の敵
		OBJ_TYPE_MAX			// 最大
	};

	CEnemy_Map(int nPriority = OBJTYPE_ENEMY_MAP);
	~CEnemy_Map();
	static CEnemy_Map *Create(D3DXVECTOR3 pos);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool GetbEnd(void) { return m_bEnd; }
private:
	void ObjCreate(void);
	void ObjLoad(void);
	void SetRowCol(void);

	OBJ_TYPE **m_apObjIndex;			// 行列
	int m_nRow;							// 行
	int m_nCol;							// 列
	D3DXVECTOR3 m_pos;					// 位置
	CEnemy* m_apEnemy[MAX_ENEMY];		// CEnemyのポインタ
	bool m_bEnd;						// 終了判定
};
#endif