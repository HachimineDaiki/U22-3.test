#include "Init.h"
#include "3Dmodel.h"
#include "Player.h"
void Sph_init() {
	//プレイヤーの初期化
	for (int i = 0; i < 2; i++) {
		sph[i].speed = 10.0f; //プレイヤー速度
		sph[i].radius = 200.0f;//プレイヤー半径
		sph[i].v0y = 0.0f; //プレイヤーY軸初速度
		sph[i].pos = VGet(100.0f, 468.0f, 1300.0f);//プレイヤー初期座標
		sph[i].color = GetColor(255, 255, 255);//プレイヤーカラー
		sph[i].zaccl = 2.0f;//プレイヤーz方向accelerator
		sph[i].zmove = 0.0f;//プレイヤーZ方向移動
		sph[i].control = 0.02f;//プレイヤー速度調整変数
		sph[i].hp = 300;//プレイヤー体力
		sph[0].front = 500;//プレイヤーの前方500
	}
	
	sph[0].v = VGet(0.0f, 0.0f, 0.0f);//プレイヤーベクトル
	g_frontmoveflg = 0;//前に坂があるかどうかの初期化
	g_CollisionReflectionFlag = 0;//0 衝突して反射していない 1 衝突して反射している
	p_zmoveflg = false;

	sph[0].direction = VGet(0, 0, 1);//プレイヤの向いて方向 初期 z方向
}

//不法投棄初期化
void Obj_init(){
	obj.pos = VGet(-3000.0f, -20000.0f, 120000.0f);//不法投棄初期座標
	obj.radius = 400.0f;//不法投棄半径
	obj.color = GetColor(0, 255, 100);//不法投棄カラー
}
//当たったらダメ―ジを受ける障害物初期化
void Damege_Init() {
	for (int i = 0; i < DAMEGE_ARIA_MAX; i++) {
		//if (i >= 0 && i <= 2) {
		//	damege_aria[i].radius = 100.0f;
		//	damege_aria[i].color = GetColor(255, 0, 0);
		//	damege_aria[i].name = S;//障害物の大きさS
		//	damege_aria[i].hp = 10;//test用の体力
		//	damege_aria[i].obj_flag = true;
		//}
		if (i >= 0 && i <= 5) {
			damege_aria[i].radius = 200.0f;
			damege_aria[i].color = GetColor(255, 255, 0);
			damege_aria[i].name = M;//障害物の大きさM
			damege_aria[i].hp = 50;//test用の体力
			damege_aria[i].obj_flag = true;
		}
		else {
			damege_aria[i].radius = 400.0f;
			damege_aria[i].color = GetColor(0, 255, 0);
			damege_aria[i].name = L;//障害物の大きさL
			damege_aria[i].hp = 100;//test用の体力
			damege_aria[i].obj_flag = true;
		}

			//ダメージエリア初期座標
			damege_aria[0].pos = VGet(11853.0f, -4330.0f, 28851.0f);
			damege_aria[1].pos = VGet(11232.0f, -4669.0f, 31544.0f);
			damege_aria[2].pos = VGet(11922.0f, -4477.0f, 29957.0f);
			damege_aria[3].pos = VGet(20700.0f, -6489.0f, 41609.0f);
			damege_aria[4].pos = VGet(24099.0f, -5814.0f, 42633.0f);
			damege_aria[5].pos = VGet(25916.0f, -9196.0f, 57011.0f);
			damege_aria[6].pos = VGet(28500.0f, -10060.0f, 61438.0f);
			damege_aria[7].pos = VGet(27000.0f, -11351.0f, 69486.0f);
			damege_aria[8].pos = VGet(25555.0f, -12654.0f, 76525.0f);
			damege_aria[9].pos = VGet(27000.0f, -12654.0f, 76525.0f);
	}
}

//減速エリア初期化
void Decelearia_init() {
	for (int i = 0; i < DECELE_ARIA_MAX; i++) {
		decele_aria[i].radius = 400.0f;
		decele_aria[i].color = GetColor(255, 0, 0);
		decele_aria[i].v = VGet(0.0f, 0.0f, 0.0f);
	}
	
	//初期座標
	decele_aria[0].pos = VGet(-1000.0f, -200.0f, 5000.0f);
	decele_aria[1].pos = VGet(1000.0f, -200.0f, 5000.0f);
	decele_aria[3].pos = VGet(100.0f, -1070.0f, 10000.0f);
	decele_aria[4].pos = VGet(500.0f, -2000.0f, 15000.0f);
	decele_aria[5].pos = VGet(-500.0f, -2000.0f, 15000.0f);
	decele_aria[6].pos = VGet(-6695.0f, -3820.0f, 25958.0f);
	/*decelearia[7].pos = VGet(-6695.0f, -3820.0f,26400.0f);*/
	decele_aria[8].pos = VGet(-20548.0f, -6289.0f, 40640.0f);
	decele_aria[9].pos = VGet(-26253.0f, -10815.0f, 66417.0f);
	decele_aria[10].pos = VGet(-25289.0f, -12677.0f, 76443.0f);
	decele_aria[11].pos = VGet(-11387.0f, -16461.0f, 98970.0f);
}

//モデルの初期化
void Model_init() {
	//地面初期座標
	ground.x = 0.0f;
	ground.y = 0.0f;
	ground.z = 0.0f;

	//壁の初期座標
	wall[0].x = -2000.0f;
	wall[0].y = -1000.0f;
	wall[0].z = 8000.0f;

	wall[1].x = 2000.0f;
	wall[1].y = -1000.0f;
	wall[1].z = 8000.0f;

	//プレイヤー岩初期座標
	//rock[0].x = 100.0f;
	//rock[0].y = 5471.0f;
	//rock[0].z = 20000.0f;
}