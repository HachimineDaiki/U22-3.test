#include<DxLib.h>
#include<math.h>
#include"Player.h"
#include"Hit_check.h"
#include"3Dmodel.h"
#include"Init.h"
#include"Camera.h"
//float g = 9.81f; //�n���̏d��

void Sph_Gravity() {
        //�d�͍쐬
       sph[0].v0y += g;
       sph[0].pos.y -= sph[0].v0y;

       if (sph[0].v0y >= 80) {
           g = 0;
       }
}
//����
float P_CollisionVelocity() {
    float e = 0.5f;
    float v_collision;//�Փˌ�̑��x
    v_collision = -e * sph[0].zmove;

    return v_collision;
}
void P_Direction() {
    //VECTOR p_oldpos;//�O��̍��W
    //
    //sph[0].direction = VSub(sph[0].pos, p_oldpos);
    //p_oldpos = sph[0].pos;

    //float len = sqrtf(sph[0].pos.x * sph[0].pos.x + sph[0].pos.y * sph[0].pos.y + sph[0].pos.z * sph[0].pos.z);
    //sph[0].direction.x = sph[0].pos.x / len;
    //sph[0].direction.y = sph[0].pos.y / len;
    //sph[0].direction.z = sph[0].pos.z / len;

    //���_
    //DrawLine3D(sph[0].pos, VAdd(sph[0].pos, VGet(0, 0, sph[0].radius * 2)), GetColor(255, 255, 255));
    ///*float dis = sqrtf(sph[0].pos.x * sph[0].pos.x + sph[0].pos.y * sph[0].pos.y + sph[0].pos.z * sph[0].pos.z);*/
    //DrawFormatString(300, 80, GetColor(255, 255, 255), " �v���C���[���� x %.1f y %.1f z %.1f", sph[0].direction.x, sph[0].direction.y, sph[0].direction.z);
}
void Accl() {
    //���䏈��
    float p_vz2 = -5 * tan(5);
    //float p_vx = 30 * cos(5);
    //float p_vy = 30 * sin(5);
    //p_vz2 / 30; //�ǂ�ǂ񑬂���ς���


    if (p_zmoveflg) {
        if (g_frontmoveflg == 0) {//�O�ɐi��ł���ƑO�ɉ���
            sph[0].zmove += p_vz2 * sph[0].control;
        }
        if (g_frontmoveflg == 1) {//���ɐi��ł���ƌ��ɉ���
            sph[0].zmove -= p_vz2 * sph[0].control;
        }

        if (g_frontpos2.HitFlag == FALSE) {//�O�ɍ₪�Ȃ��̂őO�ɐi��
            
            if (sph[0].zmove <= 0) {
                sph[0].zmove += p_vz2 * (sph[0].control + 0.01f);
            }
        }
        else if (g_frontpos2.HitFlag == TRUE) {//�O�ɍ₪����̂Ō��ɐi��
            
            if (sph[0].zmove >= 0) {

                sph[0].zmove -= p_vz2 * (sph[0].control + 0.01f);
                
            }
        }
    }

    if (sph[0].zmove >= 0.0f) {//�O�ɐi��ł�����t���O��0�ɂ���
        g_frontmoveflg = 0;
    }
    else if (sph[0].zmove < 0.0f) {//���ɐi��ł�����t���O��1�ɂ���
        g_frontmoveflg = 1;
    }

    if (sph[0].zmove >= 150.0f) {
        sph[0].zmove = 150.0f;
    }
    else if (sph[0].zmove <= -150.0f) {
        sph[0].zmove = -150.0f;
    }

    if (sph[0].zmove >= 50.0f) {
        sph[0].zaccl = 0.0f;
    }

    if (g_CollisionReflectionFlag == 1) {
        if (sph[0].zmove >= 0 && g_frontpos2.HitFlag == FALSE) {
            g_CollisionReflectionFlag == 0;
        }
        if (sph[0].zmove < 0 && g_frontpos2.HitFlag == TRUE) {
            g_CollisionReflectionFlag == 0;
        }
    }



 
}
void P_move() {    
    if (p_zmoveflg == true) {
        switch (Input_PlayerMoveDir())
        {
        case Left:
            st_model_hit.movepos = st_model_hit.leftvec; st_model_hit.moveflag = 1;
            break;
        case Right:
            st_model_hit.movepos = st_model_hit.rightvec; st_model_hit.moveflag = 1;
            break;
        }
    
    }
   Accl();//accelerator����
   P_rotate();//��]����
   P_Direction();
}

