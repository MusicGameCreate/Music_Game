//*******************************************************************************************************
//
// 3D画像描画基本クラス
//
//*******************************************************************************************************
#pragma once

//*******************************************************************************************************
// インクルード部
//*******************************************************************************************************
#include "Define.h"
#include "CDirectX.h"	// DirectX情報
#include "CInput.h"		// キーボード、マウス情報
#include "CSound.h"		// サウンド情報

#include "Camera.h"

#include "Debug_DataSave.h"

// 列挙型
enum
{
	DIRECTION_UP,
	DIRECTION_DOWN,
	DIRECTION_LEFT,
	DIRECTION_RIGHT,
	DIRECTION_CENTER,
};

//*******************************************************************************************************
// 構造体定義
//*******************************************************************************************************
typedef struct
{
	D3DXMATRIX	mtxWorld;		// ワールドマトリクス
	D3DXMATRIX	mtxScale;		// 拡大率
	D3DXMATRIX	mtxTranslate;	// 平行移動
	D3DXMATRIX	mtxRot;			// 回転

	D3DXVECTOR3	Obj_Pos;		// 座標(画像の中心を原点)
	D3DXVECTOR2	Obj_Size;		// オブジェクトのサイズ(X,Y)
	D3DXVECTOR2	Tex_Pos;		// テクスチャ座標(0.0f～1.0f)
	D3DXVECTOR2	Tex_Anim;		// 1アニメーション毎のテクスチャ座標(1アニメーションなら1.0f)
	int			Red;			// 画像のR値
	int			Green;			// 画像のG値
	int			Brue;			// 画像のB値
	int			Alpha;			// 画像のアルファ値
	D3DXVECTOR3	Obj_Rot;		// 回転角度
	D3DXVECTOR3	Obj_Scale;		// 拡大率

}TEXTURE_3D_DATA;

//*******************************************************************************************************
// クラス定義
//*******************************************************************************************************
class CTexture_3D_Base
{
	
	D3DXMATRIX				mtxView;			// ビュー行列
	VERTEX_3D*				aVertex;			// 頂点情報格納

protected:
	TEXTURE_3D_DATA*		Tex_3D_Data;		// テクスチャ情報まとめ構造体
	LPDIRECT3DTEXTURE9*		pTexture;			// テクスチャデータへのポインタ
	int						nObject_Num;		// オブジェクトを何個生成するか？(基本は1を入れておいてください)
	int						nUse_Texture_Num;	// テクスチャは何個使用するか？(基本は1を入れておいてください)

	bool					bBillboard;			// ビルボードにするかどうか指定
	bool					bAlphaTest;			// αテストを適用するかどうか指定

	bool					UseQuaternion;
	D3DXQUATERNION			q;					// 単位クォータニオン'q'を生成
	D3DXMATRIX				TurnMat;			// 回転行列
	D3DXMATRIX				mat;				//平行移動行列
	D3DXVECTOR3				NAxis;				// 任意の中心軸

	int						ScaleDirection;		// 拡縮時の方向

private:
	void					MakeVertex();		// 頂点情報初期化
	void					SetVertex();		// 頂点情報更新
	void					SetTexture();		// テクスチャ座標情報更新
	void					SetColor();			// テクスチャカラー情報更新

public:	
	virtual void Init();										// 初期化
	virtual void Load_Texture(char* TEXTURE_FILE, int NUMBER);	// テクスチャ読み込み
	virtual void Finalise();									// 終了
	virtual void Update();										// 更新
	virtual void Draw(int NUMBER, int SET_TEXTURE);				// 描画

	CTexture_3D_Base();											// コンストラクタ
	virtual ~CTexture_3D_Base();								// デストラクタ
	
	void QuaternionRotate();
};

//*******************************************************************************************************
// EOF
//*******************************************************************************************************