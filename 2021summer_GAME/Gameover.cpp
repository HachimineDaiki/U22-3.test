#include <DxLib.h>
#include"Gameover.h"
#include"Init.h"
#include"Player.h"
#include"3Dmodel.h"
#include"Camera.h"

int Gameoverload() {  //�Q�[���I�[�o�[�̉摜�����[�h����
	if ((gameover.g_gameover = LoadGraph("images/gameover2.png")) == -1)return -1;
}

void Gameoverinit() {  //�Q�[���I�[�o�[�̉摜�����[�h����
	Gameoverload();
}


void Gameoverdraw() {   //�Q�[���I�[�o�[�̉摜��`�悷��
	DrawGraph(0, 0, gameover.g_gameover, FALSE);
	if (CheckHitKey(KEY_INPUT_SPACE)) {
		
		g = 9.81f;
		rock[0].handle_num = P_rest_hp_handle(sph[0].hp);
		Sph_init();//���̏�����
		Obj_init();//�s�@�������̏�����
		Damege_Init();//��Q���̏�����
		Decelearia_init();//�����G���A������
		Model_init();//���f��������
		Camera_set();//�J�����Z�b�g
		Model3d_load();//3D���f���ǂݍ���
		Model3d_init();//3D���f��������
		gameMode = 0;
	}
}