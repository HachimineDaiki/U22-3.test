#include <DxLib.h>
#include "User_Interface.h"
#include "player.h"

VECTOR Ill_dump2;//�ړ����Ă���s�@�������̈ʒu������
float distance;//�s�@�������̈ړ������������
int judgement = 0;//1�����@2�听���@�̃t���O

//UI�Ɏg�p������̏�����
void UIinit() {
	g_Ill_dump1 = obj.pos;
	Ill_dump2 = VGet(0.0f, 0.0f, 0.0f);
	g_goalflag = 0;//�S�[���������ǂ����@0�S�[�����ĂȂ��@1�S�[������
}

void Judgement() {
	if ((sph[0].zmove >= 130) || (sph[0].zmove <= -130)){
		judgement = 2;
	}
	else if ((sph[0].zmove >= 110) || (sph[0].zmove <= -110)) {
		judgement = 1;
	}
}

//�s�@�������̔�񂾋������v�Z
void Distance_Calculation() {
	float x, y, z;

	Ill_dump2 = obj.pos;

	x = Ill_dump2.x - g_Ill_dump1.x;
	y = Ill_dump2.y - g_Ill_dump1.y;
	z = Ill_dump2.z - g_Ill_dump1.z;
	distance = VSize(VGet(x, y, z));
	 
}


//UI�̕\��
void UIdraw() {
	
	SetFontSize(100);//�����T�C�Y��ύX
//	DrawFormatString(341, 334, GetColor(255, 255, 0), " GOAL "); 
	if (obj.zmove >= 1) {
		DrawFormatString(341, 140, GetColor(0, 255, 255), " GOAL ");
	}
	if (obj.zmove < 1) {
		if (judgement == 1) {
			DrawFormatString(341, 140, GetColor(255, 255, 0), " ���� ");
		}
		else if (judgement == 2) {
			DrawFormatString(291, 140, GetColor(255, 255, 0), " �听�� ");
		}
	}
	//DrawFormatString(341, 20, GetColor(0, 255, 255), " GOAL ");
	SetFontSize(50);
	//DrawFormatString(341, 120, GetColor(0, 0, 0), "%.0f", distance);//�^��
	DrawFormatString(341, 240, GetColor(0, 0, 0), "   %.0fm", distance);//�^��

	//DrawFormatString(0, 0, GetColor(0, 0, 0), "%.0f", distance);//����
	//DrawFormatString(341, 0, GetColor(0, 0, 0), "%.0f", distance);//��
	//DrawFormatString(682, 0, GetColor(0, 0, 0), "%.0f", distance);//�E��
	//DrawFormatString(0, 256, GetColor(0, 0, 0), "%.0f", distance);//��
	//DrawFormatString(682, 434, GetColor(0, 0, 0), "%.0f", distance);//�E
	//DrawFormatString(0, 512, GetColor(0, 0, 0), "%.0f", distance);//����
	//DrawFormatString(341, 512, GetColor(0, 0, 0), "%.0f", distance);//��
	//DrawFormatString(682, 512, GetColor(0, 0, 0), "%.0f", distance);//�E��

	DrawFormatString(341, 484, GetColor(0, 0, 0), "%.0f", obj.zmove);
	SetFontSize(20);//�����T�C�Y��ύX
}