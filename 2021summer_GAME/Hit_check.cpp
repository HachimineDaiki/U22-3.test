#include <Dxlib.h>
#include <math.h>
#include "Hit_check.h"
#include "3Dmodel.h"
#include "Player.h"
#include "Camera.h"
#include "Init.h"

float p_vz = 0;
struct STAGE
{
	int		ModelHandle;				// �X�e�[�W�̃��f���n���h��
	int		CollObjBaseModelHandle;		// �R���W�������f���̔h�����n���h��
	int		CollObjModelHandle[STAGECOLLOBJ_MAXNUM];	// �X�e�[�W�ɔz�u����R���W�������f���̃n���h��
	int		CollObjNum;				// �X�e�[�W�ɔz�u���Ă���R���W�������f���̐�
};

STAGE stg;

//�����������v���C���[�ɉe������HP
int Hit_player_speed(Sph player[], int obs_info) {
	int hp = 0;
	
	if (obs_info == L) {//�傫����Q��
		if (player[0].zmove >= 0 && player[0].zmove <= 60) {
			hp = obs_damege._30;
		}
		else if (player[0].zmove >= 61 && player[0].zmove <= 100) {
			hp = obs_damege._50;
		}
		else if (player[0].zmove >= 101) {
			hp = obs_damege._100;
		}
		else {
			hp = obs_damege._0;
		}
	}
	else if(obs_info == M){//����Q��
		if (player[0].zmove >= 0 && player[0].zmove <= 60) {
			hp = obs_damege._15;
		}
		else if (player[0].zmove >= 61 && player[0].zmove <= 100) {
			hp = obs_damege._25;
		}
		else if (player[0].zmove >= 101) {
			hp = obs_damege._50;
		}
		else {
			hp = obs_damege._0;
		}
	}
	else {//��������Q��
		hp = obs_damege._0;
	}

	return hp;
}
void Hit_badobject_helth(Sph player[], int obs_info, int i) {

	if (obs_info == L) {
		if (player[0].zmove >= 100) {
			DrawFormatString(0, 0, GetColor(0, 255, 255), "HIT_L");
			damege_aria[i].obj_flag = false;
			damege_aria[i].radius = 0;
			damege_aria[i].pos = VGet(1.0f, 1.0f, 1.0f);
		}
	}
	else if (obs_info == M) {
		if (player[0].zmove >= 50) {
			DrawFormatString(0, 0, GetColor(0, 255, 255), "HIT_M");
			damege_aria[i].obj_flag = false;
			damege_aria[i].radius = 0;
			damege_aria[i].pos = VGet(1.0f, 1.0f, 1.0f);
		}
	}
	else {
		if (player[0].zmove >= 10) {
			DrawFormatString(0, 0, GetColor(0, 255, 255), "HIT_S");
			damege_aria[i].obj_flag = false;
			damege_aria[i].radius = 0;
			damege_aria[i].pos = VGet(1.0f, 1.0f, 1.0f);
		}
	}
}
//�ǂ̏�Q���ɂ��������̂�
int IsObs_check(Sph obs[], int i) {
	int obs_size = 0;//��Q���̃T�C�Y��Ԃ��ϐ�

	switch (obs[i].hit_name)//����������Q���̖��O��T��
	{
	case L:obs_size = L;//�傫���T�C�Y
		break;
	case M:obs_size = M;//���T�C�Y
		break;
	case S:obs_size = S;//�������T�C�Y
		break;
	}

	return obs_size;//��Q���̃T�C�Y��Ԃ�
}

//�����m�����蔻��
bool Sph_hit_check(Sph sp[], Sph ob) {
	sph[0].v.x = ob.pos.x - sp[0].pos.x;//x����
	sph[0].v.y = ob.pos.y - sp[0].pos.y;//y����
	sph[0].v.z = ob.pos.z - sp[0].pos.z;//z����

	s_dis = sph[0].v.x * sph[0].v.x + sph[0].v.y * sph[0].v.y + sph[0].v.z * sph[0].v.z;//2�_�Ԃ̋���

	float radius_sum = (sp[0].radius + ob.radius) * (sp[0].radius + ob.radius); //���a�̘a
	return s_dis < radius_sum ? true : false;//2�_�Ԃ̋��������a�̘a��菬������Γ������Ă���Ɣ���
}

