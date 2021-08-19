#include "Param_Info.h"
//初期化画面
void Init_Draw_Display() {
    speed_draw_str.color = GetColor(255, 255, 255);//文字色
    speed_draw_str.x = 100;
    speed_draw_str.y = 300;
    speed_draw_str.speed = 0.0f;
}

//画面描画表示
void DrawDisplay() {
    
    speed_draw_str.speed = sph[0].zmove;

    if (speed_draw_str.speed <= 0) {
        speed_draw_str.speed = 0;
    }
    
    DrawFormatString(speed_draw_str.x, speed_draw_str.y, speed_draw_str.color, "スピード [ %.0f / 150 ]", speed_draw_str.speed);
}

void DrawParam_Info() {
    SetFontSize(20);
    //// Camera.cppで使用している変数の数値など
    // 関数　Camera_move()　で使用
    //DrawFormatString(100, 20, GetColor(255, 255, 255), "カメラ縦角度 %.0f", g_cameraVAngle);
    //DrawFormatString(100, 40, GetColor(255, 255, 255), "カメラ横角度 %.0f", g_cameraHAngle);

    //DrawFormatString(100, 60, GetColor(255, 255, 255), "岩横角度 %.0f", g_p_direct);

    //// Hit_check.cppで使用している変数の数値など ////
    // 関数　Sph_hit(float dis)　で使用
    //for (int i = 0; i < DAMEGE_ARIA_MAX; i++) {
    //    DrawFormatString(500, 100 + (i + 1) * 20, GetColor(255, 255, 255), "[speed %.0f]", damege_aria[i].hit_speed);
    //}
    // 関数 Ground_model_hit_check(VECTOR MoveVector) で使用
    //DrawFormatString(300, 20, GetColor(255, 255, 255), "前に進んでいるか %d 進んでいると 0 ", g_frontmoveflg);
    //DrawFormatString(300, 40, GetColor(255, 255, 255), "前に坂があるか %d  ", g_frontpos2.HitFlag);
    //DrawFormatString(300, 60, GetColor(255, 255, 255), "ステージの上か %d", st_model_hit.lineres.HitFlag);
    
    /*DrawFormatString(100, 100, GetColor(255, 255, 255), "[sphx %.0f] [sphy %.0f] [sphz %.0f]", sph[0].pos.x, sph[0].pos.y, sph[0].pos.z);*/
    ////Player.cppで使用している変数の数値など
    //DrawFormatString(100, 250, GetColor(255, 255, 255), "%f", sph[0].zaccl);
    /*if(st_model_hit.gmoveflg==true)DrawFormatString(100, 200, GetColor(255, 255, 255), "true");
    if (st_model_hit.gmoveflg == false)DrawFormatString(100, 200, GetColor(255, 255, 255), "false");*/
    /*DrawFormatString(300, 300, GetColor(255, 255, 255), "handle num [ %d ]", rock[0].handle_num);
    DrawFormatString(100, 300, GetColor(255, 255, 255), "スピード [ %.0f /150 ]", sph[0].zmove);
    DrawFormatString(100, 250, GetColor(255, 0, 0), "向き %.1f, %.1f, %.1f ", st_model_hit.targetmovedirection.x, st_model_hit.targetmovedirection.y, st_model_hit.targetmovedirection.z);*/
}