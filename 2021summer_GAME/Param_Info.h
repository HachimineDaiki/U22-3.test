#pragma once
#include "DxLib.h"
#include "Init.h"
#include "Hit_check.h"
#include "Player.h"
#include "Camera.h"
#include "3Dmodel.h"


void Init_Draw_Display();
void DrawDisplay();
void DrawParam_Info();

struct DrawStr
{
	int color;
	int x, y, z;
	int str_size;

	float speed;
};

extern DrawStr speed_draw_str;