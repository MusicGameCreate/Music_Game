//***********************************************************************************************************
//
// 曲データ一括管理クラス
//
//***********************************************************************************************************

//***********************************************************************************************************
// インクルード部
//***********************************************************************************************************
#include "CMusic_Manager.h"
#include <locale.h>


MUSIC_DATA*		CMusic_Manager::Music_Data;		// 曲情報まとめ構造体
int				CMusic_Manager::nMusic_Count;	// 曲総数
//***********************************************************************************************************
// 初期化
//***********************************************************************************************************
void CMusic_Manager::Init(void)
{
	Music_Data		= NULL;
	nMusic_Count	= 0;
}

//***********************************************************************************************************
// 終了
//***********************************************************************************************************
void CMusic_Manager::Finalise(void)
{
	delete Music_Data;
}

//***********************************************************************************************************
// データ一括読み込み
//***********************************************************************************************************
void CMusic_Manager::Load(void)
{
	HANDLE			hFind_Folder = 0;		// フォルダを指定する時に使用
	HANDLE			hFind_File = 0;			// ファイルを指定する時に使用
	WIN32_FIND_DATA win32fd;			// 抽出したファイル情報がここに入る(ファイル名等)
	char			szFileName[256];

	// フォルダ内の一番上の「フォルダ」を指定( *.拡張子で全ての同拡張子データを参照 )
	//****************************************************************************
	hFind_Folder = FindFirstFile("../DATA/MUSIC/*.music", &win32fd);

	if ( hFind_Folder == INVALID_HANDLE_VALUE )
	{	// ファイルが無かったら終了
		MessageBox( CWindowAPI::GethWnd(), "曲が一曲も入っていません！終了します", "曲読み込み失敗！", MB_OK );
		exit( EXIT_FAILURE );
	}
	else
	{
		// 曲数インクリメント
		nMusic_Count++;
	}

	//****************************************************************************
	// 曲データ総数カウント
	//****************************************************************************
	while (1)
	{
		// FindNextFile() = 失敗すれば「0」を返す
		if ( FindNextFile( hFind_Folder, &win32fd ) != 0 )
		{	// フォルダがあったら曲総数カウント 
			nMusic_Count ++;
		}
		else
		{	// フォルダが無くなったらカウント終了
			break;
		}
	}

	// 楽曲の個数分領域確保
	//****************************************************************************
	Music_Data = new MUSIC_DATA[nMusic_Count];


	// 曲データ一括初期化
	//****************************************************************************
	for ( int i = 0 ; i < nMusic_Count ; i ++ )
	{
		Music_Data[i].Music_Title_Length	= 0;		// 曲タイトル長さ
		Music_Data[i].Music_Title[0]		= '\0';		// 曲タイトル名
		Music_Data[i].Folder_Path[0]		= '\0';		// フォルダまでのパス
		Music_Data[i].Fumen_Path[0][0]		= '\0';		// イージー譜面のパス
		Music_Data[i].Fumen_Path[1][0]		= '\0';		// ハイパー譜面のパス
		Music_Data[i].Fumen_Path[2][0]		= '\0';		// マスター譜面のパス
		Music_Data[i].Music_Path[0]			= '\0';		// 音源のパス
		Music_Data[i].Picture_Path[0]		= '\0';		// 画像のパス
		Music_Data[i].Hiscore_Path[0]		= '\0';		// ハイスコアのパス

		Music_Data[i].Easy_In				= false;	// イージー譜面があるかどうか
		Music_Data[i].Hyper_In				= false;	// ハイパー譜面があるかどうか
		Music_Data[i].Master_In				= false;	// マスター譜面があるかどうか

		Music_Data[i].Jacket_In				= false;	// ジャケット画像が入っているかどうか

		Music_Data[i].Easy_Hiscore			= 0;		// イージー譜面のハイスコア
		Music_Data[i].Hyper_Hiscore			= 0;		// ハイパー譜面のハイスコア
		Music_Data[i].Master_Hiscore		= 0;		// マスター譜面のハイスコア

		Music_Data[i].Easy_ClearMark[0]		= '\0';		// イージー譜面のクリアマーク
		Music_Data[i].Hyper_ClearMark[0]	= '\0';		// ハイパー譜面のクリアマーク
		Music_Data[i].Master_ClearMark[0]	= '\0';		// マスター譜面のクリアマーク
	}

	// ../DATA/MUSIC フォルダの一番上に指定
	//****************************************************************************
	hFind_Folder = FindFirstFile("../DATA/MUSIC/*.music", &win32fd);

	// 曲総数分ループ
	//****************************************************************************
	for ( int i = 0 ; i < nMusic_Count ; i ++ )
	{
		// 曲タイトル・タイトル文字数取得
		//************************************************************************
		int		Work = 0;
		wchar_t ws[100];
		sprintf(szFileName, "%s", win32fd.cFileName);

		setlocale( LC_CTYPE, "jpn" );			// mbstowcs()関数を使用するために必要
		Work = mbstowcs( ws, szFileName, 100);	// 文字列長検査
		Work -= 6;								// 「.music」 分減算

		// タイトル文字数格納
		//*****************************************
		Music_Data[i].Music_Title_Length = Work;

		// タイトル文字列格納
		//*****************************************
		ws[Work] = L'\0';
		sprintf( Music_Data[i].Music_Title, "%ls", ws );

		// カレントからのディレクトリを付けて再上書き ( ○○.music → ../DATA/MUSIC/○○.music )
		//************************************************************************
		sprintf(szFileName, "../DATA/MUSIC/%s", win32fd.cFileName);
		strcpy(Music_Data[i].Folder_Path, szFileName);


		int Length = 0;
		int Error = 1;
		char Difficult_Work[1];

		// 譜面データまでのパスを抽出　( △△.score   → ../DATA/MUSIC/○○.music/△△.score )
		strcpy(szFileName, Music_Data[i].Folder_Path);
		strcat(szFileName, "/*.score");

		for ( int j = 0 ; j < 3 ; j ++ )
		{
			if ( j == 0 )
			{	// 初回検索はこちら
				hFind_File = FindFirstFile( szFileName, &win32fd );
			}
			else
			{
				Error = FindNextFile( hFind_File, &win32fd );
			}
			

			if ( hFind_File == INVALID_HANDLE_VALUE || Error == 0 )
			{	// 譜面が見つからなかったら終了
				break;
			}

			Length = strlen( win32fd.cFileName );

			// 「曲名_○.score」の○の部分を検索
			Difficult_Work[0] = win32fd.cFileName[Length - 7];

			if ( Difficult_Work[0] == 'E' )
			{
				Music_Data[i].Easy_In = true;

				// イージー譜面データがあったらパスを書き込み
				sprintf(szFileName, "%s/%s", Music_Data[i].Folder_Path, win32fd.cFileName);
				strcpy(Music_Data[i].Fumen_Path[EASY], szFileName);

			}
			if ( Difficult_Work[0] == 'H' )
			{
				Music_Data[i].Hyper_In = true;

				// ハイパー譜面データがあったらパスを書き込み
				sprintf(szFileName, "%s/%s", Music_Data[i].Folder_Path, win32fd.cFileName);
				strcpy(Music_Data[i].Fumen_Path[HYPER], szFileName);

			}
			if ( Difficult_Work[0] == 'M' )
			{
				Music_Data[i].Master_In = true;

				// マスター譜面データがあったらパスを書き込み
				sprintf(szFileName, "%s/%s", Music_Data[i].Folder_Path, win32fd.cFileName);
				strcpy(Music_Data[i].Fumen_Path[MASTER], szFileName);

			}
		}

		// 音源データまでのパスを抽出 ( □□.wav → ../DATA/MUSIC/○○.music/□□.wav )
		//************************************************************************
		strcpy(szFileName, Music_Data[i].Folder_Path);
		strcat(szFileName, "/*.wav");
		hFind_File = FindFirstFile(szFileName, &win32fd);

		// 音源データのパスを抽出できなかったら(無い・もしくはmp3)条件を変更して再抽出
		//************************************************************************
		if (hFind_File == INVALID_HANDLE_VALUE)
		{
			strcpy(szFileName, Music_Data[i].Folder_Path);
			strcat(szFileName, "/*.mp3");
			hFind_File = FindFirstFile(szFileName, &win32fd);

			if (hFind_File == INVALID_HANDLE_VALUE)
			{	// wavもmp3も無かった場合









			}
			else
			{	// 音源データのパスを書き込み( .mp3 )
				sprintf(szFileName, "%s/%s", Music_Data[i].Folder_Path, win32fd.cFileName);
				strcpy(Music_Data[i].Music_Path, szFileName);
			}
			
		}
		else
		{	// 音源データのパスを書き込み( .wav )
			sprintf(szFileName, "%s/%s", Music_Data[i].Folder_Path, win32fd.cFileName);
			strcpy(Music_Data[i].Music_Path, szFileName);
		}

		// 画像の拡張子ありそうランキング
		// png → jpg → bmp → gif

		// 画像データまでのパスを抽出 ( ☆☆.png → ../DATA/MUSIC/○○.music/☆☆.png )
		//************************************************************************
		strcpy(szFileName, Music_Data[i].Folder_Path);
		strcat(szFileName, "/*.png");
		hFind_File = FindFirstFile(szFileName, &win32fd);

		// 画像データのパスを抽出できなかったら(無い・もしくはjpg)条件を変更して再抽出
		//************************************************************************
		if (hFind_File == INVALID_HANDLE_VALUE)
		{
			strcpy(szFileName, Music_Data[i].Folder_Path);
			strcat(szFileName, "/*.jpg");
			hFind_File = FindFirstFile(szFileName, &win32fd);

			// 画像データのパスを抽出できなかったら(無い・もしくはbmp)条件を変更して再抽出
			//********************************************************************
			if (hFind_File == INVALID_HANDLE_VALUE)
			{
				strcpy(szFileName, Music_Data[i].Folder_Path);
				strcat(szFileName, "/*.bmp");
				hFind_File = FindFirstFile(szFileName, &win32fd);

				// 画像データのパスを抽出できなかったら(無い・もしくはgif)条件を変更して再抽出
				//****************************************************************
				if (hFind_File == INVALID_HANDLE_VALUE)
				{
					strcpy(szFileName, Music_Data[i].Folder_Path);
					strcat(szFileName, "/*.gif");
					hFind_File = FindFirstFile(szFileName, &win32fd);

					if (hFind_File == INVALID_HANDLE_VALUE)
					{	// どの画像も無かった場合
						Music_Data[i].Jacket_In = false;
					}
					else
					{	// 画像データのパスを書き込み( .gif )
						Music_Data[i].Jacket_In = true;
						sprintf(szFileName, "%s/%s", Music_Data[i].Folder_Path, win32fd.cFileName);
						strcpy(Music_Data[i].Picture_Path, szFileName);
					}
				}
				else
				{	// 画像データのパスを書き込み( .bmp )
					Music_Data[i].Jacket_In = true;
					sprintf(szFileName, "%s/%s", Music_Data[i].Folder_Path, win32fd.cFileName);
					strcpy(Music_Data[i].Picture_Path, szFileName);
				}
			}
			else
			{	// 画像データのパスを書き込み( .jpg )
				Music_Data[i].Jacket_In = true;
				sprintf(szFileName, "%s/%s", Music_Data[i].Folder_Path, win32fd.cFileName);
				strcpy(Music_Data[i].Picture_Path, szFileName);
			}
		}
		else
		{	// 画像データのパスを書き込み( .png )
			Music_Data[i].Jacket_In = true;
			sprintf(szFileName, "%s/%s", Music_Data[i].Folder_Path, win32fd.cFileName);
			strcpy(Music_Data[i].Picture_Path, szFileName);
		}

		// ハイスコアデータまでのパスを抽出 ( ☆☆.hiscore → ../DATA/MUSIC/○○.music/☆☆.hiscore )
		//************************************************************************
		strcpy(szFileName, Music_Data[i].Folder_Path);
		strcat(szFileName, "/*.hiscore");
		hFind_File = FindFirstFile(szFileName, &win32fd);

		if ( hFind_File == INVALID_HANDLE_VALUE )
		{	// ハイスコアデータのパスが見つからない(プレイしたことが無い)場合は全てのハイスコアを0に設定
			Music_Data[i].Easy_Hiscore		= 0;
			Music_Data[i].Hyper_Hiscore		= 0;
			Music_Data[i].Master_Hiscore	= 0;
		}
		else
		{	// ハイスコアデータのパスが見つかった(過去にプレイ経験ある)場合はパスを書き込み→全てのハイスコアを抽出
			sprintf(szFileName, "%s/%s", Music_Data[i].Folder_Path, win32fd.cFileName);
			strcpy(Music_Data[i].Hiscore_Path, szFileName);

			FILE* fp;
			char Hiscore_Work[20];

			// ファイル読み込み開始
			fp = fopen( Music_Data[i].Hiscore_Path,"r" );

			while ( fscanf( fp, "%s", Hiscore_Work) != EOF )
			{
				if ( strcmp( Hiscore_Work, "EASY" ) == 0 )
				{	// 「EASY」検出
					fscanf( fp, "%d", &Music_Data[i].Easy_Hiscore );	// EASY譜面のハイスコアを抽出
					fscanf( fp, "%s", Music_Data[i].Easy_ClearMark );	// EASY譜面のクリアマークを抽出

				}

				if ( strcmp( Hiscore_Work, "HYPER" ) == 0 )
				{	// 「HYPER」検出
					fscanf(fp, "%d", &Music_Data[i].Hyper_Hiscore);		// HYPER譜面のハイスコアを抽出
					fscanf(fp, "%s", Music_Data[i].Hyper_ClearMark);	// HYPER譜面のクリアマークを抽出
				}

				if ( strcmp( Hiscore_Work, "MASTER" ) == 0 )
				{	// 「MASTER」検出
					fscanf(fp, "%d", &Music_Data[i].Master_Hiscore);	// MASTER譜面のハイスコアを抽出
					fscanf(fp, "%s", Music_Data[i].Master_ClearMark);	// MASTER譜面のクリアマークを抽出
				}
			}

			// ファイル読み込み終了
			fclose( fp );
		}

		// 次回検索フォルダに移動
		//************************************************************************
		if ( FindNextFile(hFind_Folder, &win32fd) != 0 )
		{	// フォルダがあったら作業継続
			continue;
		}
		else
		{	// フォルダが無くなったら終了
			break;
		}
	}
}

//***********************************************************************************************************
// EOF
//***********************************************************************************************************