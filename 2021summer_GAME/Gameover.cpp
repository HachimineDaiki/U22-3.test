#include <DxLib.h>
#include"Gameover.h"
#include"Init.h"
#include"Player.h"
#include"3Dmodel.h"
#include"Camera.h"

int Gameoverload() {  //ゲームオーバーの画像をロードする
	if ((gameover.g_gameover = LoadGraph("images/gameover2.png")) == -1)return -1;
}

void Gameoverinit() {  //ゲームオーバーの画像をロードする
	Gameoverload();
}


void Gameoverdraw() {   //ゲームオーバーの画像を描画する
	DrawGraph(0, 0, gameover.g_gameover, FALSE);
	if (CheckHitKey(KEY_INPUT_SPACE)) {
		
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
		gameMode = 0;
	}
}