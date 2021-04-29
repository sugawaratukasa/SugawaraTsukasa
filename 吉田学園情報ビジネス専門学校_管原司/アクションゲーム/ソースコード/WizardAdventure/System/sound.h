//******************************************************************************
// サウンド処理 [sound.h]
// Author : 管原　司
//******************************************************************************
#ifndef _SOUND_H_
#define _SOUND_H_
//******************************************************************************
// ファイルインクルード
//******************************************************************************
#include <xaudio2.h>
//******************************************************************************
// マクロ定義
//******************************************************************************
class CSound
{
public:
	typedef enum
	{
		SOUND_LABEL_BGM_TITLE = 0,		// BGMタイトル
		SOUND_LABEL_BGM_GAME,			// BGMゲーム
		SOUND_LABEL_BGM_RESULT,			// BGMリザルト
		SOUND_LABEL_SE_WALK,			// 移動音
		SOUND_LABEL_SE_BLOCK_CREATE,	// 箱生成
		SOUND_LABEL_SE_SELECT,			// 選択音
		SOUND_LABEL_SE_DETERMINATION,	// 決定音
		SOUND_LABEL_SE_FIRE_BALL,		// 火の球
		SOUND_LABEL_SE_FIRE_EXPLOSION,	// 爆発音
		SOUND_LABEL_SE_ICE_EXPLOSION,	// 爆発音
		SOUND_LABEL_SE_BUTTON_PUSH,		// ボタンを押した音
		SOUND_LABEL_SE_GATE_OPEN,		// 扉が開いた音
		SOUND_LABEL_SE_RESPAWN,			// リスポーン音
		SOUND_LABEL_MAX					// 最大
	} SOUND_LABEL;
	typedef enum
	{
		TYPE_LOOP = -1,
		TYPE_SE,
		TYPE_MAX
	}TYPE;
	CSound();
	~CSound();
	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);

private:
	typedef struct
	{
		char *pFilename;	// ファイル名
		int nCntLoop;		// ループカウント
	}PARAM;

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
	IXAudio2 *m_pXAudio2;									// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *m_pMasteringVoice;				// マスターボイス
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// ソースボイス
	BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// オーディオデータサイズ
	static PARAM m_aParam[SOUND_LABEL_MAX];					// 各音素材のパラメータ
};
#endif