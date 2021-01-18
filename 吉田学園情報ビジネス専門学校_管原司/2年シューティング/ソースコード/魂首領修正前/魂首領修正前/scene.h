//---------------------------------------------------
// �����_���[
// scene.h
// Authur:	�ǌ��i
//---------------------------------------------------
#ifndef _SCENE_H_
#define _SCENE_H_
//---------------------------------------------------
//�C���N���[�h�t�@�C��
//---------------------------------------------------
#include <dinput.h>
#include "d3dx9.h"

//---------------------------------------------------
//�}�N����`
//---------------------------------------------------
#define MAX_SCENE 1024
#define MAX_SCENE_PRIORITY 12
#define DEFAULT_PRIORITY 3
//---------------------------------------------------
//�N���X
//---------------------------------------------------
class CScene
{
public:
	typedef enum
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_BG,
		OBJTYPE_SHIP,
		OBJTYPE_SHIP_WEPON1,
		OBJTYPE_SHIP_WEPON2,
		OBJTYPE_SHIP_WEPON3,
		OBJTYPE_SHIP_WEPON4,
		OBJTYPE_SHIP_WEPON5,
		OBJTYPE_SHIP_WEPON6,
		OBJTYPE_LIFE,
		OBJTYPE_PLAYER_BULLET,
		OBJTYPE_ENEMY_BULLET,
		OBJTYPE_EXPLOSION,
		OBJTYPE_PLAYER,
		OBJTYPE_ENEMY,
		OBJTYPE_BOSS,
		OBJTYPE_BOSS_RIGHT,
		OBJTYPE_BOSS_LEFT,
		OBJTYPE_ITEM,
		OBJTYPE_MAX
	}OBJTYPE;
	typedef enum
	{
		PRIORITY_TYPE_NONE = 0,
		PRIORITY_TYPE_BG,
		PRIORITY_TYPE_SHIP,
		PRIORITY_TYPE_BULLET,
		PRIORITY_TYPE_ENEMY,
		PRIORITY_TYPE_BOSS,
		PRIORITY_TYPE_EXPLOSION,
		PRIORITY_TYPE_ITEM,
		PRIORITY_TYPE_PLAYER,
		PRIORITY_TYPE_UI,
		PRIORITY_TYPE_POLYGON,
		PRIORITY_TYPE_MAX
	}PRIORITYTYPE;
	CScene(int nPriority = DEFAULT_PRIORITY);
	virtual ~CScene();
	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int sizeX, int sizeY) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	static void UpdateAll(void);
	static void DrawAll(void);
	static void ReleaseAll(void);
	void SetObjType(OBJTYPE objType);
	OBJTYPE GetObjType(void) { return m_objType; }
	void SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	static CScene *GetScene(int nPriority, int nCnt) { return m_apScene[nPriority][nCnt]; }
	static int GetNumAll(void) { return m_nNumAll; }
protected:
	void Release(void);
private:
	static CScene * m_apScene[PRIORITY_TYPE_MAX][MAX_SCENE];	//�I�u�W�F�N�g�̏��
	OBJTYPE m_objType;
	static int m_nNumAll;	//�I�u�W�F�N�g�̑���
	int m_nPriority;	//�`��̗D�揇��
	int m_nID;	//�C���f�b�N�X
	D3DXVECTOR3 m_pos;
};
#endif