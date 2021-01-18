//=============================================================================
// score.cpp
// Author : �ǌ��i
//=============================================================================
#include "sound.h"
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "input.h"
#include "inputkeyboard.h"
#include "player.h"
#include "bullet.h"
#include "number.h"
#include "score.h"
#include <cmath>
//-----------------------------------
//�R���X�g���N�^
//-----------------------------------
CScore::CScore(int nPriority) : CScene(nPriority)
{
	memset(m_apNumber, 0, sizeof(m_apNumber));
	m_nScore = 0;
}
//-----------------------------------
//�f�X�g���N�^
//-----------------------------------
CScore::~CScore()
{
}
//-----------------------------------
//����
//-----------------------------------
CScore * CScore::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY)
{
	//CScore�N���X�̃|�C���^
	CScore * pScore;
	//�������m��
	pScore = new CScore;
	//������
	pScore->Init(pos, rot, sizeX, sizeY);
	return pScore;
}
//-----------------------------------
//������
//-----------------------------------
HRESULT CScore::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY)
{
	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		//������
		m_apNumber[nCnt] = CNumber::Create(D3DXVECTOR3(pos.x - (30.0f * nCnt), pos.y, pos.z), sizeX, sizeY);
	}
	return S_OK;
}
//-----------------------------------
//�I��
//-----------------------------------
void CScore::Uninit(void)
{
	//�I��
	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{
			m_apNumber[nCnt]->Uninit();
			delete m_apNumber[nCnt];
			m_apNumber[nCnt] = NULL;
		}
	}
	//�����[�X
	Release();
}
//-----------------------------------
//�X�V
//-----------------------------------
void CScore::Update(void)
{
}
//-----------------------------------
//�`��
//-----------------------------------
void CScore::Draw(void)
{
	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		//�`��
		m_apNumber[nCnt]->Draw();
	}
}
//-----------------------------------
//�Z�b�g
//-----------------------------------
void CScore::SetScore(int nScore)
{
	//�X�R�A���
	m_nScore = nScore;
	//�v�Z�p�ϐ�
	int integer = 0;
	//�J�E���g
	int nCntNumber = 0;

	for (int nCntDigit = 1; nCntDigit <= MAX_SCORE; nCntDigit++, nCntNumber++)
	{
		//1�̈ʈȉ���؂�̂Ă�
		integer = int(m_nScore / std::pow(10.0f, nCntDigit)); 
		integer = int(integer * std::pow(10.0f, nCntDigit));
		//�X�R�A��ݒ�
		m_apNumber[nCntNumber]->SetNumber(int((m_nScore - integer) / std::pow(10.0f, nCntDigit - 1)));
	}
}
//----------------------------------
//�X�R�A�̉��Z
//----------------------------------
void CScore::AddScore(int nValue)
{
	//���Z
	m_nScore += nValue;
	//�X�R�A�Z�b�g
	SetScore(m_nScore);
}
