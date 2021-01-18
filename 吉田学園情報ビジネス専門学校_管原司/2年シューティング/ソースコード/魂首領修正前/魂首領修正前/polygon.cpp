//---------------------------------------------------
// Polygon
// Polygon.cpp
// Author:	�ǌ��i
//---------------------------------------------------
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
#include "polygon.h"
//--------------------------------------------------
//�R���X�g���N�^
//--------------------------------------------------
CPolygon::CPolygon(int nPriority) : CScene2d(nPriority)
{
}
//--------------------------------------------------
//�f�X�g���N�^
//--------------------------------------------------
CPolygon::~CPolygon()
{
}
//--------------------------------------------------
//����
//--------------------------------------------------
CPolygon * CPolygon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY)
{
	//CPlayer�N���X�̃|�C���^
	CPolygon * pPolygon;
	//�������m��
	pPolygon = new CPolygon;
	//������
	pPolygon->Init(pos, rot, sizeX, sizeY);
	return pPolygon;
}
//--------------------------------------------------
//������
//--------------------------------------------------
HRESULT CPolygon::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY)
{
	//������
	CScene2d::Init(pos, rot, sizeX, sizeY);
	//�e�̏����ݒ�
	SetRGBA(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	return S_OK;
}
//--------------------------------------------------
//�I��
//--------------------------------------------------
void CPolygon::Uninit(void)
{
	//�I��
	CScene2d::Uninit();
}
//--------------------------------------------------
//�X�V
//--------------------------------------------------
void CPolygon::Update(void)
{
	//�X�V
	CScene2d::Update();
}
//--------------------------------------------------
//�`��
//--------------------------------------------------
void CPolygon::Draw(void)
{
	//�`��
	CScene2d::Draw();
}
