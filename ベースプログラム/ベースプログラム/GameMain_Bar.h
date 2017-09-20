//*************************************************************************
//
// �����ɃI�u�W�F�N�g�̐���
//
//*************************************************************************
#pragma once 

//*************************************************************************
// �C���N���[�h��
//*************************************************************************
#include "CTexture_2D_Base.h" 
#include <deque>

using namespace std;

//*************************************************************************
// �N���X��`
//*************************************************************************
class GameMain_Bar : public CTexture_2D_Base
{
private:
	int	LaneSize;
	int	CursolSize;

	deque<int> SelectLane;
	float MouseY;
public:
	void Initialize(int laneSize, int cursolSize);
	void Update(void);
	void Draw(void);

	void AddRotate();

	GameMain_Bar(void);
	virtual ~GameMain_Bar(void);

	deque<int> GetSelectLane();	// �I�𒆂̃��[����Ԃ�
};

//*************************************************************************
// EOF
//*************************************************************************
