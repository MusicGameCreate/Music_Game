//*************************************************************************
//
// フォント生成クラス
//
//*************************************************************************
#pragma once

//*************************************************************************
// インクルード部
//*************************************************************************
#include "CDirectX.h"

//*************************************************************************
// 構造体定義
//*************************************************************************
typedef struct
{
	D3DXVECTOR2	Obj_Pos;	// 座標(画像の中心を原点)
	D3DXVECTOR2	Obj_Size;	// オブジェクトのサイズ(X,Y)
	int			Red;		// 画像のR値
	int			Green;		// 画像のG値
	int			Brue;		// 画像のB値
	int			Alpha;		// 画像のアルファ値
}FONT_DATA;

//*************************************************************************
// クラス定義
//*************************************************************************
class CFont_Base
{
	LPDIRECT3DTEXTURE9*	pTexture;			// テクスチャデータへのポインタ
	VERTEX_2D*			aVertex;			// 頂点情報
	HFONT				hFONT;				// 
	

protected:
	FONT_DATA*			Font_Data;			// テクスチャ情報まとめ構造体
	int					nObject_Num;		// オブジェクトを何個生成するか？(基本は1を入れておいてください)
	int					nUse_Texture_Num;	// テクスチャは何個使用するか？(基本は1を入れておいてください)
	D3DXVECTOR2			Standard_Pos;		// フォント描画の基準点

private:
	void				MakeVertex();		// 頂点情報初期化
	void				SetVertex(); 		// 頂点座標更新
	void				SetColor();	 		// テクスチャカラー情報更新
	void				SetTexture();		// テクスチャ座標更新

protected:
	void				Delete_Texture(int LENGTH);	// テクスチャ削除

public:
	virtual void Init(int FONT_SIZE);								// 初期化
	virtual void Create_Texture(wchar_t* FONT_CHAR,int nLength);	// 文字テクスチャ作成
	virtual void Finalise(int LENGTH);								// 終了
	virtual void Update(void);										// 更新
	virtual void Draw(int NUMBER, int SET_TEXTURE);					// 描画

	CFont_Base(void);											// コンストラクタ
	virtual ~CFont_Base(void);										// デストラクタ
};

//*************************************************************************
// EOF
//*************************************************************************