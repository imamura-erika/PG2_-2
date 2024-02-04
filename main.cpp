#include <Novice.h>
#include "Enemy.h"
#include "Player.h"
#include <Vector2.h>
#include <cmath>

const char kWindowTitle[] = "GC1C_04_イマムラ_エリカ_スライムショット";

enum Scene {
	TITLE, PLAY, CLEAR, GAMEOVER
};

//敵と弾の当たり判定
bool CollisionBulletEnemy(float bulletPosX, float bulletPosY, float bulletRadius, float enemyPosX, float enemyPosY, float enemyRadius) {
	Vector2 distance = {};
	distance.x = bulletPosX - enemyPosX;
	distance.y = bulletPosY - enemyPosY;

	float dis = (distance.x * distance.x) + (distance.y * distance.y);
	float radius = (bulletRadius + enemyRadius) * (bulletRadius + enemyRadius);

	if (dis < radius) {
		return true;
	}
	else {
		return false;
	}
}


//敵とプレイヤーの当たり判定
bool CollisionPlayerEnemy(float playerPosX, float playerPosY, float playerRadius, float enemyPosX, float enemyPosY, float enemyRadius) {
	Vector2 distance = {};
	distance.x = playerPosX - enemyPosX;
	distance.y = playerPosY - enemyPosY;

	float dis = (distance.x * distance.x) + (distance.y * distance.y);
	float radius = float(pow(playerRadius + enemyRadius, 2) / 4);

	if (dis < radius) {
		return true;
	}
	else {
		return false;
	}
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	int title = Novice::LoadTexture("./Resources/title.png");
	int stage = Novice::LoadTexture("./Resources/stage.png");
	int clear = Novice::LoadTexture("./Resources/clear.png");
	int gameover = Novice::LoadTexture("./Resources/gameover.png");

	int clearTimer = 240;  //クリアまでの時間

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };
	//----------
	Scene scene = TITLE;
	Enemy* enemy = new Enemy();
	Player* player = new Player();
	//----------

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		//---------------------------------------------------
		switch (scene) {
		case TITLE:
			if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
				scene = PLAY;
				enemy->Initialize(); //呼び出し enemyの初期化処理
				player->Initialize(); //呼び出し playerの初期化処理
			}

			break;
			//---------------------------------------------------
		case PLAY:
			enemy->Update(); //呼び出し enemyの更新処理

			//敵とプレイヤーの当たり判定
			if (CollisionPlayerEnemy(static_cast<float>(enemy->GetPosX()), static_cast<float>(enemy->GetPosY()), static_cast<float>(enemy->GetRad()),
				static_cast<float>(player->GetPosX()), static_cast<float>(player->GetPosY()), static_cast<float>(player->GetRad())))
			{
				scene = GAMEOVER;
			}

			//敵と弾の当たり判定
			if (player->GetBullet()->isShot == 1) {
				if (CollisionBulletEnemy(
					static_cast<float>(player->GetBullet()->x), static_cast<float>(player->GetBullet()->y), static_cast<float>(player->GetBullet()->r),
					static_cast<float>(enemy->GetPosX()), static_cast<float>(enemy->GetPosY()), static_cast<float>(enemy->GetRad())))
				{
					player->GetBullet()->isShot = 0;
					if (enemy->IsAlive()) {
						enemy->SetIsAlive(false);  // isAlive を false に設定
						enemy->DecreaseRespawnTimer();
					}
				}
			}

			if (enemy->GetRespawnTimer() <= 0) {
				enemy->Respawn(); //リスポーン
				//clearTimer--;
			}

			player->Update(keys/*, preKeys*/); //呼び出し playerの更新処理

			//リスポーン後一定時間経過したらクリア画面に移動
			if (!enemy->IsAlive()) {
				clearTimer--;
				if (clearTimer <= 0) {
					scene = CLEAR;
				}
			}
	
			break;
			//---------------------------------------------------
		case CLEAR:
			if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
				scene = TITLE;
			}

			break;
			//---------------------------------------------------
		case GAMEOVER:
			if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
				scene = TITLE;
			}

			break;
		}
		//---------------------------------------------------

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		//---------------------------------------------------
		switch (scene) {
		case TITLE:
			Novice::DrawSprite(0, 0, title, 1, 1, 0.0f, WHITE);

			break;
			//---------------------------------------------------
		case PLAY:
			Novice::DrawSprite(0, 0, stage, 1, 1, 0.0f, WHITE);

			enemy->Draw(); //呼び出し enemyの描画処理
			player->Draw(); //呼び出し playerの描画処理

			//Novice::ScreenPrintf(10,10,"%d", clearTimer);

			break;
			//---------------------------------------------------
		case CLEAR:
			Novice::DrawSprite(0, 0, clear, 1, 1, 0.0f, WHITE);

			break;
			//---------------------------------------------------
		case GAMEOVER:
			Novice::DrawSprite(0, 0, gameover, 1, 1, 0.0f, WHITE);


			break;
		}
		//---------------------------------------------------


		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
//	delete player; //ゲームを閉じるタイミングでdelete忘れずに
	return 0;
}