//�_���[�W�G���A
bool Sph_ehit_chech(Sph sp[], Sph _damege_aria[], int i) {
	damege_aria[i].v.x = _damege_aria[i].pos.x - sp[0].pos.x;//x����
	damege_aria[i].v.y = _damege_aria[i].pos.y - sp[0].pos.y;//y����
	damege_aria[i].v.z = _damege_aria[i].pos.z - sp[0].pos.z;//z����

	damege_aria[i].dis = damege_aria[i].v.x * damege_aria[i].v.x + damege_aria[i].v.y * damege_aria[i].v.y + damege_aria[i].v.z * damege_aria[i].v.z;//2�_�Ԃ̋���
	damege_aria[i].radius_sum = (sp[0].radius + damege_aria[i].radius) * (sp[0].radius + damege_aria[i].radius); //���a�̘a
	
	bool hit;//���������̂��Ԃ��p

	//�_���[�W�G���A�ɓ����Ă��邩�`�F�b�N
	if (damege_aria[i].dis < damege_aria[i].radius_sum) {
		hit = true;//���������B
		damege_aria[i].hit_name = damege_aria[i].name;//���������_���[�W�G���A�̖��O������B
		damege_aria[i].hit_speed = sph[0].zmove;//�����������̃v���C���[�̑��x������B
		P_hp(IsObs_check(damege_aria, i));//���������_���[�W�G���A�̃T�C�Y��HP�����B
		Hit_badobject_helth(sph, IsObs_check(damege_aria, i), i);
	}
	else
	{
		hit = false;//�������Ă��Ȃ��B
	}

	return hit;//�������Ă��邩����Ԃ��B
}
//�����G���A�̃`�F�b�N���菈��
bool Decel_aria_check(Sph sp[], Sph decele[], int i) {
	decele_aria[i].v.x = decele[i].pos.x - sp[0].pos.x;
	decele_aria[i].v.y = decele[i].pos.y - sp[0].pos.y;
	decele_aria[i].v.z = decele[i].pos.z - sp[0].pos.z;

	decele_aria[i].dis = decele_aria[i].v.x * decele_aria[i].v.x + decele_aria[i].v.y * decele_aria[i].v.y + decele_aria[i].v.z * decele_aria[i].v.z;
	decele_aria[i].radius_sum = (decele[i].radius + sp[0].radius) * (decele[i].radius + sp[0].radius);
	return decele_aria[i].dis < decele_aria[i].radius_sum ? true : false;
}


//�������x����
void Decel_aria_effect(){

	if (sph[0].zmove > 10) {
		sph[0].zmove *= 0.93f;
	}else if (-10 > sph[0].zmove) {
		sph[0].zmove *= 0.93f;
	}


	//if (g_frontmoveflg == 1) {
	//	if ((sph[0].zmove >= -15) && (sph[0].zmove <= 0)) {
	//		sph[0].zmove = -15;
	//	}
	//}
	//if (g_frontmoveflg == 0) {
	//	if ((sph[0].zmove <= 15) && (sph[0].zmove >= 0)) {
	//		sph[0].zmove = 15;
	//	}
	//}

}

//�_���[�W�G���A�@��������
void Damege_aria_Decele() {
	sph[0].zmove *= 0.7f;
}

//���Ƌ��̓����蔻������m������̏���
void Sph_hit(float dis) {
	float len = sqrtf(dis);
	float radius_sum = sph[0].radius + obj.radius;
	float merikomi = radius_sum - len;

	if (len > 0) len = 1 / len;

	sph[0].v.x *= len;
	sph[0].v.y *= len;
	sph[0].v.z *= len;

	merikomi /= 2.0f;

	//�߂荞�ݏC��
	sph[0].pos.x -= sph[0].v.x * merikomi; 
	sph[0].pos.y -= sph[0].v.y * merikomi;
	sph[0].pos.z -= sph[0].v.z * merikomi;

	//obj.pos.x += sph[0].v.x * merikomi;
	//obj.pos.y += sph[0].v.y * merikomi;
	//obj.pos.z += sph[0].v.z * merikomi;
}

