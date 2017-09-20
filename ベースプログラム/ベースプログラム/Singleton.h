//=================================================================
// 
// シングルトンクラス[Singleton.h]
// Author	: 松本裕太
// DATE		: 2016/06/29
// UPDATE	: 2016/06/29	テンプレートシングルトンクラス作成
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