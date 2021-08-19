#include <DxLib.h>
#include "3Dmodel.h"

float wood_interval = 1300;//�؂̊Ԋu

void Model3d_load() {
	//Stage15
	//Stage_Short.mv1
	ground.handle = MV1LoadModel("3Dmodel/Stage_Short_var01.mv1");
	rock[0].handle = MV1LoadModel("3Dmodel/Rock.mv1");
	rock[1].handle = MV1LoadModel("3Dmodel/Rock_1.mv1");
	rock[2].handle = MV1LoadModel("3Dmodel/Rock_red.mv1");
	//�ǂ̃��f���ǂݍ���
	for (int i = 0; i < WALL_MAX; i++) {
		wall[i].handle = MV1LoadModel("3Dmodel/Wall_1.mv1");
	}
	//�ʂ���ݏ�
	for (int i = 0; i < DECELE_ARIA_MAX; i++) {
		gensoku[i].handle = MV1LoadModel("3Dmodel/MuDColor1.mv1");
	}
	//��Q����
	for (int i = 0; i < DAMEGE_ARIA_MAX; i++) {
		if (damege_aria[i].name == L) {
			e_rock[i].handle = MV1LoadModel("3Dmodel/Rock_L.mv1");
		}
		else if(damege_aria[i].name == M){
			e_rock[i].handle = MV1LoadModel("3Dmodel/Rock_M.mv1");
		}else if (damege_aria[i].name == S) {
			e_rock[i].handle = MV1LoadModel("3Dmodel/Rock_S.mv1");
		}
	}
}

void Model3d_init() {
	//��ʂɉf��ʒu�ɂR�c���f�����ړ�
	MV1SetPosition(ground.handle, VGet(ground.x, ground.y, ground.z));//�����ʒu�ݒ�
	
	//�ǂ̏����ʒu
	for (int i = 0; i < WALL_MAX;i++) {
		MV1SetPosition(wall[i].handle, VGet(wall[i].x,wall[i].y,wall[i].z));//�����ʒu�ݒ�
		rock[0].handle_num = 0;//�⃂�f���@�����F�@handle
	}

	for (int i = 0; i < DECELE_ARIA_MAX; i++) {
		MV1SetPosition(gensoku[i].handle, VGet(decele_aria[i].pos.x, decele_aria[i].pos.y-120, decele_aria[i].pos.z));//�����ʒu�ݒ�
	}

	for (int i = 0; i < DAMEGE_ARIA_MAX; i++) {
		MV1SetPosition(e_rock[i].handle, VGet(damege_aria[i].pos.x, damege_aria[i].pos.y - 60, damege_aria[i].pos.z));//�����ʒu�ݒ�
	}

	
	//�ǃ��f����] (�x�� * DX_PI_F / 180.0f) �œx���ɕϊ�
	MV1SetRotationXYZ(wall[0].handle, VGet(10.0f * DX_PI_F / 180.0f, 0.0f, 0.0f));
	MV1SetRotationXYZ(wall[1].handle, VGet(10.0f * DX_PI_F / 180.0f, 0.0f, 0.0f));
	MV1SetRotationXYZ(ground.handle, VGet(5.0f * DX_PI_F / 180.0f, 0.0f, 0.0f));
	//for (int i = 0; i < TREE_NUM / 4; i++) {
	//	MV1SetPosition(tree_handle[i], VGet(-1200.0f, ground.y, -650.0f + (wood_interval * i)));
	//	//MV1SetRotationXYZ(tree_handle[i], VGet(10.0f, 0.0f, 0.0f));

	//	/*MV1SetPosition(tree_handle[i + TREE_NUM / 4], VGet(-550.0f, ground.y, 0.0f + (wood_interval * i)));
	//	MV1SetRotationXYZ(tree_handle[i + TREE_NUM / 4], VGet(45.0f * DX_PI_F / 180.0f, 0.0f, 0.0f));

	//	MV1SetPosition(tree_handle[i + TREE_NUM / 2], VGet(-550.0f + wood_interval, ground.y, 0.0f + (wood_interval * i)));
	//	MV1SetRotationXYZ(tree_handle[i + TREE_NUM / 2], VGet(45.0f * DX_PI_F / 180.0f, 0.0f, 0.0f));

	//	MV1SetPosition(tree_handle[i + TREE_NUM / 4 + TREE_NUM / 2], VGet(100.0f + wood_interval, ground.y, -650.0f + (wood_interval * i)));
	//	MV1SetRotationXYZ(tree_handle[i + TREE_NUM / 4 + TREE_NUM / 2], VGet(45.0f * DX_PI_F / 180.0f, 0.0f, 0.0f));*/
	//}

	MV1SetupCollInfo(ground.handle, -1);
}

void Model3d_draw() {
	//�R�c���f���̕`��
	MV1DrawModel(ground.handle);
	MV1DrawModel(rock[rock[0].handle_num].handle);
	
	//�ǃ��f���`��
	for (int i = 0; i < WALL_MAX; i++) {
		MV1DrawModel(wall[i].handle);
	}
	for (int i = 0; i < DECELE_ARIA_MAX; i++) {
		MV1DrawModel(gensoku[i].handle);
		MV1SetRotationXYZ(gensoku[i].handle, VGet(10.0f * DX_PI_F / 180.0f, 0.0f, 0.0f));
	}
	//SetUseLighting(FALSE);//���C�e�B���O�v�Z�I�t
}

void Model3d_dlet() {
	//// ���f���n���h���̍폜
	MV1DeleteModel(ground.handle);
	//�ǃ��f���폜
	for (int i = 0; i < WALL_MAX; i++) {
		MV1DeleteModel(wall[i].handle);
	}
	for (int i = 0; i < PLYAER_COLOR; i++) { //�v���C���[�F
		MV1DeleteModel(rock[i].handle);
	}
	for (int i = 0; i < DECELE_ARIA_MAX; i++) { //�v���C���[�F
		MV1DeleteModel(gensoku[i].handle);
	}

	for (int i = 0; i < DAMEGE_ARIA_MAX; i++) { //�v���C���[�F
		MV1DeleteModel(e_rock[i].handle);
	}
}