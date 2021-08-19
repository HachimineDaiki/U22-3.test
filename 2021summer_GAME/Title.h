#pragma once
//#include "Main.h"
int TitleLoad();
void Titleinit();
void Titledraw();
void TitleSlect();
void TitleInput();

void TitleSlectInit();
struct Title
{
	int g_title;
	int x, y;//ç¿ïW
};

struct Title_Slect {
	int start_x, start_y;
	int end_x, end_y;
	int img_width , img_height;
	int color;
	int select_color;
	int selectnum;
	bool selectflg;
	char mozi[256];
};
extern Title title;
extern Title_Slect title_slect[2];
extern Title_Slect title_slectfream[2];
extern bool gameexit;