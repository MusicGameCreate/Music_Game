//***********************************************************************************************************
//
// �ȃf�[�^�ꊇ�Ǘ��N���X
//
//***********************************************************************************************************

//***********************************************************************************************************
// �C���N���[�h��
//***********************************************************************************************************
#include "CMusic_Manager.h"
#include <locale.h>


MUSIC_DATA*		CMusic_Manager::Music_Data;		// �ȏ��܂Ƃߍ\����
int				CMusic_Manager::nMusic_Count;	// �ȑ���
//***********************************************************************************************************
// ������
//***********************************************************************************************************
void CMusic_Manager::Init(void)
{
	Music_Data		= NULL;
	nMusic_Count	= 0;
}

//***********************************************************************************************************
// �I��
//***********************************************************************************************************
void CMusic_Manager::Finalise(void)
{
	delete Music_Data;
}

//***********************************************************************************************************
// �f�[�^�ꊇ�ǂݍ���
//***********************************************************************************************************
void CMusic_Manager::Load(void)
{
	HANDLE			hFind_Folder = 0;		// �t�H���_���w�肷�鎞�Ɏg�p
	HANDLE			hFind_File = 0;			// �t�@�C�����w�肷�鎞�Ɏg�p
	WIN32_FIND_DATA win32fd;			// ���o�����t�@�C����񂪂����ɓ���(�t�@�C������)
	char			szFileName[256];

	// �t�H���_���̈�ԏ�́u�t�H���_�v���w��( *.�g���q�őS�Ă̓��g���q�f�[�^���Q�� )
	//****************************************************************************
	hFind_Folder = FindFirstFile("../DATA/MUSIC/*.music", &win32fd);

	if ( hFind_Folder == INVALID_HANDLE_VALUE )
	{	// �t�@�C��������������I��
		MessageBox( CWindowAPI::GethWnd(), "�Ȃ���Ȃ������Ă��܂���I�I�����܂�", "�ȓǂݍ��ݎ��s�I", MB_OK );
		exit( EXIT_FAILURE );
	}
	else
	{
		// �Ȑ��C���N�������g
		nMusic_Count++;
	}

	//****************************************************************************
	// �ȃf�[�^�����J�E���g
	//****************************************************************************
	while (1)
	{
		// FindNextFile() = ���s����΁u0�v��Ԃ�
		if ( FindNextFile( hFind_Folder, &win32fd ) != 0 )
		{	// �t�H���_����������ȑ����J�E���g 
			nMusic_Count ++;
		}
		else
		{	// �t�H���_�������Ȃ�����J�E���g�I��
			break;
		}
	}

	// �y�Ȃ̌����̈�m��
	//****************************************************************************
	Music_Data = new MUSIC_DATA[nMusic_Count];


	// �ȃf�[�^�ꊇ������
	//****************************************************************************
	for ( int i = 0 ; i < nMusic_Count ; i ++ )
	{
		Music_Data[i].Music_Title_Length	= 0;		// �ȃ^�C�g������
		Music_Data[i].Music_Title[0]		= '\0';		// �ȃ^�C�g����
		Music_Data[i].Folder_Path[0]		= '\0';		// �t�H���_�܂ł̃p�X
		Music_Data[i].Fumen_Path[0][0]		= '\0';		// �C�[�W�[���ʂ̃p�X
		Music_Data[i].Fumen_Path[1][0]		= '\0';		// �n�C�p�[���ʂ̃p�X
		Music_Data[i].Fumen_Path[2][0]		= '\0';		// �}�X�^�[���ʂ̃p�X
		Music_Data[i].Music_Path[0]			= '\0';		// �����̃p�X
		Music_Data[i].Picture_Path[0]		= '\0';		// �摜�̃p�X
		Music_Data[i].Hiscore_Path[0]		= '\0';		// �n�C�X�R�A�̃p�X

		Music_Data[i].Easy_In				= false;	// �C�[�W�[���ʂ����邩�ǂ���
		Music_Data[i].Hyper_In				= false;	// �n�C�p�[���ʂ����邩�ǂ���
		Music_Data[i].Master_In				= false;	// �}�X�^�[���ʂ����邩�ǂ���

		Music_Data[i].Jacket_In				= false;	// �W���P�b�g�摜�������Ă��邩�ǂ���

		Music_Data[i].Easy_Hiscore			= 0;		// �C�[�W�[���ʂ̃n�C�X�R�A
		Music_Data[i].Hyper_Hiscore			= 0;		// �n�C�p�[���ʂ̃n�C�X�R�A
		Music_Data[i].Master_Hiscore		= 0;		// �}�X�^�[���ʂ̃n�C�X�R�A

		Music_Data[i].Easy_ClearMark[0]		= '\0';		// �C�[�W�[���ʂ̃N���A�}�[�N
		Music_Data[i].Hyper_ClearMark[0]	= '\0';		// �n�C�p�[���ʂ̃N���A�}�[�N
		Music_Data[i].Master_ClearMark[0]	= '\0';		// �}�X�^�[���ʂ̃N���A�}�[�N
	}

	// ../DATA/MUSIC �t�H���_�̈�ԏ�Ɏw��
	//****************************************************************************
	hFind_Folder = FindFirstFile("../DATA/MUSIC/*.music", &win32fd);

	// �ȑ��������[�v
	//****************************************************************************
	for ( int i = 0 ; i < nMusic_Count ; i ++ )
	{
		// �ȃ^�C�g���E�^�C�g���������擾
		//************************************************************************
		int		Work = 0;
		wchar_t ws[100];
		sprintf(szFileName, "%s", win32fd.cFileName);

		setlocale( LC_CTYPE, "jpn" );			// mbstowcs()�֐����g�p���邽�߂ɕK�v
		Work = mbstowcs( ws, szFileName, 100);	// �����񒷌���
		Work -= 6;								// �u.music�v �����Z

		// �^�C�g���������i�[
		//*****************************************
		Music_Data[i].Music_Title_Length = Work;

		// �^�C�g��������i�[
		//*****************************************
		ws[Work] = L'\0';
		sprintf( Music_Data[i].Music_Title, "%ls", ws );

		// �J�����g����̃f�B���N�g����t���čď㏑�� ( ����.music �� ../DATA/MUSIC/����.music )
		//************************************************************************
		sprintf(szFileName, "../DATA/MUSIC/%s", win32fd.cFileName);
		strcpy(Music_Data[i].Folder_Path, szFileName);


		int Length = 0;
		int Error = 1;
		char Difficult_Work[1];

		// ���ʃf�[�^�܂ł̃p�X�𒊏o�@( ����.score   �� ../DATA/MUSIC/����.music/����.score )
		strcpy(szFileName, Music_Data[i].Folder_Path);
		strcat(szFileName, "/*.score");

		for ( int j = 0 ; j < 3 ; j ++ )
		{
			if ( j == 0 )
			{	// ���񌟍��͂�����
				hFind_File = FindFirstFile( szFileName, &win32fd );
			}
			else
			{
				Error = FindNextFile( hFind_File, &win32fd );
			}
			

			if ( hFind_File == INVALID_HANDLE_VALUE || Error == 0 )
			{	// ���ʂ�������Ȃ�������I��
				break;
			}

			Length = strlen( win32fd.cFileName );

			// �u�Ȗ�_��.score�v�́��̕���������
			Difficult_Work[0] = win32fd.cFileName[Length - 7];

			if ( Difficult_Work[0] == 'E' )
			{
				Music_Data[i].Easy_In = true;

				// �C�[�W�[���ʃf�[�^����������p�X����������
				sprintf(szFileName, "%s/%s", Music_Data[i].Folder_Path, win32fd.cFileName);
				strcpy(Music_Data[i].Fumen_Path[EASY], szFileName);

			}
			if ( Difficult_Work[0] == 'H' )
			{
				Music_Data[i].Hyper_In = true;

				// �n�C�p�[���ʃf�[�^����������p�X����������
				sprintf(szFileName, "%s/%s", Music_Data[i].Folder_Path, win32fd.cFileName);
				strcpy(Music_Data[i].Fumen_Path[HYPER], szFileName);

			}
			if ( Difficult_Work[0] == 'M' )
			{
				Music_Data[i].Master_In = true;

				// �}�X�^�[���ʃf�[�^����������p�X����������
				sprintf(szFileName, "%s/%s", Music_Data[i].Folder_Path, win32fd.cFileName);
				strcpy(Music_Data[i].Fumen_Path[MASTER], szFileName);

			}
		}

		// �����f�[�^�܂ł̃p�X�𒊏o ( ����.wav �� ../DATA/MUSIC/����.music/����.wav )
		//************************************************************************
		strcpy(szFileName, Music_Data[i].Folder_Path);
		strcat(szFileName, "/*.wav");
		hFind_File = FindFirstFile(szFileName, &win32fd);

		// �����f�[�^�̃p�X�𒊏o�ł��Ȃ�������(�����E��������mp3)������ύX���čĒ��o
		//************************************************************************
		if (hFind_File == INVALID_HANDLE_VALUE)
		{
			strcpy(szFileName, Music_Data[i].Folder_Path);
			strcat(szFileName, "/*.mp3");
			hFind_File = FindFirstFile(szFileName, &win32fd);

			if (hFind_File == INVALID_HANDLE_VALUE)
			{	// wav��mp3�����������ꍇ









			}
			else
			{	// �����f�[�^�̃p�X����������( .mp3 )
				sprintf(szFileName, "%s/%s", Music_Data[i].Folder_Path, win32fd.cFileName);
				strcpy(Music_Data[i].Music_Path, szFileName);
			}
			
		}
		else
		{	// �����f�[�^�̃p�X����������( .wav )
			sprintf(szFileName, "%s/%s", Music_Data[i].Folder_Path, win32fd.cFileName);
			strcpy(Music_Data[i].Music_Path, szFileName);
		}

		// �摜�̊g���q���肻�������L���O
		// png �� jpg �� bmp �� gif

		// �摜�f�[�^�܂ł̃p�X�𒊏o ( ����.png �� ../DATA/MUSIC/����.music/����.png )
		//************************************************************************
		strcpy(szFileName, Music_Data[i].Folder_Path);
		strcat(szFileName, "/*.png");
		hFind_File = FindFirstFile(szFileName, &win32fd);

		// �摜�f�[�^�̃p�X�𒊏o�ł��Ȃ�������(�����E��������jpg)������ύX���čĒ��o
		//************************************************************************
		if (hFind_File == INVALID_HANDLE_VALUE)
		{
			strcpy(szFileName, Music_Data[i].Folder_Path);
			strcat(szFileName, "/*.jpg");
			hFind_File = FindFirstFile(szFileName, &win32fd);

			// �摜�f�[�^�̃p�X�𒊏o�ł��Ȃ�������(�����E��������bmp)������ύX���čĒ��o
			//********************************************************************
			if (hFind_File == INVALID_HANDLE_VALUE)
			{
				strcpy(szFileName, Music_Data[i].Folder_Path);
				strcat(szFileName, "/*.bmp");
				hFind_File = FindFirstFile(szFileName, &win32fd);

				// �摜�f�[�^�̃p�X�𒊏o�ł��Ȃ�������(�����E��������gif)������ύX���čĒ��o
				//****************************************************************
				if (hFind_File == INVALID_HANDLE_VALUE)
				{
					strcpy(szFileName, Music_Data[i].Folder_Path);
					strcat(szFileName, "/*.gif");
					hFind_File = FindFirstFile(szFileName, &win32fd);

					if (hFind_File == INVALID_HANDLE_VALUE)
					{	// �ǂ̉摜�����������ꍇ
						Music_Data[i].Jacket_In = false;
					}
					else
					{	// �摜�f�[�^�̃p�X����������( .gif )
						Music_Data[i].Jacket_In = true;
						sprintf(szFileName, "%s/%s", Music_Data[i].Folder_Path, win32fd.cFileName);
						strcpy(Music_Data[i].Picture_Path, szFileName);
					}
				}
				else
				{	// �摜�f�[�^�̃p�X����������( .bmp )
					Music_Data[i].Jacket_In = true;
					sprintf(szFileName, "%s/%s", Music_Data[i].Folder_Path, win32fd.cFileName);
					strcpy(Music_Data[i].Picture_Path, szFileName);
				}
			}
			else
			{	// �摜�f�[�^�̃p�X����������( .jpg )
				Music_Data[i].Jacket_In = true;
				sprintf(szFileName, "%s/%s", Music_Data[i].Folder_Path, win32fd.cFileName);
				strcpy(Music_Data[i].Picture_Path, szFileName);
			}
		}
		else
		{	// �摜�f�[�^�̃p�X����������( .png )
			Music_Data[i].Jacket_In = true;
			sprintf(szFileName, "%s/%s", Music_Data[i].Folder_Path, win32fd.cFileName);
			strcpy(Music_Data[i].Picture_Path, szFileName);
		}

		// �n�C�X�R�A�f�[�^�܂ł̃p�X�𒊏o ( ����.hiscore �� ../DATA/MUSIC/����.music/����.hiscore )
		//************************************************************************
		strcpy(szFileName, Music_Data[i].Folder_Path);
		strcat(szFileName, "/*.hiscore");
		hFind_File = FindFirstFile(szFileName, &win32fd);

		if ( hFind_File == INVALID_HANDLE_VALUE )
		{	// �n�C�X�R�A�f�[�^�̃p�X��������Ȃ�(�v���C�������Ƃ�����)�ꍇ�͑S�Ẵn�C�X�R�A��0�ɐݒ�
			Music_Data[i].Easy_Hiscore		= 0;
			Music_Data[i].Hyper_Hiscore		= 0;
			Music_Data[i].Master_Hiscore	= 0;
		}
		else
		{	// �n�C�X�R�A�f�[�^�̃p�X����������(�ߋ��Ƀv���C�o������)�ꍇ�̓p�X���������݁��S�Ẵn�C�X�R�A�𒊏o
			sprintf(szFileName, "%s/%s", Music_Data[i].Folder_Path, win32fd.cFileName);
			strcpy(Music_Data[i].Hiscore_Path, szFileName);

			FILE* fp;
			char Hiscore_Work[20];

			// �t�@�C���ǂݍ��݊J�n
			fp = fopen( Music_Data[i].Hiscore_Path,"r" );

			while ( fscanf( fp, "%s", Hiscore_Work) != EOF )
			{
				if ( strcmp( Hiscore_Work, "EASY" ) == 0 )
				{	// �uEASY�v���o
					fscanf( fp, "%d", &Music_Data[i].Easy_Hiscore );	// EASY���ʂ̃n�C�X�R�A�𒊏o
					fscanf( fp, "%s", Music_Data[i].Easy_ClearMark );	// EASY���ʂ̃N���A�}�[�N�𒊏o

				}

				if ( strcmp( Hiscore_Work, "HYPER" ) == 0 )
				{	// �uHYPER�v���o
					fscanf(fp, "%d", &Music_Data[i].Hyper_Hiscore);		// HYPER���ʂ̃n�C�X�R�A�𒊏o
					fscanf(fp, "%s", Music_Data[i].Hyper_ClearMark);	// HYPER���ʂ̃N���A�}�[�N�𒊏o
				}

				if ( strcmp( Hiscore_Work, "MASTER" ) == 0 )
				{	// �uMASTER�v���o
					fscanf(fp, "%d", &Music_Data[i].Master_Hiscore);	// MASTER���ʂ̃n�C�X�R�A�𒊏o
					fscanf(fp, "%s", Music_Data[i].Master_ClearMark);	// MASTER���ʂ̃N���A�}�[�N�𒊏o
				}
			}

			// �t�@�C���ǂݍ��ݏI��
			fclose( fp );
		}

		// ���񌟍��t�H���_�Ɉړ�
		//************************************************************************
		if ( FindNextFile(hFind_Folder, &win32fd) != 0 )
		{	// �t�H���_�����������ƌp��
			continue;
		}
		else
		{	// �t�H���_�������Ȃ�����I��
			break;
		}
	}
}

//***********************************************************************************************************
// EOF
//***********************************************************************************************************