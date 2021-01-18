//---------------------------------------------------
// number
// score.h
// Authur:	�ǌ��i
//---------------------------------------------------
#ifndef _CONTINUE_H_
#define _CONTINUE_H_
#define CONTINUE_SIZE_X 250
#define CONTINUE_SIZE_Y 250
class CNumber;
//---------------------------------------------------
//�N���X
//---------------------------------------------------
class CContinue : public CScene2d
{
public:
	CContinue(int nPriority = PRIORITY_TYPE_UI);
	~CContinue();
	static CContinue * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	CNumber * m_pNumber;	//�i���o�[�̏��
	int m_nContinueCount;	//�J�E���g
	int m_nContinueNum;		//�R���e�B�j���[�i���o�[
};
#endif