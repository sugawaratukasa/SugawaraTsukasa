//******************************************************************************
// �t�F�[�h [fade.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _FADE_H_
#define _FADE_H_
//******************************************************************************
// �}�N����`
//******************************************************************************
#define FADE_RATE (0.05f)											// �t�F�[�h�ړ���
#define FADE_SIZE (D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f))	// �T�C�Y
//******************************************************************************
// �O���錾
//******************************************************************************
class CSceneManager;
//******************************************************************************
// �N���X
//******************************************************************************
class CFade 
{
public:
	typedef enum
	{
		FADE_NONE = -1,
		FADE_IN,
		FADE_OUT,
		FADE_MAX
	}FADE;
	CFade();
	~CFade();
	static CFade * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CSceneManager::MODE mode);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// �o�b�t�@
	D3DXVECTOR3 m_pos;						// �ʒu���W
	D3DXVECTOR3 m_size;						// �T�C�Y
	FADE m_fade;							// �t�F�[�h
	CSceneManager::MODE m_ModeNext;			// ���[�h
	D3DXCOLOR m_colorFade;					// �J���[
};
#endif