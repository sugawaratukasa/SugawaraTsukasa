#ifndef _FADE_H_
#define _FADE_H_
#define FADE_RATE 0.05f
//---------------------------------------
//�O���錾
//---------------------------------------
class CSceneManager;
//---------------------------------------
//�N���X
//---------------------------------------
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
	static CFade * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,int sizeX, int sizeY,CSceneManager::MODE mode);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY, CSceneManager::MODE mode);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//�o�b�t�@
	D3DXVECTOR3 m_pos;
	int m_nSizeX;
	int m_nSizeY;
	FADE m_fade;	//�t�F�[�h
	CSceneManager::MODE m_ModeNext;
	D3DXCOLOR m_colorFade;	//�J���[
};
#endif