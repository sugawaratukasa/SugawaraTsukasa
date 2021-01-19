//******************************************************************************
// �R���e�B�j���[ [continue.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _CONTINUE_H_
#define _CONTINUE_H_
//******************************************************************************
// �}�N����`
//******************************************************************************
#define CONTINUE_SIZE (D3DXVECTOR3(250.0f,250.0f,0.0f))
//******************************************************************************
// �O���錾
//******************************************************************************
class CNumber;
//******************************************************************************
// �N���X
//******************************************************************************
class CContinue : public CScene2d
{
public:
	CContinue(int nPriority = OBJTYPE_UI);
	~CContinue();
	static CContinue * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	CNumber * m_pNumber;	//�i���o�[�̏��
	D3DXVECTOR3 m_pos;		// �ʒu���W
	D3DXVECTOR3 m_size;		// �T�C�Y
	int m_nContinueCount;	//�J�E���g
	int m_nContinueNum;		//�R���e�B�j���[�i���o�[
};
#endif