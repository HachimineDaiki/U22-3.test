#pragma once
#include "Player.h"
#define PLYAER_COLOR 3 //�v���C���[HP�����������ς��F
#define WALL_MAX 2
struct Model {
	float x, y, z;//���f���̍��W
	int handle;//���f���f�[�^�����
	int handle_num;//���f���̓Y�����ԍ�
};

void Model3d_init();//�������ʒu
void Model3d_load();//3D�ǂݍ���
void Model3d_draw();//3D�`��
void Model3d_dlet();//3D���f������

//extern �̓t�@�C���̊O���ɕϐ������L���������
extern Model ground;//�n��
extern Model rock[3];//�v���C���[��
extern Model wall[WALL_MAX];//�ǒǉ�
extern Model gensoku[DECELE_ARIA_MAX];
extern Model e_rock[DAMEGE_ARIA_MAX];