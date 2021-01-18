//--------------------------------------------------
//　レンダラー
//　scene.cpp
// Author : 管原司
//--------------------------------------------------
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "manager.h"
#include "fade.h"
CScene * CScene::m_apScene[PRIORITY_TYPE_MAX][MAX_SCENE] = {};
int CScene::m_nNumAll = 0;
//--------------------------------------------------
//コンストラクタ
//--------------------------------------------------
CScene::CScene(int nPriority)
{
	//初期化
	m_nID = 0;
	m_nPriority = nPriority;
	m_objType = OBJTYPE_NONE;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	{
		//NULLチェック
		if (m_apScene[m_nPriority][nCntScene] == NULL)
		{
			m_nID = nCntScene;
			//メモリ
			m_apScene[m_nPriority][nCntScene] = this;
			m_nNumAll++;
			break;
		}
	}
}
//--------------------------------------------------
//デストラクタ
//--------------------------------------------------
CScene::~CScene()
{
}
//--------------------------------------------------
//全更新
//--------------------------------------------------
void CScene::UpdateAll(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_TYPE_MAX; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			//NULLチェック
			if (m_apScene[nCntPriority][nCntScene] != NULL)
			{
				//全更新
				m_apScene[nCntPriority][nCntScene]->Update();
			}
		}
	}
}
//--------------------------------------------------
//全描画
//--------------------------------------------------
void CScene::DrawAll(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_TYPE_MAX; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			//NULLチェック
			if (m_apScene[nCntPriority][nCntScene] != NULL)
			{
				//全描画
				m_apScene[nCntPriority][nCntScene]->Draw();
			}
		}
	}
}
//--------------------------------------------------
//全終了
//--------------------------------------------------
void CScene::ReleaseAll(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_TYPE_MAX; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			//NULLチェック
			if (m_apScene[nCntPriority][nCntScene] != NULL)
			{
				//全終了
				m_apScene[nCntPriority][nCntScene]->Uninit();
				m_apScene[nCntPriority][nCntScene] = NULL;
			}
		}
	}
}
//--------------------------------------------------
//オブジェの設定
//--------------------------------------------------
void CScene::SetObjType(OBJTYPE objType)
{
	m_objType = objType;
}
//--------------------------------------------------
//座標設定
//--------------------------------------------------
void CScene::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//--------------------------------------------------
//破棄
//--------------------------------------------------
void CScene::Release(void)
{
	if (m_apScene[m_nPriority][m_nID] != NULL)
	{
		int nID = m_nID;
		int nPriority = m_nPriority;
		//メモリの破棄
		delete m_apScene[nPriority][nID];
		//NULLを代入
		m_apScene[nPriority][nID] = NULL;
		m_nNumAll--;
	}
}