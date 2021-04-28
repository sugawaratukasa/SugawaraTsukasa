//******************************************************************************
// マップ[map.cpp]
// Author : 管原司
//******************************************************************************

//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "../3D/Model/Object/3d_obj.h"
#include "../3D/3DPolygon/floor.h"
#include "../3D/Model/Block/floor_block.h"
#include "../3D/Model/Block/needle_block.h"
#include "../3D/Model/Object/button.h"
#include "../3D/Model/Object/gate.h"
#include "../3D/Model/Object/gate_roof.h"
#include "../3D/Model/Object/tree.h"
#include "../3D/Model/Object/stone.h"
#include "../3D/Model/Block/wood_block.h"
#include "../3D/Model/Object/wood.h"
#include "map.h"
//******************************************************************************
//	マクロ定義
//******************************************************************************
#define GAME_FLOOR_TEXT			("data/Map/Text/Game_Floor.csv")																										// マップ
#define GAME_BLOCK_TEXT			("data/Map/Text/Game_Map.csv")																										// 床
#define GAME_BACK_OBJ_TEXT		("data/Map/Text/Game_BackObj.csv")																									// 背景オブジェクト
#define TUTORIAL_FLOOR_TEXT		("data/Map/Text/Tutorial_Floor.csv")																							// マップ
#define TUTORIAL_BLOCK_TEXT		("data/Map/Text/Tutorial_Map.csv")																							// 床
#define TUTORIAL_BACK_OBJ_TEXT	("data/Map/Text/Tutorial_BackObj.csv")																							// 背景オブジェクト
#define FLOOR_SIZE				(D3DXVECTOR3(180.0f,0.0f,180.0f))																								// 床のサイズ
#define FLOOR_POS				(D3DXVECTOR3(nCountCol * FLOOR_SIZE.x - 1000.0f,-45.0f,nCountRow * FLOOR_SIZE.z - 400.0f))										// 床の位置
#define FLOOR_ROT				(D3DXVECTOR3(0.0f,0.0f,0.0f))																									// 床の向き
#define FLOOR_COL				(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))																								// 色
#define BLOCK_SIZE				(D3DXVECTOR3(30.0f,30.0f,30.0f))																								// ブロックのサイズ
#define BLOCK_POS				(D3DXVECTOR3(nCountCol * BLOCK_SIZE.x - 290.0f,nCountRow * -BLOCK_SIZE.y + 150.0f ,-200.0f))									// ブロックの位置
#define BLOCK_ROT				(D3DXVECTOR3(0.0f,0.0f,0.0f))																									// ブロックの向き
#define NEEDLE_SIZE				(D3DXVECTOR3(30.0f,15.0f,30.0f))																								// 針のサイズ
#define NEEDLE_POS				(D3DXVECTOR3(nCountCol * NEEDLE_SIZE.x - 290.0f,nCountRow * -NEEDLE_SIZE.y * 2 + 150.0f ,-200.0f))								// ブロックの位置
#define BUTTON_SIZE				(D3DXVECTOR3(30.0f,10.0f,30.0f))																								// ボタンサイズ
#define BUTTON_POS				(D3DXVECTOR3(nCountCol * BUTTON_SIZE.x - 290.0f,nCountRow * -BLOCK_SIZE.y + BUTTON_SIZE.y * 1.5f + 150.0f ,-200.0f))			// ボタンの位置
#define BUTTON_ROT				(D3DXVECTOR3(0.0f,0.0f,0.0f))																									// 向き
#define GATE_SIZE				(D3DXVECTOR3(30.5f,37.0f,30.0f))																								// 扉サイズ
#define GATE_POS				(D3DXVECTOR3(nCountCol * BLOCK_SIZE.x - BLOCK_SIZE.x / 2 - 290.0f,nCountRow * -BLOCK_SIZE.y + GATE_SIZE.y + 150.0f ,-200.0f))	// 扉の位置
#define GATE_ROT				(D3DXVECTOR3(0.0f,D3DXToRadian(90.0f),0.0f))																					// 扉向き
#define GATE_ROOF_SIZE			(D3DXVECTOR3(30.0f,37.0f,20.0f))																								// 扉の屋根のサイズ
#define GATE_ROOF_POS			(D3DXVECTOR3(nCountCol * GATE_ROOF_SIZE.x - 290.0f,nCountRow * -BLOCK_SIZE.y + GATE_ROOF_SIZE.y + 150.0f ,-200.0f))				// 扉の屋根の位置
#define GATE_ROOF_ROT			(D3DXVECTOR3(0.0f,D3DXToRadian(270.0f),0.0f))																					// 扉の屋根
#define TREE_SIZE				(D3DXVECTOR3(180.0f,180.0f,180.0f))																								// 木のサイズ
#define TREE_POS				(D3DXVECTOR3(nCountCol * TREE_SIZE.x - 1000.0f,-45.0f,nCountRow * TREE_SIZE.z - 400.0f))										// 木の位置
#define STONE_0_SIZE			(D3DXVECTOR3(30.0f,30.0f,30.0f))																								// 石のサイズ
#define STONE_0_POS				(D3DXVECTOR3(nCountCol * FLOOR_SIZE.x - 1000.0f,-45.0f,nCountRow * FLOOR_SIZE.z - 400.0f))										// 石の位置
#define STONE_1_SIZE			(D3DXVECTOR3(60.0f,60.0f,30.0f))																								// 石のサイズ
#define STONE_1_POS				(D3DXVECTOR3(nCountCol * FLOOR_SIZE.x - 1000.0f,-45.0f,nCountRow * FLOOR_SIZE.z - 400.0f))										// 石の位置
#define STONE_2_SIZE			(D3DXVECTOR3(120.0f,100.0f,30.0f))																								// 石のサイズ
#define STONE_2_POS				(D3DXVECTOR3(nCountCol * FLOOR_SIZE.x - 1000.0f,-45.0f,nCountRow * FLOOR_SIZE.z - 400.0f))										// 石の位置
#define BYTE_NUM				(1024)																															// 最大バイト数
#define WOOD_SIZE				(D3DXVECTOR3(100.0f,200.0f,200.0f))																								// 木のサイズ
#define WOOD_POS				(D3DXVECTOR3(nCountCol * BLOCK_SIZE.x - 290.0f,nCountRow * -BLOCK_SIZE.y + 150.0f,- 200.0f))									// 木の位置
#define GATE_BLCOK_POS			(D3DXVECTOR3(GATE_ROOF_POS.x,GATE_ROOF_POS.y + GATE_ROOF_SIZE.y,GATE_ROOF_POS.z))												// 扉のブロックの位置
//******************************************************************************
// コンストラクタ
//******************************************************************************
CMap::CMap()
{
	m_apFloorIndex		= NULL;		// 行列
	m_apObjIndex		= NULL;		// 行列
	m_apBackObjIndex	= NULL;		// 行列
	m_nRow				= INIT_INT;	// 縦
	m_nCol				= INIT_INT;	// 横
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CMap::~CMap()
{
}
//******************************************************************************
// 生成関数
//******************************************************************************
CMap * CMap::Create(TYPE type)
{
	// CMapのポインタ
	CMap *pMap = NULL;

	// NULLの場合
	if (pMap == NULL)
	{
		// メモリ確保
		pMap = new CMap;

		// NULLでない場合
		if (pMap != NULL)
		{
			// 種類代入
			pMap->m_Type = type;

			// 初期化
			pMap->Init();
		}
	}
	// ポインタを返す
	return pMap;
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CMap::Init(void)
{
	// マップ生成
	MapCreate();

	// 終了
	Uninit();
	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CMap::Uninit(void)
{
	// 破棄
	Release();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CMap::Update(void)
{
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CMap::Draw(void)
{
}
//******************************************************************************
// マップ生成
//******************************************************************************
void CMap::MapCreate(void)
{
	// 床生成
	FloorCreate();

	// ブロック生成
	BlockCreate();

	// 背景オブジェクト生成
	BackObjCreate();
}
//******************************************************************************
// 床の生成
//******************************************************************************
void CMap::FloorCreate(void)
{
	// 床のテキストの行列の数読み込み
	SetRowCol(LOAD_TYPE_FLOOR);

	// 床の情報読み込み
	FloorLoad();

	// NULLでない場合
	if (m_apFloorIndex != NULL)
	{
		// 行分回す
		for (int nCountRow = INIT_INT; nCountRow < m_nRow; nCountRow++)
		{
			// 列分回す
			for (int nCountCol = INIT_INT; nCountCol < m_nCol; nCountCol++)
			{
				switch (m_apFloorIndex[nCountRow][nCountCol])
				{
					// 床
				case FLOOR_TYPE_GLASS:
					// 床生成
					CFloor::Create(FLOOR_POS, FLOOR_ROT, FLOOR_SIZE, FLOOR_COL);
					break;

				default:
					break;
				}
			}
		}
		// 行分回す
		for (int nCntRow = INIT_INT; nCntRow < m_nRow; nCntRow++)
		{
			// メモリ破棄
			delete[] m_apFloorIndex[nCntRow];
		}
		// メモリ破棄
		delete[] m_apFloorIndex;
	}
}
//******************************************************************************
// 床の読み込み
//******************************************************************************
void CMap::FloorLoad()
{
	// FILEのポインタ
	FILE * pfile = NULL;

	// GAMEの場合
	if (m_Type == TYPE_GAME)
	{
		// ファイル読み込み
		pfile = fopen(GAME_FLOOR_TEXT, "r");
	}
	// TYPE_TUTORIALの場合
	if (m_Type == TYPE_TUTORIAL)
	{
		// ファイル読み込み
		pfile = fopen(TUTORIAL_FLOOR_TEXT, "r");
	}

	// csv読み取り処理
	char str[BYTE_NUM];

	// 行
	int nRowIndex = INIT_INT;

	// 列
	int nColIndex = INIT_INT;

	// NULLでない場合
	if (pfile != NULL)
	{
		if (m_apFloorIndex == NULL)
		{
			// メモリ確保
			m_apFloorIndex = new FLOOR_TYPE*[m_nRow];

			// NULLでない場合
			if (m_apFloorIndex != NULL)
			{
				// 行分回す
				for (int nCnt = INIT_INT; nCnt < m_nRow; nCnt++)
				{
					// 列分回す
					m_apFloorIndex[nCnt] = new FLOOR_TYPE[m_nCol];
				}
				// 一行取得
				while (fgets(str, BYTE_NUM, pfile) != NULL)
				{
					char * cTokStr;

					cTokStr = strtok(str, ",");

					// #が含まれていれば抜かす
					char cSearchStr = '#';

					// 対象文字
					strchr(cTokStr, cSearchStr);

					// NULLになるまで
					while (cTokStr != NULL)
					{
						// #が含まれていれば抜かす
						char cSearchStr = '#';

						// 対象文字
						strchr(cTokStr, cSearchStr);

						// 含まれていなかったら出力
						if (strchr(cTokStr, cSearchStr) == NULL)
						{
							// 行列にブロックのタイプを格納
							m_apFloorIndex[nRowIndex][nColIndex] = (FLOOR_TYPE)atoi(cTokStr);

							// 次の列へ
							nColIndex++;
						}
						// NULLを入れる
						cTokStr = strtok(NULL, ",");
					}
					// インクリメント
					nRowIndex++;

					// 0に
					nColIndex = INIT_INT;
				}
			}
		}
		// ファイルを閉じる
		fclose(pfile);
	}
	else
	{
		return;
	}
}
//******************************************************************************
// ブロック生成
//******************************************************************************
void CMap::BlockCreate(void)
{
	// 床のテキストの行列の数読み込み
	SetRowCol(LOAD_TYPE_BLOCK);

	// 床の情報読み込み
	BlockLoad();

	// NULLでない場合
	if (m_apObjIndex != NULL)
	{
		// 行分回す
		for (int nCountRow = INIT_INT; nCountRow < m_nRow; nCountRow++)
		{
			// 列分回す
			for (int nCountCol = INIT_INT; nCountCol < m_nCol; nCountCol++)
			{
				switch (m_apObjIndex[nCountRow][nCountCol])
				{
					// 無し
				case OBJ_TYPE_NONE:
					break;
					// 床
				case OBJ_TYPE_NORMAL_BLOCK:
					// 床生成
					CFloor_Block::Create(BLOCK_POS, BLOCK_ROT, BLOCK_SIZE, CFloor_Block::TYPE_NORMAL);
					break;
					// 針
				case OBJ_TYPE_NEEDLE:
					// 針生成
					CNeedle_Block::Create(NEEDLE_POS, BLOCK_ROT, NEEDLE_SIZE);
					break;
					// ボタン
				case OBJ_TYPE_BUTTON:
					// 床生成
					CFloor_Block::Create(BLOCK_POS, BLOCK_ROT, BLOCK_SIZE, CFloor_Block::TYPE_NORMAL);
					// ボタン生成
					CButton::Create(BUTTON_POS, BUTTON_ROT, BUTTON_SIZE);
					break;
					// ボタン
				case OBJ_TYPE_GATE:
					// 床生成
					CFloor_Block::Create(GATE_BLCOK_POS, BLOCK_ROT, BLOCK_SIZE, CFloor_Block::TYPE_NORMAL);
					// 床生成
					CFloor_Block::Create(BLOCK_POS, BLOCK_ROT, BLOCK_SIZE, CFloor_Block::TYPE_NORMAL);
					// 扉生成
					CGate::Create(GATE_POS, GATE_ROT, GATE_SIZE);
					// 扉生成
					CGate_Roof::Create(GATE_ROOF_POS, GATE_ROOF_ROT, GATE_ROOF_SIZE);
					break;
					// チェックポイント
				case OBJ_TYPE_CHECK_POINT:
					// 床生成
					CFloor_Block::Create(BLOCK_POS, BLOCK_ROT, BLOCK_SIZE, CFloor_Block::TYPE_CHECK_POINT);
					break;
					// 終了
				case OBJ_TYPE_END:
					// 床生成
					CFloor_Block::Create(BLOCK_POS, BLOCK_ROT, BLOCK_SIZE, CFloor_Block::TYPE_END);
					break;
					// 木箱
				case OBJ_TYPE_WOOD_BOX:
					// 木箱生成
					CWood_Block::Create(BLOCK_POS, BLOCK_ROT, BLOCK_SIZE);
					break;
				case OBJ_TYPE_WOOD:
					// 木生成
					CWood::Create(WOOD_POS, WOOD_SIZE);
					break;
				case OBJ_TYPE_ENEMY_CREATE:
					// 床生成
					CFloor_Block::Create(BLOCK_POS, BLOCK_ROT, BLOCK_SIZE, CFloor_Block::TYPE_ENEMY_CREATE);
					break;
				default:
					break;
				}
			}
		}
		// 行分回す
		for (int nCntRow = INIT_INT; nCntRow < m_nRow; nCntRow++)
		{
			// メモリ破棄
			delete[] m_apObjIndex[nCntRow];
		}
		// メモリ破棄
		delete[] m_apObjIndex;
	}
}
//******************************************************************************
// ブロック読み込み
//******************************************************************************
void CMap::BlockLoad(void)
{
	// FILEのポインタ
	FILE * pfile = NULL;

	// GAMEの場合
	if (m_Type == TYPE_GAME)
	{
		// ファイル読み込み
		pfile = fopen(GAME_BLOCK_TEXT, "r");
	}
	// TYPE_TUTORIALの場合
	if (m_Type == TYPE_TUTORIAL)
	{
		// ファイル読み込み
		pfile = fopen(TUTORIAL_BLOCK_TEXT, "r");
	}
	// csv読み取り処理
	char str[BYTE_NUM];

	// 行
	int nRowIndex = INIT_INT;

	// 列
	int nColIndex = INIT_INT;

	// NULLでない場合
	if (pfile != NULL)
	{
		if (m_apObjIndex == NULL)
		{
			// メモリ確保
			m_apObjIndex = new OBJ_TYPE*[m_nRow];

			// NULLでない場合
			if (m_apObjIndex != NULL)
			{
				// 行分回す
				for (int nCnt = INIT_INT; nCnt < m_nRow; nCnt++)
				{
					// 列分回す
					m_apObjIndex[nCnt] = new OBJ_TYPE[m_nCol];
				}
				// 一行取得
				while (fgets(str, BYTE_NUM, pfile) != NULL)
				{
					char * cTokStr;

					cTokStr = strtok(str, ",");

					// #が含まれていれば抜かす
					char cSearchStr = '#';

					// 対象文字
					strchr(cTokStr, cSearchStr);

					// NULLになるまで
					while (cTokStr != NULL)
					{
						// #が含まれていれば抜かす
						char cSearchStr = '#';

						// 対象文字
						strchr(cTokStr, cSearchStr);

						// 含まれていなかったら出力
						if (strchr(cTokStr, cSearchStr) == NULL)
						{
							// 行列にブロックのタイプを格納
							m_apObjIndex[nRowIndex][nColIndex] = (OBJ_TYPE)atoi(cTokStr);

							// 次の列へ
							nColIndex++;
						}
						// NULLを入れる
						cTokStr = strtok(NULL, ",");
					}
					// インクリメント
					nRowIndex++;

					// 0に
					nColIndex = INIT_INT;
				}
			}
		}
		// ファイルを閉じる
		fclose(pfile);
	}
	else
	{
		return;
	}
}
//******************************************************************************
// 背景オブジェクト生成
//******************************************************************************
void CMap::BackObjCreate(void)
{
	// 床のテキストの行列の数読み込み
	SetRowCol(LOAD_TYPE_BACK_OBJ);

	// 床の情報読み込み
	BackObjLoad();

	// NULLでない場合
	if (m_apBackObjIndex != NULL)
	{
		// 行分回す
		for (int nCountRow = INIT_INT; nCountRow < m_nRow; nCountRow++)
		{
			// 列分回す
			for (int nCountCol = INIT_INT; nCountCol < m_nCol; nCountCol++)
			{
				switch (m_apBackObjIndex[nCountRow][nCountCol])
				{
					// 無し
				case BACK_OBJ_NONE:
					break;
					// 木生成
				case BACK_OBJ_TREE:
					CTree::Create(TREE_POS, TREE_SIZE);
					break;
				case BACK_OBJ_STONE_0:
					CStone::Create(STONE_0_POS, STONE_0_SIZE, C3D_Obj::TYPE_STONE_0);
					break;
				case BACK_OBJ_STONE_1:
					CStone::Create(STONE_1_POS, STONE_1_SIZE, C3D_Obj::TYPE_STONE_1);
					break;
				case BACK_OBJ_STONE_2:
					CStone::Create(STONE_2_POS, STONE_2_SIZE, C3D_Obj::TYPE_STONE_2);
					break;
				default:
					break;
				}
			}
		}
		// 行分回す
		for (int nCntRow = INIT_INT; nCntRow < m_nRow; nCntRow++)
		{
			// メモリ破棄
			delete[] m_apBackObjIndex[nCntRow];
		}
		// メモリ破棄
		delete[] m_apBackObjIndex;
	}
}
//******************************************************************************
// 背景オブジェクト読み込み
//******************************************************************************
void CMap::BackObjLoad(void)
{
	// FILEのポインタ
	FILE * pfile = NULL;

	// GAMEの場合
	if (m_Type == TYPE_GAME)
	{
		// ファイル読み込み
		pfile = fopen(GAME_BACK_OBJ_TEXT, "r");
	}
	// GAMEの場合
	if (m_Type == TYPE_TUTORIAL)
	{
		// ファイル読み込み
		pfile = fopen(TUTORIAL_BACK_OBJ_TEXT, "r");
	}
	// csv読み取り処理
	char str[BYTE_NUM];

	// 行
	int nRowIndex = INIT_INT;

	// 列
	int nColIndex = INIT_INT;

	// NULLでない場合
	if (pfile != NULL)
	{
		if (m_apBackObjIndex == NULL)
		{
			// メモリ確保
			m_apBackObjIndex = new BACK_OBJ_TYPE*[m_nRow];

			// NULLでない場合
			if (m_apBackObjIndex != NULL)
			{
				// 行分回す
				for (int nCnt = INIT_INT; nCnt < m_nRow; nCnt++)
				{
					// 列分回す
					m_apBackObjIndex[nCnt] = new BACK_OBJ_TYPE[m_nCol];
				}
				// 一行取得
				while (fgets(str, BYTE_NUM, pfile) != NULL)
				{
					char * cTokStr;

					cTokStr = strtok(str, ",");

					// #が含まれていれば抜かす
					char cSearchStr = '#';

					// 対象文字
					strchr(cTokStr, cSearchStr);

					// NULLになるまで
					while (cTokStr != NULL)
					{
						// #が含まれていれば抜かす
						char cSearchStr = '#';

						// 対象文字
						strchr(cTokStr, cSearchStr);

						// 含まれていなかったら出力
						if (strchr(cTokStr, cSearchStr) == NULL)
						{
							// 行列にブロックのタイプを格納
							m_apBackObjIndex[nRowIndex][nColIndex] = (BACK_OBJ_TYPE)atoi(cTokStr);

							// 次の列へ
							nColIndex++;
						}
						// NULLを入れる
						cTokStr = strtok(NULL, ",");
					}
					// インクリメント
					nRowIndex++;

					// 0に
					nColIndex = INIT_INT;
				}
			}
		}
		// ファイルを閉じる
		fclose(pfile);
	}
	else
	{
		return;
	}
}
//******************************************************************************
// 行と列設定
//******************************************************************************
void CMap::SetRowCol(LOAD_TYPE load_type)
{
	FILE * pfile = NULL;

	// NULLの場合
	if (pfile == NULL)
	{
		// LOAD_TYPE_FLOORの場合
		if (load_type == LOAD_TYPE_FLOOR)
		{
			// GAMEの場合
			if (m_Type == TYPE_GAME)
			{
				pfile = fopen(GAME_FLOOR_TEXT, "r");
			}
			// TUTORIALの場合
			if (m_Type == TYPE_TUTORIAL)
			{
				pfile = fopen(TUTORIAL_FLOOR_TEXT, "r");
			}
		}
		// LOAD_TYPE_BLOCKの場合
		if (load_type == LOAD_TYPE_BLOCK)
		{
			// GAMEの場合
			if (m_Type == TYPE_GAME)
			{
				pfile = fopen(GAME_BLOCK_TEXT, "r");
			}
			// TUTORIALの場合
			if (m_Type == TYPE_TUTORIAL)
			{
				pfile = fopen(TUTORIAL_BLOCK_TEXT, "r");
			}
		}
		// LOAD_TYPE_BACK_OBJの場合
		if (load_type == LOAD_TYPE_BACK_OBJ)
		{
			// GAMEの場合
			if (m_Type == TYPE_GAME)
			{
				pfile = fopen(GAME_BACK_OBJ_TEXT, "r");
			}
			// TUTORIALの場合
			if (m_Type == TYPE_TUTORIAL)
			{
				pfile = fopen(TUTORIAL_BACK_OBJ_TEXT, "r");
			}
		}
		// 行初期化
		m_nRow = INIT_INT;

		// 列初期化
		m_nCol = INIT_INT;

		// csv読み取り処理
		char str[BYTE_NUM];

		// 行
		int nRowIndex = INIT_INT;

		// 列
		int nColIndex = INIT_INT;

		// NULLでない場合
		if (pfile != NULL)
		{
			// 一行取得
			while (fgets(str, BYTE_NUM, pfile) != NULL)
			{
				char * cTokStr;

				cTokStr = strtok(str, ",");

				// NULLになるまで
				while (cTokStr != NULL)
				{
					// #が含まれていれば抜かす
					char cSearchStr = '#';

					// 対象文字
					strchr(cTokStr, cSearchStr);

					// 含まれていなかったら出力
					if (strchr(cTokStr, cSearchStr) == NULL)
					{
						// 次の列へ
						nColIndex++;
					}

					// NULLを入れる
					cTokStr = strtok(NULL, ",");
				}
				// 列保存
				m_nCol = nColIndex;

				// 0に
				nColIndex = INIT_INT;

				// インクリメント
				nRowIndex++;

				// 行保存
				m_nRow = nRowIndex;
			}
			// ファイルを閉じる
			fclose(pfile);
		}
		else
		{
			return;
		}
	}
}