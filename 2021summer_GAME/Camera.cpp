#include <DxLib.h>
#include <math.h>
#include "Init.h"
#include "Camera.h"
#include "Player.h"
#include "Hit_check.h"



// 移動速度
#define MOVESPEED				     10.0f

// カメラの回転速度
#define CAMERA_ANGLE_SPEED	          3.0f

// カメラの注視点の高さ
#define CAMERA_LOOK_AT_HEIGHT         250.0f

// カメラと注視点の距離
#define CAMERA_LOOK_AT_DISTANCE    1100.0f



void Camera_set() {


	// カメラの向きを初期化
	g_cameraHAngle = 0.0f;
	g_cameraVAngle = 25.0f;
    g_p_direct = 0.0f;
   // g_cameraPosition;


}

void Camera_move() {
    SetCameraNearFar(100.0f, 300000.0f);
    VECTOR tempPosition1;
    VECTOR tempPosition2;
    VECTOR cameraLookAtPosition;
    float sinParam;
    float cosParam;

    // 注視点はキャラクターモデルの座標から CAMERA_LOOK_AT_HEIGHT 分だけ高い位置
    cameraLookAtPosition = VGet(sph[0].pos.x,sph[0].pos.y,sph[0].pos.z);
    cameraLookAtPosition.y += CAMERA_LOOK_AT_HEIGHT;

    // カメラの位置はカメラの水平角度と垂直角度から算出

    // 最初に垂直角度を反映した位置を算出
    sinParam = (float)sin(g_cameraVAngle / 180.0f * DX_PI_F);
    cosParam = (float)cos(g_cameraVAngle / 180.0f * DX_PI_F);
    tempPosition1.x = 0.0f;
    tempPosition1.y = sinParam * CAMERA_LOOK_AT_DISTANCE;
    tempPosition1.z = -cosParam * CAMERA_LOOK_AT_DISTANCE;

    // 次に水平角度を反映した位置を算出
    sinParam = (float)sin(g_cameraHAngle / 180.0f * DX_PI_F);
    cosParam = (float)cos(g_cameraHAngle / 180.0f * DX_PI_F);
    tempPosition2.x = cosParam * tempPosition1.x - sinParam * tempPosition1.z;
    tempPosition2.y = tempPosition1.y;
    tempPosition2.z = sinParam * tempPosition1.x + cosParam * tempPosition1.z;

    // 算出した座標に注視点の位置を加算したものがカメラの位置
    g_cameraPosition = VAdd(tempPosition2, cameraLookAtPosition);

    // 角度表示
    DrawFormatString(300, 0, GetColor(255, 255, 255), "カメラ座標 X%.0f Y%.0f Z%.0f", g_cameraPosition.x, g_cameraPosition.y, g_cameraPosition.z);
   // DrawFormatString(100, 40, GetColor(255, 255, 255), "カメラ横角度 %.0f", g_cameraHAngle);
    //DrawFormatString(0,0,GetColor(255,255,255), "カメラざ");
    // カメラの設定に反映する
    SetCameraPositionAndTarget_UpVecY(g_cameraPosition, cameraLookAtPosition);

}

