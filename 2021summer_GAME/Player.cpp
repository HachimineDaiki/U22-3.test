#include<DxLib.h>
#include<math.h>
#include"Player.h"
#include"Hit_check.h"
#include"3Dmodel.h"
#include"Init.h"
#include"Camera.h"
//float g = 9.81f; //地球の重力

void Sph_Gravity() {
        //重力作成
       sph[0].v0y += g;
       sph[0].pos.y -= sph[0].v0y;

       if (sph[0].v0y >= 80) {
           g = 0;
       }
}
//反射
float P_CollisionVelocity() {
    float e = 0.5f;
    float v_collision;//衝突後の速度
    v_collision = -e * sph[0].zmove;

    return v_collision;
}
void P_Direction() {
    //VECTOR p_oldpos;//前回の座標
    //
    //sph[0].direction = VSub(sph[0].pos, p_oldpos);
    //p_oldpos = sph[0].pos;

    //float len = sqrtf(sph[0].pos.x * sph[0].pos.x + sph[0].pos.y * sph[0].pos.y + sph[0].pos.z * sph[0].pos.z);
    //sph[0].direction.x = sph[0].pos.x / len;
    //sph[0].direction.y = sph[0].pos.y / len;
    //sph[0].direction.z = sph[0].pos.z / len;

    //視点
    //DrawLine3D(sph[0].pos, VAdd(sph[0].pos, VGet(0, 0, sph[0].radius * 2)), GetColor(255, 255, 255));
    ///*float dis = sqrtf(sph[0].pos.x * sph[0].pos.x + sph[0].pos.y * sph[0].pos.y + sph[0].pos.z * sph[0].pos.z);*/
    //DrawFormatString(300, 80, GetColor(255, 255, 255), " プレイヤー方向 x %.1f y %.1f z %.1f", sph[0].direction.x, sph[0].direction.y, sph[0].direction.z);
}
void Accl() {
    //鉢嶺処理
    float p_vz2 = -5 * tan(5);
    //float p_vx = 30 * cos(5);
    //float p_vy = 30 * sin(5);
    //p_vz2 / 30; //どんどん速さを変える


    if (p_zmoveflg) {
        if (g_frontmoveflg == 0) {//前に進んでいると前に加速
            sph[0].zmove += p_vz2 * sph[0].control;
        }
        if (g_frontmoveflg == 1) {//後ろに進んでいると後ろに加速
            sph[0].zmove -= p_vz2 * sph[0].control;
        }

        if (g_frontpos2.HitFlag == FALSE) {//前に坂がないので前に進む
            
            if (sph[0].zmove <= 0) {
                sph[0].zmove += p_vz2 * (sph[0].control + 0.01f);
            }
        }
        else if (g_frontpos2.HitFlag == TRUE) {//前に坂があるので後ろに進む
            
            if (sph[0].zmove >= 0) {

                sph[0].zmove -= p_vz2 * (sph[0].control + 0.01f);
                
            }
        }
    }

    if (sph[0].zmove >= 0.0f) {//前に進んでいたらフラグを0にする
        g_frontmoveflg = 0;
    }
    else if (sph[0].zmove < 0.0f) {//後ろに進んでいたらフラグを1にする
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
   Accl();//accelerator処理
   P_rotate();//回転処理
   P_Direction();
}

//ここまで
//プレイヤーのHP管理処理
void P_hp(int obssize) {
    //プレイヤーの当たった時のスピードと障害物の種類でHPを減らす。
    sph[0].hp -= Hit_player_speed(sph, obssize);
    rock[0].handle_num = P_rest_hp_handle(sph[0].hp);
    //HPが0より下がらない
    if (sph[0].hp <= 0) {
       // gameMode = 2;
        sph[0].hp = 0;
    }
}

int  P_rest_hp_handle(int hp) {
    //HPの残りゲージを見て色を返す。
    int handle_num = 0;//色の添え字

    if (300 >= hp && 151 <= hp) { //300～151
        handle_num = 0;
    }
    else if (150 >= hp && 76 <= hp) { //151～76
        handle_num = 1;
    }
    else if (75 >= hp && 0 <= hp) { //75～0
        handle_num = 2;
    }
    else if (0 > hp) { //0以下
        handle_num = 2;
    }
    return handle_num;
}


//プレイヤー回転
void P_rotate() {
    const int rotate_amount = 15;//回転量
    g_p_rotate_amount = sph[0].zmove / rotate_amount;//回転量生成
    g_p_Rotate += g_p_rotate_amount;//回転量を回転に反映させる。
   /* DrawFormatString(500, 160, GetColor(0, 255, 255), " プレイヤーの回転量 %.0f ",g_p_rotate_amount);*/
    if (g_p_Rotate >= 360) {
        g_p_Rotate = 0;
    }
    //回転をセット
    MV1SetRotationXYZ(rock[rock[0].handle_num].handle, VGet(g_p_Rotate * DX_PI_F / 180.0f, -g_p_direct * DX_PI_F / 180.0f, 0.0f));
}

//プレイヤー入力受付
void P_input_move() {
    //スペースを押したら前進

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

    //判定処理
    Move_Limits();

}
//プレイヤーが押している方向を返す関数
int Input_PlayerMoveDir() {

    int input_dir = -1;

    if (htdrow.hitflg == false) {
        if (CheckHitKey(KEY_INPUT_R)) {// 具志堅が処理　来週にinitをまとめる
            g = 9.81f;
            rock[0].handle_num = P_rest_hp_handle(sph[0].hp);
            Sph_init();//球の初期化
            Obj_init();//不法投棄物の初期化
            Damege_Init();//障害物の初期化
            Decelearia_init();//減速エリア初期化
            Model_init();//モデル初期化
            Camera_set();//カメラセット
            Model3d_load();//3Dモデル読み込み
            Model3d_init();//3Dモデル初期化

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