#include <DxLib.h>
#include "User_Interface.h"
#include "player.h"

VECTOR Ill_dump2;//移動している不法投棄物の位置を入れる
float distance;//不法投棄物の移動距離をいれる
int judgement = 0;//1成功　2大成功　のフラグ

//UIに使用する情報の初期化
void UIinit() {
	g_Ill_dump1 = obj.pos;
	Ill_dump2 = VGet(0.0f, 0.0f, 0.0f);
	g_goalflag = 0;//ゴールしたかどうか　0ゴールしてない　1ゴールした
}

void Judgement() {
	if ((sph[0].zmove >= 130) || (sph[0].zmove <= -130)){
		judgement = 2;
	}
	else if ((sph[0].zmove >= 110) || (sph[0].zmove <= -110)) {
		judgement = 1;
	}
}

//不法投棄物の飛んだ距離を計算
void Distance_Calculation() {
	float x, y, z;

	Ill_dump2 = obj.pos;

	x = Ill_dump2.x - g_Ill_dump1.x;
	y = Ill_dump2.y - g_Ill_dump1.y;
	z = Ill_dump2.z - g_Ill_dump1.z;
	distance = VSize(VGet(x, y, z));
	 
}


//UIの表示
void UIdraw() {
	
	SetFontSize(100);//文字サイズを変更
//	DrawFormatString(341, 334, GetColor(255, 255, 0), " GOAL "); 
	if (obj.zmove >= 1) {
		DrawFormatString(341, 140, GetColor(0, 255, 255), " GOAL ");
	}
	if (obj.zmove < 1) {
		if (judgement == 1) {
			DrawFormatString(341, 140, GetColor(255, 255, 0), " 成功 ");
		}
		else if (judgement == 2) {
			DrawFormatString(291, 140, GetColor(255, 255, 0), " 大成功 ");
		}
	}
	//DrawFormatString(341, 20, GetColor(0, 255, 255), " GOAL ");
	SetFontSize(50);
	//DrawFormatString(341, 120, GetColor(0, 0, 0), "%.0f", distance);//真ん中
	DrawFormatString(341, 240, GetColor(0, 0, 0), "   %.0fm", distance);//真ん中

	//DrawFormatString(0, 0, GetColor(0, 0, 0), "%.0f", distance);//左上
	//DrawFormatString(341, 0, GetColor(0, 0, 0), "%.0f", distance);//上
	//DrawFormatString(682, 0, GetColor(0, 0, 0), "%.0f", distance);//右上
	//DrawFormatString(0, 256, GetColor(0, 0, 0), "%.0f", distance);//左
	//DrawFormatString(682, 434, GetColor(0, 0, 0), "%.0f", distance);//右
	//DrawFormatString(0, 512, GetColor(0, 0, 0), "%.0f", distance);//左下
	//DrawFormatString(341, 512, GetColor(0, 0, 0), "%.0f", distance);//下
	//DrawFormatString(682, 512, GetColor(0, 0, 0), "%.0f", distance);//右下

	DrawFormatString(341, 484, GetColor(0, 0, 0), "%.0f", obj.zmove);
	SetFontSize(20);//文字サイズを変更
}