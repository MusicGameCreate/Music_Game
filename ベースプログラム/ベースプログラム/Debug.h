#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <d3dx9.h>
#include "CDirectX.h"
#include "Define.h"

// �f�o�b�O���O�o�̓N���X
class CDebugLog
{
private:
	char*		font;
public:
	void Init();
	void Finalise();

	void Output(char* str);
};