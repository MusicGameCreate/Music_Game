#include"MusicDataReader.h"

CMusicDataReader::CMusicDataReader()
{
	m_MusicData.Notes.NotesCount.Normal_L_Count = 0;
	m_MusicData.Notes.NotesCount.Normal_L_Long_Count = 0;
	m_MusicData.Notes.NotesCount.Normal_R_Count = 0;
	m_MusicData.Notes.NotesCount.Normal_R_Long_Count = 0;
	m_MusicData.Notes.NotesCount.Click_L_Count = 0;
	m_MusicData.Notes.NotesCount.Click_L_Long_Count = 0;
	m_MusicData.Notes.NotesCount.Click_R_Count = 0;
	m_MusicData.Notes.NotesCount.Click_R_Long_Count = 0;
	m_MusicData.Notes.NotesCount.Wheel_U_Count = 0;
	m_MusicData.Notes.NotesCount.Wheel_D_Count = 0;
}

CMusicDataReader::~CMusicDataReader()
{

}

void CMusicDataReader::MusicDataLoad(string fileName)
{
	deque<string> MusicData;
	FILE* fp;
	char* buf = new char[fileName.size() + 1];
	fp = fopen(fileName.c_str(), "rb");

	// 読み込みで開く
	if (!fp)
	{// ファイルオープンエラー
		return;
	}

	// ファイルの内容を文字列で格納
	while (fgets(buf, 48, fp) != NULL)
	{
		MusicData.push_back(buf);
	}

	int cnt = 0;
	int NotesCnt = 0;
	int NotesNum = 0;
	deque<int> List;
	deque<int> LongList;
	bool MusicFlag = false;
	int MusicCnt = 0;
	int ColumnCnt = 0;

	// ジャケット情報読み込み
	JacketFileLoad(fileName);

	// 楽曲情報読み込み
	for (deque<string>::iterator it = MusicData.begin(); it != MusicData.end(); it++)
	{
		// 楽曲情報読み込みは飛ばす
		if (cnt < MUSIC_DATA_MAX + 1)
		{
			cnt++;
			continue;
		}

		// 16行で1小節なので1行飛ばす
		if (ColumnCnt >= 16)
		{
			ColumnCnt = 0;
			continue;
		}

		string StrData = *it;	// 1行のデータ

		//if (StrData.substr(0, 2) == "--")
		//{// １小節の節目
		//	MusicFlag = true;
		//	continue;
		//}

		const char* CharData = StrData.c_str();
		// 譜面情報保存
		for (int j = 0; MusicCnt < 5; j ++)	// 譜面上にあるデータの数だけ繰り返す
		{
			for (int i = 0; i < 8; i++, j ++)
			{
				// ホイールノーツなら2つで終了
				if (MusicCnt >= 4 && i >= 2)
					break;

				// 譜面が置かれていればカウントしていく
				int type = (int)CharData[j] - (int)'0';
				switch (type)
				{
				case 0:// ノーツ無し
					List.push_back(0);
					LongList.push_back(0);
					break;
				case 1:// 通常ノーツ
					List.push_back(type);
					LongList.push_back(0);
					break;
				case 2:// ロングノーツ
					List.push_back(0);
					LongList.push_back(type);
					break;
				default:
					break;
				}

				// ノーツカウントアップ
				if (type)
				{
					switch (MusicCnt)
					{
					case 0:// 左ノーマル
						if (type == 1)
						{
							m_MusicData.Notes.NotesCount.Normal_L_Count++;
						}
						else if (type == 2)
						{
							m_MusicData.Notes.NotesCount.Normal_L_Long_Count++;
						}
						break;
					case 1:// 右ノーマル
						if (type == 1)
						{
							m_MusicData.Notes.NotesCount.Normal_R_Count++;
						}
						else if (type == 2)
						{
							m_MusicData.Notes.NotesCount.Normal_R_Long_Count++;
						}
						break;
					case 2:// 左クリック
						if (type == 1)
						{
							m_MusicData.Notes.NotesCount.Click_L_Count++;
						}
						else if (type == 2)
						{
							m_MusicData.Notes.NotesCount.Click_L_Long_Count++;
						}
						break;
					case 3:// 右クリック
						if (type == 1)
						{
							m_MusicData.Notes.NotesCount.Click_R_Count++;
						}
						else if (type == 2)
						{
							m_MusicData.Notes.NotesCount.Click_R_Long_Count++;
						}
						break;
					case 4:// ホイール
						if (type == 1)
						{
							m_MusicData.Notes.NotesCount.Wheel_U_Count++;
						}
						else if(type == 2)
						{
							m_MusicData.Notes.NotesCount.Wheel_D_Count++;
						}
						break;
					default:
						break;
					}
				}
			}

			switch (MusicCnt)
			{
			case 0:
				m_MusicData.Notes.Normal_L.push_back(List);
				m_MusicData.Notes.Normal_L_Long.push_back(LongList);
				break;
			case 1:
				m_MusicData.Notes.Normal_R.push_back(List);
				m_MusicData.Notes.Normal_R_Long.push_back(LongList);
				break;
			case 2:
				m_MusicData.Notes.Click_L.push_back(List);
				m_MusicData.Notes.Click_L_Long.push_back(LongList);
				break;
			case 3:
				m_MusicData.Notes.Click_R.push_back(List);
				m_MusicData.Notes.Click_R_Long.push_back(LongList);
				break;
			case 4:
				m_MusicData.Notes.Wheel_U.push_back(List);
				m_MusicData.Notes.Wheel_D.push_back(LongList);
				break;
			default:
				break;
			}
			List.clear();
			LongList.clear();
			MusicCnt++;
		}

		MusicCnt = 0;
		ColumnCnt++;
	}

	// 16分の数を格納
	m_MusicData.Notes.NotesCount.BeatCount = m_MusicData.Notes.Normal_L.size();
	m_MusicData.Notes.NotesCount.MajorCount =
		(
			m_MusicData.Notes.NotesCount.Normal_L_Count +
			m_MusicData.Notes.NotesCount.Normal_L_Long_Count +
			m_MusicData.Notes.NotesCount.Normal_R_Count +
			m_MusicData.Notes.NotesCount.Normal_R_Long_Count +
			m_MusicData.Notes.NotesCount.Click_L_Count +
			m_MusicData.Notes.NotesCount.Click_L_Long_Count +
			m_MusicData.Notes.NotesCount.Click_R_Count +
			m_MusicData.Notes.NotesCount.Click_R_Long_Count +
			m_MusicData.Notes.NotesCount.Wheel_U_Count +
			m_MusicData.Notes.NotesCount.Wheel_D_Count
		);

	fclose(fp);
}

