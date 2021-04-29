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
		SOUND_LABEL_BGM000 = 0,		// BGM0
		SOUND_LABEL_SE_SHOT,		// 弾発射音
		SOUND_LABEL_SE_EXPLOSION,	// 爆発音
		SOUND_LABEL_SE_SELECT,		// 選択音
		SOUND_LABEL_SE_BOM,			// ボム音
		SOUND_LABEL_SE_BEAM,		// ビーム音
		SOUND_LABEL_MAX,
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