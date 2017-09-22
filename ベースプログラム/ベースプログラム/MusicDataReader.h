// �y�ȏ��ƃm�[�c����ǂݍ��ރN���X
#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<string>
#include<deque>

using namespace std;

// �m�[�c���X�g�񋓑�
enum
{
	NOTES_LIST_NORMAL_L,
	NOTES_LIST_NORMAL_L_LONG,
	NOTES_LIST_NORMAL_R,
	NOTES_LIST_NORMAL_R_LONG,
	NOTES_LIST_CLICK_L,
	NOTES_LIST_CLICK_L_LONG,
	NOTES_LIST_CLICK_R,
	NOTES_LIST_CLICK_R_LONG,
	NOTES_LIST_WHEEL_U,
	NOTES_LIST_WHEEL_D,

	NOTES_LIST_MAX
};

//// ���ʎ擾�p�񋓑�
//enum _NOTES_TYPE
//{
//	NOTES_READ_NORMAL_L,
//	NOTES_READ_NORMAL_R,
//	NOTES_READ_CLICK_L,
//	NOTES_READ_CLICK_R,
//	NOTES_READ_WHEEL,
//
//	NOTES_READ_MAX
//};

// �y�ȃf�[�^�񋓑�
enum _MUSIC_DATA_LIST
{
	TITLE_NAME,
	ARTIST_NAME,
	CREATOR_NAME,
	JACKET_PASS,
	ILLUSTRATOR_NAME,
	DIFFICULTY,
	LEVEL,
	BPM,
	MUSIC_PASS,
	MUSIC_VOLUME,
	ST,
	PST,
	PLE,
	BG,
	BGA,

	MUSIC_DATA_MAX
};

// �y�ȃf�[�^�\����
typedef struct
{
	string		TitleName;			// �y�Ȗ�
	string		ArtistName;			// ��Ȏ�
	string		CreatorName;		// ���ʍ쐬��
	string		JacketPass;			// �W���P�b�g�̃p�X
	string		IllustratorName;	// �W���P�b�g�����
	int			Difficulty;			// ��Փx
	int			Level;				// ���x��
	int			Bpm;				// BPM
	string		MusicPass;			// �y�Ȃ̃p�X
	int			Volume;				// ���ʃ{�����[��(%)
	int			StartTiming;		// �Ȃ̐擪�^�C�~���O
	int			Pst;				// �I�ȉ�ʂ̋ȃX�^�[�g�ʒu
	int			Ple;				// �ȃX�^�[�g�ʒu���痬������
									//int		Beat[2];			// �����́����q
	int			Bg;					// �w�i�p�^�[��
	int			BgAnim;				// �w�i�A�j���[�V����
} JacketData;

// �m�[�c�o�����i�[�\����
typedef struct
{
	int Normal_L_Count;			// ���m�[�}���m�[�c�̐�
	int Normal_L_Long_Count;	// ���m�[�}�������O�m�[�c�̐�
	int Normal_R_Count;			// �E�m�[�}���m�[�c�̐�
	int Normal_R_Long_Count;	// �E�m�[�}�������O�m�[�c�̐�
	int Click_L_Count;			// ���N���b�N�m�[�c�̐�
	int Click_L_Long_Count;		// ���N���b�N�����O�m�[�c�̐�
	int Click_R_Count;			// �E�N���b�N�m�[�c�̐�
	int Click_R_Long_Count;		// �E�N���b�N�����O�m�[�c�̐�
	int Wheel_U_Count;			// ��z�C�[���m�[�c�̐�
	int Wheel_D_Count;			// ���z�C�[���m�[�c�̐�
	int	BeatCount;				// 16���̑�����
	int MajorCount;				// ���m�[�c��
} NotesCount;

// �m�[�c�f�[�^�\����
typedef struct
{
	deque<deque<int>> Normal_L;		// ���m�[�}���m�[�c
	deque<deque<int>> Normal_L_Long;// ���m�[�}���m�[�c
	deque<deque<int>> Normal_R;		// �E�m�[�}���m�[�c
	deque<deque<int>> Normal_R_Long;// �E�m�[�}���m�[�c
	deque<deque<int>> Click_L;		// ���N���b�N�m�[�c
	deque<deque<int>> Click_L_Long;	// ���N���b�N�m�[�c
	deque<deque<int>> Click_R;		// �E�N���b�N�m�[�c
	deque<deque<int>> Click_R_Long;	// �E�N���b�N�m�[�c
	deque<deque<int>> Wheel_U;		// �z�C�[���m�[�c
	deque<deque<int>> Wheel_D;		// �z�C�[���m�[�c
	NotesCount NotesCount;			// �m�[�c���̏o�����J�E���g
} NotesData;

// �y�ȃf�[�^�\����
typedef struct
{
	JacketData	Jacket;
	NotesData	Notes;				// �m�[�c�f�[�^
} MusicData;

// �y�ȏ��ǂݎ��N���X
class CMusicDataReader
{
private:
	MusicData	m_MusicData;		// �y�ȃf�[�^

									//void NotesDataLoad();
									//void MusicDataLoad();
public:
	CMusicDataReader();
	~CMusicDataReader();

	// �w��t�@�C���̏��ƕ��ʏ���ǂݍ���
	void MusicDataLoad(string fileName);
	// �w��t�@�C���̃W���P�b�g���̂ݓǂݍ���
	void JacketFileLoad(string fileName, FILE* fp = NULL);
	// �y�ȏ���Ԃ�
	inline const MusicData* GetMusicData() { return &m_MusicData; };
	// �m�[�c����Ԃ�
	deque<int> GetNotesData(int notesType);
	// �����O�̐���Ԃ��Ē��g������
	int GetLongNum(int notesType);
};