void Input_camera_move() {
    // 方向キーでカメラを回転
    if (CheckHitKey(KEY_INPUT_UP) == 1)
    {
        g_cameraVAngle -= CAMERA_ANGLE_SPEED / 4;
        if (g_cameraVAngle <= 0.0f)
        {
            g_cameraVAngle = 0.0f;
        }
    }
    if (CheckHitKey(KEY_INPUT_DOWN) == 1)
    {
        g_cameraVAngle += CAMERA_ANGLE_SPEED / 4;
        if (g_cameraVAngle >= 45.0f)
        {
            g_cameraVAngle = 45.0f;
        }
    }
    if (CheckHitKey(KEY_INPUT_LEFT) == 1)
    {
        g_cameraHAngle += CAMERA_ANGLE_SPEED / 4;
        if (g_cameraHAngle >= 180.0f)
        {
            g_cameraHAngle -= 360.0f;
        }
    }
    if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
    {
        g_cameraHAngle -= CAMERA_ANGLE_SPEED / 4;
        if (g_cameraHAngle <= -180.0f)
        {
            g_cameraHAngle += 360.0f;
        }
    }
    if (p_zmoveflg == true) {
        // if (sph[0].pos.z >= branch.branch_point[branch.branch_position]) {
        if (CheckHitKey(KEY_INPUT_A) == 1)
        {
            g_p_direct += CAMERA_ANGLE_SPEED / 2;
            if (g_p_direct >= 180.0f)
            {
                g_p_direct -= 360.0f;

                g_cameraHAngle -= 360.0f;
            }

        }
        if (CheckHitKey(KEY_INPUT_D) == 1)
        {
            g_p_direct -= CAMERA_ANGLE_SPEED / 2;
            if (g_p_direct <= -180.0f) {
                g_p_direct += 360.0f;

                g_cameraHAngle += 360.0f;
            }

        }

        if ((sph[0].zmove >= 0)||(g_CollisionReflectionFlag == 1 && sph[0].zmove < 0)) {// 岩が前に進んでいるときの岩の処理
            if (g_p_direct >= g_cameraHAngle - 10 || g_p_direct <= g_cameraHAngle + 10) {//岩の前方の範囲
                if (g_p_direct >= g_cameraHAngle) {
                    g_cameraHAngle += CAMERA_ANGLE_SPEED / 4;
                    if (g_cameraHAngle >= g_p_direct) {
                        g_cameraHAngle = g_p_direct;
                    }
                    if (g_cameraHAngle <= g_p_direct - 10) {
                        g_cameraHAngle = g_p_direct - 10;
                    }
                }
                if (g_p_direct <= g_cameraHAngle) {
                    g_cameraHAngle -= CAMERA_ANGLE_SPEED / 4;
                    if (g_cameraHAngle <= g_p_direct) {
                        g_cameraHAngle = g_p_direct;
                    }
                    if (g_cameraHAngle >= g_p_direct + 10) {
                        g_cameraHAngle = g_p_direct + 10;
                    }
                }
            }
        }
        else if ((sph[0].zmove < 0) || (g_CollisionReflectionFlag == 1 && sph[0].zmove >= 0)) {//後ろに進んでいるときのカメラの動き
            if (g_p_direct >= 0) {//岩の向きが整数なら
                if ((g_p_direct - 180) >= g_cameraHAngle - 10 || (g_p_direct - 180) <= g_cameraHAngle + 10) {
                    if ((g_p_direct - 180) >= g_cameraHAngle) {
                        g_cameraHAngle += CAMERA_ANGLE_SPEED / 4;
                        if (g_cameraHAngle >= g_p_direct - 180) {
                            g_cameraHAngle = g_p_direct - 180;
                        }
                        if (g_cameraHAngle <= (g_p_direct - 180) - 10) {
                            g_cameraHAngle = (g_p_direct - 180) - 10;
                        }
                    }
                    if ((g_p_direct - 180) <= g_cameraHAngle) {
                        g_cameraHAngle -= CAMERA_ANGLE_SPEED / 4;
                        if (g_cameraHAngle <= g_p_direct - 180) {
                            g_cameraHAngle = g_p_direct - 180;
                        }
                        if (g_cameraHAngle >= (g_p_direct - 180) + 10) {
                            g_cameraHAngle = (g_p_direct - 180) + 10;
                        }
                    }
                }
            }
            else if (g_p_direct < 0) {// 輪の向きが負の数なら
                if ((g_p_direct + 180) >= g_cameraHAngle - 10 || (g_p_direct + 180) <= g_cameraHAngle + 10) {
                    if ((g_p_direct + 180) >= g_cameraHAngle) {
                        g_cameraHAngle += CAMERA_ANGLE_SPEED / 4;
                        if (g_cameraHAngle >= g_p_direct + 180) {
                            g_cameraHAngle = g_p_direct + 180;
                        }
                        if (g_cameraHAngle <= (g_p_direct + 180) - 10) {
                            g_cameraHAngle = (g_p_direct + 180) - 10;
                        }
                    }
                    if ((g_p_direct + 180) <= g_cameraHAngle) {
                        g_cameraHAngle -= CAMERA_ANGLE_SPEED / 4;
                        if (g_cameraHAngle <= g_p_direct + 180) {
                            g_cameraHAngle = g_p_direct + 180;
                        }
                        if (g_cameraHAngle >= (g_p_direct + 180) + 10) {
                            g_cameraHAngle = (g_p_direct + 180) + 10;
                        }
                    }
                }

            }
        }
    }
}