void Sph_ehit(float dis , int i) {
	float len = sqrtf(dis);
	float radius_sum = sph[0].radius + obj.radius;
	float merikomi = radius_sum - len;

	if (len > 0) len = 1 / len;

	sph[0].v.x *= len;
	sph[0].v.y *= len;
	sph[0].v.z *= len;

	merikomi /= 2.0f;

	//�߂荞�ݏC��
	sph[0].pos.x -= sph[0].v.x * merikomi;
	sph[0].pos.y -= sph[0].v.y * merikomi;
	sph[0].pos.z -= sph[0].v.z * merikomi;
//	float len = sqrtf(dis);
//	float radius_sum = sph[0].radius + damege_aria[i].radius;
//	float merikomi = radius_sum - len;
//
//	if (len > 0) len = 1 / len;
//
//	sph[0].v.x *= len;
//	sph[0].v.y *= len;
//	sph[0].v.z *= len;
//
//	merikomi /= 2.0f;
//
//	//sph[0].pos.x -= sph[i].v.x * merikomi;
//	//sph[0].pos.y -= sph[i].v.y * merikomi/* - 800*/;
//	//sph[0].pos.z -= sph[i].v.z * merikomi/* + 1600*/;
//
//	//sph[0].v.x += damege_aria[i].v.x * merikomi;
//	//sph[0].v.y += damege_aria[i].v.y * merikomi;
//	//sph[0].v.z += damege_aria[i].v.z * merikomi;
//
//	/*_damege_aria.pos.x += sph[0].v.x * merikomi;
//	_damege_aria.pos.y += sph[0].v.y * merikomi;
//	_damege_aria.pos.z += sph[0].v.z * merikomi;*/
}

