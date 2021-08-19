#pragma once
#include <DxLib.h>
#include <math.h>
#include "Init.h"
#include"Player.h"

// �v���C���[�֌W�̒�`
#define PLAYER_MOVE_SPEED			30.0f		// �ړ����x
#define PLAYER_ANGLE_SPEED			0.2f		// �p�x�ω����x
#define PLAYER_MAX_HITCOLL			2048		// ��������R���W�����|���S���̍ő吔
#define PLAYER_ENUM_DEFAULT_SIZE	200.0f		// ���͂̃|���S�����o�Ɏg�p���鋅�̏����T�C�Y
#define PLAYER_HIT_WIDTH			100.0f		// �����蔻��
#define PLAYER_HIT_HEIGHT			100.0f		// �����蔻��
#define PLAYER_HIT_TRYNUM			16		// �ǉ����o�������̍ő厎�s��
#define PLAYER_HIT_SLIDE_LENGTH		5.0f		// ��x�̕ǉ����o�������ŃX���C�h�����鋗��

// �X�e�[�W�֌W�̒�`
#define STAGECOLLOBJ_MAXNUM			256		// �ǉ��̃R���W�����I�u�W�F�N�g�̍ő吔

//�v���g�^�C�v�錾
bool Sph_hit_check(Sph sp[], Sph ob);
bool Sph_ehit_chech(Sph sp[], Sph e_obj[], int i);
bool Decel_aria_check(Sph sp[], Sph decelaria[], int i);
void Decel_aria_effect();//�G���A�ɓ��������̌���
int IsObs_check(Sph obs[], int i);//�ǂ̏�Q���ɓ���������
int Hit_player_speed(Sph player[], int obs_info);//�����������̃v���C���[���x
void Hit_badobject_helth(Sph player[], int obs_info,int i);//�����������̏�Q���̔���
void Sph_hit(float dis);
void Sph_ehit(float dis, int i);//��Q�������蔻��
//void Model_hit_check();
//void Model_hit();
void Ground_model_hit();
void Ground_model_hit_check(VECTOR MoveVector);
void Move_Limits();		//�v���C���[�̍��E�ړ��𐧌�����
void Damege_aria_Decele();//�_���[�W�G���A�̌���
struct StageModelHit
{
	int i, j, k;						// �ėp�J�E���^�ϐ�
	int moveflag;						// ���������Ɉړ��������ǂ����̃t���O( �O:�ړ����Ă��Ȃ�  �P:�ړ����� )
	int hitflag;						// �|���S���ɓ����������ǂ������L�����Ă����̂Ɏg���ϐ�( �O:�������Ă��Ȃ�  �P:�������� )
	MV1_COLL_RESULT_POLY_DIM hitdim[STAGECOLLOBJ_MAXNUM + 1];			// �v���C���[�̎��͂ɂ���|���S�������o�������ʂ��������铖���蔻�茋�ʍ\����
	int hitdimnum;						// HitDim �̗L���Ȕz��v�f��
	int kabenum;						// �ǃ|���S���Ɣ��f���ꂽ�|���S���̐�
	int yukanum;						// ���|���S���Ɣ��f���ꂽ�|���S���̐�
	MV1_COLL_RESULT_POLY* kabe[PLAYER_MAX_HITCOLL];	// �ǃ|���S���Ɣ��f���ꂽ�|���S���̍\���̂̃A�h���X��ۑ����Ă������߂̃|�C���^�z��
	MV1_COLL_RESULT_POLY* yuka[PLAYER_MAX_HITCOLL];	// ���|���S���Ɣ��f���ꂽ�|���S���̍\���̂̃A�h���X��ۑ����Ă������߂̃|�C���^�z��
	MV1_COLL_RESULT_POLY* poly;				// �|���S���̍\���̂ɃA�N�Z�X���邽�߂Ɏg�p����|�C���^( �g��Ȃ��Ă��ς܂����܂����v���O�����������Ȃ�̂ŁE�E�E )
	HITRESULT_LINE lineres;				// �����ƃ|���S���Ƃ̓����蔻��̌��ʂ�������\����
	VECTOR oldpos;						// �ړ��O�̍��W	
	VECTOR nowpos;						// �ړ���̍��W
	//�ړ��x�N�g��
	VECTOR targetmovedirection;			// ���f���������ׂ������̃x�N�g��
	VECTOR movepos;

	VECTOR upvec = VGet(0.0f, 0.0f, 10.0f);
	VECTOR downvec = VGet(0.0f, 0.0f, -1.0f);
	VECTOR rightvec = VGet(1.0f, 0.0f, 0.0f);
	VECTOR leftvec = VGet(-1.0f, 0.0f, 0.0f);

	bool groundflg = false;

	
	
};


struct HitDrow
{
	bool hitflg;
	bool e_hitflg;
};

struct Decel {
	bool  hit_flg;
};

//����\����
struct Branch
{
	//int glimits_verification[2] = { -1500,1800 }; //�[�̐��l�@0: ���̒[ 900 : �E�̒[
	//int landr_move = 0;			//0:�Ȃ��@1:�� 2:�E		���E�̃{�^���ǂ���������Ă��邩
	//bool gmoveflg = false;    //false:�����͈͓��@true:�����͈͊O
	//int move_branch = 0;		//0:�����@1:�� 2:�E ����ȊO:�Ȃ�	���̕���
	//int branch_point[1] = { 20000 };	//����n�_�̍��W
	//int branch_position = 0;		//�v���C���[���ǂ̃R�[�i�[�ɂ��邩�̃J�E���g
};

extern Decel decel;
extern HitDrow htdrow;
extern StageModelHit st_model_hit;
extern Branch branch;
extern VECTOR g_frontVector;
extern HITRESULT_LINE g_frontpos2;//��̎�O�ɍ₪���邩�ǂ����𒲂ׂ邽�߂̂���