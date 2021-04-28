//******************************************************************************
// マップ[map.h]
// Author : 管原司
//******************************************************************************
#ifndef _MAP_H_
#define _MAP_H_
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "scene.h"
//******************************************************************************
// 前方宣言
//******************************************************************************

//******************************************************************************
// クラス
//******************************************************************************
class CMap : public CScene
{
public:
	enum TYPE
	{
		TYPE_TUTORIAL = 0,
		TYPE_GAME
	};
	//読み込む種類
	typedef enum
	{
		LOAD_TYPE_FLOOR = -1,
		LOAD_TYPE_BLOCK,
		LOAD_TYPE_BACK_OBJ,
		LOAD_TYPE_MAX
	}LOAD_TYPE;
	// 種類
	typedef enum
	{
		FLOOR_TYPE_NONE = -1,	// 最小
		FLOOR_TYPE_GLASS,		// 床ブロック
		FLOOR_TYPE_MAX			// 最大
	}FLOOR_TYPE;

	// 種類
	typedef enum
	{
		OBJ_TYPE_NONE = 0,		// 無し
		OBJ_TYPE_NORMAL_BLOCK,	// 床ブロック
		OBJ_TYPE_NEEDLE,		// 針ブロック
		OBJ_TYPE_BUTTON,		// ボタン
		OBJ_TYPE_GATE,			// 扉
		OBJ_TYPE_CHECK_POINT,	// チェックポイント
		OBJ_TYPE_END,			// クリア
		OBJ_TYPE_WOOD_BOX,		// 木箱
		OBJ_TYPE_WOOD,			// 木
		OBJ_TYPE_ENEMY_CREATE,	// 敵生成
		OBJ_TYPE_MAX			// 最大
	}OBJ_TYPE;

	// 背景オブジェクトの種類
	enum BACK_OBJ_TYPE
	{
		BACK_OBJ_NONE = 0,	// 最小
		BACK_OBJ_TREE,		// 木
		BACK_OBJ_STONE_0,	// 石大
		BACK_OBJ_STONE_1,	// 石中
		BACK_OBJ_STONE_2,	// 石小
		BACK_OBJ_MAX		// 最大
	};
	CMap();
	~CMap();
	static CMap *Create(TYPE type);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	void MapCreate(void);
	void FloorCreate(void);
	void FloorLoad(void);
	void BlockCreate(void);
	void BlockLoad(void);
	void BackObjCreate(void);
	void BackObjLoad(void);
	void SetRowCol(LOAD_TYPE load_type);

	FLOOR_TYPE **m_apFloorIndex;		// 行列
	OBJ_TYPE **m_apObjIndex;			// 行列
	BACK_OBJ_TYPE **m_apBackObjIndex;	// 行列
	int m_nRow;							// 行
	int m_nCol;							// 列
	TYPE m_Type;						// 種類
};
#endif