void Ground_model_hit() {
	st_model_hit.movepos = VGet(0.0f, 0.0f,0.0f);//�ړ��x�N�g��
	st_model_hit.moveflag = 0;// �ړ��������ǂ����̃t���O��������Ԃł́u�ړ����Ă��Ȃ��v��\���O�ɂ���

	P_input_move();//�v���C���[����
	P_move();
	//�n�ʂɂ��Ă��Ȃ�������d�͔���
	//if (!st_model_hit.groundflg) {
	//	Sph_Gravity();//�d��
	//}
	Sph_Gravity();//�d��
	// �ړ��{�^���������ꂽ���ǂ����ŏ����𕪊�
	if (st_model_hit.moveflag == 1)
	{
		// �ړ��x�N�g���𐳋K���������̂��v���C���[�������ׂ������Ƃ��ĕۑ�
		st_model_hit.targetmovedirection = VNorm(st_model_hit.movepos);
		/*DrawFormatString(100, 200, GetColor(255, 255, 255), " %.1f , %.1f , %.1f ", st_model_hit.TargetMoveDirection.x, st_model_hit.TargetMoveDirection.y, st_model_hit.TargetMoveDirection.z);*/
		// �v���C���[�������ׂ������x�N�g�����v���C���[�̃X�s�[�h�{�������̂��ړ��x�N�g���Ƃ���
		st_model_hit.movepos = VScale(st_model_hit.targetmovedirection, sph[0].speed);
	}
	if (p_zmoveflg == true) {

		st_model_hit.movepos.z = st_model_hit.movepos.z + sph[0].zmove;

		// �J�����̊p�x�ɍ��킹�Ĉړ��x�N�g������]���Ă�����Z
		g_sinParam = (float)sin(g_p_direct / 180.0f * DX_PI_F);
		g_cosParam = (float)cos(g_p_direct / 180.0f * DX_PI_F);
		//��̌����Ă�������̌v�Z(�ڂ̑O���₩�ǂ����𔻒f����̂Ɏg��)
		TempMoveVector.x = st_model_hit.movepos.x * g_cosParam - sph[0].front * g_sinParam;
		TempMoveVector.y = 0.0f;
		TempMoveVector.z = st_model_hit.movepos.x * g_sinParam + sph[0].front * g_cosParam;

		g_frontVector = VAdd(sph[0].pos, TempMoveVector);
		// �e�x�N�g�����ƂɌv�Zy�͕��u

		TempMoveVector.x = st_model_hit.movepos.x * g_cosParam - st_model_hit.movepos.z * g_sinParam;
		TempMoveVector.y = 0.0f;
		TempMoveVector.z = st_model_hit.movepos.x * g_sinParam + st_model_hit.movepos.z * g_cosParam;

		st_model_hit.movepos = TempMoveVector;
	}

	Ground_model_hit_check(st_model_hit.movepos);
}
void Ground_model_hit_check(VECTOR MoveVector) {
	// �ړ��O�̍��W��ۑ�
	st_model_hit.oldpos = sph[0].pos;
	// �ړ���̍��W���Z�o
	st_model_hit.nowpos = VAdd(sph[0].pos, MoveVector);

	VECTOR frontpos = g_frontVector;
	stg.CollObjNum = 2;//�e�X�g������

	 //�v���C���[�̎��͂ɂ���X�e�[�W�|���S�����擾����
	 //( ���o����͈͈͂ړ��������l������ )
	st_model_hit.hitdim[0] = MV1CollCheck_Sphere(ground.handle, -1, sph[0].pos, PLAYER_ENUM_DEFAULT_SIZE + VSize(MoveVector));
	// �v���C���[�̎��͂ɂ���R���W�����I�u�W�F�N�g�̃|���S�����擾����
	for (int i = 0; i < stg.CollObjNum; i++)
	{
		st_model_hit.hitdim[i + 1] = MV1CollCheck_Sphere(stg.CollObjModelHandle[i], -1, sph[0].pos, PLAYER_ENUM_DEFAULT_SIZE + VSize(MoveVector));
	}
	// HitDim �̗L���Ȑ��̓R���W�����I�u�W�F�N�g�̐��ƃX�e�[�W���̂̃R���W����
	st_model_hit.hitdimnum = stg.CollObjNum + 1;
	// x����y�������� 0.01f �ȏ�ړ������ꍇ�́u�ړ������v�t���O���P�ɂ���
	if (fabs(MoveVector.x) > 0.01f || fabs(MoveVector.z) > 0.01f)
	{
		st_model_hit.moveflag = 1;
	}
	else
	{
		st_model_hit.moveflag = 0;
	}

	// ���o���ꂽ�|���S�����ǃ|���S��( �w�y���ʂɐ����ȃ|���S�� )�����|���S��( �w�y���ʂɐ����ł͂Ȃ��|���S�� )���𔻒f����
	{
		// �ǃ|���S���Ə��|���S���̐�������������
		st_model_hit.kabenum = 0;
		st_model_hit.yukanum = 0;


		DrawFormatString(100, 20, GetColor(255, 0, 0), " %f");
		// ���o���ꂽ�|���S���̐������J��Ԃ�
		for (int j = 0; j < st_model_hit.hitdimnum; j++)
		{
			for (int i = 0; i < st_model_hit.hitdim[j].HitNum; i++)
			{
				// �w�y���ʂɐ������ǂ����̓|���S���̖@���̂x�������O�Ɍ���Ȃ��߂����ǂ����Ŕ��f����
				if (st_model_hit.hitdim[j].Dim[i].Normal.y < 0.000001f && st_model_hit.hitdim[j].Dim[i].Normal.y > -0.000001f)
				{
					// �ǃ|���S���Ɣ��f���ꂽ�ꍇ�ł��A�v���C���[�̂x���W�{�P�D�O����荂���|���S���̂ݓ����蔻����s��
					if (st_model_hit.hitdim[j].Dim[i].Position[0].y > sph[0].pos.y + 1.0f ||
						st_model_hit.hitdim[j].Dim[i].Position[1].y > sph[0].pos.y + 1.0f ||
						st_model_hit.hitdim[j].Dim[i].Position[2].y > sph[0].pos.y + 1.0f)
					{
						// �|���S���̐����񋓂ł�����E���ɒB���Ă��Ȃ�������|���S����z��ɒǉ�
						if (st_model_hit.kabenum < PLAYER_MAX_HITCOLL)
						{
							// �|���S���̍\���̂̃A�h���X��ǃ|���S���|�C���^�z��ɕۑ�����
							st_model_hit.kabe[st_model_hit.kabenum] = &st_model_hit.hitdim[j].Dim[i];

							// �ǃ|���S���̐������Z����
							st_model_hit.kabenum++;
						}
					}
				}
				else
				{
					// �|���S���̐����񋓂ł�����E���ɒB���Ă��Ȃ�������|���S����z��ɒǉ�
					if (st_model_hit.yukanum < PLAYER_MAX_HITCOLL)
					{
						// �|���S���̍\���̂̃A�h���X�����|���S���|�C���^�z��ɕۑ�����
						st_model_hit.yuka[st_model_hit.yukanum] = &st_model_hit.hitdim[j].Dim[i];

						// ���|���S���̐������Z����
						st_model_hit.yukanum++;
					}
				}
			}
		}
	}
	//���������
	// �ǃ|���S���Ƃ̓����蔻�菈��
	if (st_model_hit.kabenum != 0)
	{
		// �ǂɓ����������ǂ����̃t���O�͏�����Ԃł́u�������Ă��Ȃ��v�ɂ��Ă���
		st_model_hit.hitflag = 0;

		// �ړ��������ǂ����ŏ����𕪊�
		if (st_model_hit.moveflag == 1)
		{
			// �ǃ|���S���̐������J��Ԃ�
			//for (int i = 0; i < st_model_hit.kabenum; i++)
			//{
			//	// i�Ԗڂ̕ǃ|���S���̃A�h���X��ǃ|���S���|�C���^�z�񂩂�擾
			//	st_model_hit.poly = st_model_hit.kabe[i];

			//	// �|���S���ƃv���C���[���������Ă��Ȃ������玟�̃J�E���g��
			//	if (HitCheck_Capsule_Triangle(st_model_hit.nowpos, VAdd(st_model_hit.nowpos, VGet(0.0f, PLAYER_HIT_HEIGHT, 0.0f)), PLAYER_HIT_WIDTH, st_model_hit.poly->Position[0], st_model_hit.poly->Position[1], st_model_hit.poly->Position[2]) == FALSE) continue;

			//	// �����ɂ�����|���S���ƃv���C���[���������Ă���Ƃ������ƂȂ̂ŁA�|���S���ɓ��������t���O�𗧂Ă�
			//	st_model_hit.hitflag = 1;

			//	//�ǂɓ���������ǂɎՂ��Ȃ��ړ������������ړ�����
			//	{
			//		VECTOR SlideVec;	// �v���C���[���X���C�h������x�N�g��

			//		// �i�s�����x�N�g���ƕǃ|���S���̖@���x�N�g���ɐ����ȃx�N�g�����Z�o
			//		SlideVec = VCross(MoveVector, st_model_hit.poly->Normal);

			//		// �Z�o�����x�N�g���ƕǃ|���S���̖@���x�N�g���ɐ����ȃx�N�g�����Z�o�A���ꂪ
			//		// ���̈ړ���������Ǖ����̈ړ������𔲂����x�N�g��
			//		SlideVec = VCross(st_model_hit.poly->Normal, SlideVec);

			//		// ������ړ��O�̍��W�ɑ��������̂�V���ȍ��W�Ƃ���
			//		st_model_hit.nowpos = VAdd(st_model_hit.oldpos, SlideVec);
			//	}

			//	int j;
			//	// �V���Ȉړ����W�ŕǃ|���S���Ɠ������Ă��Ȃ����ǂ����𔻒肷��
			//	for (j = 0; j < st_model_hit.kabenum; j++)
			//	{
			//		// j�Ԗڂ̕ǃ|���S���̃A�h���X��ǃ|���S���|�C���^�z�񂩂�擾
			//		st_model_hit.poly = st_model_hit.kabe[j];

			//		// �������Ă����烋�[�v���甲����
			//		if (HitCheck_Capsule_Triangle(st_model_hit.nowpos, VAdd(st_model_hit.nowpos, VGet(0.0f, PLAYER_HIT_HEIGHT, 0.0f)), PLAYER_HIT_WIDTH, st_model_hit.poly->Position[0], st_model_hit.poly->Position[1], st_model_hit.poly->Position[2]) == TRUE) break;
			//	}

			//	// j �� KabeNum �������ꍇ�͂ǂ̃|���S���Ƃ�������Ȃ������Ƃ������ƂȂ̂�
			//	// �ǂɓ��������t���O��|������Ń��[�v���甲����
			//	if (j == st_model_hit.kabenum)
			//	{
			//		st_model_hit.hitflag = 0;
			//		break;
			//	}
			//}
		}
		else
		{
			// �ړ����Ă��Ȃ��ꍇ�̏���

			// �ǃ|���S���̐������J��Ԃ�
			for (int i = 0; i < st_model_hit.kabenum; i++)
			{
				// i�Ԗڂ̕ǃ|���S���̃A�h���X��ǃ|���S���|�C���^�z�񂩂�擾
				st_model_hit.poly = st_model_hit.kabe[i];

				// �|���S���ɓ������Ă����瓖�������t���O�𗧂Ă���Ń��[�v���甲����
				if (HitCheck_Capsule_Triangle(st_model_hit.nowpos, VAdd(st_model_hit.nowpos, VGet(0.0f, PLAYER_HIT_HEIGHT, 0.0f)), PLAYER_HIT_WIDTH, st_model_hit.poly->Position[0], st_model_hit.poly->Position[1], st_model_hit.poly->Position[2]) == TRUE)
				{
					st_model_hit.hitflag = 1;
					break;
				}
			}
		}
	}


	// ���|���S���Ƃ̓����蔻��
	if (st_model_hit.yukanum != 0)
	{


		float maxy;

		// ���~�����W�����v���ł͂Ȃ��ꍇ�̏���

		// ���|���S���ɓ����������ǂ����̃t���O��|���Ă���
		st_model_hit.hitflag = 0;

		// ��ԍ������|���S���ɂԂ���ׂ̔���p�ϐ���������
		maxy = 0.0f;

		// ���|���S���̐������J��Ԃ�
		for (int i = 0; i < st_model_hit.yukanum; i++)
		{
			// i�Ԗڂ̏��|���S���̃A�h���X�����|���S���|�C���^�z�񂩂�擾
			st_model_hit.poly = st_model_hit.yuka[i];


			// �����Ă���ꍇ�͓��̐悩�炻�������Ⴂ�ʒu�̊Ԃœ������Ă��邩�𔻒�( �X�΂ŗ�����ԂɈڍs���Ă��܂�Ȃ��� )
			/*st_model_hit.LineRes = HitCheck_Line_Triangle(VAdd(st_model_hit.NowPos, VGet(0.0f, 0.0f, 0.0f)), VAdd(st_model_hit.NowPos, VGet(0.0f, PLAYER_HIT_HEIGHT, 0.0f)), st_model_hit.Poly->Position[0], st_model_hit.Poly->Position[1], st_model_hit.Poly->Position[2]);*/
			st_model_hit.lineres = HitCheck_Line_Triangle(st_model_hit.nowpos, VAdd(st_model_hit.nowpos, VGet(0.0f, -200.0f, 0.0f)), st_model_hit.poly->Position[0], st_model_hit.poly->Position[1], st_model_hit.poly->Position[2]);

			g_frontpos2 = HitCheck_Line_Triangle(st_model_hit.nowpos,VAdd(g_frontVector,VGet(0.0f,-100.0f,0.0f)), st_model_hit.poly->Position[0], st_model_hit.poly->Position[1], st_model_hit.poly->Position[2]);


			if (st_model_hit.lineres.HitFlag == FALSE) { 
				
				continue; 
			}
			//�����܂ł����
			
			// ���ɓ��������|���S��������A�����܂Ō��o�������|���S�����Ⴂ�ꍇ�͉������Ȃ�
			if (st_model_hit.hitflag == 1 && maxy > st_model_hit.lineres.Position.y) continue;

			// �|���S���ɓ��������t���O�𗧂Ă�
			st_model_hit.hitflag = 1;
			// �ڐG�����x���W��ۑ�����
			maxy = st_model_hit.lineres.Position.y + sph[0].radius;
			/*DrawFormatString(100, 240, GetColor(255, 0, 0), " Line.Y %d", st_model_hit.LineRes.Position.y);*/
			st_model_hit.groundflg = true; //�n�ʂɂ����t���O�𗧂Ă�
		}
		DrawLine3D(st_model_hit.nowpos, VAdd(st_model_hit.nowpos,VGet(0.0f,-200.f,0.0f)), GetColor(255, 0, 0));
		DrawLine3D(st_model_hit.nowpos, VAdd(g_frontVector, VGet(0.0f, -200.0f, 0.0f)), GetColor(255, 0, 0));
		//DrawLine3D(VAdd(st_model_hit.nowpos, VGet(-300.0f, -110.0f, 0.0f)), VAdd(st_model_hit.nowpos, VGet(300.0f, -200.0f, 0.0f)), GetColor(255, 0, 0));
		//DrawLine3D(VAdd(st_model_hit.nowpos, VGet(0.0f, -110.0f, -300.0f)), VAdd(st_model_hit.nowpos, VGet(0.0f, -200.0f, 300.0f)), GetColor(255, 0, 0));
		//// ��̎��͂��ȈՓI�Ɍ����
		//DrawLine3D(VAdd(st_model_hit.nowpos, VGet(-300.0f, 0.0f, 0.0f)), VAdd(st_model_hit.nowpos, VGet(300.0f, 0.0f, 0.0f)), GetColor(255, 0, 0));
		//DrawLine3D(VAdd(st_model_hit.nowpos, VGet(0.0f, 0.0f, -300.0f)), VAdd(st_model_hit.nowpos, VGet(0.0f, 0.0f, 300.0f)), GetColor(255, 0, 0));
		// ���|���S���ɓ����������ǂ����ŏ����𕪊�
		if (st_model_hit.hitflag == 1)
		{
			// ���������ꍇ

			// �ڐG�����|���S���ň�ԍ����x���W���v���C���[�̂x���W�ɂ���
			st_model_hit.nowpos.y = maxy;
		}

	}



	
	sph[0].pos = st_model_hit.nowpos;
	
	MV1SetPosition(rock[rock[0].handle_num].handle, sph[0].pos);//�v���C���[���f���`��

	/*DrawSphere3D(sph[0].pos, sph[0].radius, 32, sph[0].color, GetColor(255, 255, 255), TRUE);*/
	// ���o�����v���C���[�̎��͂̃|���S�������J������
	for (int i = 0; i < st_model_hit.hitdimnum; i++)
	{
		MV1CollResultPolyDimTerminate(st_model_hit.hitdim[i]);
	}
}