void CMusicDataReader::JacketFileLoad(string fileName, FILE* fp)
{
	deque<string> MusicData;
	char* buf = new char[fileName.size() + 1];
	int cnt = 0;

	if (!fp)
	{
		fp = fopen(fileName.c_str(), "rb");

		// 読み込みで開く
		if (!fp)
		{// ファイルオープンエラー
			return;
		}

		// ファイルの内容を文字列で格納
		while (fgets(buf, fileName.size() + 1, fp) != NULL)
		{
			MusicData.push_back(buf);
		}

		fclose(fp);
	}

	// 曲情報保存
	for (deque<string>::iterator it = MusicData.begin(); cnt < MUSIC_DATA_MAX; it++, cnt ++)
	{
		string StrData = *it;	// 1行のデータ

		switch (cnt)
		{
		case TITLE_NAME:		// 楽曲名
			m_MusicData.Jacket.TitleName = StrData;
			break;
		case ARTIST_NAME:		// 作曲者
			m_MusicData.Jacket.ArtistName = StrData;
			break;
		case CREATOR_NAME:		// 譜面製作者
			m_MusicData.Jacket.CreatorName = StrData;
			break;
		case JACKET_PASS:		// ジャケットファイル名
			m_MusicData.Jacket.JacketPass = StrData;
			break;
		case ILLUSTRATOR_NAME:	// ジャケット製作者
			m_MusicData.Jacket.IllustratorName = StrData;
			break;
		case DIFFICULTY:		// 難易度
			m_MusicData.Jacket.Difficulty = atoi(StrData.c_str());
			break;
		case LEVEL:				// レベル
			m_MusicData.Jacket.Level = atoi(StrData.c_str());
			break;
		case BPM:				// BPM
			m_MusicData.Jacket.Bpm = atoi(StrData.c_str());
			break;
		case MUSIC_PASS:		// 楽曲のパス
			m_MusicData.Jacket.MusicPass = StrData;
			break;
		case MUSIC_VOLUME:		// 音量ボリューム(%)
			m_MusicData.Jacket.Volume = atoi(StrData.c_str());
			break;
		case ST:				// 曲の先頭タイミング
			m_MusicData.Jacket.StartTiming = atoi(StrData.c_str());
			break;
		case PST:				// 選曲画面の時の曲スタート位置
			m_MusicData.Jacket.Pst = atoi(StrData.c_str());
			break;
		case PLE:				// ↑から流す長さ
			m_MusicData.Jacket.Ple = atoi(StrData.c_str());
			break;
		case BG:				// 背景パターン
			m_MusicData.Jacket.Bg = atoi(StrData.c_str());
			break;
		case BGA:				// 背景アニメーション
			m_MusicData.Jacket.BgAnim = atoi(StrData.c_str());
			break;
			//case 15:	// ○分の○拍子
			//	char beat[1];
			//	beat[0] = StrData[0];
			//	m_MusicData.Beat[0] = atoi(beat);
			//	beat[0] = StrData[2];
			//	m_MusicData.Beat[1] = atoi(beat);
			//	break;
		default:
			break;
		}
	}
}

