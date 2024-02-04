#include <Novice.h>
#include <Bullet.h>

Bullet::Bullet() //メンバ変数の初期化
{
	x = -100;
	y = -100;
	isShot = 0;
	r = 8;
	speed = 4;
}

void Bullet::Update() //更新処理
{
	if (isShot == 1) { //発射状態のとき上方向に移動
		y -= speed;
		if (y <= -8) { //画面外に出たとき発射フラグを0にする
			isShot = 0;
		}
	}
}

void Bullet::Draw() //描画処理
{
	//弾の描画
	if (isShot == 1) { //発射状態のみ描画する
		Novice::DrawEllipse(x - r, y - r, r, r, 0.0f, RED, kFillModeSolid);
	}
}