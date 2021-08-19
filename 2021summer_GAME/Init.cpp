#include "Init.h"
#include "3Dmodel.h"
#include "Player.h"
void Sph_init() {
	//�v���C���[�̏�����
	for (int i = 0; i < 2; i++) {
		sph[i].speed = 10.0f; //�v���C���[���x
		sph[i].radius = 200.0f;//�v���C���[���a
		sph[i].v0y = 0.0f; //�v���C���[Y�������x
		sph[i].pos = VGet(100.0f, 468.0f, 1300.0f);//�v���C���[�������W
		sph[i].color = GetColor(255, 255, 255);//�v���C���[�J���[
		sph[i].zaccl = 2.0f;//�v���C���[z����accelerator
		sph[i].zmove = 0.0f;//�v���C���[Z�����ړ�
		sph[i].control = 0.02f;//�v���C���[���x�����ϐ�
		sph[i].hp = 300;//�v���C���[�̗�
		sph[0].front = 500;//�v���C���[�̑O��500
	}
	
	sph[0].v = VGet(0.0f, 0.0f, 0.0f);//�v���C���[�x�N�g��
	g_frontmoveflg = 0;//�O�ɍ₪���邩�ǂ����̏�����
	g_CollisionReflectionFlag = 0;//0 �Փ˂��Ĕ��˂��Ă��Ȃ� 1 �Փ˂��Ĕ��˂��Ă���
	p_zmoveflg = false;

	sph[0].direction = VGet(0, 0, 1);//�v���C���̌����ĕ��� ���� z����
}

//�s�@����������
void Obj_init(){
	obj.pos = VGet(-3000.0f, -20000.0f, 120000.0f);//�s�@�����������W
	obj.radius = 400.0f;//�s�@�������a
	obj.color = GetColor(0, 255, 100);//�s�@�����J���[
}
//����������_���\�W���󂯂��Q��������
void Damege_Init() {
	for (int i = 0; i < DAMEGE_ARIA_MAX; i++) {
		//if (i >= 0 && i <= 2) {
		//	damege_aria[i].radius = 100.0f;
		//	damege_aria[i].color = GetColor(255, 0, 0);
		//	damege_aria[i].name = S;//��Q���̑傫��S
		//	damege_aria[i].hp = 10;//test�p�̗̑�
		//	damege_aria[i].obj_flag = true;
		//}
		if (i >= 0 && i <= 5) {
			damege_aria[i].radius = 200.0f;
			damege_aria[i].color = GetColor(255, 255, 0);
			damege_aria[i].name = M;//��Q���̑傫��M
			damege_aria[i].hp = 50;//test�p�̗̑�
			damege_aria[i].obj_flag = true;
		}
		else {
			damege_aria[i].radius = 400.0f;
			damege_aria[i].color = GetColor(0, 255, 0);
			damege_aria[i].name = L;//��Q���̑傫��L
			damege_aria[i].hp = 100;//test�p�̗̑�
			damege_aria[i].obj_flag = true;
		}

			//�_���[�W�G���A�������W
			damege_aria[0].pos = VGet(11853.0f, -4330.0f, 28851.0f);
			damege_aria[1].pos = VGet(11232.0f, -4669.0f, 31544.0f);
			damege_aria[2].pos = VGet(11922.0f, -4477.0f, 29957.0f);
			damege_aria[3].pos = VGet(20700.0f, -6489.0f, 41609.0f);
			damege_aria[4].pos = VGet(24099.0f, -5814.0f, 42633.0f);
			damege_aria[5].pos = VGet(25916.0f, -9196.0f, 57011.0f);
			damege_aria[6].pos = VGet(28500.0f, -10060.0f, 61438.0f);
			damege_aria[7].pos = VGet(27000.0f, -11351.0f, 69486.0f);
			damege_aria[8].pos = VGet(25555.0f, -12654.0f, 76525.0f);
			damege_aria[9].pos = VGet(27000.0f, -12654.0f, 76525.0f);
	}
}

//�����G���A������
void Decelearia_init() {
	for (int i = 0; i < DECELE_ARIA_MAX; i++) {
		decele_aria[i].radius = 400.0f;
		decele_aria[i].color = GetColor(255, 0, 0);
		decele_aria[i].v = VGet(0.0f, 0.0f, 0.0f);
	}
	
	//�������W
	decele_aria[0].pos = VGet(-1000.0f, -200.0f, 5000.0f);
	decele_aria[1].pos = VGet(1000.0f, -200.0f, 5000.0f);
	decele_aria[3].pos = VGet(100.0f, -1070.0f, 10000.0f);
	decele_aria[4].pos = VGet(500.0f, -2000.0f, 15000.0f);
	decele_aria[5].pos = VGet(-500.0f, -2000.0f, 15000.0f);
	decele_aria[6].pos = VGet(-6695.0f, -3820.0f, 25958.0f);
	/*decelearia[7].pos = VGet(-6695.0f, -3820.0f,26400.0f);*/
	decele_aria[8].pos = VGet(-20548.0f, -6289.0f, 40640.0f);
	decele_aria[9].pos = VGet(-26253.0f, -10815.0f, 66417.0f);
	decele_aria[10].pos = VGet(-25289.0f, -12677.0f, 76443.0f);
	decele_aria[11].pos = VGet(-11387.0f, -16461.0f, 98970.0f);
}

//���f���̏�����
void Model_init() {
	//�n�ʏ������W
	ground.x = 0.0f;
	ground.y = 0.0f;
	ground.z = 0.0f;

	//�ǂ̏������W
	wall[0].x = -2000.0f;
	wall[0].y = -1000.0f;
	wall[0].z = 8000.0f;

	wall[1].x = 2000.0f;
	wall[1].y = -1000.0f;
	wall[1].z = 8000.0f;

	//�v���C���[�⏉�����W
	//rock[0].x = 100.0f;
	//rock[0].y = 5471.0f;
	//rock[0].z = 20000.0f;
}