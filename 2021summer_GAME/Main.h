#pragma once
#include <Dxlib.h>
#include "Init.h"
#include "Hit_check.h"
#include "Player.h"
#include "Camera.h"
#include "3Dmodel.h"
#include "Param_Info.h"
#include "Title.h"
#include "Gameover.h"

enum GAMEMODE { TITLE, GAME, GAMEOVER};//ゲームモード
//構造体
Sph sph[2];//プレイヤー
Sph obj;//不法投棄
Sph damege_aria[DAMEGE_ARIA_MAX];//障害物
Sph decele_aria[DECELE_ARIA_MAX];//減速エリア
Model ground;//地面
Model rock[3];//岩
StageModelHit st_model_hit;//モデルヒット
HitDrow htdrow;//ヒット描画
VECTOR TempMoveVector;
VECTOR g_frontVector;//プレイヤーの前方を取る
VECTOR g_cameraPosition;//カメラの座標
VECTOR g_Ill_dump1;//不法投棄物の初期値を入れる
Decel decel;//減速
Title title;//タイトル
Gameover gameover;//ゲームオーバー
Branch branch;
Damege obs_damege;//障害物のダメージ量
Model wall[WALL_MAX];
HITRESULT_LINE g_frontpos2;
Model gensoku[DECELE_ARIA_MAX];
Model e_rock[DAMEGE_ARIA_MAX];

DrawStr speed_draw_str; //文字描画
Title_Slect title_slect[2];
Title_Slect title_slectfream[2];
bool gameexit;
//列挙体

float g=9.81;//重力を代入

void Gamemain();//ゲームメイン関数
float s_dis;
float es_dis;
bool p_zmoveflg;

float g_sinParam;
float g_cosParam;
float g_cameraHAngle;
float g_cameraVAngle;

float g_p_direct; // プレイヤーの向き
float g_p_Rotate; // プレイヤーの回転
float g_p_rotate_amount;//回転量

float merikomi;//めり込む量

int g_frontmoveflg;//0　前に進んでいる　1　後ろに進んでいる
int g_CollisionReflectionFlag;//0 衝突して反射していない 1 衝突して反射している
int g_goalflag;//ゴールしたかどうか　0ゴールしてない　1ゴールした

int gameMode;//ゲームモード
