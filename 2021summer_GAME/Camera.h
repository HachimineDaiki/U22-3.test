#pragma once


void Camera_set();

void Camera_move();

void Input_camera_move();


extern float  g_sinParam;
extern float  g_cosParam;
extern float  g_cameraHAngle;//横アングル
extern float  g_cameraVAngle;//縦アングル
extern VECTOR g_cameraPosition;//カメラの座標