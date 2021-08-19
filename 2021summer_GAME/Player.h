#pragma once
#define VECTOR_SLIDE 0.86602540378
#define DECELE_ARIA_MAX 100 //�����G���A�ő�l
#define DAMEGE_ARIA_MAX 10//�_���[�W�G���A�ő�l
struct Sph
{
	float radius;
	float speed;
	float v0y;
	int color;
	VECTOR pos;
	VECTOR v;
	float dis;
	float radius_sum;
	float zaccl; //Z������
	float zmove; //Z������
	float control;
	int hp; //�v���C���[��HP
	int name;//�v���C���[name���
	int hit_name;//��������name���
	float hit_speed;//���������X�s�[�h�ۑ�
	float front;//�v���C���[�̑O��
	bool obj_flag;//�G�����݂��邩�t���O�B
	VECTOR direction; //�����Ă������
};

struct Damege {
	const int _0 = 0;
	const int _15 = 15;
	const int _25 = 25;
	const int _30 = 30;
	const int _50 = 50;
	const int _100 = 100;
};

int Input_PlayerMoveDir();//�v���C���[���͕���
void P_input_move();//�v���C���[�̓��͎�t
void P_move();//�v���C���[����
void P_rotate();
int  P_rest_hp_handle(int hp);//�c��hp����B
void P_hp(int obssize); //�v���C���[hp�Ǘ�
void Sph_Gravity();//�v���C���[�d��
void Accl();//��������
void P_Direction();//�v���C���[����
float P_CollisionVelocity();//���ˏ���
struct Input {
	bool space;
};

enum Dir { Left, Right, Down, Up };
enum Size { S = 1, M, L };//�������l1����J�n
enum Color { RED, GREEN, BULE };

extern float g;//�d�� 9.81

//�I�u�W�F�N�g����
extern Sph sph[2];//�v���C���[
extern Sph obj;//�s�@������
extern Sph damege_aria[DAMEGE_ARIA_MAX]; //������ƃ_���[�W��������I�u�W�F�N�g
extern Sph decele_aria[DECELE_ARIA_MAX]; //�����G���A

extern float s_dis;
extern float es_dis;//��Q���p
extern float g_p_direct;//�v���C���[����
extern float g_p_Rotate;//�v���C���[�̉�]
extern float g_p_rotate_amount;//�v���C���[�̉�]��
extern bool p_zmoveflg;//�O�i�Ɉړ�����t���O
extern VECTOR TempMoveVector;
extern Input input;
extern Damege obs_damege;//��Q���̃_���[�W��
extern int g_frontmoveflg;//0�@�O�ɍ�i�V�@1�@�O�ɍ�A��
extern int g_CollisionReflectionFlag;//0 �Փ˂��Ĕ��˂��Ă��Ȃ� 1 �Փ˂��Ĕ��˂��Ă���