//�����܂�
//�v���C���[��HP�Ǘ�����
void P_hp(int obssize) {
    //�v���C���[�̓����������̃X�s�[�h�Ə�Q���̎�ނ�HP�����炷�B
    sph[0].hp -= Hit_player_speed(sph, obssize);
    rock[0].handle_num = P_rest_hp_handle(sph[0].hp);
    //HP��0��艺����Ȃ�
    if (sph[0].hp <= 0) {
        gameMode = 2;
        sph[0].hp = 0;
    }
}

int  P_rest_hp_handle(int hp) {
    //HP�̎c��Q�[�W�����ĐF��Ԃ��B
    int handle_num = 0;//�F�̓Y����

    if (300 >= hp && 151 <= hp) { //300�`151
        handle_num = 0;
    }
    else if (150 >= hp && 76 <= hp) { //151�`76
        handle_num = 1;
    }
    else if (75 >= hp && 0 <= hp) { //75�`0
        handle_num = 2;
    }
    else if (0 > hp) { //0�ȉ�
        handle_num = 2;
    }
    return handle_num;
}


//�v���C���[��]
void P_rotate() {
    const int rotate_amount = 15;//��]��
    g_p_rotate_amount = sph[0].zmove / rotate_amount;//��]�ʐ���
    g_p_Rotate += g_p_rotate_amount;//��]�ʂ���]�ɔ��f������B
   /* DrawFormatString(500, 160, GetColor(0, 255, 255), " �v���C���[�̉�]�� %.0f ",g_p_rotate_amount);*/
    if (g_p_Rotate >= 360) {
        g_p_Rotate = 0;
    }
    //��]���Z�b�g
    MV1SetRotationXYZ(rock[rock[0].handle_num].handle, VGet(g_p_Rotate * DX_PI_F / 180.0f, -g_p_direct * DX_PI_F / 180.0f, 0.0f));
}

//�v���C���[���͎�t
void P_input_move() {
    //�X�y�[�X����������O�i

    if (CheckHitKey(KEY_INPUT_SPACE)) {
        p_zmoveflg = true;
    }
    switch (Input_PlayerMoveDir())
    {
    case Left:st_model_hit.movepos = st_model_hit.leftvec; st_model_hit.moveflag = 1; 
        break;
    case Right:st_model_hit.movepos = st_model_hit.rightvec; st_model_hit.moveflag = 1;
        break;
    }

    //���菈��
    Move_Limits();

}
//�v���C���[�������Ă��������Ԃ��֐�
int Input_PlayerMoveDir() {

    int input_dir = -1;

    if (htdrow.hitflg == false) {
        if (CheckHitKey(KEY_INPUT_R)) {// ��u���������@���T��init���܂Ƃ߂�
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

        }
    }


    if (CheckHitKey(KEY_INPUT_A))
    {
        input_dir = Left;
    }
    if (CheckHitKey(KEY_INPUT_D))
    {
        input_dir = Right;
    }


    if (CheckHitKey(KEY_INPUT_S))
    {
        input_dir = Down;
    }
    if (CheckHitKey(KEY_INPUT_W))
    {
        input_dir = Up;
    }
    return input_dir;
}

//void P_debug() {
//    if (CheckHitKey(KEY_INPUT_A))
//    {
//        sph[0].pos.x -= 10;
//    }
//
//    if (CheckHitKey(KEY_INPUT_D))
//    {
//        sph[0].pos.x += 10;
//    }
//
//    if (CheckHitKey(KEY_INPUT_W))
//    {
//        sph[0].pos.z += 10;
//    }
//
//    if (CheckHitKey(KEY_INPUT_S))
//    {
//        sph[0].pos.z -= 10;
//    }
//}