#include <Dxlib.h>
#include "Main.h"
#include "Init.h"
#include "Hit_check.h"
#include "Player.h"
#include "Camera.h"
#include "3Dmodel.h"
#include "Param_Info.h"
#include "Title.h"
#include "Gameover.h"
#include "User_Interface.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    //�^�C�g��
    SetMainWindowText("���̕s�@�������ɏl�����I");
    // ��ʃ��[�h�̐ݒ�
    SetGraphMode(1024,768, 32);
    ChangeWindowMode(TRUE);

    //SetGraphMode(800, 600, 32);

    SetBackgroundColor(70, 130, 180);

    if (DxLib_Init() < 0)
    {
        // �G���[�����������璼���ɏI��
        return -1;
    }
    SetDrawScreen(DX_SCREEN_BACK);
    //--------------�������֐�
    Titleinit();
    Gameoverinit();
    gameMode = TITLE;
    Sph_init();//���̏�����
    Obj_init();//�s�@�������̏�����
    Damege_Init();//��Q���̏�����
    Decelearia_init();//�����G���A������
    Model_init();//���f��������
    Camera_set();//�J�����Z�b�g
    Model3d_load();//3D���f���ǂݍ���
    Model3d_init();//3D���f��������
    UIinit();//UI�̏�����
    Init_Draw_Display();//��ʕ`�揉����
    // �y�o�b�t�@��L���ɂ���
    SetUseZBuffer3D(TRUE);
    // �y�o�b�t�@�ւ̏������݂�L���ɂ���
    SetWriteZBuffer3D(TRUE);

    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
    {
        // ��ʂ��N���A
        ClearDrawScreen();

        //�Q�[���J��
        switch (gameMode)
        {
        case TITLE: Titledraw();
            break;
        case GAME: Gamemain();
            break;
        case GAMEOVER:Gameoverdraw();
            break;
        }

        //�Q�[���I��
        if (gameexit) {
            return -1;
        }
        ScreenFlip();//����ʂ̓��e��\��ʂɔ��f����
    }

    Model3d_dlet();//3d���f���폜
    DxLib_End();
    // �\�t�g�̏I��
    return 0;
}

void Gamemain() {
    //------------------------------���͊֐�
    Input_camera_move();//�J��������
    //------------------------------�v�Z�֐�
    Camera_move();//�J����������
    Ground_model_hit();

   //�s�@�������ƃv���C���[�̓����蔻��
    if (Sph_hit_check(sph, obj)) {
        Sph_hit(s_dis);
        htdrow.hitflg = true;
    }

    //�s�@���������΂�����
    if (htdrow.hitflg) {
     //   obj.pos.x += 1;
        //obj.pos.y += 30 * cos(10) * 10;
        //obj.pos.z += 200 * tan(10) * 10;


        obj.pos.z += obj.zmove;
        //obj.pos.x += 90 * tan(5);
        DrawFormatString(341, 0, GetColor(0, 255, 255), "[x %.0f][y %.0f][z %.0f]", obj.pos.x, obj.pos.y, obj.pos.z);

    }

    //��Q���G���A�̓����蔻��
    for (int i = 0; i < DAMEGE_ARIA_MAX; i++) {
        if (Sph_ehit_chech(sph, damege_aria,i)) {
            g_CollisionReflectionFlag = 1;//�Փ˃t���O���P�ɂ���
            Damege_aria_Decele();
            Sph_ehit(es_dis,i);
            sph[0].zmove = P_CollisionVelocity();//�Փˌ�̑��x
        }
    }

    //�s�@������΂�
    if (htdrow.hitflg) {
        if (obj.zmove > 0) {
            obj.zmove = obj.zmove * 0.89;
        }
        else if (obj.zmove <= 0) {
            obj.zmove = 0;
        }
    }

    //�����G���A�ɓ����Ă��邩�`�F�b�N
    decel.hit_flg = false;//�����t���O
    for (int i = 0; i < DECELE_ARIA_MAX; i++) {
        if (Decel_aria_check(sph, decele_aria, i)) {
            decel.hit_flg = true;//���������猸���̃t���O��ON
        }
    }
    
    //�S�[���܂Ō�������ړ����~�߂�
    if (htdrow.hitflg) {
        if (g_goalflag == 0) {
            obj.zmove = sph[0].zmove * (sph[0].hp / 3);
            Judgement();
            g_goalflag = 1;
        }
        p_zmoveflg = false;
        g_p_Rotate = 0;
        sph[0].zmove = 0.0f;
        SetFontSize(50);
        //DrawFormatString(512, 140, GetColor(0, 255, 255), " GOAL ");
        SetFontSize(20);
        Distance_Calculation(); 

        if (CheckHitKey(KEY_INPUT_SPACE)) {// ��u�������� �d�͂������Ȃ��Ȃ�̂ŏC���K�v�@���T��init���܂Ƃ߂�
            g = 9.81;
            p_zmoveflg = true;
            htdrow.hitflg = false;
            rock[0].handle_num = P_rest_hp_handle(sph[0].hp);
            Sph_init();//���̏�����
            Obj_init();//�s�@�������̏�����
            Damege_Init();//��Q���̏�����
            Decelearia_init();//�����G���A������
            Model_init();//���f��������
            Camera_set();//�J�����Z�b�g
            Model3d_load();//3D���f���ǂݍ���
            Model3d_init();//3D���f��������
            UIinit();//UI�̏�����
            gameMode = 0;

        }
    }

    //------------------------------�`��֐�
    Model3d_draw();//3D���f���`��
    //�s�@�������`��
    DrawSphere3D(obj.pos, obj.radius, 32, obj.color, GetColor(255, 255, 255), TRUE);

    //��Q���`��
    for (int i = 0; i < DAMEGE_ARIA_MAX;i++) {
        if (damege_aria[i].obj_flag) {
            MV1DrawModel(e_rock[i].handle);
        }
    }

    //�̗͕`��
    DrawFormatString(0, 300, GetColor(0, 255, 255), "[HP: %d]", sph[0].hp);
    
    DrawDisplay();//��ʏ��

    ////�����G���A�`��
    //for (int i = 0; i < DECELE_ARIA_MAX; i++) {
    //    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 127);		//�u�����h���[�h����(128/255)�ɐݒ�
    //    DrawSphere3D(decele_aria[i].pos, decele_aria[i].radius, 32, decele_aria[i].color, GetColor(255, 255, 255), TRUE);
    //    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		//�u�����h���[�h���I�t
    //}

    //�����G���A�ɓ����Ă���ԂɌ������イ�̕�����`��
    if (decel.hit_flg) {
        Decel_aria_effect();//�����G���A�ɓ��������̏���
        SetFontSize(50);//�����T�C�Y��ύX
        SetFontSize(20);//�����T�C�Y�����̃T�C�Y�ɕύX
    }
    DrawFormatString(100, 250, GetColor(255, 0, 0), "���� %.1f, %.1f, %.1f ", st_model_hit.targetmovedirection.x, st_model_hit.targetmovedirection.y, st_model_hit.targetmovedirection.z);
    //�p�����[�^�[��\�������鏈��
    DrawParam_Info();
    //�S�[���܂ōs������s�@�������̔�񂾋�����\��
    if (htdrow.hitflg) {
        UIdraw();
    }
}