deque<int> CMusicDataReader::GetNotesData(int notesType)
{
	deque<int> front;

	// ノーツタイプによって分岐
	switch (notesType)
	{
	case NOTES_LIST_NORMAL_L:// 左ノーマル
		front = m_MusicData.Notes.Normal_L.front();
		m_MusicData.Notes.Normal_L.pop_front();
		break;
	case NOTES_LIST_NORMAL_L_LONG:// 左ロングノーマル
		front = m_MusicData.Notes.Normal_L_Long.front();
		m_MusicData.Notes.Normal_L_Long.pop_front();
		break;
	case NOTES_LIST_NORMAL_R:// 右ノーマル
		front = m_MusicData.Notes.Normal_R.front();
		m_MusicData.Notes.Normal_R.pop_front();
		break;
	case NOTES_LIST_NORMAL_R_LONG:// 右ロングノーマル
		front = m_MusicData.Notes.Normal_R_Long.front();
		m_MusicData.Notes.Normal_R_Long.pop_front();
		break;
	case NOTES_LIST_CLICK_L:// 左クリック
		front = m_MusicData.Notes.Click_L.front();
		m_MusicData.Notes.Click_L.pop_front();
		break;
	case NOTES_LIST_CLICK_L_LONG:// 左ロングクリック
		front = m_MusicData.Notes.Click_L_Long.front();
		m_MusicData.Notes.Click_L_Long.pop_front();
		break;
	case NOTES_LIST_CLICK_R:// 右クリック
		front = m_MusicData.Notes.Click_R.front();
		m_MusicData.Notes.Click_R.pop_front();
		break;
	case NOTES_LIST_CLICK_R_LONG:// 右ロングクリック
		front = m_MusicData.Notes.Click_R_Long.front();
		m_MusicData.Notes.Click_R_Long.pop_front();
		break;
	case NOTES_LIST_WHEEL_U:// 上ホイール
		front = m_MusicData.Notes.Wheel_U.front();
		m_MusicData.Notes.Wheel_U.pop_front();
		break;
	case NOTES_LIST_WHEEL_D:// 下ホイール
		front = m_MusicData.Notes.Wheel_D.front();
		m_MusicData.Notes.Wheel_D.pop_front();
		break;
	default:
		break;
	}

	return front;
}

