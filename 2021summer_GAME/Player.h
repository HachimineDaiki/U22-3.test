#pragma once
#define VECTOR_SLIDE 0.86602540378
#define DECELE_ARIA_MAX 100 //減速エリア最大値
#define DAMEGE_ARIA_MAX 10//ダメージエリア最大値
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
	float zaccl; //Z軸加速
	float zmove; //Z軸動く
	float control;
	int hp; //プレイヤーのHP
	int name;//プレイヤーname情報
	int hit_name;//当たったname情報
	float hit_speed;//当たったスピード保存
	float front;//プレイヤーの前方
	bool obj_flag;//敵が存在するかフラグ。
	VECTOR direction; //向いている方向
};

struct Damege {
	const int _0 = 0;
	const int _15 = 15;
	const int _25 = 25;
	const int _30 = 30;
	const int _50 = 50;
	const int _100 = 100;
};

int Input_PlayerMoveDir();//プレイヤー入力方向
void P_input_move();//プレイヤーの入力受付
void P_move();//プレイヤー動き
void P_rotate();
int  P_rest_hp_handle(int hp);//残りhp見る。
void P_hp(int obssize); //プレイヤーhp管理
void Sph_Gravity();//プレイヤー重力
void Accl();//加速処理
void P_Direction();//プレイヤー方向
float P_CollisionVelocity();//反射処理
struct Input {
	bool space;
};

enum Dir { Left, Right, Down, Up };
enum Size { S = 1, M, L };//内部数値1から開始
enum Color { RED, GREEN, BULE };

extern float g;//重力 9.81

//オブジェクト生成
extern Sph sph[2];//プレイヤー
extern Sph obj;//不法投棄物
extern Sph damege_aria[DAMEGE_ARIA_MAX]; //当たるとダメージをうけるオブジェクト
extern Sph decele_aria[DECELE_ARIA_MAX]; //減速エリア

extern float s_dis;
extern float es_dis;//障害物用
extern float g_p_direct;//プレイヤー方向
extern float g_p_Rotate;//プレイヤーの回転
extern float g_p_rotate_amount;//プレイヤーの回転量
extern bool p_zmoveflg;//前進に移動するフラグ
extern VECTOR TempMoveVector;
extern Input input;
extern Damege obs_damege;//障害物のダメージ量
extern int g_frontmoveflg;//0　前に坂ナシ　1　前に坂アリ
extern int g_CollisionReflectionFlag;//0 衝突して反射していない 1 衝突して反射している