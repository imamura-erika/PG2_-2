#include "Player.h"
#include <Novice.h>

void Player::Initialize()
{
	x = 500;
	y = 500;
	r = 16;
	speed = 4;
	isAlive = 1;
	bullet_ = new Bullet(); //弾クラスの実体を生成
}

//Player::~Player()
//{
//	delete bullet_; //ポインタ削除
//}

void Player::Update(char* keys/*, char* preKeys*/)
{
	//移動処理
	if (keys[DIK_W]) {
		y -= speed;
	}
	if (keys[DIK_S]) {
		y += speed;
	}
	if (keys[DIK_A]) {
		x -= speed;
	}
	if (keys[DIK_D]) {
		x += speed;
	}

	//発射処理
	if (keys[DIK_SPACE] && bullet_->isShot == 0) {
		bullet_->x = x; //弾の座標を自機に座標に合わせる
		bullet_->y = y;
		bullet_->isShot = 1; //弾の発射フラグを1にする
	}

	//弾の更新処理
	bullet_->Update(); //bulletからUpdate関数を呼び出す
}

void Player::Draw() //描画処理
{
	if (isAlive == 1) { //生きてる場合描画
		Novice::DrawEllipse(x, y, r, r, 0.0f, BLUE, kFillModeSolid);
	}

	//弾の描画
	bullet_->Draw(); //bulletからDraw関数を呼び出す
}
