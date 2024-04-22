#include"sound.h"
#include"DxLib.h"

int Sound::Bgm::handle[BGM_MAX_NUM];
int Sound::Se::handle[SE_MAX_NUM];

//BGMのパス
char bgmSoundPath[BGM_MAX_NUM][255] =
{
	//音楽
	"data/sound/bgm/titleBGM.mp3",	//タイトル
	"data/sound/bgm/playBGM.mp3",	//プレイ
	"data/sound/bgm/resultBGM.mp3",	//リザルト
};

//音量
int soundVolume_bgm[BGM_MAX_NUM] =
{
	60,	//タイトル
	50,	//プレイ
	60,	//リザルト
};

//SEのパス
char seSoundPath[SE_MAX_NUM][255] =
{
	"data/sound/se/system.mp3",		//システム
	"data/sound/se/get.mp3",		//アイテムゲット
	"data/sound/se/guarantee.mp3",	//エリアに確保
	"data/sound/se/start.mp3",		//ゲームスタート
	"data/sound/se/time.mp3",		//時間制限
	"data/sound/se/finish.mp3",		//ゲーム終了
};

//音量
int soundVolume_se[SE_MAX_NUM] =
{
	80,			//システム
	80,			//アイテムゲット
	80,			//エリアに確保
	80,			//ゲームスタート
	80,		//時間制限
	80,			//ゲーム終了
};

//サウンドまとめ初期化
void Sound::Init()
{
	Bgm::Init();
	Se::Init();
}

//BGMの初期化
void Sound::Bgm::Init()
{
	for (int i = 0; i < BGM_MAX_NUM; i++)
	{
		//読み込み
		handle[i] = LoadSoundMem(bgmSoundPath[i]);
		//ボリュームの設定
		ChangeVolumeSoundMem(255 * soundVolume_bgm[i] / 100, handle[i]);
	}
}
//BGMの通常処理：種類
void Sound::Bgm::Play(int type)
{
	//BGMの再生
	PlaySoundMem(handle[type], DX_PLAYTYPE_LOOP, true);
}
//BGMの音量調節：種類,音量(ﾊﾟｰｾﾝﾃｰｼﾞ)
void Sound::Bgm::SetVolume(int type, int volume)
{
	//音量の設定（0〜255）（↓はvolume％の音量で出力）
	ChangeVolumeSoundMem(255 * volume / 100, handle[type]);
}
//BGMの停止：種類
void Sound::Bgm::StopSound(int type)
{
	//BGMの停止
	StopSoundMem(handle[type]);
}

//SEの初期化
void Sound::Se::Init()
{
	for (int i = 0; i < SE_MAX_NUM; i++)
	{
		//読み込み
		handle[i] = LoadSoundMem(seSoundPath[i]);
		//ボリュームの設定
		int vo = soundVolume_se[i];
		SetVolume(i, vo);
	}
}
//SEの通常処理：種類
void Sound::Se::Play(int type)
{
	//効果音の再生
	PlaySoundMem(handle[type], DX_PLAYTYPE_BACK, true);
}
//SEの音量調節：種類,音量(ﾊﾟｰｾﾝﾃｰｼﾞ)
void Sound::Se::SetVolume(int type, int volume)
{
	//音量の設定（0〜255）（↓はvolume％の音量で出力）
	ChangeVolumeSoundMem(255 * volume / 100, handle[type]);
}