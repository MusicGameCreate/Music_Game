//***********************************************************************************************************
//
// 曲セレクトシーン一括管理
//
//***********************************************************************************************************
#pragma once

//***********************************************************************************************************
// インクルード部
//***********************************************************************************************************
#include "BaseScene.h"
#include "IPlayDataMgr.h"
#include "MusicSelect_BackGround.h"
#include "MusicSelect_BackEffect.h"
#include "MusicSelect_LeftFrame.h"

#include "MusicSelect_RightFrame.h"
#include "MusicSelect_Score.h"
#include "MusicSelect_BPM.h"
#include "MusicSelect_Illustrator.h"
#include "MusicSelect_Creator.h"

#include "MusicSelect_RightFrame.h"
#include "MusicSelect_Jacket.h"
#include "MusicSelect_Level.h"


#include "CMusic_Manager.h"
#include "MusicDataReader.h"

typedef struct
{
	MusicData	Music_Data;			// 曲データのほとんど
	int			Hi_Score[3];		// 各難易度ハイスコア
	int			Difficult_Level[3];	// 各難易度レベル
	int			Clear_Mark[3];		// 各難易度クリアマーク種類
	int			Button_Rate[3];		// 各難易度ボタン割合
	int			Click_Rate[3];		// 各難易度クリック割合
	int			Wheel_Rate[3];		// 各難易度ホイール割合

}MUSICSELECT_ALL_DATA;

//***********************************************************************************************************
// クラス定義
//***********************************************************************************************************
class MusicSelect_Scene : public CBaseScene
{
private:
	// オブジェクトはここで
	MusicSelect_BackGround*		BackGround;
	MusicSelect_BackEffect*		BackEffect;
	MusicSelect_LeftFrame*		LeftFrame;

	MusicSelect_Score*			Score;
	MusicSelect_BPM*			BPM;
	MusicSelect_Illustrator*	Illustrator;
	MusicSelect_Creator*		Creator;

	MusicSelect_RightFrame*		RightFrame;			// フレーム
	MusicSelect_Jacket*			Jacket;				// ジャケット
	MusicSelect_Level*			Level;				// 各難易度レベル

	CMusicDataReader			Reader;
	MUSICSELECT_ALL_DATA*		M_Data;

	int							nSelect_Data;		// 現在選択中の曲データ
	int							nNow_Difficult;		// 現在難易度
	bool						bMove_Up;			// 上移動フラグ
	bool						bMove_Down;			// 下移動フラグ
	int							nFrame_Count;
	bool						bData_Change_Flg;	// データ変更タイミング

	IPlayDataMgr*				mPlayDataMgr;
public:

	void Initialize();
	void Finalize();
	void Update(void);			// 更新
	void Draw(void);				// 描画

	MusicSelect_Scene(ISceneChanger* changer, IPlayDataMgr* dataMgr);			// コンストラクタ
	~MusicSelect_Scene(void) override;	// デストラクタ

};

//***********************************************************************************************************
// EOF
//***********************************************************************************************************