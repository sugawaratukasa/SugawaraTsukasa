//******************************************************************************
// �^�C�g�� [title.h]
// Author : �ǌ� �i
//******************************************************************************
#ifndef _TITLE_H_
#define _TITLE_H_
#include "mode.h"
//******************************************************************************
// �N���X
//******************************************************************************
class CTitle : public CMode
{
public:
	
	CTitle();
	~CTitle();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	bool m_bfade;	// �t�F�[�h�p��bool�ϐ�
};
#endif