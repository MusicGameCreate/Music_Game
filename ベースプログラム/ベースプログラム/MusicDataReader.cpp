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

	// �ǂݍ��݂ŊJ��
	if (!fp)
	{// �t�@�C���I�[�v���G���[
		return;
	}

	// �t�@�C���̓��e�𕶎���Ŋi�[
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

	// �W���P�b�g���ǂݍ���
	JacketFileLoad(fileName);

	// �y�ȏ��ǂݍ���
	for (deque<string>::iterator it = MusicData.begin(); it != MusicData.end(); it++)
	{
		// �y�ȏ��ǂݍ��݂͔�΂�
		if (cnt < MUSIC_DATA_MAX + 1)
		{
			cnt++;
			continue;
		}

		// 16�s��1���߂Ȃ̂�1�s��΂�
		if (ColumnCnt >= 16)
		{
			ColumnCnt = 0;
			continue;
		}

		string StrData = *it;	// 1�s�̃f�[�^

		//if (StrData.substr(0, 2) == "--")
		//{// �P���߂̐ߖ�
		//	MusicFlag = true;
		//	continue;
		//}

		const char* CharData = StrData.c_str();
		// ���ʏ��ۑ�
		for (int j = 0; MusicCnt < 5; j ++)	// ���ʏ�ɂ���f�[�^�̐������J��Ԃ�
		{
			for (int i = 0; i < 8; i++, j ++)
			{
				// �z�C�[���m�[�c�Ȃ�2�ŏI��
				if (MusicCnt >= 4 && i >= 2)
					break;

				// ���ʂ��u����Ă���΃J�E���g���Ă���
				int type = (int)CharData[j] - (int)'0';
				switch (type)
				{
				case 0:// �m�[�c����
					List.push_back(0);
					LongList.push_back(0);
					break;
				case 1:// �ʏ�m�[�c
					List.push_back(type);
					LongList.push_back(0);
					break;
				case 2:// �����O�m�[�c
					List.push_back(0);
					LongList.push_back(type);
					break;
				default:
					break;
				}

				// �m�[�c�J�E���g�A�b�v
				if (type)
				{
					switch (MusicCnt)
					{
					case 0:// ���m�[�}��
						if (type == 1)
						{
							m_MusicData.Notes.NotesCount.Normal_L_Count++;
						}
						else if (type == 2)
						{
							m_MusicData.Notes.NotesCount.Normal_L_Long_Count++;
						}
						break;
					case 1:// �E�m�[�}��
						if (type == 1)
						{
							m_MusicData.Notes.NotesCount.Normal_R_Count++;
						}
						else if (type == 2)
						{
							m_MusicData.Notes.NotesCount.Normal_R_Long_Count++;
						}
						break;
					case 2:// ���N���b�N
						if (type == 1)
						{
							m_MusicData.Notes.NotesCount.Click_L_Count++;
						}
						else if (type == 2)
						{
							m_MusicData.Notes.NotesCount.Click_L_Long_Count++;
						}
						break;
					case 3:// �E�N���b�N
						if (type == 1)
						{
							m_MusicData.Notes.NotesCount.Click_R_Count++;
						}
						else if (type == 2)
						{
							m_MusicData.Notes.NotesCount.Click_R_Long_Count++;
						}
						break;
					case 4:// �z�C�[��
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

	// 16���̐����i�[
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

		// �ǂݍ��݂ŊJ��
		if (!fp)
		{// �t�@�C���I�[�v���G���[
			return;
		}

		// �t�@�C���̓��e�𕶎���Ŋi�[
		while (fgets(buf, fileName.size() + 1, fp) != NULL)
		{
			MusicData.push_back(buf);
		}

		fclose(fp);
	}

	// �ȏ��ۑ�
	for (deque<string>::iterator it = MusicData.begin(); cnt < MUSIC_DATA_MAX; it++, cnt ++)
	{
		string StrData = *it;	// 1�s�̃f�[�^

		switch (cnt)
		{
		case TITLE_NAME:		// �y�Ȗ�
			m_MusicData.Jacket.TitleName = StrData;
			break;
		case ARTIST_NAME:		// ��Ȏ�
			m_MusicData.Jacket.ArtistName = StrData;
			break;
		case CREATOR_NAME:		// ���ʐ����
			m_MusicData.Jacket.CreatorName = StrData;
			break;
		case JACKET_PASS:		// �W���P�b�g�t�@�C����
			m_MusicData.Jacket.JacketPass = StrData;
			break;
		case ILLUSTRATOR_NAME:	// �W���P�b�g�����
			m_MusicData.Jacket.IllustratorName = StrData;
			break;
		case DIFFICULTY:		// ��Փx
			m_MusicData.Jacket.Difficulty = atoi(StrData.c_str());
			break;
		case LEVEL:				// ���x��
			m_MusicData.Jacket.Level = atoi(StrData.c_str());
			break;
		case BPM:				// BPM
			m_MusicData.Jacket.Bpm = atoi(StrData.c_str());
			break;
		case MUSIC_PASS:		// �y�Ȃ̃p�X
			m_MusicData.Jacket.MusicPass = StrData;
			break;
		case MUSIC_VOLUME:		// ���ʃ{�����[��(%)
			m_MusicData.Jacket.Volume = atoi(StrData.c_str());
			break;
		case ST:				// �Ȃ̐擪�^�C�~���O
			m_MusicData.Jacket.StartTiming = atoi(StrData.c_str());
			break;
		case PST:				// �I�ȉ�ʂ̎��̋ȃX�^�[�g�ʒu
			m_MusicData.Jacket.Pst = atoi(StrData.c_str());
			break;
		case PLE:				// �����痬������
			m_MusicData.Jacket.Ple = atoi(StrData.c_str());
			break;
		case BG:				// �w�i�p�^�[��
			m_MusicData.Jacket.Bg = atoi(StrData.c_str());
			break;
		case BGA:				// �w�i�A�j���[�V����
			m_MusicData.Jacket.BgAnim = atoi(StrData.c_str());
			break;
			//case 15:	// �����́����q
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

	// �m�[�c�^�C�v�ɂ���ĕ���
	switch (notesType)
	{
	case NOTES_LIST_NORMAL_L:// ���m�[�}��
		front = m_MusicData.Notes.Normal_L.front();
		m_MusicData.Notes.Normal_L.pop_front();
		break;
	case NOTES_LIST_NORMAL_L_LONG:// �������O�m�[�}��
		front = m_MusicData.Notes.Normal_L_Long.front();
		m_MusicData.Notes.Normal_L_Long.pop_front();
		break;
	case NOTES_LIST_NORMAL_R:// �E�m�[�}��
		front = m_MusicData.Notes.Normal_R.front();
		m_MusicData.Notes.Normal_R.pop_front();
		break;
	case NOTES_LIST_NORMAL_R_LONG:// �E�����O�m�[�}��
		front = m_MusicData.Notes.Normal_R_Long.front();
		m_MusicData.Notes.Normal_R_Long.pop_front();
		break;
	case NOTES_LIST_CLICK_L:// ���N���b�N
		front = m_MusicData.Notes.Click_L.front();
		m_MusicData.Notes.Click_L.pop_front();
		break;
	case NOTES_LIST_CLICK_L_LONG:// �������O�N���b�N
		front = m_MusicData.Notes.Click_L_Long.front();
		m_MusicData.Notes.Click_L_Long.pop_front();
		break;
	case NOTES_LIST_CLICK_R:// �E�N���b�N
		front = m_MusicData.Notes.Click_R.front();
		m_MusicData.Notes.Click_R.pop_front();
		break;
	case NOTES_LIST_CLICK_R_LONG:// �E�����O�N���b�N
		front = m_MusicData.Notes.Click_R_Long.front();
		m_MusicData.Notes.Click_R_Long.pop_front();
		break;
	case NOTES_LIST_WHEEL_U:// ��z�C�[��
		front = m_MusicData.Notes.Wheel_U.front();
		m_MusicData.Notes.Wheel_U.pop_front();
		break;
	case NOTES_LIST_WHEEL_D:// ���z�C�[��
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

	// �m�[�c�^�C�v�ɂ���ĕ���
	switch (notesType)
	{
	case NOTES_LIST_NORMAL_L_LONG:// �������O�m�[�}��
		while (LongFlag)
		{
			column = 0;
			LongFlag = false;
			if (m_MusicData.Notes.Normal_L_Long.size() > 0)	// �m�[�c���X�g���܂��c���Ă���΃`�F�b�N
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
				case 2:	// �����O�m�[�c�̏ꏊ
					num++;
					LongFlag = true;
					break;
				default:
					break;
				}
			}
			if (LongFlag)
			{// �����O��������
				m_MusicData.Notes.Normal_L_Long.pop_front();
			}
			else
			{// �����O�Ȃ�����
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
	case NOTES_LIST_NORMAL_R_LONG:// �E�����O�m�[�}��
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
				case 2:	// �����O�m�[�c�̏ꏊ
					num++;
					LongFlag = true;
					break;
				default:
					break;
				}
			}
			if (LongFlag)
			{// �����O��������
				m_MusicData.Notes.Normal_R_Long.pop_front();
			}
			else
			{// �����O�Ȃ�����
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
	case NOTES_LIST_CLICK_L_LONG:// �������O�N���b�N
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
				case 2:	// �����O�m�[�c�̏ꏊ
					num++;
					LongFlag = true;
					break;
				default:
					break;
				}
			}
			if (LongFlag)
			{// �����O��������
				m_MusicData.Notes.Click_L_Long.pop_front();
			}
			else
			{// �����O�Ȃ�����
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
	case NOTES_LIST_CLICK_R_LONG:// �E�����O�N���b�N
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
				case 2:	// �����O�m�[�c�̏ꏊ
					num++;
					LongFlag = true;
					break;
				default:
					break;
				}
			}
			if (LongFlag)
			{// �����O��������
				m_MusicData.Notes.Click_R_Long.pop_front();
			}
			else
			{// �����O�Ȃ�����
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
//	// �m�[�c�^�C�v�ɂ���ĕ���
//	switch (notesType)
//	{
//	case NOTES_READ_NORMAL_L:// ���m�[�}��
//		front = m_MusicData.Notes.Normal_L.front();
//		m_MusicData.Notes.Normal_L.pop_front();
//		break;
//	case NOTES_READ_NORMAL_R:// �E�m�[�}��
//		front = m_MusicData.Notes.Normal_R.front();
//		m_MusicData.Notes.Normal_R.pop_front();
//		break;
//	case NOTES_READ_CLICK_L:// ���N���b�N
//		front = m_MusicData.Notes.Click_L.front();
//		m_MusicData.Notes.Click_L.pop_front();
//		break;
//	case NOTES_READ_CLICK_R:// �E�N���b�N
//		front = m_MusicData.Notes.Click_R.front();
//		m_MusicData.Notes.Click_R.pop_front();
//		break;
//	case NOTES_READ_WHEEL:// �z�C�[��
//		front = m_MusicData.Notes.Wheel.front();
//		m_MusicData.Notes.Wheel.pop_front();
//		break;
//	default:
//		break;
//	}
//
//	return front;
//}