// 
int CMusicDataReader::GetLongNum(int notesType)
{
	int num = 0;
	int column = 0;
	deque<int> front;
	bool		LongFlag = true;

	// ノーツタイプによって分岐
	switch (notesType)
	{
	case NOTES_LIST_NORMAL_L_LONG:// 左ロングノーマル
		while (LongFlag)
		{
			column = 0;
			LongFlag = false;
			if (m_MusicData.Notes.Normal_L_Long.size() > 0)	// ノーツリストがまだ残っていればチェック
				front = m_MusicData.Notes.Normal_L_Long.front();
			else
				break;
			for (deque<int>::iterator it = front.begin(); it != front.end(); it++, column++)
			{
				int type = *it;
				if (type == 0)
					continue;
				switch (type)
				{
				case 2:	// ロングノーツの場所
					num++;
					LongFlag = true;
					break;
				default:
					break;
				}
			}
			if (LongFlag)
			{// ロングがあった
				m_MusicData.Notes.Normal_L_Long.pop_front();
			}
			else
			{// ロングなかった
				deque<int> push;
				for (int i = 0; i < num; i++)
				{
					for (int j = 0; j < 8; j++)
					{
						push.push_back(0);
					}
					m_MusicData.Notes.Normal_L_Long.push_front(push);
				}
			}
		}
		break;
	case NOTES_LIST_NORMAL_R_LONG:// 右ロングノーマル
		while (LongFlag)
		{
			column = 0;
			LongFlag = false;
			if (m_MusicData.Notes.Normal_R_Long.size() > 0)
				front = m_MusicData.Notes.Normal_R_Long.front();
			else
				break;
			for (deque<int>::iterator it = front.begin(); it != front.end(); it++, column++)
			{
				int type = *it;
				if (type == 0)
					continue;
				switch (type)
				{
				case 2:	// ロングノーツの場所
					num++;
					LongFlag = true;
					break;
				default:
					break;
				}
			}
			if (LongFlag)
			{// ロングがあった
				m_MusicData.Notes.Normal_R_Long.pop_front();
			}
			else
			{// ロングなかった
				deque<int> push;
				for (int i = 0; i < num; i++)
				{
					for (int j = 0; j < 8; j++)
					{
						push.push_back(0);
					}
					m_MusicData.Notes.Normal_R_Long.push_front(push);
				}
			}
		}
		break;
	case NOTES_LIST_CLICK_L_LONG:// 左ロングクリック
		while (LongFlag)
		{
			column = 0;
			LongFlag = false;
			if (m_MusicData.Notes.Click_L_Long.size() > 0)
				front = m_MusicData.Notes.Click_L_Long.front();
			else
				break;
			for (deque<int>::iterator it = front.begin(); it != front.end(); it++, column++)
			{
				int type = *it;
				if (type == 0)
					continue;
				switch (type)
				{
				case 2:	// ロングノーツの場所
					num++;
					LongFlag = true;
					break;
				default:
					break;
				}
			}
			if (LongFlag)
			{// ロングがあった
				m_MusicData.Notes.Click_L_Long.pop_front();
			}
			else
			{// ロングなかった
				deque<int> push;
				for (int i = 0; i < num; i++)
				{
					for (int j = 0; j < 8; j++)
					{
						push.push_back(0);
					}
					m_MusicData.Notes.Click_L_Long.push_front(push);
				}
			}
		}
		break;
	case NOTES_LIST_CLICK_R_LONG:// 右ロングクリック
		while (LongFlag)
		{
			column = 0;
			LongFlag = false;
			if (m_MusicData.Notes.Click_R_Long.size() > 0)
				front = m_MusicData.Notes.Click_R_Long.front();
			else
				break;
			for (deque<int>::iterator it = front.begin(); it != front.end(); it++, column++)
			{
				int type = *it;
				if (type == 0)
					continue;
				switch (type)
				{
				case 2:	// ロングノーツの場所
					num++;
					LongFlag = true;
					break;
				default:
					break;
				}
			}
			if (LongFlag)
			{// ロングがあった
				m_MusicData.Notes.Click_R_Long.pop_front();
			}
			else
			{// ロングなかった
				deque<int> push;
				for (int i = 0; i < num; i++)
				{
					for (int j = 0; j < 8; j++)
					{
						push.push_back(0);
					}
					m_MusicData.Notes.Click_R_Long.push_front(push);
				}
			}
		}
		break;
	default:
		break;
	}

	return num + 1;
}

//deque<int> CMusicDataReader::GetNotesData(int notesType)
//{
//	deque<int> front;
//	int i = 0;
//
//	// ノーツタイプによって分岐
//	switch (notesType)
//	{
//	case NOTES_READ_NORMAL_L:// 左ノーマル
//		front = m_MusicData.Notes.Normal_L.front();
//		m_MusicData.Notes.Normal_L.pop_front();
//		break;
//	case NOTES_READ_NORMAL_R:// 右ノーマル
//		front = m_MusicData.Notes.Normal_R.front();
//		m_MusicData.Notes.Normal_R.pop_front();
//		break;
//	case NOTES_READ_CLICK_L:// 左クリック
//		front = m_MusicData.Notes.Click_L.front();
//		m_MusicData.Notes.Click_L.pop_front();
//		break;
//	case NOTES_READ_CLICK_R:// 右クリック
//		front = m_MusicData.Notes.Click_R.front();
//		m_MusicData.Notes.Click_R.pop_front();
//		break;
//	case NOTES_READ_WHEEL:// ホイール
//		front = m_MusicData.Notes.Wheel.front();
//		m_MusicData.Notes.Wheel.pop_front();
//		break;
//	default:
//		break;
//	}
//
//	return front;
//}