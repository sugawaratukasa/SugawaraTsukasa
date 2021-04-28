//******************************************************************************
// 敵の生成 [enemy_map.cpp]
// Author : 管原　司
//******************************************************************************
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "enemy.h"
#include "ghost.h"
#include "../3D/Model/Block/floor_block.h"
#include "enemy_map.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define OBJ_TEXT	("data/Map/Text/Enemy_Map.csv")																			// テキストのパス
#define BLOCK_SIZE	(D3DXVECTOR3(30.0f,30.0f,30.0f))																		// ブロックのサイズ
#define BLOCK_ROT	(D3DXVECTOR3(0.0f,0.0f,0.0f))																			// 向き
#define BLOCK_POS	(D3DXVECTOR3(nCountCol * BLOCK_SIZE.x + m_pos.x - 500,nCountRow * -BLOCK_SIZE.y + 150.0f ,-200.0f))		// ブロックの位置
#define ENEMY_SIZE	(D3DXVECTOR3(30.0f,30.0f,30.0f))																		// 敵のサイズ
#define ENEMY_POS	(D3DXVECTOR3(nCountCol * ENEMY_SIZE.x + m_pos.x - 500.0f,nCountRow * -ENEMY_SIZE.y + 150.0f ,-200.0f))	// 敵の位置
#define BYTE_NUM	(1024)																									// 読み取れる文字数
#define MIN_ENEMY	(0)																										// 敵の最小数
//******************************************************************************
// コンストラクタ
//******************************************************************************
CEnemy_Map::CEnemy_Map(int nPriority) : CScene(nPriority)
{
	m_apObjIndex	= NULL;
	m_nRow			= INIT_INT;
	m_nCol			= INIT_INT;
	m_pos			= INIT_D3DXVECTOR3;
	memset(m_apEnemy, NULL, sizeof(m_apEnemy));
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CEnemy_Map::~CEnemy_Map()
{
}
//******************************************************************************
// 生成関数
//******************************************************************************
CEnemy_Map * CEnemy_Map::Create(D3DXVECTOR3 pos)
{
	// CEnemy_Mapのポインタ
	CEnemy_Map *pEnemy_Map = NULL;

	// NULLの場合
	if (pEnemy_Map == NULL)
	{
		// メモリ確保
		pEnemy_Map = new CEnemy_Map;

		// NULLでない場合
		if (pEnemy_Map != NULL)
		{
			// 位置代入
			pEnemy_Map->m_pos = pos;

			// 初期化関数
			pEnemy_Map->Init();
		}
	}
	// ポインタを返す
	return pEnemy_Map;
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CEnemy_Map::Init(void)
{
	// オブジェクトタイプ設定
	SetObjType(OBJTYPE_ENEMY_MAP);

	// 生成
	ObjCreate();
	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CEnemy_Map::Uninit(void)
{
	// 破棄
	Release();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CEnemy_Map::Update(void)
{
	// 状態のカウント
	int nEnemyNum = INIT_INT;
	// 最大数分繰り返す
	for (int nCnt = INIT_INT; nCnt < MAX_ENEMY; nCnt++)
	{
		// NULLでない場合
		if (m_apEnemy[nCnt] != NULL)
		{
			// インクリメント
			nEnemyNum++;

			// 状態取得
			int nState = m_apEnemy[nCnt]->GetState();

			// 死亡状態の場合
			if (nState == CEnemy::STATE_DEAD)
			{
				m_apEnemy[nCnt] = NULL;

				// デクリメント
				nEnemyNum--;
			}
		}
	}
	// nEnemyNumが0の場合
	if (nEnemyNum == MIN_ENEMY)
	{
		// trueに
		m_bEnd = true;
	}
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CEnemy_Map::Draw(void)
{
}
//******************************************************************************
// ブロック生成
//******************************************************************************
void CEnemy_Map::ObjCreate(void)
{
	// 床のテキストの行列の数読み込み
	SetRowCol();

	// 床の情報読み込み
	ObjLoad();

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
					// ブロック
				case OBJ_TYPE_BLOCK:
					// ブロック生成
					CFloor_Block::Create(BLOCK_POS, BLOCK_ROT, BLOCK_SIZE, CFloor_Block::TYPE_ENEMY);
					break;
				case OBJ_TYPE_ENEMY_FIRE:
					// 火の敵生成
					for (int nCnt = INIT_INT; nCnt < MAX_ENEMY; nCnt++)
					{
						if (m_apEnemy[nCnt] == NULL)
						{
							m_apEnemy[nCnt] = CGhost::Create(ENEMY_POS, ENEMY_SIZE, CGhost::TYPE_FIRE);
							break;
						}
					}
					break;
				case OBJ_TYPE_ENEMY_ICE:
					// 氷の敵生成
					for (int nCnt = INIT_INT; nCnt < MAX_ENEMY; nCnt++)
					{
						if (m_apEnemy[nCnt] == NULL)
						{
							m_apEnemy[nCnt] = CGhost::Create(ENEMY_POS, ENEMY_SIZE, CGhost::TYPE_ICE);
							break;
						}
					}
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
void CEnemy_Map::ObjLoad(void)
{
	// ファイル読み込み
	FILE * pfile = fopen(OBJ_TEXT, "r");

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
// 行と列設定
//******************************************************************************
void CEnemy_Map::SetRowCol(void)
{
	FILE * pfile = NULL;

	// NULLの場合
	if (pfile == NULL)
	{
		// ファイル読み込み
		pfile = fopen(OBJ_TEXT, "r");

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