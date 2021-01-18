//--------------------------------------------------
//�@�����_���[
//�@scene.cpp
// Author : �ǌ��i
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
//�R���X�g���N�^
//--------------------------------------------------
CScene::CScene(int nPriority)
{
	//������
	m_nID = 0;
	m_nPriority = nPriority;
	m_objType = OBJTYPE_NONE;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	{
		//NULL�`�F�b�N
		if (m_apScene[m_nPriority][nCntScene] == NULL)
		{
			m_nID = nCntScene;
			//������
			m_apScene[m_nPriority][nCntScene] = this;
			m_nNumAll++;
			break;
		}
	}
}
//--------------------------------------------------
//�f�X�g���N�^
//--------------------------------------------------
CScene::~CScene()
{
}
//--------------------------------------------------
//�S�X�V
//--------------------------------------------------
void CScene::UpdateAll(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_TYPE_MAX; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			//NULL�`�F�b�N
			if (m_apScene[nCntPriority][nCntScene] != NULL)
			{
				//�S�X�V
				m_apScene[nCntPriority][nCntScene]->Update();
			}
		}
	}
}
//--------------------------------------------------
//�S�`��
//--------------------------------------------------
void CScene::DrawAll(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_TYPE_MAX; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			//NULL�`�F�b�N
			if (m_apScene[nCntPriority][nCntScene] != NULL)
			{
				//�S�`��
				m_apScene[nCntPriority][nCntScene]->Draw();
			}
		}
	}
}
//--------------------------------------------------
//�S�I��
//--------------------------------------------------
void CScene::ReleaseAll(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_TYPE_MAX; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			//NULL�`�F�b�N
			if (m_apScene[nCntPriority][nCntScene] != NULL)
			{
				//�S�I��
				m_apScene[nCntPriority][nCntScene]->Uninit();
				m_apScene[nCntPriority][nCntScene] = NULL;
			}
		}
	}
}
//--------------------------------------------------
//�I�u�W�F�̐ݒ�
//--------------------------------------------------
void CScene::SetObjType(OBJTYPE objType)
{
	m_objType = objType;
}
//--------------------------------------------------
//���W�ݒ�
//--------------------------------------------------
void CScene::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//--------------------------------------------------
//�j��
//--------------------------------------------------
void CScene::Release(void)
{
	if (m_apScene[m_nPriority][m_nID] != NULL)
	{
		int nID = m_nID;
		int nPriority = m_nPriority;
		//�������̔j��
		delete m_apScene[nPriority][nID];
		//NULL����
		m_apScene[nPriority][nID] = NULL;
		m_nNumAll--;
	}
}