////���f���Ƌ��̓����蔻��`�F�b�N
//void Model_hit_check() {
//	//���̃x�N�g���^ Pos�ɑ��
//	sph[0].pos = VGet(sph[0].x, sph[0].y, sph[0].z);
//
//	//���f���Ƌ��̓����蔻����擾
//	for (int i = 0; i < TREE_NUM; i++) {
//		HitPolyDim[i] = MV1CollCheck_Sphere(tree_handle[i], -1, sph[0].pos, sph[0].radius);
//	}
//}

//void Model_hit() {
//	//�����蔻������m������̏���
//	for (int j = 0; j < TREE_NUM; j++) {
//		if (HitPolyDim[j].HitNum >= 1)
//		{
//			SetFontSize(50);
//			DrawFormatString(600, 250, GetColor(255, 0, 0), "[�؂̃��f�� HIT]");
//			SetFontSize(20);
//		}
//		//DrawFormatString(100, 300 + ((j + 1) * 20), GetColor(255, 255, 255), "%d", HitPolyDim[j].HitNum);//�����������f����polygon���\��
//	}
//
//	//���f������̃��������
//	for (int i = 0; i < TREE_NUM; i++) {
//		MV1CollResultPolyDimTerminate(HitPolyDim[i]);
//	}
//}

