//*************************************************************************
//
// 曲セレクト画面・各難易度レベル
//
//*************************************************************************
#pragma once 

//*************************************************************************
// インクルード部
//*************************************************************************
#include "CTexture_2D_Base.h" 
#include "MusicSelect_RightFrame.h"
#include "CMusic_Manager.h"

typedef struct
{
	int Easy_Level;
	int Hyper_Level;
	int Master_Level;
}MUSIC_LEVEL;

//*************************************************************************
// クラス定義
//*************************************************************************
class MusicSelect_Level : public CTexture_2D_Base
{
private:
	int					nOver_UP;			// 現在最上にあるオブジェクトの数字
	int					nOver_DOWN;			// 現在最下にあるオブジェクトの数字
	bool				bOne_Flg;			// 初回のみ変更を加えるときに使用

	OBJECT_MOVE_VEC		Move_Vec[7];		// 移動する時の移動方向
	MUSIC_LEVEL*		All_Level;			// 全曲難易度レベル
	MUSIC_LEVEL			Music_Level[7];		// 各曲に設定するべきレベル

	D3DXVECTOR3 MOVE_POSITION;				// オブジェクトが移動する際の移動距離
	D3DXVECTOR3 RIMIT_POSITION_UP;			// オブジェクト座標の上限
	D3DXVECTOR3 POSITION_CENTER_UP_SPEAR;	// オブジェクト上スペア座標
	D3DXVECTOR3 POSITION_CENTER_UP_UP;		// オブジェクトセンター2つ上座標
	D3DXVECTOR3 POSITION_CENTER_UP;			// オブジェクトセンター1つ上座標
	D3DXVECTOR3 POSITION_CENTER;			// オブジェクトセンター座標
	D3DXVECTOR3 POSITION_CENTER_DOWN;		// オブジェクトセンター1つ下座標
	D3DXVECTOR3 POSITION_CENTER_DOWN_DOWN;	// オブジェクトセンター2つ下座標
	D3DXVECTOR3 POSITION_CENTER_DOWN_SPEAR;	// オブジェクト下スペア座標
	D3DXVECTOR3 RIMIT_POSITION_DOWN;		// オブジェクト座標の下限	

	void Set_Move_Vec(D3DXVECTOR3 POSITION, int nNum, int Soezi);

public:
	void Update(bool UP, bool DOWN);
	void Draw(int NUM);

	void Set_Level( int LEVEL, int NUM, int DIFFICULT );

	MusicSelect_Level(void);
	virtual ~MusicSelect_Level(void);
};



//*************************************************************************
// EOF
//*************************************************************************
