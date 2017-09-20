//=================================================================
// 
// �V���O���g���N���X[Singleton.h]
// Author	: ���{�T��
// DATE		: 2016/06/29
// UPDATE	: 2016/06/29	�e���v���[�g�V���O���g���N���X�쐬
//
// 
//=================================================================
#pragma once

#include <memory>

template <class T>
class Singleton
{
public:
	static T* getInstance(void)
	{
		static T instance;
		return &instance;
	}
protected:
	Singleton(void) {}
	virtual ~Singleton(void) {}
private:
	Singleton(const T& obj);
	//Singleton& operator = (const Singleton& obj);
};