//�v���C���[�̍��E�ړ��͈͂𐧌�����
void Move_Limits()
{
	////�����̂�X���W�����Ƃɍ��
	//int lhit_magnification = 2;    //X�̈ړ��͈͊O�ɂł��ꍇ�̖߂��͂̔{��
	////�v���C���[�������������̍��W���i�[����
	//static VECTOR player_before_pos = VGet(0.0f, 0.0f, 0.0f);

	//if (sph[0].pos.y < 5470.0f) {
	//	//���E�̂ǂ��炩�͈̔͊O�Ɉړ����悤�Ƃ�����t���O��true�ɂ���
	//	if ((sph[0].pos.x <= st_model_hit.glimits_verification[branch.branch_position] ||
	//		sph[0].pos.x >= st_model_hit.glimits_verification[branch.branch_position+1]) && st_model_hit.gmoveflg != true && branch.move_branch == 0) {
	//		st_model_hit.gmoveflg = true;
	//		player_before_pos = sph[0].pos;
	//	}

	//	if (st_model_hit.gmoveflg == true) {
	//		//�͈͓��ɖ߂�����(��)
	//		if (sph[0].pos.x <= player_before_pos.x + sph[0].zmove * lhit_magnification && st_model_hit.landr_move == 1) {
	//			sph[0].pos.x += 10;
	//		}
	//		//�͈͓��ɖ߂�����(�E)
	//		else if (sph[0].pos.x >= player_before_pos.x - sph[0].zmove * lhit_magnification && st_model_hit.landr_move == 2) {
	//			sph[0].pos.x -= 10;
	//		}
	//		//�t���O�����Ƃɖ߂�
	//		else {
	//			st_model_hit.gmoveflg = false;
	//		}

	//	}
	//}
	////�R�[�i�[�ɋȂ��������ɃJ�E���g��1������
	//if (sph[0].pos.z >= branch.branch_point[branch.branch_position]) branch.move_branch = 1;
}