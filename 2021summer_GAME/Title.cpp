#include <DxLib.h>
#include "Title.h"
#include "Init.h"

int down_num = 0;
int up_num = 0;
int input_count = 0;

int TitleLoad() {//�摜�̓ǂݍ���	
	if ((title.g_title = LoadGraph("images/title.png")) == -1)return -1;
}
void Titleinit() {
	TitleLoad();
	TitleSlectInit();
	//�^�C�g���̏������W�Ƃ������
}
void TitleSlectInit() {
	
	gameexit = false; //�Q�[���I���t���O

	for (int i = 0; i < 2; i++) {
		title_slectfream[i].color = GetColor(0, 0, 0);//�I����ʃt���[��
		title_slect[i].color = GetColor(255, 255, 255);//�����J���[��
		title_slect[i].select_color = GetColor(0, 255, 0);//�I������Ă����ԃO���[���F
		title_slect[i].selectflg = false;
	}
	title_slect[0].selectnum = 0;
	title_slect[1].selectnum = 1;
	
	//0
	title_slect[0].start_x = 392;
	title_slect[0].start_y = 504;
	title_slect[0].end_x = 631;
	title_slect[0].end_y = 566;
	
	//1
	title_slect[1].start_x = 390;
	title_slect[1].start_y = 614;
	title_slect[1].end_x = 631;
	title_slect[1].end_y = 680;
}
void Titledraw() {//�摜�̕`��
	DrawGraph(0,0,title.g_title,FALSE); 
	TitleSlect();
	//if (CheckHitKey(KEY_INPUT_S)) {
	////	gameMode = 1;
	//}

	TitleInput();
}
void TitleInput() {
	
	if (CheckHitKey(KEY_INPUT_DOWN)) {
		down_num++;
	}
	else {
		down_num = 0;
	}

	if (down_num == 1) {
		input_count--;
	}
	else if (up_num == 1) {
		input_count++;
	}

	if (CheckHitKey(KEY_INPUT_UP)) {
		up_num++;
	}
	else {
		up_num = 0;
	}

	//�I����Ԃ��I���ɂ���
	if (input_count % 2 == title_slect[0].selectnum) {
		title_slect[0].selectflg = true;
		if (title_slect[0].selectflg) {
			title_slect[1].selectflg = false;
		}
	}
	else {
		title_slect[1].selectflg = true;
		if (title_slect[1].selectflg) {
			title_slect[0].selectflg = false;
		}
	}

	if (CheckHitKey(KEY_INPUT_SPACE)) {
		for (int i = 0; i < 2; i++){
			if (title_slect[i].selectflg) {
				int slectstate = title_slect[i].selectnum;
				if (slectstate == 0) { //�Q�[���X�^�[�g����
					//1000=1�b�҂�
					WaitTimer(1000);
					gameMode = 1;
				}
				else {//�Q�[���I��
					gameexit = true;
				}
			}
		}
	}
}
void TitleSlect() {
	//�I����ʂ̘g
	DrawBox(388, 500, 635, 570, title_slectfream[0].color, TRUE);
	DrawBox(386, 610, 635, 684, title_slectfream[1].color, TRUE);
	
	for (int i = 0; i < 2; i++) {
		//flg���I���Ȃ�I�����
		if (title_slect[i].selectflg) {
			DrawBox(title_slect[i].start_x, title_slect[i].start_y, title_slect[i].end_x, title_slect[i].end_y, title_slect[i].select_color, TRUE);
		}
		else {
			DrawBox(title_slect[i].start_x, title_slect[i].start_y, title_slect[i].end_x, title_slect[i].end_y, title_slect[i].color, TRUE);
		}
	}
	/*DrawFormatString(100, 100, GetColor(0, 255, 0), "[input_count %d ]", input_count % 2);*/
	DrawFormatString(470, 530, GetColor(0, 0, 0), "�Q�[���J�n");
	DrawFormatString(470, 640, GetColor(0, 0, 0), "�Q�[���I��");
}