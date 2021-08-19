#pragma once
#include <DxLib.h>
#include <math.h>
#include "Init.h"
#include"Player.h"

// プレイヤー関係の定義
#define PLAYER_MOVE_SPEED			30.0f		// 移動速度
#define PLAYER_ANGLE_SPEED			0.2f		// 角度変化速度
#define PLAYER_MAX_HITCOLL			2048		// 処理するコリジョンポリゴンの最大数
#define PLAYER_ENUM_DEFAULT_SIZE	200.0f		// 周囲のポリゴン検出に使用する球の初期サイズ
#define PLAYER_HIT_WIDTH			100.0f		// 当たり判定
#define PLAYER_HIT_HEIGHT			100.0f		// 当たり判定
#define PLAYER_HIT_TRYNUM			16		// 壁押し出し処理の最大試行回数
#define PLAYER_HIT_SLIDE_LENGTH		5.0f		// 一度の壁押し出し処理でスライドさせる距離

// ステージ関係の定義
#define STAGECOLLOBJ_MAXNUM			256		// 追加のコリジョンオブジェクトの最大数

//プロトタイプ宣言
bool Sph_hit_check(Sph sp[], Sph ob);
bool Sph_ehit_chech(Sph sp[], Sph e_obj[], int i);
bool Decel_aria_check(Sph sp[], Sph decelaria[], int i);
void Decel_aria_effect();//エリアに入った時の効果
int IsObs_check(Sph obs[], int i);//どの障害物に当たったか
int Hit_player_speed(Sph player[], int obs_info);//当たった時のプレイヤー速度
void Hit_badobject_helth(Sph player[], int obs_info,int i);//当たった時の障害物の判定
void Sph_hit(float dis);
void Sph_ehit(float dis, int i);//障害物当たり判定
//void Model_hit_check();
//void Model_hit();
void Ground_model_hit();
void Ground_model_hit_check(VECTOR MoveVector);
void Move_Limits();		//プレイヤーの左右移動を制限する
void Damege_aria_Decele();//ダメージエリアの減速
struct StageModelHit
{
	int i, j, k;						// 汎用カウンタ変数
	int moveflag;						// 水平方向に移動したかどうかのフラグ( ０:移動していない  １:移動した )
	int hitflag;						// ポリゴンに当たったかどうかを記憶しておくのに使う変数( ０:当たっていない  １:当たった )
	MV1_COLL_RESULT_POLY_DIM hitdim[STAGECOLLOBJ_MAXNUM + 1];			// プレイヤーの周囲にあるポリゴンを検出した結果が代入される当たり判定結果構造体
	int hitdimnum;						// HitDim の有効な配列要素数
	int kabenum;						// 壁ポリゴンと判断されたポリゴンの数
	int yukanum;						// 床ポリゴンと判断されたポリゴンの数
	MV1_COLL_RESULT_POLY* kabe[PLAYER_MAX_HITCOLL];	// 壁ポリゴンと判断されたポリゴンの構造体のアドレスを保存しておくためのポインタ配列
	MV1_COLL_RESULT_POLY* yuka[PLAYER_MAX_HITCOLL];	// 床ポリゴンと判断されたポリゴンの構造体のアドレスを保存しておくためのポインタ配列
	MV1_COLL_RESULT_POLY* poly;				// ポリゴンの構造体にアクセスするために使用するポインタ( 使わなくても済ませられますがプログラムが長くなるので・・・ )
	HITRESULT_LINE lineres;				// 線分とポリゴンとの当たり判定の結果を代入する構造体
	VECTOR oldpos;						// 移動前の座標	
	VECTOR nowpos;						// 移動後の座標
	//移動ベクトル
	VECTOR targetmovedirection;			// モデルが向くべき方向のベクトル
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

//分岐構造体
struct Branch
{
	//int glimits_verification[2] = { -1500,1800 }; //端の数値　0: 左の端 900 : 右の端
	//int landr_move = 0;			//0:なし　1:左 2:右		左右のボタンどちらを押しているか
	//bool gmoveflg = false;    //false:制限範囲内　true:制限範囲外
	//int move_branch = 0;		//0:直線　1:左 2:右 それ以外:なし	道の分岐
	//int branch_point[1] = { 20000 };	//分岐地点の座標
	//int branch_position = 0;		//プレイヤーがどのコーナーにいるかのカウント
};

extern Decel decel;
extern HitDrow htdrow;
extern StageModelHit st_model_hit;
extern Branch branch;
extern VECTOR g_frontVector;
extern HITRESULT_LINE g_frontpos2;//岩の手前に坂があるかどうかを調べるためのもの